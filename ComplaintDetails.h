#pragma once
#include "Report.h"
#include "Complaint.h"
#include "ControllerFunctions.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <chrono>
#include "Teacher.h"
#include "Manager.h"
#include "Employee.h"

class ComplaintDetails : public IReportGenerator
{
public:
	void GenerateReport(Complaint cmp[]) override
	{
		int ID;

		cout << "Enter Complaint ID of the complaint you want to search for: ";
		cin >> ID;

		int numComplaints = 0;
		readComplaintsFromFile(cmp, numComplaints);

		bool found = false;

		for (int i = 0; i < numComplaints; i++)
		{
			if (cmp[i].getID() == ID)
			{
				cmp[i].SpecificDeatails();

				Teacher t1;

				t1.SetterByGivenID(cmp[i].getTeacherID());
				cout << "Teacher Name: " << t1.getName() << endl;

				Manager m1;

				m1.setManagerByDept(cmp[i].getIdentifier());
				cout << "\nManager Name: " << m1.getName() << endl;
				cout << "Department Name: " << m1.getDept() << endl;
				
				if (cmp[i].getAyear() != -1)
				{
					cout << "Assignment Date: ";
					cmp[i].PrintAdate();
					Employee E1[10];

					EmpSetterByCiD(E1, cmp[i].getID());

					for (int i = 0; E1[i].getID() != -1; i++)
					{
						cout << "\nEmployee " << i + 1 << " Details: " << endl;
						cout << E1[i].getName() << endl;
					}
					cout << endl;
				}
				else
				{
					cout << "No Employee has been assigned this complaint till yet." << endl;
				}
				Sleep(2000);

				found = true;

				break;
				// EMPLOYEE AND JOB ASSIGNMENT NEEDED TO BE PRINTED
			}
		}
		if (!found)
		{
			cout << "Complaint Not Found !!" << endl;
		}


	}
};

