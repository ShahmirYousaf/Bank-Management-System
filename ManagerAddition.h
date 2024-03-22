#pragma once
#include "IUserAddition.h"

class ManagerAddition : public IUserAddition
{
public:
	void AddUser() override 
	{
		int dept = InputDept();

		string existingData = readFromFile(dept);

		if (!existingData.empty())
		{
			cout << "Manager already exist, we cannot add another one" << endl;
			Sleep(10);
			return;
		}

		string newData = takeUserInput();

		writeToFile(newData);

		cout << "Manager added successfully." << endl;
		Sleep(10);
	}
private:
	int InputDept()
	{
		cout << "\nPress(1) for IT Dept" << endl;
		cout << "Press(2) for Admin Dept" << endl;
		cout << "Press(3) for Accounts Dept" << endl;
		cout << "Enter Option: ";
		int opt;
		cin >> opt;

		return opt;
	}
	string readFromFile(int d)
	{
		ifstream file;

		if (d == 1)
		{
			file.open("ITManagerData.txt");
		}
		else if (d == 2)
		{
			file.open("AdminManagerData.txt");
		}
		else
		{
			file.open("AccountsManagerData.txt");
			
		}
		
		string data;

		if (file.is_open())
		{
			
			getline(file, data); // read a single line from the file as there can be only 1 record of manager

			file.close();
		}

		return data;
	}
	void writeToFile(string& data)
	{
		ofstream file("ManagerData.txt");

		if (file.is_open())
		{
			file << data;
			file.close();
		}
	}
	string takeUserInput()
	{
		string username, password, name, age, phoneNumber, dept;

		cout << "Enter new Manager data:\n";

		cout << "Username: ";
		cin.ignore(); // Ignore newline character left in the stream
		getline(cin, username);

		cout << "Password: ";
		getline(cin, password);

		cout << "Name: ";
		getline(cin, name);

		cout << "Age: ";
		getline(cin, age);

		cout << "PhoneNumber: ";
		getline(cin, phoneNumber);

		cout << "Department: ";
		getline(cin, dept);

		// Construct a string in the required format: username,password,Name,Age,PhoneNumber
		return username + "," + password + "," + name + "," + age + "," + phoneNumber + "," + dept;
	}
};
