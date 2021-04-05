#pragma once
#include <string>

class Message
{
	static int m_totalCount; // ��������� ���������

	std::string m_message; // ���������

	int m_maxDuration; // ������������� ����� ����������

	int m_maxCount; // ������������ ���������� ����������

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

