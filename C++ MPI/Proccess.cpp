#include "Proccess.h"
#include "mpi.h"

Process::Process()
{
	MPI_Init(nullptr, nullptr);
	MPI_Comm_size(MPI_COMM_WORLD, &m_processCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &m_rank);
}

Process::~Process()
{
	MPI_Finalize();
}

int Process::GetRank() const
{
	return m_rank;
}

int Process::GetProcessCount() const
{
	return m_processCount;
}

bool Process::IsMaster() const
{
	return GetRank() == MasterRank;
}
