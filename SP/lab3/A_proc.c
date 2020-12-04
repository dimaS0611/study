#include <windows.h>
#include <stdio.h>
#include <TlHelp32.h>

#define MAXLENGTH 101
DWORD getProcessID(const WCHAR*);					// функция получения ID процесса

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
	HANDLE hProcessB = INVALID_HANDLE_VALUE;		// дескриптор процесса B
	HANDLE hPipe = INVALID_HANDLE_VALUE;
	LPVOID szAddress = NULL;						// адрес в памяти процесса B
	DWORD cbWritten, cbRead, dBuf;					// буфферы (имеют промежуточное значение)
	BOOL Success;									// флаг успешного открытия/считывания/записи
	DWORD szSize = sizeof(char) * MAXLENGTH;		// размер вводимой строки
	char* str = (char*)malloc(szSize);				// сама строка

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
		PROCESS_ALL_ACCESS,			// устанавливает уровень доступа к объекту процесса
		FALSE,						// параметр дескриптора наследования
		idProcessB);	            // ID процесса (в данном случае - процесса B)
	if (hProcessB == INVALID_HANDLE_VALUE) {
		printf("Failure!\n");
		freeResources(hProcessB, hPipe, szAddress, str);
		system("pause");
		return -1;
	}

	printf("Success!\nAllocating memory for ProcessB...");
	szAddress = VirtualAllocEx(
		hProcessB,													// дескриптор процесса (в данном случае - процесса B)
		0,															// система сама решает, где выделять память
		szSize,														// объём резервируемой памяти
		MEM_RESERVE |												// память зарезервирована и освобождена
		MEM_COMMIT,
		PAGE_EXECUTE_READWRITE);									// атрибут защиты

	printf("Success!\nWriting your string in ProcessB memory...");
	Success = WriteProcessMemory(
		hProcessB,													// дескриптор процесса (в данном случае - процесса B)
		szAddress,													// куда записывать
		str,														// что записывать
		szSize,														// объём записываемых данных
		0);															// указатель на переменную, которая получает число байтов, переданное в указанный процесс (игнорируется)
	if (Success == FALSE) {
		printf("Failure!\n");
		freeResources(hProcessB, hPipe, szAddress, str);
		system("pause");
		return -1;
	}

	printf("Success!\nConnecting to named pipe...");

	while (hPipe == INVALID_HANDLE_VALUE) {
		LPCWSTR pipename = L"\\\\.\\pipe\\mynamedpipe";				// имя канала
		hPipe = CreateFileW(
			pipename,												// имя именованного канала
			GENERIC_READ |											// требуем доступ к чтению и записи
			GENERIC_WRITE,
			0,														// без совместного доступа 
			NULL,													// без дескрипторов защиты
			OPEN_EXISTING,											// открываем существующий канал
			0,														// атрибуты файла по умолчанию 
			NULL);													// без дескриптора файла шаблона
	}

	printf("Success!\nWriting memory address...\n");
	dBuf = (DWORD)szAddress;
	Success = WriteFile(
		hPipe,														// дескриптор канала 
		&dBuf,														// данные для записи (в данном случае - адрес памяти в процессе B) 
		sizeof(dBuf),												// объём записываемых данных
		&cbWritten,													// количество записанных данных (не используем)
		NULL);														// асинхронный буфер (не используем)
	if (Success == FALSE) {
		DWORD err = GetLastError();
		printf("Failure error=%d!\n", err);
		freeResources(hProcessB, hPipe, szAddress, str);
		system("pause");
		return -1;
	}

	printf("Success!\nWaiting answer from ProcessB...");
	Success = ReadFile(
		hPipe,														// имя именованного канала
		&szAddress,													// буфер для считывания
		sizeof(szAddress),											// объём считываемых данных
		&cbRead,													// количество считанных данных (не используем)
		NULL);														// асинхронный буфер (не используем)
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