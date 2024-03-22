#pragma once
#include "User.h"
#include "IUserAddition.h"
#include "TeacherAddition.h"
#include "EmployeeAddition.h"
#include "ManagerAddition.h"
#include "IUserRemoval.h"
#include "TeacherRemoval.h"
#include "EmployeeRemoval.h"
#include "ManagerRemoval.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "system.h"

using namespace std;

// Observer Design Pattern Being Used with IUserAddition and IUserRemoval things
class Administrator : public User // SRP & OCP Solid Principle Being Used
{
private:
	void addTeacher()
	{
		TeacherAddition tAdd;
		tAdd.AddUser();
	}

	void addEmployee()
	{
		EmployeeAddition eAdd;
		eAdd.AddUser();
	}
	void addManager()
	{
		ManagerAddition mAdd;
		mAdd.AddUser();
	}
	void removeTeacher()
	{
		TeacherRemoval tRemove;
		tRemove.RemoveUser();
	}
	void removeEmployee()
	{
		EmployeeRemoval eRemove;
		eRemove.RemoveUser();
	}
	void removeManager()
	{
		ManagerRemoval mRemove;
		mRemove.RemoveUser();
	}
public:
	Administrator() : User()
	{
	}
	static User* CreateUser() // factory method
	{
		return new Administrator();
	}
	void Display() override
	{

	}
	void PerformAction(int type) override
	{
		switch (type)
		{
		case 1:
			addTeacher();
			break;
		case 2:
			addEmployee();
			break;
		case 3:
			addManager();
			break;
		case 4:
			removeTeacher();
			break;
		case 5:
			removeEmployee();
			break;
		case 6:
			removeManager();
			break;
		}
	}
	string getUserType() const override
	{
		return "Administrator";
	}
	bool ValidateUser(string uName, string pass) override
	{
		ifstream File("AdminData.txt");

		if (!File.is_open())
		{
			cout << "Error in opening file" << endl;
			return false;
		}

		string line;

		while (getline(File, line))
		{
			istringstream iss(line);

			string storedUname, storedPass, name, age, pNumber;

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
};
