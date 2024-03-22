#pragma once

class Date
{
	int day;
	int month;
	int year;
public:
	Date()
	{
		day = -1;
		month = -1;
		year = -1;
	}
	Date(int D, int M, int Y)
	{
		day = D;
		month = M;
		year = Y;
	}
	void setDay(int d)
	{
		day = d;
	}
	void setMonth(int m)
	{
		month = m;
	}
	void setYear(int y)
	{
		year = y;
	}
	int getDay()
	{
		return day;
	}
	int getMonth()
	{
		return month;
	}
	int getYear()
	{
		return year;
	}
	// Comparison operators
	bool operator==(const Date& other) const
	{
		return (year == other.year) && (month == other.month) && (day == other.day);
	}

	bool operator!=(const Date& other) const
	{
		return !(*this == other);
	}

	bool operator<(const Date& other) const
	{
		if (year != other.year)
			return year < other.year;
		if (month != other.month)
			return month < other.month;
		return day < other.day;
	}

	bool operator>(const Date& other) const
	{
		return other < *this;
	}

	bool operator<=(const Date& other) const
	{
		return !(other < *this);
	}

	bool operator>=(const Date& other) const
	{
		return !(*this < other);
	}
};
