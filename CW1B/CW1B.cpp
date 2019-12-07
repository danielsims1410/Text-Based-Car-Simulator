// CW1B.cpp : Defines the entry pouint16_t for the console application.
//
#include "stdafx.h"
#include "Authentication.h"
#include "Builder.h"
#include "Header.h"

////////////////LOGIN AUTHORISE METHOD//////////////////////
//
DriverTypes LoginAuthorise()
{
	uint16_t loopcheck = 0; //Unsigned 16-bit Integer

	while (loopcheck == 0)
	{
		Subject subject;
		Authenticator authenticator;
		ProofID *proofID = authenticator.authenticateUser(subject);

		if (proofID != nullptr)
		{
			cout << "Subject proof of ID: " << subject.getProofID() << endl;
			cout << "System proof of ID: " << proofID->getProofID() << endl;
			loopcheck = 1;
			if (subject.getID() == "FullDriver") 
			{ 
				cout << "You are a Full Driver!" << endl;
				return FullD;
			}
			else if (subject.getID() == "LearnerDriver") 
			{
				cout << "You are a Learner Driver!" << endl << endl; 
				return LearnerD;
			}
		}
	}
}
//
//////////////////////////////////////////////////////////


/////////////////INTERFACE CLASS//////////////////////////
//
class Interface
{
private:
	bool engineoff = false;
public:
	Interface() {};
	~Interface() {};
	void ShowInterface();
	void InterfaceChoice(uint16_t choice, Car* MyCar, DriverTypes drivertype);
	void Accelerate(Car* MyCar, DriverTypes drivertype);
	void Deaccelerate(Car* MyCar);
	void ChangeTemperature(Car* MyCar);
	void TurnOff(Car* MyCar);
	void UpdateOnGoing(Car* MyCar);
	void EmergencyStop(Car* MyCar);
	void ViewLogs(Car* MyCar, DriverTypes drivertype);
	bool GetEngineOff() { return engineoff; }
};

void Interface::ViewLogs(Car* MyCar, DriverTypes drivertype)
{
	CarRecordsProcessing NewCarRecord;
	if (drivertype == FullD)
	{
		NewCarRecord.loadRecords("CarRecords.txt");
		NewCarRecord.displayRecordsExceedingSpeedLimit();
	}

	else
	{
		cout << " [!] UNAUTHORISED! Full Drivers Only! [!] " << endl;
	}
}

void Interface::UpdateOnGoing(Car* MyCar)
{
	//CHECKS FUEL STATE
	if (MyCar->fuelGauge->getReading() == 0) {}
	else
	{
		MyCar->fuelGauge->updateReading((MyCar->fuelGauge->getReading()) - 1);
		MyCar->fuelGauge->calculatePercentage(MyCar->fuelGauge->getReading(), MyCar->fuelGauge->getTankCapacity());
	}
	
	//CHECKS AIR CON STATE
	if (MyCar->aircon->getAirConState() == "Heating")
	{
		MyCar->temp->updateReading(MyCar->temp->getReading() + 1);
		if (MyCar->temp->getReading() == 25)
		{
			cout << "\n [!] Too Hot! Turning Heating Off! [!] " << endl << endl;
			MyCar->aircon->setAirConState(Neutral);
		}
	}

	else if (MyCar->aircon->getAirConState() == "Air-Con")
	{
		MyCar->temp->updateReading(MyCar->temp->getReading() - 1);
		if (MyCar->temp->getReading() == -5)
		{
			cout << "\n [!] Too Cold! Turning Air Con Off! [!] " << endl << endl;
			MyCar->aircon->setAirConState(Neutral);
		}
	}

	else {};
}

void Interface::Accelerate(Car* MyCar, DriverTypes drivertype)
{
	if (MyCar->fuelGauge->getReading() == 0)
	{
		cout << "\n [!] Out of Fuel! Coming to a Stop! [!] " << endl;
		Deaccelerate(MyCar);
	}
	else if ((drivertype == LearnerD) && (MyCar->speedo->getReading() == 70))
	{
		cout << "\n [!] LEARNER DRIVERS CANNOT EXCEED 70MPH! [!] " << endl;
	}
	else if (MyCar->speedo->getReading() >= MyCar->engine->getMaxSpeed()) 
	{ 
		cout << "\n [!] Speed Limit Reached! [!]" << endl;
		cout << "\n [!] Cannot Accelerate Further! [!]" << endl;
	}
	else { MyCar->speedo->updateReading((MyCar->speedo->getReading()) + 10); };
}

