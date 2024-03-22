#pragma once
#include "Complaint.h"

class IReportGenerator
{
public:
	virtual void GenerateReport(Complaint cmp[]) = 0;
	virtual ~IReportGenerator() = default;
};
