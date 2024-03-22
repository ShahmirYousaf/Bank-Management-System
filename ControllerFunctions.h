#pragma once
#include <Windows.h>
#include <conio.h>
#include <string>
#include <iomanip>
#include <iostream>
#include "Complaint.h"

using namespace std;

void ClearScreen()
{
	system("CLS");
}
void pushX(int num)
{
	for (int i = 0; i < num; i++)
		cout << " ";
}
void StartingUI()
{
	cout << "Press (1) for Teacher's Interface" << endl;
	cout << "Press (2) for Employee's Interface" << endl;
	cout << "Press (3) for Director's Interface" << endl;
	cout << "Press (4) for Admin's Interface" << endl;
	cout << "Press (5) for Manager's Interface" << endl;
	cout << "Press (6) for Exiting the system" << endl;
	cout << "Enter your option: " << endl;
}
int InputValidator(int opt)
{
	while (opt < 1 || opt > 6)
	{
		cout << "Invalid option !!! ERROR !!!" << endl;
		cout << "Enter your option again: " << endl;
		cin >> opt;
	}

	return opt;
}
void TeacherUI()
{
	cout << "\nPress(1) to Register a complaint or request any service" << endl;
	cout << "Press(2) to Record feedback about resolved complaint" << endl;
	cout << "Press(3) to Exit" << endl;
	cout << "Enter your option: " << endl;

}
int TeacherInputValidator(int opt)
{
	while (!(opt == 1 || opt == 2 || opt == 3))
	{
		cout << "Invalid option !!! ERROR !!!" << endl;
		cout << "Enter your option again: " << endl;
		cin >> opt;
	}
	return opt;

}
void DirectorUI()
{
	cout << "\nPress(1) to View complaint summarry within given dates" << endl;
	cout << "Press(2) to Search about specific complaint" << endl;
	cout << "Press(3) to Exit" << endl;
	cout << "Enter your option: " << endl;
}
int DirectorInputValidator(int opt)
{
	while (!(opt == 1 || opt == 2 || opt == 3))
	{
		cout << "Invalid option !!! ERROR !!!" << endl;
		cout << "Enter your option again: " << endl;
		cin >> opt;
	}
	return opt;

}
void ManagerUI()
{
	cout << "\nPress(1) to Assign job to employee(s)" << endl;
	cout << "Press(2) to Review job done by employee" << endl;
	cout << "Press(3) to Exit" << endl;
	cout << "Enter your option: " << endl;

}
int ManagerInputValidator(int opt)
{
	while (!(opt == 1 || opt == 2 || opt == 3))
	{
		cout << "Invalid option !!! ERROR !!!" << endl;
		cout << "Enter your option again: " << endl;
		cin >> opt;
	}
	return opt;

}
int EmployeeInputValidator(int opt)
{
	while (!(opt == 1 || opt == 2))
	{
		cout << "Invalid option !!! ERROR !!!" << endl;
		cout << "Enter your option again: " << endl;
		cin >> opt;
	}

	return opt;
}
void EmployeeUI()
{
	cout << "\nPress(1) To complete job" << endl;
	cout << "Press(2) To exit" << endl;
	cout << "Enter your option: " << endl;
}
void WelcomeUI()
{
	for (int j = 0; j < 40; j++)
	{
		ClearScreen();
		pushX(j);
		cout << "------------------------------------------------------" << endl;
		pushX(j);
		cout << "------Welcome to the Complaint Management System------" << endl;
		pushX(j);
		cout << "------------------------------------------------------" << endl;
		Sleep(80);
	}
}
void ErrorMessage()
{
	cout << "Wrong Credentials entered!!" << endl;
	cout << "you have to LOG IN again" << endl;
	Sleep(2500);
}
void AdminUI()
{
	cout << "\nPress(1) for Adding a Teacher" << endl;
	cout << "Press(2) for Adding an Employee" << endl;
	cout << "Press(3) for Adding a Manager" << endl;
	cout << "Press(4) for Removing a Teacher" << endl;
	cout << "Press(5) for Removing an Employee" << endl;
	cout << "Press(6) for Removing a Manager" << endl;
	cout << "Press(7) to Exit" << endl;
	cout << "Enter your option: " << endl;
}
int AdminInputValidator(int opt)
{
	while (opt < 0 || opt > 7)
	{
		cout << "Invalid option !!! ERROR !!!" << endl;
		cout << "Enter your option again: " << endl;
		cin >> opt;
	}

	return opt;
}
string getAssignedDate(int cID)
{
	ifstream file("ComplaintAssignment.txt");

	if (!file.is_open())
	{
		cout << "Error in opening file!!" << endl;
		return "\0";
	}

	string line;

	while (getline(file, line))
	{
		istringstream ss(line);
		string Adate = "\0";
		int id, no2;
		char comma;

		ss >> id >> comma
			>> Adate >> comma
			>> no2;

		if (cID == id)
		{
			return Adate;
		}
	}

	file.close();

	return "\0";
}
void convertDate(const string& dateString, int& day, int& month, int& year)
{
	istringstream ss(dateString);

	char dash;  // to read and discard the dashes

	// Read day, month, and year from the string
	ss >> day >> dash >> month >> dash >> year;
}
void readComplaintsFromFile(Complaint cmp[], int& noOfComplaint)
{
	ifstream file("ComplaintData.txt");

	if (!file.is_open())
	{
		cout << "Error in opening file!!" << endl;
		return;
	}

	string line;
	
	while (getline(file, line))
	{
		istringstream ss(line);
		char delimeter, dept;
		int Cid, Tid, st, day, month, year, fback, aDay = -1, aMonth= -1, aYear= -1;
		string desc, AssignmentDate;

		ss >> Cid >> delimeter
			>> Tid >> delimeter;
		char ch;
		while (ss.get(ch) && ch != ',')
		{
			desc += ch;
		}
			
		ss >> st >> delimeter
		>> dept >> delimeter
		>> day >> delimeter
		>> month >> delimeter
		>> year >> delimeter
			>> fback;

		AssignmentDate = getAssignedDate(Cid);

		if (AssignmentDate != "\0")
		{
			convertDate(AssignmentDate, aDay, aMonth, aYear);
		}

		cmp[noOfComplaint++].Setter(Cid, st, desc, dept, day, month, year, Tid,fback, aDay, aMonth, aYear);
	}
	file.close();
}
void CountITComplains(Complaint cmp[])
{
	int count = 0;
	
	for (int i = 0; cmp[i].getID() != -1; i++)
	{
		if (cmp[i].getIdentifier() == 'I')
		{
			cmp[i].PrintStatusAndId();
			count++;
		}
	}

	cout << "Number of Complaints of IT Department are: " << count << endl;
}
void CountAdminComplains(Complaint cmp[])
{
	int count = 0;

	for (int i = 0; cmp[i].getID() != -1; i++)
	{
		if (cmp[i].getIdentifier() == 'A')
		{
			cmp[i].PrintStatusAndId();
			count++;
		}
	}

	cout << "Number of Complaints of Admin Department are: " << count << endl;
}
void CountAccountComplains(Complaint cmp[])
{
	int count= 0;

	for (int i = 0; cmp[i].getID() != -1; i++)
	{
		if (cmp[i].getIdentifier() == 'a')
		{
			cmp[i].PrintStatusAndId();
			count++;
		}
	}

	cout << "Number of Complaints of Accounts Department are: " << count << endl;
}
void EmpSetterByCiD(Employee emp[], int cID)
{
	int idx = 0;

	ifstream file("ComplaintAssignedEmployee.txt");

	if (!file.is_open())
	{
		cout << "Error in opening file!!" << endl;
		return;
	}

	string line;

	while (getline(file, line))
	{
		istringstream iss(line);
		int number1, number2, number3;

		iss >> number1;

		if (number1 == cID)
		{
			char comma;
			iss >> comma;
			iss >> number3;
			iss >> comma;
			while (iss >> number2)
			{
				iss >> comma;

				if (number2 != 0)
				{
					emp[idx++].SetterByID(number2);
				}
				
			}
		}
	}

	file.close();
}