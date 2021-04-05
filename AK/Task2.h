#pragma once
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "mpi.h"
#include "Proccess.h"

class Task2
{
public:
	static void SolverTask2()
	{
		
		auto process = Process::Process();

		float* data1 = nullptr;
		float* data2 = nullptr;
		float* answer = nullptr;

		float** matrix1 = nullptr;
		float** matrix2 = nullptr;

		int M = 4;
		int L = 4;

		if (process.IsMaster())
		{
			data1 = new float[M * L];
			data2 = new float[M * L];
			answer = new float[M * L];

			matrix1 = new float* [M];
			for (int i = 0; i < M; i++)
				matrix1[i] = new float[L];

			matrix2 = new float* [M];
			for (int i = 0; i < M; i++)
				matrix2[i] = new float[L];


			Fill(matrix1, M, L);
			std::cout << "First Matrix: " << std::endl;
			for (auto i = 0; i < M; i++)
			{
				for (int j = 0; j < L; j++)
					std::cout << std::setw(8) << matrix1[i][j] << "|";
				std::cout << "\n---------------------------------------------------------\n";
			}
			


			Fill(matrix2, M, L);
			std::cout << "Second Matrix: " << std::endl;

			for (auto i = 0; i < M; i++)
			{
				for (int j = 0; j < L; j++)
					std::cout << std::setw(8) << matrix2[i][j] << "|";
				std::cout << "\n-------------------------------------------------------\n";
			}
			

			data1 = ConvertToVector(matrix1, M, L);
			data2 = ConvertToVector(matrix2, M, L);
		}

		int* sizes = new int[process.GetProcessCount()];
		int* displs = new int[process.GetProcessCount()];

		FillSizes(sizes, process.GetProcessCount(), M * L, displs);

		int MAX_SIZE = M * L / process.GetProcessCount() + 1;
		int* first_matrix_slice = new int[MAX_SIZE];
		int* second_matrix_slice = new int[MAX_SIZE];

		MPI_Scatterv(data1, sizes, displs, MPI_INT, first_matrix_slice, sizes[process.GetRank()], MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Scatterv(data2, sizes, displs, MPI_INT, second_matrix_slice, sizes[process.GetRank()], MPI_INT, 0, MPI_COMM_WORLD);
		for (int i = 0; i < sizes[process.GetRank()]; i++)
		{
			first_matrix_slice[i] += second_matrix_slice[i];
		}

		MPI_Gatherv(first_matrix_slice, sizes[process.GetRank()], MPI_INT, answer, sizes, displs, MPI_INT, 0, MPI_COMM_WORLD);

		if (process.IsMaster())
		{
			ConvertToMatrix(answer, M, L, matrix1);
			std::cout << "Answer Matrix:" << std::endl;


			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < L; j++)
					std::cout << std::setw(15) << matrix1[i][j] << "|";

				std::cout << "\n-------------------------------------------------------------------\n";

			}
			for (int i = 0; i < M; i++)
				delete[] matrix1[i];
			delete[] matrix1;

			for (int i = 0; i < M; i++)
				delete[] matrix2[i];
			delete[] matrix2;

			delete[] data1;
			delete[] data2;
			delete[] answer;
		}

		delete[] first_matrix_slice;
		delete[] second_matrix_slice;
		delete[] displs;
		delete[] sizes;
	}

private:
	static void Fill(float** matrix, int M, int L)
	{
		srand(442);
		for (auto i = 0; i < M; i++)
		{
			for (int j = 0; j < L; j++)
				matrix[i][j] = (rand() % 10 - 5) / (rand() % 10 + 1);
		}
	}

	static void FillSizes(int* data, int process_count, int datalen, int* displs)
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

	static float* ConvertToVector(float** matrix, int M, int L)
	{
		float* answer = new float[M * L];

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < L; j++)
			{
				answer[i * L + j] = matrix[i][j];
			}
		}

		return answer;
	}

	static void ConvertToMatrix(float* vector, int M, int L, float** matrix)
	{
		for (int i = 0; i < M * L; i++)
		{
			matrix[i / L][i % L] = vector[i];
		}
	}
};

