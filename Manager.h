#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include "User.h"
#include <ctime>
#include <chrono>
using namespace std;

#include "TotalNumber.h"
#include "User.h"
#include "Complaint.h"
#include "Employee.h"

class Manager : public User
{
	Complaint* complains;
	Complaint* Acomplains;
	Complaint* tcom;
	Complaint* Dcom;
	string Dept;
	int noOfComplaints;
	Employee* Emp;
public:
	Manager() : User()
	{
		Dept = "\0";
	}
	void Display() override
	{
		User::Display();
		cout << "Department: " << Dept << endl;
	}
	string getDept()
	{
		return Dept;
	}
	static User* CreateUser() // factory method
	{
		return new Manager();
	}
	void setDept(string dName)
	{
		Dept = dName;
	}
	void PerformAction(int type) override
	{
		if (type == 1)
		{
			// Assign Job
			AssignJob();
		}

		else if (type == 2)
		{
			// Review Job
			ReviewJob();
		}
	}
	void setManagerByDept(char d)
	{
		ifstream file;

		if (d == 'I')
		{
			file.open("ITManagerData.txt");
		}
		else if (d == 'a')
		{
			file.open("AccountsManagerData.txt");
		}
		else
		{
			file.open("AdminManagerData.txt");
		}

		if (!file.is_open())
		{
			cout << "Error in opening file" << endl;
			return ;
		}
		string line;

		getline(file, line);
		
		istringstream iss(line);

		string storedUname, storedPass, name, age, pNumber, deptN;

		getline(iss, storedUname, ',');
		getline(iss, storedPass, ','); 
		getline(iss, name, ',');
		getline(iss, age, ',');
		getline(iss, pNumber, ',');
		getline(iss, deptN, ',');
			
		User::SetUserName(storedUname);
		User::SetPassword(storedPass);
		User::SetName(name);
		User::SetAge(stoi(age));
		User::SetPhoneNumber(pNumber);
		setDept(deptN);

		file.close();

	}
	string getUserType() const override
	{
		return "Manager";
	}
	bool ValidateUser(string uName, string pass) override
	{
		char dept = '\0';
		cout << "Select Your Department ('I' for IT , 'A' for Admin , 'a' for Account)\n-> ";
		cin >> dept;

		while (1)
		{
			if (!(dept == 'I' || dept == 'A' || dept == 'a'))
			{
				cout << "\nWrong Input" << endl;
				cout << "Enter Again:\n-> ";
				cin >> dept;
			}
			else
			{
				break;
			}
		}

		string dName;
		if (dept == 'I')
		{
			dName = "IT";
		}
		else if (dept == 'A')
		{
			dName = "Admin";
		}
		else if (dept == 'a')
		{
			dName = "Accounts";
		}

		string fileN = dName + "ManagerData.txt";
		ifstream File(fileN);

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

			string storedUname, storedPass, name, age, pNumber, deptN;

			if (getline(iss, storedUname, ',') &&
				getline(iss, storedPass, ',') &&
				getline(iss, name, ',') &&
				getline(iss, age, ',') &&
				getline(iss, pNumber, ',') &&
				getline(iss, deptN, ','))
			{
				if (uName == storedUname && pass == storedPass)
				{
					User::SetUserName(storedUname);
					User::SetPassword(storedPass);
					User::SetName(name);
					User::SetAge(stoi(age));
					User::SetPhoneNumber(pNumber);
					setDept(deptN);

					return true;
				}
			}
		}

