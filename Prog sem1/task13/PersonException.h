#pragma once
#include <exception>

class PersonException : public std::exception
{
public:
	const char* Error(const char*);
};


