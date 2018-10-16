/*
	This is a library for the SW03 
	Precision Pressure Sensor

	The board uses I2C for communication.
	
	The board communicates with the following I2C device:
	* 	MPL3115A2
	
	Data Sheets:
	MPL3315A2 - http://www.nxp.com/assets/documents/data/en/data-sheets/MPL3115A2.pdf
*/

// System Includes
#include <arduino-SW03.h>

/********************************************************
 	Constructor
*********************************************************/
xSW03::xSW03(){
	temperature = 0.0;
	altitude = 0.0;
	pressure = 0.0;
}

/********************************************************
 	Configure Sensor
*********************************************************/
bool xSW03::begin(void){
	uint8_t ID = 0;
	
	ID = xCore.read8(MPL3115A2_I2C_ADDRESS, MPL3115A2_WHOAMI);
	
	if( ID == 0xC4 ){ 
		xCore.write8(MPL3115A2_I2C_ADDRESS, MPL3115A2_CTRL_REG, (MPL3115A2_MODE_BARO|MPL3115A2_CTRL_REG1_OS128));
		xCore.write8(MPL3115A2_I2C_ADDRESS, MPL3115A2_PT_DATA_CFG, (MPL3115A2_PT_DATA_CFG_TDEFE|MPL3115A2_PT_DATA_CFG_PDEFE|MPL3115A2_PT_DATA_CFG_DREM));
		return true;
	} else {
	return false;
	}
}

/********************************************************
 	Read Data from MPL3115A2 Sensor
*********************************************************/
void xSW03::poll(void){
	readTemperature();
	readPressure();
}

/********************************************************
 	Read Temperature from MPL3115A2 Sensor
*********************************************************/
float xSW03::getTempC(void){
	return temperature;
}

float xSW03::getTempF(void){
	temperature = temperature * 1.8 + 32;
	return temperature;
}

/********************************************************
 	Read Altitude from MPL3115A2 Sensor
*********************************************************/
float xSW03::getAltitude(void){
	float atmospheric = pressure / 100.0F;
	altitude = 44330.0 * (1.0 - pow(atmospheric / 1013.25, 0.1903));
	return altitude;
}

/********************************************************
 	Read Pressure from MPL3115A2 Sensor 
*********************************************************/
float xSW03::getPressure(void){
	return pressure;
}

/*--Private Class Function--*/

/********************************************************
 	Read Pressure from MPL3115A2 Sensor 
*********************************************************/
void xSW03::readPressure(void) {
	uint32_t temp_pressure = 0;
	
	xCore.write8(MPL3115A2_I2C_ADDRESS, MPL3115A2_CTRL_REG, (MPL3115A2_MODE_BARO|MPL3115A2_CTRL_REG1_OS128|MPL3115A2_CTRL_REG1_SBYB));
	
	uint8_t sta = 0;
	while (! (sta & MPL3115A2_REG_STATUS_PDR)) {
    sta = xCore.read8(MPL3115A2_I2C_ADDRESS,MPL3115A2_REG_STATUS);
    delay(10);
	}
	
	xCore.write1(MPL3115A2_I2C_ADDRESS, MPL3115A2_REG_PRESSURE_MSB);
	
	temp_pressure = xCore.read24(MPL3115A2_I2C_ADDRESS, MPL3115A2_REG_PRESSURE_MSB);
	temp_pressure >>= 4;
	
	float calc_pressure = temp_pressure;
	calc_pressure /= 4.0;
	pressure = calc_pressure;
}


/********************************************************
 	Read Temperature from MPL3115A2 Sensor 
*********************************************************/
void xSW03::readTemperature(void) {
	int16_t t;
	
	xCore.write8(MPL3115A2_I2C_ADDRESS, MPL3115A2_CTRL_REG, (MPL3115A2_MODE_ALTI|MPL3115A2_CTRL_REG1_OS128|MPL3115A2_CTRL_REG1_SBYB));
	
	uint8_t sta = 0;
	while (! (sta & MPL3115A2_REG_STATUS_TDR)) {
		sta = xCore.read8(MPL3115A2_I2C_ADDRESS,MPL3115A2_REG_STATUS);
		delay(10);
	}
	
	xCore.write1(MPL3115A2_I2C_ADDRESS, MPL3115A2_REG_TEMP_MSB);
	
	t = xCore.read16(MPL3115A2_I2C_ADDRESS, MPL3115A2_REG_TEMP_MSB);
	t >>= 4;

	temperature = t;
	temperature /= 16.0;
}
