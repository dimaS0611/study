#pragma once
#include <string>

class Message
{
	static int m_totalCount; // колічество сообщений

	std::string m_message; // сообщение

	int m_maxDuration; // максимателное время выполнения

	int m_maxCount; // максимальное количество повторений

	int m_count = 0;

	int m_takt = 0;

public:
	Message(int takt, int maxDuration = 0, int maxCount = 0, const std::string& message = "");
	virtual ~Message();
	
	void operator()();

	static int totalCount()
	{
		return m_totalCount;
	}

};

