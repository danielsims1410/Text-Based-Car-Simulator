#pragma once
#include "Header.h"
#include "FileIO.h"

//BUILDER SECURE PATTERN

///////////////////////SENSOR CLASS////////////////////////
//
class Sensor //Abstract Class for sensors specified below
{
public:
	Sensor() {} 
	~Sensor() {} 
	float reading; 
	virtual float getReading() { return reading; } 
	virtual void updateReading(float reading) { this->reading = reading; } 
};
//
//////////////////////////////////////////////////////////


//////////////////TEMPERATURE CLASS///////////////////////
//
class Temperature : public Sensor 
{
private:
public:
	Temperature() {} //Constructor
	~Temperature() {} //Destructor
	
};
//
//////////////////////////////////////////////////////////


//////////////////////AIR-CON CLASS///////////////////////
//
class AirCon : public Temperature
{
private:
	AirConTypes airconstate = Neutral;
	string airconstateString; 
public:
	AirCon() {}
	~AirCon() {}
	string getAirConState() 
	{
		if (airconstate == Neutral) { airconstateString = "Neutral"; } 
		else if (airconstate == Warmer) { airconstateString = "Heating"; } 
		else if (airconstate == Cooler) { airconstateString = "Air-Con"; }
		return airconstateString; 
	}

	void setAirConState(AirConTypes state)
	{
		airconstate = state;
	}
};
//
//////////////////////////////////////////////////////////


//////////////////////FUEL TANK CLASS/////////////////////
//
class FuelTank : public Sensor //Fuel Tank class - Sensor
{
private:
	float petrolRemainingPerc;
	uint16_t petrolRemaining; //Unsigned 16-bit Integer
	float tankCapacity; 
public:
	FuelTank() {}
	~FuelTank() {}

	uint16_t getPetrolRemaining() { return petrolRemaining; }  //Unsigned 16-bit Integer
	uint16_t getTankCapacity() { return tankCapacity; } //Unsigned 16-bit Integer
	float getTankRemaining() { return petrolRemainingPerc; } 

	void setPetrolRemaining(uint16_t petrol) { petrolRemaining = petrol; } //Unsigned 16-bit Integer
	void setTankCapacity(uint16_t tankcapacity) { tankCapacity = tankcapacity; } //Unsigned 16-bit Integer
	void calculatePercentage(float petrol, float tankcapacity); 
};

void FuelTank::calculatePercentage(float petrol, float tankcapacity)
{
	petrolRemainingPerc = ((petrol / tankcapacity) * 100);
}
//
//////////////////////////////////////////////////////////


//////////////////SPEEDOMETER CLASS///////////////////////
//
class Speedometer : public Sensor //Speedometer Sensor
{
public:
	Speedometer() {}
	~Speedometer() {}
};
//
//////////////////////////////////////////////////////////


////////////////////ENGINE CLASS//////////////////////////
//
class Engine
{
public:
	Engine() {};
	~Engine() {};

	uint16_t maxspeed; //Unsigned 16-bit Integer
	uint16_t horsepower; //Unsigned 16-bit Integer
	uint16_t getHorsepower() { return horsepower; } 
	void setHorsepower(uint16_t hp) { horsepower = hp; } 

	uint16_t getMaxSpeed() { return maxspeed; } //Unsigned 16-bit Integer
	void setMaxSpeed(uint16_t max) { maxspeed = max; }

	uint16_t MPG; //Unsigned 16-bit Integer
	uint16_t getMPG() { return MPG; } //Unsigned 16-bit Integer
	void setMPG(uint16_t MPGs) { MPG = MPGs; }
};
//
//////////////////////////////////////////////////////////



////////////////////////CAR CLASS/////////////////////////
//
class Car
{
protected:
	ofstream outputfile;
	string name = "";
public:
	Engine* engine;
	Speedometer* speedo;
	Temperature* temp;
	FuelTank* fuelGauge;
	AirCon* aircon;
	Car(void)
	{
		engine = new Engine();
		temp = new Temperature();
		speedo = new Speedometer();
		fuelGauge = new FuelTank();
		aircon = new AirCon();
	}

	virtual void specs(string filename)
	{
		outputfile.open(filename, ios::app);
		cout << "-- STATS -------------------------------\n";
		cout << "Name: " << name << endl;
		outputfile << name << endl;
		cout << "Horsepower: " << engine->getHorsepower() << endl;
		outputfile << engine->getHorsepower() << endl;
		cout << "Max Speed: " << engine->getMaxSpeed() << endl;
		cout << "MPG: " << engine->getMPG() << endl;
		outputfile << engine->getMPG() << endl;
		cout << "Temperature " << temp->getReading() << "C" << endl;
		cout << "Temperature Control Type: " << aircon->getAirConState() << endl;
		outputfile << temp->getReading() << endl;
		cout << "Speed: " << speedo->getReading() << "MPH" << endl;
		outputfile << speedo->getReading() << endl;
		cout << "Petrol Tank Capacity: " << fuelGauge->getTankCapacity() << "L" << endl;
		cout << "Petrol Remaining: " << fuelGauge->getReading() << "L (" << fuelGauge->getTankRemaining() << "%)" << endl;
		cout << "----------------------------------------\n";
		outputfile << fuelGauge->getReading() << endl;
		outputfile << fuelGauge->getTankRemaining() << endl;
		outputfile.close();
	}

	virtual ~Car()
	{
		delete engine;
		delete temp;
		delete speedo;
		delete fuelGauge;
		delete aircon;
	}
};
//
//////////////////////////////////////////////////////////


//////////////////CAR BUILDER CLASS///////////////////////
//
class CarBuilder : public Car
{
public:
	CarBuilder(string carname, uint16_t horsepower, uint16_t MPG, uint16_t maxspeed, uint16_t temperature, float petrolremaining, uint16_t tankcapacity, uint16_t speed)
	{
		name = carname;
		engine->setHorsepower(horsepower);
		engine->setMPG(MPG);
		engine->setMaxSpeed(maxspeed);
		temp->updateReading(temperature);
		fuelGauge->updateReading(petrolremaining);
		fuelGauge->setPetrolRemaining(petrolremaining);
		fuelGauge->calculatePercentage(petrolremaining, tankcapacity);
		fuelGauge->setTankCapacity(tankcapacity);
		speedo->updateReading(speed);
	}
	void specs() { Car::specs("CarRecords.txt"); }
};
//
//////////////////////////////////////////////////////////
