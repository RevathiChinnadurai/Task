#include<iostream>
#include<Windows.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

int main()
{
	HANDLE hshm;
	BOOL result;
	PCHAR buffer = NULL;
	hshm = OpenFileMapping(
		FILE_MAP_ALL_ACCESS, FALSE,
		L"sharedmemory");

	if (hshm == NULL)
	{
		cout << "Open file mapping failed" << GetLastError() << endl;
	}
	cout << "Open File Mapping success" << endl;
	buffer = (PCHAR) MapViewOfFile (hshm, FILE_MAP_ALL_ACCESS, 0, 0, 256);

	if (buffer == NULL)
	{
		cout << "MapViewof File failed" << GetLastError() << endl;
	}
	cout << "MapViewof File success" << endl;

	cout << "Message From Server :" << buffer << endl;
	result = UnmapViewOfFile (buffer);
	if (result == FALSE)
	{
		cout << "UnmapView of file Failed" << GetLastError() << endl;
	}
	cout << "Unmapview of file Success" << endl;

	CloseHandle (hshm);
	system("pause");
	return 0;
}