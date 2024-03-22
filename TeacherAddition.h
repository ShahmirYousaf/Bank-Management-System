#pragma once

#include "IUserAddition.h"
#include "TotalNumber.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class TeacherAddition : public IUserAddition
{
public:
	void AddUser() override
	{		 
		string NewData = takeUserInput();  // taking new data from user

		writeToFile(NewData);  // writinhg it to file again

		setNumbers(1); // incrementing number of teachers in count file

		cout << "Teacher Added Successfully into the System" << endl;

	}
private:
	string readFromFile()
	{
		ifstream file("TeachersData,txt");

		string data;

		if (file.is_open())
		{
			stringstream buffer;

			buffer << file.rdbuf();  // using in-built function to read data in buffer 
			data = buffer.str();

			file.close();
		}

		return data;
	}
	void writeToFile(const string& data)
	{
		ofstream file("TeachersData.txt", ios::app);

		if (file.is_open())
		{
			file << data << "\n";

			file.close();
		}
	}
	string takeUserInput()
	{
		string username, password, name, age, phoneNumber, position;
		int id = -1;
		id = getNumbers(1, id); // passing 1 for teacher type
		id += 1; // increasing id to get next number

		cout << "Enter new teacher data:\n";

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

		cout << "Position: ";
		getline(cin, position);

		string ID = to_string(id);

		// Construct a string in the required format: username,password,Name,Age,PhoneNumber,Position
		return ID + "," + username + "," + password + "," + name + ","  + age + "," + phoneNumber + "," + position;
	}
};
