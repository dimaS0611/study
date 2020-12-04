#include <windows.h>
#include <stdio.h>

DWORD szAddress;												// адрес выделенной памяти

void printResult(BOOL ok)
{
	if (ok == FALSE) {
		printf("Failure!\n");
	}
	else {
		printf("Success!\n");
	}
}

void freeResources(
	HANDLE hPipe,
	LPVOID ptr
)
{
	if (ptr)
		free(ptr);
/*
	if (virtMemB)
	{
		printf("Releasing memory...");
		printResult(
			VirtualFreeEx(
				hProcessB,
				virtMemB,
				0,
				MEM_RELEASE)
		);
	}
	*/
	if (hPipe != INVALID_HANDLE_VALUE)
	{
		printf("Closing named pipe...");
		printResult(CloseHandle(hPipe));
	}
	/*
	if (hProcessB != INVALID_HANDLE_VALUE)
	{
		printf("Closing ProcessB...");
		printResult(CloseHandle(hProcessB));
	}*/
}

int main(void) {
	LPCTSTR pipename = L"\\\\.\\pipe\\mynamedpipe";					// имя канала
	HANDLE hNamedPipe;												// дескриптор именованного канала
	DWORD cbRead, cbWritten;										// буфферы
	char* msg;														// получаемая строка
	BOOL Success;													// флаг успешного открытия/считывания/записи

	printf("Creating pipe ");
	hNamedPipe = CreateNamedPipeW(
		pipename,									// имя канала
		PIPE_ACCESS_DUPLEX,							// канал двунаправленный; серверные и клиентские процессы могут читать с канала и записывать в него
		PIPE_TYPE_MESSAGE |							// данные записываются в канал и считываются из него как поток сообщений
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,									// неограниченное ожидание в течение выполнения действий клиентским процессом
		PIPE_UNLIMITED_INSTANCES,					// максимальное число экземпляров
		sizeof(DWORD),								// резерв для выводимого буфера
		sizeof(DWORD),								// резерв для вводимого буфера
		100,										// спецификатор значения time-out
		NULL);										// атрибуты защиты

	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		DWORD error = GetLastError();
		printf("Failure! err=%d\n", error);
		freeResources(hNamedPipe, msg);
		system("pause");
		return -1;
	}

	printf("Success!\nConnecting to pipe   ");
	ConnectNamedPipe(hNamedPipe, NULL);

	printf("Success!\nReading from pipe    ");
	Success = ReadFile(
		hNamedPipe,								// имя именованного канала
		&szAddress,								// буфер для считывания
		sizeof(szAddress),						// объём считываемых данных
		&cbRead,								// количество считанных данных 
		NULL);									// асинхронный буфер 
	if (Success == FALSE) {
		printf("Failure!\n");
		freeResources(hNamedPipe, msg);
		system("pause");
		return -1;
	}

	printf("Success!\nYour string: ");
	msg = (char*)szAddress;
	printf_s("%s\n", msg);

	printf("Sending answer to ProccessA    ");
	Success = WriteFile(
		hNamedPipe,													// дескриптор канала 
		&szAddress,													// данные для записи 
		sizeof(szAddress),											// объём записываемых данных
		&cbWritten,													// количество записанных данных 
		NULL);														// асинхронный буфер 
	if (Success == FALSE) {
		printf("Failure!\n");
		freeResources(hNamedPipe, msg);
		system("pause");
		return -1;
	}

	printf("Success!\nGetCurrentProcess    ");
	HANDLE hProcess = GetCurrentProcess();
	if (!hProcess) {
		printf("Failure!\n");
		freeResources(hNamedPipe, msg);
		system("pause");
		return -1;
	}


	printf("Success!\nReleasing memory   ");

	freeVirualMem(hProcess);

	printf("Success!\nDisconnecting from named pipe   ");
	Success = DisconnectNamedPipe(hNamedPipe);
	if (Success == FALSE) {
		printf("Failure!\n");
		freeResources(hNamedPipe, msg);
		system("pause");
		return -1;
	}

	printf("Success!\nClosing named pipe   ");
	Success = CloseHandle(hNamedPipe);
	if (Success == FALSE) {
		printf("Failure!\n");
		freeResources(hNamedPipe, msg);
		system("pause");
		return -1;
	}

	printf("Success!\nProcessB was finished   \n");
	system("pause");
	return 0;
}


void freeVirualMem(HANDLE hProcess)
{
	BOOL Success;
	printf("\nReleasing memory   ");

	Success = VirtualFreeEx(
		hProcess,											// дескриптор процесса
		(LPVOID)szAddress,									// указатель на память для очищения
		0,													// размер в байтах для удаления
		MEM_RELEASE);										// тип освобождения памяти

	if (Success == FALSE) {
		printf("Failure!\n");
		system("pause");
		return -1;
	}
}