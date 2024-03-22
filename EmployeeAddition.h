#pragma once
#include "IUserAddition.h"
#include "TotalNumber.h"

class EmployeeAddition : public IUserAddition
{
public:
	void AddUser() override
	{
		string NewData = takeUserInput();  // taking new data from user

		writeToFile(NewData);  // writinhg it to file again

		setNumbers(3); // incrementing no of employees in count file

		cout << "Employee Added Successfully into the System" << endl;
	}
private:
	void writeToFile(const string& data)
	{
		ofstream file("EmployeeData.txt", ios::app);

		if (file.is_open())
		{
			file << data << "\n";

			file.close();
		}
	}
	string takeUserInput()
	{
		string username, password, name, age, phoneNumber, sal;
		int id = -1;
		id = getNumbers(3, id);
		id += 1;

		cout << "Enter new Employee data:\n";

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

		cout << "Salary: ";
		getline(cin, sal);

		string ID = to_string(id);

		// Construct a string in the required format: username,password,Name,Age,PhoneNumber,Salary
		return ID + "," + username + "," + password + "," + name + "," + age + "," + phoneNumber + "," + sal;
	}
};
