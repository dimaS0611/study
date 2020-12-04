#pragma once
#include <ctime>
#include <sstream>
#include <iostream>

#include "mpi.h"
#include "Proccess.h"
class Task1
{
public:
	static void SolverTask1(int argc, char* argv[])
	{
		srand(time(0));
		auto process = Process::Process();

		int* data1 = nullptr;
		int* data2 = nullptr;
		int* answer = nullptr;

		// Vector length
		int data_len = 0;

		std::stringstream len(argv[1]);
		if (!(len >> data_len))
			data_len = 0;

		if (process.IsMaster())
		{
			data1 = new int[data_len];
			data2 = new int[data_len];
			answer = new int[process.GetProcessCount()];

			//Fill first matrix
			fill(data1, data_len);
			std::cout << "First:  ";
			for (int i = 0; i < data_len; i++)
			{
				std::cout << data1[i] << " ";
			}
			std::cout << std::endl;

			fill(data2, data_len);
			std::cout << "Second: ";
			for (int i = 0; i < data_len; i++)
			{
				std::cout << data2[i] << " ";
			}
			std::cout << std::endl;
		}

		int* sizes = new int[process.GetProcessCount()];
		int* displs = new int[process.GetProcessCount()];

		fill_sizes(sizes, process.GetProcessCount(), data_len, displs);

		int processCount = process.GetProcessCount();
		const int MAX_SIZE = (data_len + processCount - 1) / processCount; //---
		int* slice1 = new int[MAX_SIZE];
		int* slice2 = new int[MAX_SIZE];

		MPI_Scatterv(data1, sizes, displs, MPI_INT, slice1, sizes[process.GetRank()], MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Scatterv(data2, sizes, displs, MPI_INT, slice2, sizes[process.GetRank()], MPI_INT, 0, MPI_COMM_WORLD);

		int sum = 0;
		for (int i = 0; i < sizes[process.GetRank()]; i++)
		{
			sum += slice1[i] * slice2[i];
		}
		MPI_Gather(&sum,1,	MPI_INT, answer, 1,	MPI_INT, Process::MasterRank, MPI_COMM_WORLD);

		if (process.IsMaster())
		{
			int answer_sum = 0;
			for (int i = 0; i < process.GetProcessCount(); i++)
			{
				answer_sum += answer[i];
			}

			std::cout << "Scalar multiplication = " << answer_sum << std::endl;


			delete[] data1;
			delete[] data2;
			delete[] answer;
		}

		delete[] slice1;
		delete[] slice2;
		delete[] displs;
		delete[] sizes;
	}

private:
	static void fill(int* data, int length)
	{
		for (auto i = 0; i < length; i++)
		{
			data[i] = rand() % 2 - 1;
		}
	}
	static void fill_sizes(int* data, int process_count, int datalen, int* displs)
	{
		int after = datalen;
		int MAX_PROCESSES = (after / (process_count)) + 1;
		for (auto i = 0; i < process_count; i++)
		{
			if (after / (process_count - i) < ((double)after / (process_count - i)))
			{
				data[i] = (after / (process_count - i)) + 1;
				after -= (after / (process_count - i)) + 1;
			}
			else
			{
				data[i] = (after / (process_count - i));
				after -= (after / (process_count - i));
			}
			if (i != 0)
				displs[i] = displs[i - 1] + data[i - 1];
			else
				displs[i] = 0;
		}
	}
};

