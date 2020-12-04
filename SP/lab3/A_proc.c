#include <windows.h>
#include <stdio.h>
#include <TlHelp32.h>

#define MAXLENGTH 101
DWORD getProcessID(const WCHAR*);					// ������� ��������� ID ��������

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
	HANDLE hProcessB,
	HANDLE hPipe,
	LPVOID virtMemB,
	LPVOID ptr
)
{
	if (ptr)
		free(ptr);

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

	if (hPipe != INVALID_HANDLE_VALUE)
	{
		printf("Closing named pipe...");
		printResult(CloseHandle(hPipe));
	}

	if (hProcessB != INVALID_HANDLE_VALUE)
	{
		printf("Closing ProcessB...");
		printResult(CloseHandle(hProcessB));
	}
}

int main(void)
{
	HANDLE hProcessB = INVALID_HANDLE_VALUE;		// ���������� �������� B
	HANDLE hPipe = INVALID_HANDLE_VALUE;
	LPVOID szAddress = NULL;						// ����� � ������ �������� B
	DWORD cbWritten, cbRead, dBuf;					// ������� (����� ������������� ��������)
	BOOL Success;									// ���� ��������� ��������/����������/������
	DWORD szSize = sizeof(char) * MAXLENGTH;		// ������ �������� ������
	char* str = (char*)malloc(szSize);				// ���� ������

	printf("Enter your string: ");
	gets_s(str, MAXLENGTH - 1);

	DWORD idProcessB = getProcessID(L"b.exe");
	if (!idProcessB) {
		printf("process <b.exe> not found!\n");
		freeResources(hProcessB, hPipe, szAddress, str);
		system("pause");
		return -1;
	}

	printf("Opening ProcessB...");
	hProcessB = OpenProcess(
		PROCESS_ALL_ACCESS,			// ������������� ������� ������� � ������� ��������
		FALSE,						// �������� ����������� ������������
		idProcessB);	            // ID �������� (� ������ ������ - �������� B)
	if (hProcessB == INVALID_HANDLE_VALUE) {
		printf("Failure!\n");
		freeResources(hProcessB, hPipe, szAddress, str);
		system("pause");
		return -1;
	}

	printf("Success!\nAllocating memory for ProcessB...");
	szAddress = VirtualAllocEx(
		hProcessB,													// ���������� �������� (� ������ ������ - �������� B)
		0,															// ������� ���� ������, ��� �������� ������
		szSize,														// ����� ������������� ������
		MEM_RESERVE |												// ������ ��������������� � �����������
		MEM_COMMIT,
		PAGE_EXECUTE_READWRITE);									// ������� ������

	printf("Success!\nWriting your string in ProcessB memory...");
	Success = WriteProcessMemory(
		hProcessB,													// ���������� �������� (� ������ ������ - �������� B)
		szAddress,													// ���� ����������
		str,														// ��� ����������
		szSize,														// ����� ������������ ������
		0);															// ��������� �� ����������, ������� �������� ����� ������, ���������� � ��������� ������� (������������)
	if (Success == FALSE) {
		printf("Failure!\n");
		freeResources(hProcessB, hPipe, szAddress, str);
		system("pause");
		return -1;
	}

	printf("Success!\nConnecting to named pipe...");

	while (hPipe == INVALID_HANDLE_VALUE) {
		LPCWSTR pipename = L"\\\\.\\pipe\\mynamedpipe";				// ��� ������
		hPipe = CreateFileW(
			pipename,												// ��� ������������ ������
			GENERIC_READ |											// ������� ������ � ������ � ������
			GENERIC_WRITE,
			0,														// ��� ����������� ������� 
			NULL,													// ��� ������������ ������
			OPEN_EXISTING,											// ��������� ������������ �����
			0,														// �������� ����� �� ��������� 
			NULL);													// ��� ����������� ����� �������
	}

	printf("Success!\nWriting memory address...\n");
	dBuf = (DWORD)szAddress;
	Success = WriteFile(
		hPipe,														// ���������� ������ 
		&dBuf,														// ������ ��� ������ (� ������ ������ - ����� ������ � �������� B) 
		sizeof(dBuf),												// ����� ������������ ������
		&cbWritten,													// ���������� ���������� ������ (�� ����������)
		NULL);														// ����������� ����� (�� ����������)
	if (Success == FALSE) {
		DWORD err = GetLastError();
		printf("Failure error=%d!\n", err);
		freeResources(hProcessB, hPipe, szAddress, str);
		system("pause");
		return -1;
	}

	printf("Success!\nWaiting answer from ProcessB...");
	Success = ReadFile(
		hPipe,														// ��� ������������ ������
		&szAddress,													// ����� ��� ����������
		sizeof(szAddress),											// ����� ����������� ������
		&cbRead,													// ���������� ��������� ������ (�� ����������)
		NULL);														// ����������� ����� (�� ����������)
	if (Success == FALSE) {
		printf("Failure!\n");
		freeResources(hProcessB, hPipe, NULL, str);
		system("pause");
		return -1;
	}

	printf("Success!\n");

	freeResources(hProcessB, hPipe, NULL, str);

	printf("ProcessA was finished...\n");
	system("pause");
	return 0;
}

DWORD getProcessID(const WCHAR* process) {
	PROCESSENTRY32 processEntry;
	DWORD processID = 0;
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Snapshot != INVALID_HANDLE_VALUE) {
		processEntry.dwSize = sizeof(processEntry);
		Process32First(Snapshot, &processEntry);

		do {
			if (wcscmp(processEntry.szExeFile, process) == 0) {
				processID = processEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(Snapshot, &processEntry));

		CloseHandle(Snapshot);
	}

	return processID;
}