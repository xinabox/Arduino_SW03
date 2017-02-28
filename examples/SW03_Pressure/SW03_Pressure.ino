/*************************************************************
	This is an examples for the SW03
	Digital Temperature, Pressure and Altitude Sensor
	
	You can buy one on our store!
	-----> https://xinabox.cc/SW03/
	
	This example request a altitude meausrement to be 
	made by the SW01 and display the data over the Serial
	bus.
	
	Currently Supported on:
	- CW01
	- CC01
	- CR01
	
	The sensor communicates over the I2C Bus.
	
	------------------------TIPS--------------------------
	Change this line ----->Wire.begin(2,14);
	to this			 ----->Wire.begin();
	to allow this sensor to communicate with CC01 and CR01
	
*************************************************************/

#include <xCore.h>
#include <xSW03.h>

const int DELAY_TIME = 1000;

void setup(){
	// Start the Serial Monitor
	Serial.begin(115200);
	
	// Start the I2C Comunication
	Wire.begin(2,14);
	
	// Start the SW03 Sensor
	SW03.begin();
	
	Serial.println("================================");
	Serial.println("     XINABOX SW03 Pressure      ");
	Serial.println("================================");	
	delay(DELAY_TIME);
}

void loop() {
	// Create a variable to store the data read from SW03
	float pressure;
	pressure = 0;
	
	// Poll the sensor to read all available data
	SW03.poll();
	
	// Request SW03 to get the pressure measurement and store in
	// the pressure variable
	pressure = SW03.getPressure();
	
	// Display the recorded data over the serial monitor
	Serial.println("Pressure: ");
	Serial.print(pressure);
	Serial.print(" kPa");
	delay(DELAY_TIME);
}
