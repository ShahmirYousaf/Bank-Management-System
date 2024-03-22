#pragma once
#include "Manager.h"
#include "Employee.h"
#include "Complaint.h"

const int MAX_COMPLAINTS = 100;
const int MAX_EMP = 50;

// FACTORY METHOD
class Department
{
	string Name;
	int DeptID;
	Manager mgr;
	Complaint* complain[MAX_COMPLAINTS];
	Employee emp[MAX_EMP];
	int numOfComplaints;
	int numOfEmployees;
public:
	Department() : numOfComplaints(0), numOfEmployees(0), DeptID(-1) {}

};