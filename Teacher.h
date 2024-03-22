#pragma once
#pragma warning(disable : 4996)
#include "User.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include "Complaint.h"

using namespace std;

class Teacher : public User
{
	string Position;
	Complaint* complains;
	Complaint* tcom;
	int noOfComplaints;
	int TeacherID;
public:
	Teacher() : User()
	{
		noOfComplaints = 0;
		Position = "\0";
		TeacherID = -1;
	}
	void setTeacherID(int id)
	{
		TeacherID = id;
	}
	int getTeacherID()
	{
		return TeacherID;
	}
	void setPosition(string pos)
	{
		Position = pos;
	}
	string getPosition()
	{
		return Position;
	}
	void Display() override
	{
		User::Display();
		cout << "Position: " << Position << endl;
		cout << "No of Complaints: " << noOfComplaints << endl;
	}
	void SetterByGivenID(int Tid)
	{
		string temp = to_string(Tid);

		ifstream File("TeachersData.txt");

		if (!File.is_open())
		{
			cout << "Error in opening file" << endl;
			return;
		}
		string line;
		
		while (getline(File, line))
		{
			istringstream iss(line);

			string storedUname, storedPass, name, id, age, pNumber, pos;

			if (getline(iss, id, ',') &&
				getline(iss, storedUname, ',') &&
				getline(iss, storedPass, ',') &&
				getline(iss, name, ',') &&
				getline(iss, age, ',') &&
				getline(iss, pNumber, ',') &&
				getline(iss, pos, ','))
			{
				if (temp == id)
				{
					setTeacherID(stoi(id));
					User::SetUserName(storedUname);
					User::SetPassword(storedPass);
					User::SetName(name);
					User::SetAge(stoi(age));
					User::SetPhoneNumber(pNumber);
					setPosition(pos);

				}
			}
		}
	}
	bool ValidateUser(string uName, string pass) override
	{
		ifstream File("TeachersData.txt");

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

			string storedUname, storedPass, name, id, age, pNumber, pos;

			if (getline(iss, id, ',') &&
				getline(iss, storedUname, ',') &&
				getline(iss, storedPass, ',') &&
				getline(iss, name, ',') &&
				getline(iss, age, ',') &&
				getline(iss, pNumber, ',') &&
				getline(iss, pos, ','))
			{
				if (uName == storedUname && pass == storedPass)
				{
					User::SetUserName(storedUname);
					User::SetPassword(storedPass);
					User::SetName(name);
					User::SetAge(stoi(age));
					User::SetPhoneNumber(pNumber);
					setPosition(pos);
					setTeacherID(stoi(id));

					tid = stoi(id);

					//populateTComplaint(tid);

					return true;
				}
			}
		}

		File.close();

