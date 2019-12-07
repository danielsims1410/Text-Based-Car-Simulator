#pragma once
#include "Header.h"

class CarRecord
{
public:
	string name;
	string horsepower;
	string MPG;
	string temperature;
	uint16_t  speed; //Unsigned 16-bit Integer
	string petrolremaining;
	string petrolremainingperc;
	string time;
};

class CarRecordsProcessing
{
private:
	ifstream inputfile;
	vector<CarRecord> CarRecordsVector;
public:
	void loadRecords(string filename);
	void displayRecordsExceedingSpeedLimit();
};

void CarRecordsProcessing::loadRecords(string filename)
{
	CarRecord NewCarRecord;
	string dump;

	inputfile.open(filename);

	if (!inputfile)
	{
		cout << filename << " does NOT exist!" << endl;
		return;
	}

	else
	{
		while (!inputfile.eof())
		{
			getline(inputfile, NewCarRecord.name);
			getline(inputfile, NewCarRecord.horsepower);
			getline(inputfile, NewCarRecord.MPG);
			getline(inputfile, NewCarRecord.temperature);
			inputfile >> NewCarRecord.speed;
			getline(inputfile, NewCarRecord.petrolremaining);
			getline(inputfile, NewCarRecord.petrolremainingperc);
			getline(inputfile, NewCarRecord.time);

			CarRecordsVector.push_back(NewCarRecord);
		}
	}
	inputfile.close();
}

void CarRecordsProcessing::displayRecordsExceedingSpeedLimit()
{
	uint16_t  speedlimit; //Unsigned 16-bit Integer
	cout << "=====================================\n";
	cout << "Please Enter a Speed Limit: ";
	cin >> speedlimit;
	while (speedlimit < 0)
	{
		cout << "Speed limit cannot be negative! Retry: ";
		cin >> speedlimit;
	}
	cout << "=====================================\n";

	for (uint16_t  i = 0; i < CarRecordsVector.size(); i++) //Unsigned 16-bit Integer
	{
		if (CarRecordsVector[i].speed >= speedlimit)
		{
			cout << "=====================================\n";
			cout << "NAME: " << CarRecordsVector[i].name << "HP" << endl;
			cout << "HORSEPOWER: " << CarRecordsVector[i].horsepower << endl;
			cout << "SPEED: " << CarRecordsVector[i].speed << "MPH" << endl;
			cout << "PETROL REMAINING: " << CarRecordsVector[i].petrolremainingperc << "%" << endl;
			cout << "=====================================\n";
		}
	}
}
