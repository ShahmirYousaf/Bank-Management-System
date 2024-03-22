#pragma once
#include "IUserRemoval.h"
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

class EmployeeRemoval : public IUserRemoval
{
public:
	void RemoveUser() override
	{
		int Tid;
		string name;

		cout << "Enter ID: ";
		cin >> Tid;

		cout << "\nEnter User-Name: ";
		cin >> name;

		string existingData = readFromFile();

		size_t pos = findEmployee(existingData, Tid, name);

		if (pos != string::npos)
		{
			// removing the record that is found
			existingData.erase(pos, getRecordLength(existingData, pos));

			// now we have to update the IDs

			updateEmployeeIDs(existingData, Tid);

			// writing updated data back
			writeToFile(existingData);

			cout << "Employee Removed Successfully" << endl;
		}
		else
		{
			cout << "Employee not found" << endl;
		}
	}
private:
	string readFromFile()
	{
		ifstream file("EmployeeData.txt");
		string data;

		if (file.is_open())
		{
			data.assign((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
			file.close();
		}

		return data;
	}
	void writeToFile(const string& data)
	{
		ofstream file("EmployeeData.txt");

		if (file.is_open())
		{
			file << data;

			file.close();
		}
	}
	size_t findEmployee(const string& data, int empID, const string& uName)
	{
		istringstream iss(data);
		string line;

		while (getline(iss, line))
		{
			istringstream record(line);
			int currentID;
			string currName;

			record >> currentID;
			record.ignore();
			getline(record, currName, ',');

			if (currentID == empID && currName == uName)
			{
				return static_cast<size_t>(iss.tellg()) - line.length() - 1;
			}
		}

		return string::npos;

	}
	size_t getRecordLength(const string& data, size_t pos)
	{
		size_t newLinePos = data.find('\n', pos);

		if (newLinePos == string::npos)
		{
			return data.length() - pos;
		}

		return newLinePos - pos + 1;
	}
	void updateEmployeeIDs(string& data, int remEmpID)
	{
		istringstream iss(data);
		ostringstream oss;
		string line;

		while (getline(iss, line))
		{
			istringstream record(line);

			int currID;

			record >> currID;

			if (currID > remEmpID) 
			{
				string updatedLine = to_string(currID - 1) + line.substr(line.find(','));
				oss << updatedLine << '\n';
			}
			else
			{
				oss << line << '\n';
			}
		}

		data = oss.str();
	}
};
