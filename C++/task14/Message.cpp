#include "Message.h"
#include <iostream>
#include <chrono>
#include <mutex>

int64_t timeMsec() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

std::mutex mutexMessage;

int Message::m_totalCount = 0;

Message::Message(int takt, int maxDuration, int maxCount, const std::string& message)
	: m_takt(takt)
	, m_message(message)
	, m_maxDuration(maxDuration)
	, m_maxCount(maxCount)
{
}

void Message::operator()()
{
	auto timeStart = timeMsec();
	auto timeLast = 0;

	for (;;)
	{
		if (m_maxCount > 0 && m_count >= m_maxCount)
			return;

		if (m_maxDuration > 0 && timeLast >= m_maxDuration)
			return;

		auto it = timeMsec() - timeStart;
		if (it - timeLast >= m_takt)
		{
			timeLast = it;

			mutexMessage.lock();
			std::cout << "time: " << it / 1000 << " sec\t" << m_message << "\n";
			m_totalCount++;
			mutexMessage.unlock();
		}
	}
}

Message::~Message()
{
}
