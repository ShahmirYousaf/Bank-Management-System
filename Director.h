#pragma once
#include "User.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "system.h"
#include "Complaint.h"
#include "Report.h"
#include "ComplaintDetails.h"
#include "SummaryGenerator.h"
#include "ControllerFunctions.h"

using namespace std;

Complaint cmp[100];

class Director : public User
{
private:
	void GenerateSummary()
	{
		SummaryGenerator SG;
		SG.GenerateReport(cmp);
	}
	void GenerateComplaintDetails()
	{
		ComplaintDetails CD;
		CD.GenerateReport(cmp);
	}
	Director() : User()
	{
	}
	// Declare a static instance of the Director class
	static Director* instance;

	// Declare a flag to check if an instance has been created
	static bool instanceCreated;
public:
	static Director* getInstance()
	{
		if (!instanceCreated)
		{
			instance = new Director();
			instanceCreated = true;
		}
		return instance;
	}

	void PerformAction(int type) override
	{
		switch (type)
		{
		case 1:
			GenerateSummary();
			break;
		case 2:
			GenerateComplaintDetails();
			break;
		case 3:
			break;
		}
	}
	void Display() override
	{
		User::Display();
	}
	string getUserType() const override
	{
		return "Director";
	}
	bool ValidateUser(string uName, string pass) override
	{
		ifstream File("DirectorData.txt");

		if (!File.is_open())
		{
			cout << "Error in opening file" << endl;
			return false;
		}

		string line;
		int tid = -1;

		while (getline(File, line))
		{
			istringstream iss(line);

			string storedUname, storedPass, name, age, pNumber, deptN;

			if (getline(iss, storedUname, ',') &&
				getline(iss, storedPass, ',') &&
				getline(iss, name, ',') &&
				getline(iss, age, ',') &&
				getline(iss, pNumber, ','))
			{
				if (uName == storedUname && pass == storedPass)
				{
					User::SetUserName(storedUname);
					User::SetPassword(storedPass);
					User::SetName(name);
					User::SetAge(stoi(age));
					User::SetPhoneNumber(pNumber);
					
					return true;
				}
			}
		}

		return false;
	}
	static User* CreateUser() // factory method
	{
		return Director::getInstance();;
	}
};
Director* Director::instance = nullptr;

// Initialize the static flag
bool Director::instanceCreated = false;
