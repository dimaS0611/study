#include <windows.h>
#include <stdio.h>

DWORD szAddress;												// ����� ���������� ������

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
	LPCTSTR pipename = L"\\\\.\\pipe\\mynamedpipe";					// ��� ������
	HANDLE hNamedPipe;												// ���������� ������������ ������
	DWORD cbRead, cbWritten;										// �������
	char* msg;														// ���������� ������
	BOOL Success;													// ���� ��������� ��������/����������/������

	printf("Creating pipe ");
	hNamedPipe = CreateNamedPipeW(
		pipename,									// ��� ������
		PIPE_ACCESS_DUPLEX,							// ����� ���������������; ��������� � ���������� �������� ����� ������ � ������ � ���������� � ����
		PIPE_TYPE_MESSAGE |							// ������ ������������ � ����� � ����������� �� ���� ��� ����� ���������
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,									// �������������� �������� � ������� ���������� �������� ���������� ���������
		PIPE_UNLIMITED_INSTANCES,					// ������������ ����� �����������
		sizeof(DWORD),								// ������ ��� ���������� ������
		sizeof(DWORD),								// ������ ��� ��������� ������
		100,										// ������������ �������� time-out
		NULL);										// �������� ������

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
		hNamedPipe,								// ��� ������������ ������
		&szAddress,								// ����� ��� ����������
		sizeof(szAddress),						// ����� ����������� ������
		&cbRead,								// ���������� ��������� ������ 
		NULL);									// ����������� ����� 
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
		hNamedPipe,													// ���������� ������ 
		&szAddress,													// ������ ��� ������ 
		sizeof(szAddress),											// ����� ������������ ������
		&cbWritten,													// ���������� ���������� ������ 
		NULL);														// ����������� ����� 
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
		hProcess,											// ���������� ��������
		(LPVOID)szAddress,									// ��������� �� ������ ��� ��������
		0,													// ������ � ������ ��� ��������
		MEM_RELEASE);										// ��� ������������ ������

	if (Success == FALSE) {
		printf("Failure!\n");
		system("pause");
		return -1;
	}
}