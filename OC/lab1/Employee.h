#pragma once
#include <string>
#include <string.h>

struct Employee
{
	int m_id = 0;
	char m_name[11] = { 0 };
	double m_hours = 0.0;

	Employee(int id = 0, const std::string& name = "", double hours = 0.0)
		: m_id(id), m_hours(hours)
	{
		strcpy_s(m_name, 10, name.data());
	}
};
