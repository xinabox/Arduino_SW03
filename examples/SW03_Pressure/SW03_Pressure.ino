/*************************************************************
	This is an example for the SW03
	Digital Temperature, Pressure and Humidity Sensor
	
	You can buy one on our store!
	-----> https://xinabox.cc/products/SW03
	
	This example request a altitude meausrement to be 
	made by the SW01 and display the data over the Serial
	bus.
	
	Supported on the all ☒CHIPs
	
	The sensor communicates over the I2C Bus.
	
*************************************************************/

#include <xCore.h>
#include <Arduino_SW03.h>

const int DELAY_TIME = 1000;

xSW03 SW03;

void setup(){
	// Start the Serial Monitor
	Serial.begin(115200);
	
	// Set the I2C Pins for CW01
	#ifdef ESP8266
	  Wire.pins(2, 14);
	  Wire.setClockStretchLimit(15000);
	#endif
	
	// Start the I2C Comunication
	Wire.begin();
	
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
	Serial.print("Pressure: ");
	Serial.print(pressure);
	Serial.println(" Pa");
	
	delay(DELAY_TIME);
}
