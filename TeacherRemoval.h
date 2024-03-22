#pragma once
#include "IUserRemoval.h"
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

class TeacherRemoval : public IUserRemoval
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

		size_t pos = findTeacher(existingData, Tid, name);

		if (pos != string::npos)
		{
			// removing the record that is found
			existingData.erase(pos, getRecordLength(existingData, pos));

			// now we have to update the IDs

			updateTeacherIDs(existingData, Tid);

			// writing updated data back
			writeToFile(existingData);

			cout << "Teacher Removed Successfully" << endl;
		}
		else
		{
			cout << "Teacher not found" << endl;
		}
	}
private:
	string readFromFile()
	{
		ifstream file("TeachersData.txt");
		string data;

		if (file.is_open())
		{
			// Reading entire content of file into string data

			data.assign((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
			file.close();
		}
		return data;
	}
	void writeToFile(const string& data)
	{
		ofstream file("TeachersData.txt");

		if (file.is_open())
		{
			file << data;
			file.close();
		}
	}
	size_t findTeacher(const string& data, int teacherID, const string& name)
	{
		istringstream iss(data);
		string line;

		while (getline(iss, line))
		{
			istringstream record(line);
			int currentID;
			string currName;

			// the format of record is: teacherID,username,pass,name,age,pNumber,position
			record >> currentID;
			record.ignore(); // ignoring comma
			getline(record, currName, ',');

			// check if record matches
			if (currentID == teacherID && currName == name)
			{
				return static_cast<size_t>(iss.tellg()) - line.length() - 1;
			}
		}

		return string::npos;
	}
	size_t getRecordLength(const string& data, size_t pos)
	{
		// finding length of record starting from provided position
		size_t newLinePos = data.find('\n', pos);

		if (newLinePos == string::npos)
		{
			return data.length() - pos;
		}

		return newLinePos - pos + 1;
	}
	void updateTeacherIDs(string& data, int removedID)
	{
		istringstream iss(data);
		ostringstream oss;
		string line;

		while (getline(iss, line))
		{
			istringstream record(line);
			int currentID;
			record >> currentID;

			//Updating IDs after the removed one
			if (currentID > removedID)
			{
				string updatedLine = to_string(currentID - 1) + line.substr(line.find(','));
				oss << updatedLine << '\n';
			}
			else
			{
				oss << line << '\n';
			}
		}
		data = oss.str(); // updating original data
	}
};
