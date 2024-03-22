#pragma once

#include "Department.h"

class InformationTechnology : public Department
{
public:
	InformationTechnology() : Department()
	{

	}
	static Department* CreateInstance()
	{
		return new InformationTechnology();
	}
};
