#pragma once
#include "Report.h"
#include "Complaint.h"
#include "ControllerFunctions.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <chrono>
#include "Date.h"

class SummaryGenerator : public IReportGenerator
{
public:
	void GenerateReport(Complaint complaints[]) override
	{
        int numComplaints = 0;
		readComplaintsFromFile(complaints, numComplaints);

        string sDate, eDate;

        cout << "Enter Start Date (eg, dd-mm-yyyy): ";
        cin >> sDate;

        cout << "Enter End Date (eg, dd-mm-yyyy): ";
        cin >> eDate;

        cout << "Summary of Complaints filed between " << sDate << " and " << eDate << ":\n";

        for (int i = 0; i < numComplaints; i++) 
        {

            int d1, m1, y1, d2, m2, y2;

            convertDate(sDate, d1, m1, y1);
            convertDate(eDate, d2, m2, y2);

            Date start(d1, m1, y1);
            Date end(d2, m2, y2);

            if (complaints[i].getDate() >= start && complaints[i].getDate() <= end)
            {
                complaints[i].Display();
                Sleep(2000);
            }
        }

        cout << endl;
        CountITComplains(complaints);
        Sleep(2100);
        CountAdminComplains(complaints);
        Sleep(2100);
        CountAccountComplains(complaints);
        Sleep(2500);

	}
};
