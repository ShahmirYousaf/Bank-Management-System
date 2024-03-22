#pragma once
#include "User.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "TotalNumber.h"

using namespace std;

class Employee : public User
{
	int salary;
	int EmployeeID;
	int* EmployeeComplaints;
	int* cID, * DD, * DM, * DY, * Dec;
	int noOfEcomplaints;
public:
	Employee() : User()
	{
		EmployeeID = -1;
		salary = -1;
		noOfEcomplaints = 0;
	}
	static User* CreateUser() // factory method
	{
		return new Employee();
	}
	int getID()
	{
		return EmployeeID;
	}
	void PerformAction(int type) override
	{
		if (type == 1)
		{
			CompleteJob();
		}
		else
		{
			return;
		}
	}
	void Display() override
	{
		User::Display();
		cout << "Employee ID: " << EmployeeID <<  endl;
		cout << "Salary: " << salary << endl;
	}
	string getUserType() const override
	{
		return "Employee";
	}
	void setEmployeeID(int id)
	{
		EmployeeID = id;
	}
	int getSalary()
	{
		return salary;
	}
	void setSalary(int s)
	{
		salary = s;
	}
	bool ValidateUser(string uName, string pass) override
	{
		ifstream File("EmployeeData.txt");

		if (!File.is_open())
		{
			cout << "Error in opening file" << endl;
			return false;
		}

		string line;

		while (getline(File, line))
		{
			istringstream iss(line);

			string storedUname, storedPass, name, age, pNumber, sal, id;

			if (getline(iss, id, ',') &&
				getline(iss, storedUname, ',') &&
				getline(iss, storedPass, ',') &&
				getline(iss, name, ',') &&
				getline(iss, age, ',') &&
				getline(iss, pNumber, ',') &&
				getline(iss, sal, ','))
			{
				if (uName == storedUname && pass == storedPass)
				{
					User::SetUserName(storedUname);
					User::SetPassword(storedPass);
					User::SetName(name);
					User::SetAge(stoi(age));
					User::SetPhoneNumber(pNumber);
					setSalary(stoi(sal));
					setEmployeeID(stoi(id));

					populateEComplaint(EmployeeID);

					return true;
				}
			}
		}
		return false;
	}
	void SetterByID(int Eid)
	{
		ifstream file("EmployeeData.txt");

		if (!file.is_open())
		{
			cout << "Error in opening file" << endl;
			return;
		}

		string line;

		while (getline(file, line))
		{
			istringstream iss(line);

			string storedUname, storedPass, name, age, pNumber, sal, id;

			if (getline(iss, id, ',') &&
				getline(iss, storedUname, ',') &&
				getline(iss, storedPass, ',') &&
				getline(iss, name, ',') &&
				getline(iss, age, ',') &&
				getline(iss, pNumber, ',') &&
				getline(iss, sal, ','))
			{
				if (stoi(id) == Eid)
				{
					User::SetUserName(storedUname);
					User::SetPassword(storedPass);
					User::SetName(name);
					User::SetAge(stoi(age));
					User::SetPhoneNumber(pNumber);
					setSalary(stoi(sal));
					setEmployeeID(stoi(id));
				}
			}
		}

	}
	void populateEComplaint(int EID)
	{
		int comID, noe, empID;
		string temp;
		ifstream fin;
		fin.open("ComplaintAssignedEmployee.txt");

		while (!fin.eof())
		{
			fin >> comID;
			fin.ignore();

			fin >> noe;

			for (int j = 0; j < noe; j++)
			{
				fin.ignore();
				fin >> empID;

				if (empID == EID)
				{
					noOfEcomplaints++;
				}
			}

			fin.ignore();
		}

		fin.close();

		EmployeeComplaints = new int[noOfEcomplaints];
		fin.open("ComplaintAssignedEmployee.txt");
		int i = 0;

		while (!fin.eof())
		{
			fin >> comID;
			fin.ignore();

			fin >> noe;

			for (int j = 0; j < noe; j++)
			{
				fin.ignore();
				fin >> empID;

				if (empID == EID)
				{
					EmployeeComplaints[i] = comID;
					i++;
				}
			}
		}
		fin.close();
	}
	void CompleteJob()
	{
		int z = 1;
		ifstream fin;
		cout << "\nFollowing are Your Pending Complaints: ";

		if (noOfEcomplaints == 0)
		{
			cout << "\nNo Pending Complaints";
			//return;
		}
		else
		{
			for (int i = 0; i < noOfEcomplaints; i++)
			{
				fin.open("ComplaintData.txt");
				int comID;
				string des, temp;

				while (!fin.eof())
				{
					fin >> comID;
					fin.ignore();
					fin.ignore();
					fin.ignore();
					getline(fin, des, ',');

					if (comID == EmployeeComplaints[i])
					{
						cout << "\n" << z << ". " << des;
						z++;
					}
					else
					{
					}

					getline(fin, temp, '\n');
				}

				fin.close();
			}
			int zd = 0;
			cout << "\n\nSelect From Above: ";
			cin >> zd;

			while (1)
			{
				if (zd<1 || zd>z - 1)
				{
					cout << "\nWrong Input !!!" << endl;
					cout << "Enter Again: ";
					cin >> zd;
				}
				else
				{
					break;
				}
			}

			int SelectedID = 0;

			for (int i = 1; i < zd; i++)
			{
				SelectedID = EmployeeComplaints[i - 1];
			}

			setComplaintAssignment(SelectedID);
		}

		
	}
	void setComplaintAssignment(int SelectedID)
	{
		int no = 0;
		no = getNumbers(2, no);
		cID = new int[no];
		DD = new int[no];
		DM = new int[no];
		DY = new int[no];
		Dec = new int[no];
		int comID, dd, dm, dy, dec, i = 0;

		ifstream fin;
		fin.open("ComplaintAssignment.txt");

		while (!fin.eof())
		{
			fin >> comID;
			fin.ignore();

			fin >> dd;
			fin.ignore();
			fin >> dm;
			fin.ignore();
			fin >> dy;
			fin.ignore();

			fin >> dec;
			fin.ignore();

			if (comID == SelectedID)
			{
				dec = 1;
			}
			else
			{
			}

			cID[i] = comID;
			DD[i] = dd;
			DM[i] = dm;
			DY[i] = dy;
			Dec[i] = dec;

			i++;
		}

		fin.close();

		ofstream fout;
		fout.open("ComplaintAssignment.txt", ios::trunc);

		for (int j = 0; j < no; j++)
		{
			comID = cID[j];
			dd = DD[j];
			dm = DM[j];
			dy = DY[j];
			dec = Dec[j];

			fout << comID << "," << dd << "-" << dm << "-" << dy << "," << dec;

			if (!(j == no - 1))
			{
				fout << "\n";
			}
			else
			{
			}
		}

		fout.close();
	}
};