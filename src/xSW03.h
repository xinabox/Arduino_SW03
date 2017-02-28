/*
	This is a library for the SW03 
	Precision Pressure Sensor

	The board uses I2C for communication.
	
	The board communicates with the following I2C device:
	* 	MPL3115A2
	
	Data Sheets:
	MPL3315A2 - http://www.nxp.com/assets/documents/data/en/data-sheets/MPL3115A2.pdf
*/

#ifndef xSW03_h
#define xSW03_h

// System Includes
#include <inttypes.h>
#include <Arduino.h>
#include "xCore.h"

//Device I2C Address
#define MPL3115A2_I2C_ADDRESS			(0x60)

// Register Defines
#define MPL3115A2_REG_STATUS 			0x00
#define MPL3115A2_REG_STATUS_TDR 		0x02
#define MPL3115A2_REG_STATUS_PDR 		0x04
#define MPL3115A2_REG_STATUS_PTDR 		0x08
#define MPL3115A2_REG_STATUS_DR         0x06

#define MPL3115A2_WHOAMI                (0x0C)
#define MPL3115A2_REG_STARTCONVERSION   (0x12)

#define MPL3115A2_REG_PRESSURE_MSB      (0x01)
#define MPL3115A2_REG_PRESSURE_CSB      (0x02)
#define MPL3115A2_REG_PRESSURE_LSB      (0x03)
#define MPL3115A2_REG_TEMP_MSB          (0x04)
#define MPL3115A2_REG_TEMP_LSB          (0x05)

// Data Register Defines
#define MPL3115A2_OUT_P_DELTA_MSB       (0x07)
#define MPL3115A2_OUT_P_DELTA_CSB       (0x08)
#define MPL3115A2_OUT_P_DELTA_LSB       (0x09)
#define MPL3115A2_OUT_T_DELTA_MSB       (0x0A)
#define MPL3115A2_OUT_T_DELTA_LSB       (0x0B)
#define MPL3115A2_PT_DATA_CFG 			(0x13)
#define MPL3115A2_PT_DATA_CFG_TDEFE 	(0x01)
#define MPL3115A2_PT_DATA_CFG_PDEFE 	(0x02)
#define MPL3115A2_PT_DATA_CFG_DREM 		(0x04)

// Control Register Defines
#define MPL3115A2_CTRL_REG1             (0x26)
#define MPL3115A2_CTRL_REG1_SBYB 		(0x01)
#define MPL3115A2_CTRL_REG1_OST 		(0x02)
#define MPL3115A2_CTRL_REG1_RST 		(0x04)
#define MPL3115A2_CTRL_REG1_OS1 		(0x00)
#define MPL3115A2_CTRL_REG1_OS2 		(0x08)
#define MPL3115A2_CTRL_REG1_OS4 		(0x10)
#define MPL3115A2_CTRL_REG1_OS8 		(0x18)
#define MPL3115A2_CTRL_REG1_OS16 		(0x20)
#define MPL3115A2_CTRL_REG1_OS32 		(0x28)
#define MPL3115A2_CTRL_REG1_OS64 		(0x30)
#define MPL3115A2_CTRL_REG1_OS128 		(0x38)
#define MPL3115A2_CTRL_REG1_RAW 		(0x40)
#define MPL3115A2_CTRL_REG1_ALT 		(0x80)
#define MPL3115A2_CTRL_REG1_BAR 		(0x00)
#define MPL3115A2_CTRL_REG2             (0x27)
#define MPL3115A2_CTRL_REG3             (0x28)
#define MPL3115A2_CTRL_REG4             (0x29)
#define MPL3115A2_CTRL_REG5             (0x2A)

/*=========================================================================*/

class xSW03: public xCoreClass
{
	public:
		xSW03();
		void 	poll();
		void 	setMode();
		bool 	begin(void);
		float 	getPressure(void);
		float 	getAltitude(void);
		float 	getTemperature(void);
		
	private:
		void 	readTemperature(void);
		void 	readPressure(void);
		void 	readAltitude(void);
			
		float    temperature;                       // stores temperature value	
		float    pressure;                          // stores pressure value
		float 	 altitude;							// stores calculated altitude 

};

extern xSW03 SW03;

#endif