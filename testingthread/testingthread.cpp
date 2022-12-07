#include <fstream>
#include <iostream>
#include <string.h>
#include <windows.h>

using namespace std;
CRITICAL_SECTION cs;
HANDLE t1, t2;
const char buf1[1024] = "Hello";
const char buf2[1024] = "world";

DWORD WINAPI filefun(LPVOID lpParam)
{
	ofstream file1;
	int i=0;
	
	file1.open("deva.txt", ios::app);
	
	
	for (i = 0; i <= 1000; i++)
	{
		EnterCriticalSection(&cs);
		cout << "thread 1 running" << endl;
		file1 << buf1 << endl;
		LeaveCriticalSection(&cs);
	}
	
	file1.close();
	
	return 1;
}
DWORD WINAPI filefun2(LPVOID lpParam)
{
	ofstream file2;
	int i=0;
	
	file2.open("deva.txt", ios::app);
	for (i = 0; i <= 1000; i++)
	{
		EnterCriticalSection(&cs);
		cout << "thread 2 running" << endl;
		file2 << buf2 << endl;
		LeaveCriticalSection(&cs);
	}
	
	file2.close();
	
	return 1;
}


int main()
{
	HANDLE t1, t2;
	InitializeCriticalSection(&cs);
	
	ofstream file1,file2;

	t1 = CreateThread(
		NULL, 
		0,
		filefun,
	(void *)&buf1,
		0, NULL);
	WaitForSingleObject(t1, INFINITE);

	t2 = CreateThread(
		NULL,
		0,
		filefun2,
		(void*)&buf2,
		0, NULL);
	
	WaitForSingleObject(t2, INFINITE);

	CloseHandle (t1);
	CloseHandle (t2);

	DeleteCriticalSection(&cs);
	return 0;
}
