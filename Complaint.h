#pragma once
#include <iostream>
#include "Date.h"
#include "User.h"
#include "Employee.h"

using namespace std;

class Complaint
{
	// STATE PATTERN
	enum class State { NEW, ASSIGNED, RESOLVED, CLOSED };

	int ComplainID;
	State state;
	string Description;
	char Identifier; // "I" for IT dept, "A" for Admin and "a" for Account
	int TeacherID;
	bool Feedback; // "0" for unsatisfied and "1" for satisfied
	int Decision;
	int noOfEmployees;
	Date AssignedDate;
	Date date;
	Employee* Emp;
	string stateToString(State s)
	{
		switch (s)
		{
		case State::NEW: return "NEW";
		case State::ASSIGNED: return "ASSIGNED";
		case State::RESOLVED: return "RESOLVED";
		case State::CLOSED: return "CLOSED";
		}
	}
public:
	Complaint()
	{
		ComplainID = -1;
		Description = "\0";
		state = State::NEW;
		Identifier = '\0';
		TeacherID = -1;
		Feedback = 0;
		noOfEmployees = 0;
		Decision = 0;
	}

	Complaint(int id, string& desc, char identifier, Date& d, int Tid, bool feedback, int emp, int dec, Date& aD) : ComplainID(id), Identifier(identifier), date(d), TeacherID(Tid), Feedback(feedback)
	{
		AssignedDate = aD;
		Decision = dec;
		noOfEmployees = emp;
		state = State::NEW;
	}

	void Setter(int id, int st, string& desc, char identifier, int day, int mon, int y, int Tid, int feedback, int aDay, int aMon, int aYear)
	{
		setID(id);
		setState(st);
		setDescription(desc);
		setIdentifier(identifier);
		setDate(day, mon, y);
		setTeacherID(Tid);
		setFeedback(feedback);
		setAssignedDate(aDay, aMon, aYear);
	}

	void Display()
	{
		cout << "\nComplaintID: " << ComplainID << endl;
		cout << "TeacherID: " << TeacherID << endl;
		cout << "Description: " << Description << endl;
		cout << "State: " << stateToString(state) << endl;
		cout << "Date: " << date.getDay() << "-" << date.getMonth() << "-" << date.getYear() << endl;
		cout << "Feedback: " << Feedback << endl;
	}

	void PrintAdate()
	{
		cout << "Date: " << getAday() << "-" << getAmonth() << "-" << getAyear() << endl;
	}

	void SpecificDeatails()
	{
		cout << "\nComplaintID: " << ComplainID << endl;
		cout << "Description: " << Description << endl;
		cout << "State: " << stateToString(state) << endl;
		cout << "Date: " << date.getDay() << "-" << date.getMonth() << "-" << date.getYear() << endl;
	}

	void PrintStatusAndId()
	{
		cout << "Complaint ID: " << ComplainID << endl;
		cout << "State: " << stateToString(state) << endl;
	}

	void setID(int id)
	{
		ComplainID = id;
	}

	void setFeedback(bool f)
	{
		Feedback = f;
	}
	void setState(int st)
	{
		if (st == 1)
		{
			state = State::NEW;
		}

		else if (st == 2)
		{
			state = State::ASSIGNED;
		}

		else if (st == 3)
		{
			state = State::RESOLVED;
		}

		else if (st == 4)
		{
			state = State::CLOSED;
		}
	}
	void setDescription(string des)
	{
		Description = des;
	}
	void setIdentifier(char iden)
	{
		Identifier = iden;
	}
	void setTeacherID(int id)
	{
		TeacherID = id;
	}
	void setDate(int d, int m, int y)
	{
		date.setDay(d);
		date.setMonth(m);
		date.setYear(y);
	}
	void setAssignedDate(int d, int m, int y)
	{
		AssignedDate.setDay(d);
		AssignedDate.setMonth(m);
		AssignedDate.setYear(y);
	}
	void setDecision(int n)
	{
		Decision = n;
	}
	void setNoOfEmployees(int no)
	{
		noOfEmployees = no;
	}
	void setEmployeeArray()
	{
		Emp = new Employee[noOfEmployees];
	}
	void setEmployee(int idx, int id)
	{
		Emp[idx].setEmployeeID(id);
	}
	int getID()
	{
		return ComplainID;
	}
	char getIdentifier()
	{
		return Identifier;
	}
	int getTeacherID()
	{
		return TeacherID;
	}
	string getDescription()
	{
		return Description;
	}
	int getState()
	{
		if (state == State::NEW)
		{
			return 1;
		}

		else if (state == State::ASSIGNED)
		{
			return 2;
		}

		else if (state == State::RESOLVED)
		{
			return 3;
		}

		else if (state == State::CLOSED)
		{
			return 4;
		}
	}
	int getday()
	{
		return date.getDay();
	}
	int getmonth()
	{
		return date.getMonth();
	}
	int getyear()
	{
		return date.getYear();
	}
	bool getFeedback()
	{
		return Feedback;
	}
	int getAday()
	{
		return AssignedDate.getDay();
	}
	int getAmonth()
	{
		return AssignedDate.getMonth();
	}
	int getAyear()
	{
		return AssignedDate.getYear();
	}
	int getDecision()
	{
		return Decision;
	}
	int getNoOfEmployees()
	{
		return noOfEmployees;
	}
	int getEmployee(int idx)
	{
		return Emp[idx].getID();
	}
	Date getDate()
	{
		return date;
	}
};