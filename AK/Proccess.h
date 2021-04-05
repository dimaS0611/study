#pragma once
#include "mpi.h"

	class Process
	{
		int m_processCount;
		int m_rank;
	public:
		static const int MasterRank = 0;
	public:
		Process();
		~Process();

		int GetRank() const;
		int GetProcessCount() const;
		bool IsMaster() const;
	};
