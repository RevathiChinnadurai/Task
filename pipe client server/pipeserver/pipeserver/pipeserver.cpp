#include<iostream>
#include<Windows.h>
  
using namespace std;

int main()
{
	HANDLE hpipe;
	hpipe = CreateNamedPipe(L"\\\\.\\pipe\\mypipe",
	    PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE,
		1,
		0,
		0,
		0,
		NULL);
	if ( hpipe == INVALID_HANDLE_VALUE)
	{
		wcout << "Failed to create pipe" << GetLastError() << endl;
		system("pause");
		return 1;
	}
	wcout << "Waiting for a client to connect to the pipe..." << endl;
	BOOL result = ConnectNamedPipe(hpipe, NULL);
	if (!result) {
		wcout << "Failed to make connection on named pipe." <<GetLastError() <<endl;
		
		CloseHandle(hpipe); 
		system("pause");
		return 1;
	}
	wcout << "Sending data to client" << endl;
	const wchar_t* data = L"This is the first pipe communication program";
	DWORD byteswritten = 0;

	DWORD bytesread = 0;
	result = WriteFile(hpipe,
		data,
		wcslen(data) * sizeof(wchar_t),
		&byteswritten,
		NULL);
	if (result) {
		wcout << "Number of bytes sent: " << byteswritten << endl;
	}
	else {
		wcout << "Failed to send data." << GetLastError()<<endl;
	}

	wchar_t buffer[127];
BOOL resul = ReadFile(hpipe,
		buffer,
		127 * sizeof(wchar_t),
		&bytesread,
		NULL
	);
	if (resul) {
		buffer[ bytesread / sizeof(wchar_t)] = '\0';
		wcout << "Message: " << buffer << endl;
		wcout << "Number of bytes read: " << bytesread << endl;
		
	}
	else {
		wcout << "Failed to read data from the pipe." << endl;
	}
	CloseHandle(hpipe);
	wcout << "Done." << endl;
	system("pause");
	return 0;
}