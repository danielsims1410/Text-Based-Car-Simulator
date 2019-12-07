#pragma once
#include "Header.h"

//Access Control Pattern

using namespace std;

class Subject
{
private:
	string id;
	string password;
	string proofID;
public:
	Subject(string id, string pass);
	Subject();
	string getID() { return id; }
	string getPassword() { return password; }
	void setProofID(string proof) { proofID = proof; }
	string getProofID() { return proofID; }
};

Subject::Subject(string aID, string aPass) : id(aID), password(aPass) 
{
	proofID = "";
};

Subject::Subject()
{
	cout << "== LOG IN ==============================\n";
	cout << "Enter User ID: ";
	cin >> id;
	cout << "Enter Password: ";
	cin >> password;
	cout << "========================================\n";
	proofID = "";
}

class AuthenticationInfo
{
private:
	map<string, string> Users;
public:
	AuthenticationInfo();
	bool validateUser(string name, string password);
};

AuthenticationInfo::AuthenticationInfo() //Usernames and passwords are stored here
{
	Users.insert(pair<string, string>("FullDriver", "FTesla123"));
	Users.insert(pair<string, string>("LearnerDriver", "LTesla123"));
}

bool AuthenticationInfo::validateUser(string name, string password)
{
	bool validUser = false;
	map<string, string>::iterator iterator;
	iterator = Users.find(name);
	if (iterator != Users.end())
	{
		if (!(iterator->second.compare(password)))
		{
			validUser = true;
		}
	}
	return validUser;
}

class ProofID
{
private:
	string proofID;
public:
	ProofID() {};
	ProofID(string);
	string getProofID() { return proofID; }
	void setProofID(string proof) { proofID = proof; }
};

ProofID::ProofID(string proof) : proofID(proof) {};

class Authenticator
{
private:
	string encryptDecrypt(string encrypt);
public:
	Authenticator() {};
	ProofID* authenticateUser(Subject &s);
};

string Authenticator::encryptDecrypt(string encrypt)
{
	char key = 'T';
	string output = encrypt;
	for (uint16_t i = 0; i < encrypt.size(); i++) { output[i] = encrypt[i] ^ key; }
	return output;
}


ProofID* Authenticator::authenticateUser(Subject &s)
{
	AuthenticationInfo authinfo;
	ProofID *proofID = nullptr;
	string ID = s.getID();
	string pass = s.getPassword();
	string token = "";

	if (authinfo.validateUser(ID, pass))
	{
		cout << "\nWelcome!";
		cout << "\nAuthenticated!\n";
		token = encryptDecrypt(ID + pass);
		proofID = new ProofID(token);
		s.setProofID(token);
	}
	
	else 
	{
		cout << "Invalid User ID or Password!" << endl;
		cout << "Please Try Again!" << endl << endl;
	}

	return proofID;
}





