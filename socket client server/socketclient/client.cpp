
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include<iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include<stdlib.h>
#define PORT 20005

using namespace std;
#pragma warning(disable:4996) 
#pragma comment(lib, "Ws2_32.lib")
int main()
{
	WSADATA w;
	int ret = 0;
	struct sockaddr_in d;
	ret = WSAStartup(MAKEWORD(2, 2), &w);
	if (ret < 0)
	{
		cout << "Cannot Initialize Socket Library" << GetLastError() << endl;
		return -1;
	}
	int lsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (lsocket < 0)
	{
		cout << "Cannot Initialize Listener Socket" << GetLastError() << endl;
		return -1;
	}
	else
	{
		cout << "Socket created successfully" << endl;
	}

	d.sin_family = AF_INET;
	d.sin_addr.s_addr = inet_addr("127.0.0.1");
	d.sin_port = htons(PORT);
	memset(&(d.sin_zero), 0, 8);

	ret = connect(lsocket, (struct sockaddr*)&d, sizeof(d));
	if (ret < 0)
	{
		cout << "Cannot connect to the server" << GetLastError() << endl;
		return -1;
	}
	cout << " Connected successfully" << endl;
	char buf[1024] = { 0, };
	//int choice;
	while (1)
	{
	cout << "Enter the message for server" << endl;
	fgets(buf, 1023, stdin);
	send(lsocket, buf, strlen(buf), 0);
	cout << "Message sent successfully" << endl;
	recv(lsocket, buf, 1024, 0);
	cout << "Message from server :  " << buf << endl;
	}

	return 0;
}