		return false;
	}
	void populateComplaint()
	{
		ifstream fin;
		int no = 0;
		no = getNumbers(2, no);
		tcom = new Complaint[no];
		int i = 0;
		string des;
		int comID, st, teacID, dd, dm, dy, feedback;
		char ident;

		fin.open("ComplaintData.txt");

		if (!fin.is_open())
		{
			cout << "Error in opening file" << endl;
		}
		while (!fin.eof())
		{
			fin >> comID;
			fin.ignore();

			fin >> teacID;
			fin.ignore();

			getline(fin, des, ',');

			fin >> st;
			fin.ignore();

			fin >> ident;
			fin.ignore();

			fin >> dd;
			fin.ignore();
			fin >> dm;
			fin.ignore();
			fin >> dy;
			fin.ignore();

			fin >> feedback;
			fin.ignore();

			tcom[i].setID(comID);
			tcom[i].setTeacherID(teacID);
			tcom[i].setDescription(des);
			tcom[i].setState(st);
			tcom[i].setIdentifier(ident);
			tcom[i].setDate(dd, dm, dy);
			tcom[i].setFeedback(feedback);

			i++;
		}

		fin.close();
	}
	void populateTComplaint(int id)
	{
		ifstream fin;
		string temp;
		fin.open("ComplaintData.txt");

		if (!fin.is_open())
		{
			cout << "Error in opening file123" << endl;
		}

		int ID = -1;

		while (!fin.eof())
		{
			fin.ignore();
			fin.ignore();

			fin >> ID;

			if (ID == id)
			{
				noOfComplaints++;
			}
			else
			{
			}

			getline(fin, temp, '\n');
		}
		complains = new Complaint[noOfComplaints];
		fin.close();

		fin.open("ComplaintData.txt");
		string des;
		int comID, st, teacID, dd, dm, dy, feedback;
		char ident;

		int i = 0;

		while (!fin.eof())
		{
			fin >> comID;
			fin.ignore();
			fin >> teacID;
			fin.ignore();

			if (teacID == id)
			{
				getline(fin, des, ',');

				fin >> st;
				fin.ignore();

				fin >> ident;
				fin.ignore();

				fin >> dd;
				fin.ignore();
				fin >> dm;
				fin.ignore();
				fin >> dy;
				fin.ignore();

				fin >> feedback;
				fin.ignore();

				complains[i].setID(comID);
				complains[i].setTeacherID(teacID);
				complains[i].setDescription(des);
				complains[i].setState(st);
				complains[i].setIdentifier(ident);
				complains[i].setDate(dd, dm, dy);
				complains[i].setFeedback(feedback);

				i++;
			}
			else
			{
				getline(fin, temp, '\n');
			}
		}

		fin.close();
	}
	void PerformAction(int type) override
	{
		if (type == 1)
		{
			// Register Complaint
			RegisterComplaint();
		}
		else if(type == 2)
		{
			// Feedback
			RecordFeedback();
		}
		else
		{
			return;
			// EXIT
		}
	}
	void RegisterComplaint()
	{
		string des;
		int comID, st, teacID, dd, dm, dy, feedback;
		char ident;
		comID = 0;

		comID = getNumbers(2, comID) + 1;
		setNumbers(2);
		teacID = getTeacherID();

		cout << "Enter Complaint Description: ";
		cin.ignore();
		getline(cin, des, '\n');

		st = 1;

		bool z = 1;
		while (z)
		{
			cout << "\nEnter Department ('I' for IT dept, 'A' for Admin dept,'a' for Account dept)\n=>";
			cin >> ident;

			if (ident == 'I' || ident == 'A' || ident == 'a')
			{
				z = 0;
			}

			else
			{
				z = 1;
				cout << "Invalid Input !!!" << endl;
			}
		}

		dd = dm = dy = 0;
		getDate(dd, dm, dy);

		feedback = 0;

		ofstream fout;
		fout.open("ComplaintData.txt", ios::app);

		fout << "\n" << comID << "," << teacID << "," << des << "," << st << "," << ident << "," << dd << "-" << dm << "-" << dy << "," << feedback << "\n";

		fout.close();

		//populateComplaint(getTeacherID());

		fout.open("ComplaintAssignment.txt", ios::app);
		fout << "\n" << comID << ",00-00-0000,0";
		fout.close();

		fout.open("ComplaintAssignedEmployee.txt", ios::app);
		fout << "\n" << comID << ",0";
		fout.close();
	}
	void getDate(int& dd, int& dm, int& dy)
	{
		auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		tm* currentDate = std::localtime(&currentTime);
		

		dy = currentDate->tm_year + 1900;
		dm = currentDate->tm_mon + 1;
		dd = currentDate->tm_mday;
	}
	void RecordFeedback()
	{
		populateComplaint();
		cout << "Following Are Your Complaints That Deparment Has Resolved:\n" << endl;

		int count = 0;
		int* cID;
		string* des;

		for (int i = 0; i < noOfComplaints; i++)
		{
			if (complains[i].getState() == 3)
			{
				count++;
			}
		}

		cID = new int[count];
		des = new string[count];
		count = 0;

		for (int i = 0; i < noOfComplaints; i++)
		{
			if (complains[i].getState() == 3)
			{
				cID[count] = complains[i].getID();
				des[count] = complains[i].getDescription();
				count++;
			}
		}

		if (count == 0)
		{
			cout << "\nNo Resolved Complaints\n";
		}
		else
		{
			for (int i = 0; i < count; i++)
			{
				cout << i + 1 << ". " << des[i] << "\n";
			}

			cout << "Select From Above To Record Its Feedback: ";
			int choi;
			cin >> choi;

			while (1)
			{
				if (choi<1 || choi>count)
				{
					cout << "\nWrong Input !!!" << endl;
					cout << "Enter Again: ";
					cin >> choi;
				}

				else
				{
					break;
				}
			}

			int comID;
			bool sta = 0;

			cout << "If you are Satisfied with Complaint Solution press '1' otherwise '0'\n";
			cout << "->";
			cin >> sta;

			while (1)
			{
				if (!(sta == 0 || sta == 1))
				{
					cout << "\nWrong Input !!!" << endl;
					cout << "Enter Again: ";
					cin >> sta;
				}

				else
				{
					break;
				}
			}

			if (sta == 1)
			{
				for (int i = 1; i <= choi; i++)
				{
					comID = cID[i - 1];
				}

				for (int i = 0; i < noOfComplaints; i++)
				{
					if (comID == complains[i].getID())
					{
						complains[i].setState(4);
					}
				}

				int n = 0;
				n = getNumbers(2, n);

				for (int i = 0; i < n; i++)
				{
					if (comID == tcom[i].getID())
					{
						tcom[i].setState(4);
						tcom[i].setFeedback(1);
					}
				}
			}

			int n = 0;
			n = getNumbers(2, n);
			string des;
			int compID, st, teacID, dd, dm, dy, feedback;
			char ident;

			ofstream fout;
			fout.open("ComplaintData.txt", ios::trunc);

			for (int i = 0; i < n; i++)
			{
				compID = tcom[i].getID();
				teacID = tcom[i].getTeacherID();
				des = tcom[i].getDescription();
				st = tcom[i].getState();
				ident = tcom[i].getIdentifier();
				dd = tcom[i].getday();
				dm = tcom[i].getmonth();
				dy = tcom[i].getyear();
				feedback = tcom[i].getFeedback();

				fout << compID << "," << teacID << "," << des << "," << st << "," << ident << "," << dd << "-" << dm << "-" << dy << "," << feedback << "\n";

				if (i != n - 1)
				{
					fout << "\n";
				}
				else
				{
				}
			}

			fout.close();
		}
	}
	string getUserType() const override
	{
		return "Teacher";
	}
	static User* CreateUser() // factory method
	{
		return new Teacher();
	}
};