void Interface::Deaccelerate(Car* MyCar)
{
	if (MyCar->speedo->getReading() == 0)
	{
		cout << "\n [!] Car is stopped! [!] " << endl;
	}

	else
	{
		MyCar->speedo->updateReading((MyCar->speedo->getReading()) - 10);
	}
}

void Interface::TurnOff(Car* MyCar)
{
	if (MyCar->speedo->getReading() == 0)
	{
		cout << "========================================\n";
		cout << "THANK YOU FOR DRIVING SMARTCAR!" << endl;
		cout << "========================================\n";
		engineoff = true;
	}

	else
	{
		cout << " [!] Car is still moving! Stop First! [!] " << endl << endl;
	}
}

void Interface::ChangeTemperature(Car* MyCar)
{
	uint16_t switchtrigger;
	cout << "== TEMPERATURE CONTROL =================";
	cout << "\n[1] -- Switch Air Con ON";
	cout << "\n[2] -- Switch Heating ON";
	cout << "\n[3] -- Turn Temperature Control OFF";
	cout << "\nSELECTION: ";
	cin >> switchtrigger;
	while (switchtrigger < 0 || switchtrigger > 4)
	{
		cout << "Invalid Option!" << endl;
		cout << "Select 1, 2, or 3: ";
		cin >> switchtrigger;
	}
	cout << "=======================================\n";

	switch (switchtrigger)
	{
	case 1:
		MyCar->aircon->setAirConState(Cooler);
		break;
	case 2:
		MyCar->aircon->setAirConState(Warmer);
		break;
	case 3:
		MyCar->aircon->setAirConState(Neutral);
		break;
	}
}

void Interface::EmergencyStop(Car* MyCar)
{
	if (MyCar->speedo->getReading() == 0)
	{
		cout << " [!] Car is already stopped! [!] " << endl;
	}

	else
	{
		cout << " [!] Breaks slammed on! [!] " << endl;
		cout << " [!] Car is now stopped! [!] " << endl;
		MyCar->speedo->updateReading(0);
	}
}

void Interface::ShowInterface()
{
		cout << "\n== MENU ================================";
		cout << "\nPLEASE SELECT AN OPTION:";
		cout << "\n[1] -- Accelerate (+10mph)";
		cout << "\n[2] -- Deccelerate (-10mph)";
		cout << "\n[3] -- Temperature Settings";
		cout << "\n[4] -- Emergency Stop";
		cout << "\n[5] -- View Logs (Exceeding Speed Limit)";
		cout << "\n[6] -- Turn Car Off (Exit)";
		cout << "\nSELECTION: ";
}

void Interface::InterfaceChoice(uint16_t choice, Car* MyCar, DriverTypes drivertype)
{
	
	
	switch (choice)
	{
	case 1:
		Accelerate(MyCar, drivertype);
		break;
	case 2:
		Deaccelerate(MyCar);
		break;
	case 3:
		ChangeTemperature(MyCar);
		break;
	case 4:
		EmergencyStop(MyCar);
		break;
	case 5:
		ViewLogs(MyCar, drivertype);
		break;
	case 6:
		TurnOff(MyCar);
		break;
	default:
		break;
	}
	UpdateOnGoing(MyCar);
}
//
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
//
uint16_t main()
{
	DriverTypes typeofdriver;
	Interface NewInterface;
	Car* MyCar = new CarBuilder("SmartCar", 400, 50, 150, 0, 60, 60, 0);

	uint16_t choice = 0; //Unsigned 16-bit Integer
	cout << "========================================\n";
	cout << "========= WELCOME TO SMART CAR =========\n";
	cout << "========================================\n\n";
	typeofdriver = LoginAuthorise();
	while (true)
	{
		NewInterface.ShowInterface();
		cin >> choice;
		if (choice > 0 && choice < 7)
		{
			cout << "========================================\n\n";
			NewInterface.InterfaceChoice(choice, MyCar, typeofdriver);
			if (NewInterface.GetEngineOff()) { break; }
			MyCar->specs("CarRecords.txt");
		}

		else
		{
			cout << " [!] INVALID OPTION! [!]" << endl;
		}
	}
	delete MyCar;
	return 0;
}
//
//////////////////////////////////////////////////////////

