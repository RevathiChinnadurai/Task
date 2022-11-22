#include<iostream>
#include<Windows.h>


using namespace std;

int main()
{
	HANDLE hpipe;
	hpipe = CreateFile(L"\\\\.\\pipe\\mypipe",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hpipe == INVALID_HANDLE_VALUE)
	{
		wcout << " Failed to connect " << endl;
		system("pause");
		return 1;
	}
	wchar_t buffer[127];
	DWORD bytestoread = 0;
	DWORD bytestowrite = 0;
	BOOL result = ReadFile(hpipe,
		buffer,
		127 * sizeof(wchar_t),
		&bytestoread,
		NULL);
	if (result) {
		buffer [bytestoread / sizeof(wchar_t)] = '\0'; // null terminate the string
		wcout << "Number of bytes read: " << bytestoread << endl;
		wcout << "Message: " << buffer << endl;
	}
	else {
		wcout << "Failed to read data from the pipe." << endl;
	}
	const wchar_t * buf = L"From Client: Got the Message.. Thank u..";
	BOOL  resul = WriteFile(hpipe,
		buf,
		wcslen(buf) * sizeof(wchar_t),
		&bytestowrite,
		NULL);
	if (resul) {
		wcout << "Number of bytes sent: " << bytestowrite << endl;
	}
	else {
		wcout << "Failed to send data." << endl;
		// look up error code here using GetLastError()
	}
	CloseHandle(hpipe);
	system("pause");
	return 0;
}