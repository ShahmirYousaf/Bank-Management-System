#pragma once
#include "Department.h"

class Admin : public Department
{
public:
	Admin() : Department()
	{
		//
	}
	static Department* CreateInstance()
	{
		return new Admin();
	}
};
