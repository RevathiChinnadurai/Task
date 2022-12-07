#include<Windows.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;

int main()
{
	HANDLE hshm;
	BOOL result;
	PCHAR buffer = NULL;
	char Buf[1024] = { 0, };
	size_t szBuffer = sizeof(Buf);

	hshm = CreateFileMapping(INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		256,
		L"sharedmemory");

	if (hshm == FALSE)
	{
		cout << "CreateSharedMemory failed" << GetLastError ()<< endl;
	}

	cout << "CreateSharedMemory Success"<< endl;

	buffer = (PCHAR)MapViewOfFile(hshm, FILE_MAP_ALL_ACCESS, 0, 0, szBuffer);
	if (buffer == NULL)
	{
		cout << "MapView of file failed" << GetLastError() << endl;
	}

	cout << "MapView of file Success" << endl;
	memset(Buf, 1023, sizeof(Buf));
	cout << "Enter message for client" << endl;
	fgets(Buf, 1024, stdin);
	CopyMemory(buffer, Buf, szBuffer);
	result = UnmapViewOfFile(buffer);

	if (result == FALSE)
	{
		cout << "Unmapviewof file failed" << GetLastError() << endl;
	}

	cout << "Unmapviewof file Success" << endl;
	//CloseHandle(hshm);
	system("pause");
	return 0;
}