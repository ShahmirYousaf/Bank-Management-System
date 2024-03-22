#pragma once

#include "Department.h"

class Account : public Department
{
public:
	Account() : Department()
	{

	}
	static Department* CreateInstance()
	{
		return new Account();
	}
};