		return false;
	}
	void populateComplaint(string depart)
	{
		ifstream fin;
		string temp;
		fin.open("ComplaintData.txt");

		char Dep = '\0';
		char dept = '\0';

		if (depart == "IT")
		{
			dept = 'I';
		}
		else if (depart == "Admin")
		{
			dept = 'A';
		}
		else if (depart == "Accounts")
		{
			dept = 'a';
		}

		if (!fin.is_open())
		{
			cout << "Error in opening file" << endl;
		}

		while (!fin.eof())
		{
			fin.ignore();
			fin.ignore();
			fin.ignore();
			fin.ignore();
			getline(fin, temp, ',');
			fin.ignore();
			fin.ignore();

			fin >> Dep;
			fin.ignore();

			if (Dep == dept)
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

			getline(fin, des, ',');

			fin >> st;
			fin.ignore();

			fin >> ident;
			fin.ignore();

			if (ident == dept)
			{
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

		fin.open("ComplaintAssignment.txt");
		i = 0;
		int dec;
		string t;

		while (!fin.eof())
		{
			getline(fin, t, ',');
			getline(fin, t, ',');

			fin >> dec;
			complains[i].setDecision(dec);

			fin.ignore();

			i++;
		}

		fin.close();
	}
	void populateComplaintAssigneing()
	{
		ifstream fin;
		fin.open("ComplaintAssignedEmployee.txt");

		int no = 0;
		no = getNumbers(2, no);
		Acomplains = new Complaint[no];

		int cID, noe, eID;
		int i = 0;

		while (!fin.eof())
		{
			fin >> cID;
			fin.ignore();
			Acomplains[i].setID(cID);

			fin >> noe;
			Acomplains[i].setNoOfEmployees(noe);
			Acomplains[i].setEmployeeArray();

			for (int j = 0; j < noe; j++)
			{
				fin.ignore();
				fin >> eID;
				Acomplains[i].setEmployee(j, eID);
			}

			fin.ignore();

			i++;
		}

		fin.close();
	}
	void populateTComplaint()
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
	void populateDComplaint()
	{
		ifstream fin;
		int no = 0;
		no = getNumbers(2, no);
		Dcom = new Complaint[no];
		int ID, dd, dm, dy, dec;
		fin.open("ComplaintAssignment.txt");
		int i = 0;
		string temp;

		while (!fin.eof())
		{
			fin >> ID;
			fin.ignore();

			fin >> dd;
			fin.ignore();
			fin >> dm;
			fin.ignore();
			fin >> dy;
			fin.ignore();

			fin >> dec;
			fin.ignore();

			Dcom[i].setID(ID);
			Dcom[i].setAssignedDate(dd, dm, dy);
			Dcom[i].setDecision(dec);

			i++;
		}

		fin.close();
	}
	void AssignJob()
	{
		populateComplaint(Dept);
		populateComplaintAssigneing();
		populateTComplaint();
		populateDComplaint();
		cout << "Following Are New Complaints:\n" << endl;

		int count = 0;
		int* cID;
		string* des;

		for (int i = 0; i < noOfComplaints; i++)
		{
			if (complains[i].getState() == 1)
			{
				count++;
			}
		}

		cID = new int[count];
		des = new string[count];
		count = 0;

		for (int i = 0; i < noOfComplaints; i++)
		{
			if (complains[i].getState() == 1)
			{
				cID[count] = complains[i].getID();
				des[count] = complains[i].getDescription();
				count++;
			}
		}

		if (count == 0)
		{
			cout << "\nNo New Complaints\n";
		}
		else
		{
			for (int i = 0; i < count; i++)
			{
				cout << i + 1 << ". " << des[i] << "\n";
			}

			cout << "Select From Above To Assign it to Employee(s): ";
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

			for (int i = 1; i <= choi; i++)
			{
				comID = cID[i - 1];
			}

			getEmployees();

			cout << "\n\nFollowing are Employees:\n\n";

			int no = 0, choic = 0, n = 0;
			no = getNumbers(3, no);

			for (int i = 0; i < no; i++)
			{
				cout << i + 1 << ".  " << Emp[i].getName() << endl;
			}

			cout << "\nHow many Employees you want to Select:\n->  ";
			cin >> n;

			while (1)
			{
				if (n<1 || n>no)
				{
					cout << "Wrong Input !!!" << endl;
					cout << "Enter Again:\n->  ";
					cin >> n;
				}
				else
				{
					break;
				}
			}

			int counnter = 0;

			for (int i = 0; i < noOfComplaints; i++)
			{
				if (comID == complains[i].getID())
				{
					complains[i].setNoOfEmployees(n);
					complains[i].setEmployeeArray();

					counnter = i;
					break;
				}
			}

			int z = 0;
			z = getNumbers(2, z);

			for (int i = 0; i < z; i++)
			{
				if (comID == tcom[i].getID())
				{
					tcom[i].setState(2);
					break;
				}
			}

			for (int i = 0; i < z; i++)
			{
				if (comID == Dcom[i].getID())
				{
					int dd, dm, dy;
					dd = dm = dy = 0;

					getDate(dd, dm, dy);
					Dcom[i].setAssignedDate(dd, dm, dy);

					break;
				}
			}

			for (int i = 0; i < z; i++)
			{
				if (comID == Acomplains[i].getID())
				{
					Acomplains[i].setNoOfEmployees(n);
					Acomplains[i].setEmployeeArray();

					z = i;
					break;
				}
			}

			cout << "Enter Employees:" << endl;

			for (int i = 0; i < n; i++)
			{
				cout << "-> ";
				cin >> choic;

				while (1)
				{
					if (choic<1 || choic>no)
					{
						cout << "Wrong Input !!!" << endl;
						cout << "Enter Again:\n->  ";
						cin >> choic;
					}
					else
					{
						break;
					}
				}

				int empID;
				for (int j = 0; j < choic; j++)
				{
					empID = Emp[j].getID();
				}

				complains[counnter].setEmployee(i, empID);
				Acomplains[z].setEmployee(i, empID);

			}
		}

		ofstream fout;
		fout.open("ComplaintAssignedEmployee.txt", ios::trunc);

		int z = 0;
		z = getNumbers(2, z);
		int compID, noe, eID;

		for (int i = 0; i < z; i++)
		{
			compID = Acomplains[i].getID();
			noe = Acomplains[i].getNoOfEmployees();

			fout << compID << "," << noe;

			for (int j = 0; j < noe; j++)
			{
				eID = Acomplains[i].getEmployee(j);

				fout << "," << eID;
			}

			if (i != z - 1)
			{
				fout << "\n";
			}
			else
			{
			}
		}

		fout.close();

		string desc;
		int st, teacID, dd, dm, dy, feedback;
		char ident;
		fout.open("ComplaintData.txt", ios::trunc);

		for (int i = 0; i < z; i++)
		{
			compID = tcom[i].getID();
			teacID = tcom[i].getTeacherID();
			desc = tcom[i].getDescription();
			st = tcom[i].getState();
			ident = tcom[i].getIdentifier();
			dd = tcom[i].getday();
			dm = tcom[i].getmonth();
			dy = tcom[i].getyear();
			feedback = tcom[i].getFeedback();

			fout << compID << "," << teacID << "," << desc << "," << st << "," << ident << "," << dd << "-" << dm << "-" << dy << "," << feedback;

			if (i != z - 1)
			{
				fout << "\n";
			}
			else
			{
			}
		}

		fout.close();

		int dec;
		fout.open("ComplaintAssignment.txt", ios::trunc);

		for (int i = 0; i < z; i++)
		{
			compID = Dcom[i].getID();
			dd = Dcom[i].getAday();
			dm = Dcom[i].getAmonth();
			dy = Dcom[i].getAyear();
			dec = Dcom[i].getDecision();

			fout << compID << "," << dd << "-" << dm << "-" << dy << "," << dec;

			if (i != z - 1)
			{
				fout << "\n";
			}
			else
			{
			}
		}

		fout.close();
	}
	void getDate(int& dd, int& dm, int& dy) {
		auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		tm* currentDate = std::localtime(&currentTime);

		dy = currentDate->tm_year + 1900;
		dm = currentDate->tm_mon + 1;
		dd = currentDate->tm_mday;
	}
	void getEmployees()
	{
		ifstream fin;
		fin.open("EmployeeData.txt");

		int no = 0;
		no = getNumbers(3, no);
		Emp = new Employee[no];

		string eName, temp;
		int eID;
		int i = 0;

		while (!fin.eof())
		{
			fin >> eID;
			fin.ignore();

			getline(fin, temp, ',');
			getline(fin, temp, ',');

			getline(fin, eName, ',');

			getline(fin, temp, '\n');

			Emp[i].setEmployeeID(eID);
			Emp[i].SetName(eName);

			i++;
		}

		fin.close();
	}
	void ReviewJob()
	{
		populateComplaint(Dept);

		cout << "Following Are Resolved Complaints:\n" << endl;

		int count = 0;
		int* cID;
		string* des;
		ifstream fin;
		int ai, de, ad;

		for (int i = 0; i < noOfComplaints; i++)
		{
			if (complains[i].getState() == 2 && complains[i].getDecision() == 1)
			{
				count++;
			}
		}

		cID = new int[count];
		des = new string[count];
		count = 0;

		for (int i = 0; i < noOfComplaints; i++)
		{
			if (complains[i].getState() == 2 && complains[i].getDecision() == 1)
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

			cout << "\nSelect From Above To Review It: ";
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

			for (int i = 1; i <= choi; i++)
			{
				comID = cID[i - 1];
			}

			for (int i = 0; i < noOfComplaints; i++)
			{
				if (comID == complains[i].getID())
				{
					complains[i].setState(3);
					break;
				}
			}

			ofstream fout;
			string desc;
			int st, compID, teacID, dd, dm, dy, feedback;
			char ident;
			fout.open("ComplaintData.txt", ios::trunc);

			for (int i = 0; i < noOfComplaints; i++)
			{
				compID = complains[i].getID();
				teacID = complains[i].getTeacherID();
				desc = complains[i].getDescription();
				st = complains[i].getState();
				ident = complains[i].getIdentifier();
				dd = complains[i].getday();
				dm = complains[i].getmonth();
				dy = complains[i].getyear();
				feedback = complains[i].getFeedback();

				fout << compID << "," << teacID << "," << desc << "," << st << "," << ident << "," << dd << "-" << dm << "-" << dy << "," << feedback;

				if (i != noOfComplaints - 1)
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
};