#pragma once
#include <iostream>

using namespace std;

// FACTORY METHOD BEING USED 

class User
{
	string UserName;
	string Password;
	string Name;
	int Age;
	string PhoneNumber;
public:
	User()
	{
		UserName = "\0";
		Password = "\0";
		Name = "\0";
		Age = -1;
		PhoneNumber = "\0";
	}
	void SetUserName(string& userN)
	{
		UserName = userN;
	}
	void SetPassword(string& pass)
	{
		Password = pass;
	}
	void SetName(string& name)
	{
		Name = name;
	}
	void SetAge(int a)
	{
		Age = a;
	}
	void SetPhoneNumber(string& pNo)
	{
		PhoneNumber = pNo;
	}
	string getUserName()
	{
		return UserName;
	}
	string getPassword()
	{
		return Password;
	}
	string getName()
	{
		return Name;
	}
	int getAge()
	{
		return Age;
	}
	string getPhoneNumber()
	{
		return PhoneNumber;
	}
	virtual void PerformAction(int type) = 0;
	
	virtual bool ValidateUser(string Uname, string Pass) = 0;
	
	virtual string getUserType() const = 0;

	virtual void Display()
	{
		cout << "Name: " << getName() << endl;
		cout << "Age: " << getAge() << endl;
		cout << "Phone Number: " << getPhoneNumber() << endl;
	}

	virtual ~User() = default;
	

};