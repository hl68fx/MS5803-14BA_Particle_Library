/******************************************************************************
Demo Program for MS5803 pressure sensors for Particle devices.
Ported from Thomas Rockenbauer

Created from Casey Kuhns @ SparkFun Electronics
7/20/2014
https://github.com/sparkfun/MS5803-14BA_Breakout/

The MS58XX MS57XX and MS56XX by Measurement Specialties is a low cost I2C pressure
sensor.  This sensor can be used in weather stations and for altitude
estimations. It can also be used underwater for water depth measurements. 

This code is beerware. If you see me (or any other SparkFun employee) at the
local pub, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#ifndef MS5803_I2C_h
#define MS5803_I2C_h

#include <application.h>

// Define units for conversions. 
enum temperature_units
{
	CELSIUS,
	FAHRENHEIT,
};

// Define measurement type.
enum measurement
{	
	PRESSURE = 0x00,
	TEMPERATURE = 0x10
};

// Define constants for Conversion precision
enum precision
{
	ADC_256  = 0x00,
	ADC_512  = 0x02,
	ADC_1024 = 0x04,
	ADC_2048 = 0x06,
	ADC_4096 = 0x08
};

// Define address choices for the device (I2C mode)
enum ms5803_addr
{
	ADDRESS_HIGH = 0x76,
	ADDRESS_LOW  = 0x77
};

//Commands
#define CMD_RESET 0x1E // reset command 
#define CMD_ADC_READ 0x00 // ADC read command 
#define CMD_ADC_CONV 0x40 // ADC conversion command 

#define CMD_PROM 0xA0 // Coefficient location


class MS5803
{
	public:	
		MS5803(ms5803_addr address); 
		void reset(void);	 //Reset device
		uint8_t begin(void); // Collect coefficients from sensor
		
		// Return calculated temperature from sensor
		float getTemperature(temperature_units units, precision _precision);
		// Return calculated pressure from sensor
		float getPressure(precision _precision);

	private:
		
		int32_t _temperature_actual;
		int32_t _pressure_actual;
	
		ms5803_addr _address; 		// Variable used to store I2C device address.
		uint16_t coefficient[8];// Coefficients;
		
		void getMeasurements(precision _precision);

		void sendCommand(uint8_t command);	// General I2C send command function
		uint32_t getADCconversion(measurement _measurement, precision _precision);	// Retrieve ADC result

		void sensorWait(uint8_t time); // General delay function see: delay()
};

#endif