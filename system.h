#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H
#include "Department.h"
#include "User.h"
#include "Complaint.h"
#include "Administrator.h"
#include "Director.h"
#include "Teacher.h"
#include "Employee.h"
#include "Manager.h"
#include "IT.h"
#include "Admin.h"
#include "Account.h"

// SINGLETON PATTERN 

class System
{
	static System* instance;  // Singleton instance
	int NumOfUsers;
	Department** dept;
	User** users;
	Complaint* cmp;
	System(int Num) : NumOfUsers(Num)
	{
		users = new User * [NumOfUsers];

		for (int i = 0; i < NumOfUsers; i++)
		{
			users[i] = CreateUser(i);  // Use the factory method
		}

		cmp = new Complaint[100];
	}
public:
	// Static method to access the singleton instance
	static System* getInstance(int Num)
	{
		if (!instance)
		{
			instance = new System(Num);
		}
		return instance;
	}
	static Department* CreateDepartment(int deptType);
	static User* CreateUser(int userType);
	void RunSystem(int idx, int type)
	{
		users[idx]->PerformAction(type);
	}
	bool RunValidation(int idx,const string& name,const string& pass)
	{
		return users[idx]->ValidateUser(name, pass);
	}
	~System()
	{
		/*for (int i = 0; i < NumOfUsers; i++)
		{
			delete users[i];
		}*/
	}
};
System* System::instance = nullptr;

User* System::CreateUser(int userType)
{
	switch (userType)
	{
	case 0:
		return Teacher::CreateUser();
	case 1:
		return Employee::CreateUser();
	case 2:
		return Director::CreateUser();
	case 3:
		return Administrator::CreateUser();
	case 4:
		return Manager::CreateUser();
	default:
		return nullptr; // Handle invalid userType
	}
}
Department* System::CreateDepartment(int deptType)
{
	switch (deptType)
	{
	case 0:
		return Admin::CreateInstance();
	case 1:
		return Account::CreateInstance();
	case 2:
		return InformationTechnology::CreateInstance();
	default:
		return nullptr; // Handle invalid deptType
	}
}
#endif // SYSTEM_H
