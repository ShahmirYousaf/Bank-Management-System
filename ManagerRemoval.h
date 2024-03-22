#pragma once
#include "IUserRemoval.h"
#include <sstream>
#include <fstream>
#include <string>

class ManagerRemoval : public IUserRemoval
{
public:
	void RemoveUser() override
	{
		string deptN;

		cout << "Which Department Manager you want to remove: ";
		cin >> deptN;

		string fileN = getFileName(deptN);

		string existingData = readFromFile(fileN);

		if (existingData.empty())
		{
			cout << "ERROR: No Manager found for this department" << endl;
		}
		else
		{
			existingData.clear();

			writeToFile(existingData, fileN);

			cout << "Manager removed succesfully" << endl;
		}
	}
private:
	string readFromFile(const string& fName)
	{
		ifstream file(fName);
		string data;

		if (file.is_open())
		{
			data.assign((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
			file.close();
		}

		return data;
	}
	void writeToFile(const string& data, const string& fName)
	{
		ofstream file(fName);

		if (file.is_open())
		{
			file << data;
			file.close();
		}
	}
	string getFileName(const string& deptName)
	{
		return deptName + "ManagerData.txt";
	}


};