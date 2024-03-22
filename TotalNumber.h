#pragma once
#include <iostream>
#include <fstream>

using namespace std;

int getNumbers(int Type, int number)
{
	ifstream fin;
	fin.open("Count.txt");

	if (!fin.is_open())
	{
		cout << "Error in opening file" << endl;
	}

	if (Type == 1)           // For Teacher
	{
		fin >> number;
	}

	else if (Type == 2)     // For Complaint
	{
		fin.ignore();
		fin.ignore();
		fin >> number;
	}

	else if (Type == 3)     // For Employee
	{
		fin.ignore();
		fin.ignore();
		fin.ignore();
		fin >> number;
	}

	else
	{
		//
	}

	fin.close();

	return number;
}
void setNumbers(int Type)
{
	int no = 0, no1 = 0, no2 = 0;

	if (Type == 1)
	{
		// "no" for Teacher, "no1" for Complaint, "no2" for Employee

		no = getNumbers(1, no) + 1;
		no1 = getNumbers(2, no1);
		no2 = getNumbers(3, no2);

		ofstream fout;
		fout.open("Count.txt", ios::trunc);

		fout << no << "\n" << no1 << "\n" << no2;

		fout.close();
	}

	else if (Type == 2)
	{
		// "no" for Compaint, "no1" for Teacher, "no2" for Employee

		no = getNumbers(2, no) + 1;
		no1 = getNumbers(1, no1);
		no2 = getNumbers(3, no2);

		ofstream fout;
		fout.open("Count.txt", ios::trunc);

		fout << no1 << "\n" << no << "\n" << no2;

		fout.close();
	}

	else if (Type == 3)
	{
		// "no" for Employee, "no1" for Teacher, "no2" for Complaint

		no = getNumbers(3, no) + 1;
		no1 = getNumbers(1, no1);
		no2 = getNumbers(2, no2);

		ofstream fout;
		fout.open("Count.txt", ios::trunc);

		fout << no1 << "\n" << no2 << "\n" << no;

		fout.close();
	}
}