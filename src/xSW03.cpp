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
#include <xSW03.h>

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
bool xSW03::begin(){
	uint8_t whoami = xCore.read8(MPL3115A2_I2C_ADDRESS,MPL3115A2_WHOAMI);
	if (whoami != 0xC4) {
		return false;
	}
	xCore.write8(MPL3115A2_I2C_ADDRESS, MPL3115A2_CTRL_REG1,MPL3115A2_CTRL_REG1_SBYB |MPL3115A2_CTRL_REG1_OS128 | MPL3115A2_CTRL_REG1_ALT);
	xCore.write8(MPL3115A2_I2C_ADDRESS, MPL3115A2_PT_DATA_CFG, MPL3115A2_PT_DATA_CFG_TDEFE |MPL3115A2_PT_DATA_CFG_PDEFE | MPL3115A2_PT_DATA_CFG_DREM);
	return true;
}

/********************************************************
 	Read Data from MPL3115A2 Sensor
*********************************************************/
void xSW03::poll(){
	readTemperature();
	readPressure();
	readAltitude();
}

/********************************************************
 	Read Temperature from MPL3115A2 Sensor
*********************************************************/
float xSW03::getTemperature(){
	return temperature;
}

/********************************************************
 	Read Altitude from MPL3115A2 Sensor
*********************************************************/
float xSW03::getAltitude(){
	return altitude;
}

/********************************************************
 	Read Pressure from MPL3115A2 Sensor 
*********************************************************/
float xSW03::getPressure(){
	return pressure;
}

/*--Private Class Function--*/

/********************************************************
 	Read Pressure from MPL3115A2 Sensor 
*********************************************************/
void xSW03::readPressure() {
	uint32_t pres;

	xCore.write8(MPL3115A2_I2C_ADDRESS, MPL3115A2_CTRL_REG1, MPL3115A2_CTRL_REG1_SBYB | MPL3115A2_CTRL_REG1_OS128 | MPL3115A2_CTRL_REG1_BAR);

	uint8_t sta = 0;
	while (! (sta & MPL3115A2_REG_STATUS_PDR)) {
    sta = xCore.read8(MPL3115A2_I2C_ADDRESS,MPL3115A2_REG_STATUS);
    delay(10);
	}
	
	pres = xCore.read24(MPL3115A2_I2C_ADDRESS, MPL3115A2_REG_PRESSURE_MSB);
	pres >>= 4;
	
	float baro = pres;
	baro /= 4.0;
	pressure = baro;
}

/********************************************************
 	Read Altitude from MPL3115A2 Sensor 
*********************************************************/
void xSW03::readAltitude() {
	uint32_t alt;
	xCore.write8(MPL3115A2_I2C_ADDRESS, MPL3115A2_CTRL_REG1, MPL3115A2_CTRL_REG1_SBYB | MPL3115A2_CTRL_REG1_OS128 | MPL3115A2_CTRL_REG1_ALT);
	uint8_t sta = 0;
	while (! (sta & MPL3115A2_REG_STATUS_PDR)) {
		sta = xCore.read8(MPL3115A2_I2C_ADDRESS, MPL3115A2_REG_STATUS);
		delay(10);
	}
	
	alt = xCore.read24(MPL3115A2_I2C_ADDRESS, MPL3115A2_REG_PRESSURE_MSB);
	alt >>= 4;

	if (alt & 0x80000) {
		alt |= 0xFFF00000;
	}

	altitude = alt;
	altitude /= 16.0;
}

/********************************************************
 	Read Temperature from MPL3115A2 Sensor 
*********************************************************/
void xSW03::readTemperature() {
	int16_t t;

	uint8_t sta = 0;
	while (! (sta & MPL3115A2_REG_STATUS_TDR)) {
		sta = xCore.read8(MPL3115A2_I2C_ADDRESS,MPL3115A2_REG_STATUS);
		delay(10);
	}
	
	t = xCore.read16(MPL3115A2_I2C_ADDRESS, MPL3115A2_REG_TEMP_MSB);
	t >>= 4;

	temperature = t;
	temperature /= 16.0;
}

xSW03 SW03 = xSW03();