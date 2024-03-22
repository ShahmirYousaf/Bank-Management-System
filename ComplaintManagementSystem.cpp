// PROJECT BY
// MUHAMMAD SHAHMIR YOUSAF (21L-5259) & MURTAZA AHMED (21L-5173)
// 5J

#include <iostream>
#include <cstring>
#include <windows.graphics.h>
#include <string>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <Windows.h>
#include <conio.h>

// System Controller Class Header
#include "system.h"

//function header
#include "ControllerFunctions.h"

using namespace std;

int main()
{
	System* CMS = System::getInstance(5);

	WelcomeUI();
	
	int option = -1;

	do
	{
		ClearScreen(); 
		StartingUI();
		string Uname, Pass;
		bool isValid;
		int var;
		cin >> option;
		if (option < 1 || option > 6)
		{
			option = InputValidator(option);  // Validation Check
		}

		if (option != 6)
		{
			cout << "\nPlease Enter your Credentials to Log-In" << endl;
			cout << "\nEnter User Name: ";
			cin >> Uname;
			cout << "Enter Password: ";
			cin >> Pass;
			cout << endl;
		}

		if (option == 1) // teacher
		{
			ClearScreen();

			isValid = CMS->RunValidation(option-1, Uname, Pass);
		
			if (isValid)
			{

				while (1)
				{
					TeacherUI();

					cin >> var;
					var = TeacherInputValidator(var);

					if (var == 1 || var == 2)
					{
						CMS->RunSystem(option-1, var);
					}
					else if (var == 3)
					{
						break;
					}
				}
			}
			else
			{
				ErrorMessage();
			}
		}
		else if (option == 2) // employee
		{
			ClearScreen();

			isValid = CMS->RunValidation(option-1, Uname, Pass);

			if (isValid)
			{
				while (1)
				{
					EmployeeUI();

					cin >> var;

					var = EmployeeInputValidator(var);

					if (var != 2)
					{
						CMS->RunSystem(option - 1, var);
					}
					else
					{
						break;
					}
				}

			}
			else
			{
				ErrorMessage();
			}

		}
		else if (option == 3) // director
		{
			ClearScreen();

			isValid = CMS->RunValidation(option - 1, Uname, Pass);

			if (isValid)
			{
				while (1)
				{
					DirectorUI();

					cin >> var;

					var = DirectorInputValidator(var);
					if (var != 3)
					{
						CMS->RunSystem(option - 1, var);
						//Sleep(500);
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				ErrorMessage();
			}
		}
		else if (option == 4) // administrator
		{
			ClearScreen();

			isValid = CMS->RunValidation(option-1, Uname, Pass);

			if (isValid)
			{
				while (1)
				{
					AdminUI();
					cin >> var;

					var = AdminInputValidator(var);

					if (var != 7)
					{
						CMS->RunSystem(option - 1, var);
						//Sleep(1000);
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				ErrorMessage();
			}
		}
		else if (option == 5) // manager
		{
			ClearScreen();

			isValid = CMS->RunValidation(option - 1, Uname, Pass);

			if (isValid)
			{
				while (1)
				{
					ManagerUI();
					cin >> var;

					var = ManagerInputValidator(var);

					if (var != 3)
					{
						CMS->RunSystem(option - 1, var);
						//Sleep(1000);
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				ErrorMessage();
			}
		}
		else if(option == 6)
		{
			cout << "!!! THANK YOU FOR USING COMPLAINT MANAGEMENT SYSTEM !!!" << endl;
			delete CMS;
			break;
		}

	} while (option != 6);

	return 0;
}