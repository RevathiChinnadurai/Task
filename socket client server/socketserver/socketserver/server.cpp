
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include<iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#define PORT 20005
using namespace std;
//#pragma comment(lib,"Ws2_32.lib")

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
	d.sin_addr.s_addr = INADDR_ANY;
	d.sin_port = htons(PORT);
	memset(&(d.sin_zero), 0, 8);

	ret = bind(lsocket, (struct sockaddr*)&d, sizeof(d));
	if (ret < 0)
	{
		cout << "Cannot bind at port" << GetLastError() << endl;
		return -1;
	}
	cout << "Bound successfully" << endl;

	ret = listen(lsocket, 5);
	if (ret < 0)
	{
		cout << "Cannot listen at port" << GetLastError() << endl;
		return -1;
	}
	cout << "Listening" << endl;

	int nclient;
	int len = sizeof(d);
	nclient = accept(lsocket, (struct sockaddr*)&d, &len);

	if (ret < 0)
	{
		cout << "Cannot Accept At port" << GetLastError() << endl;
		return -1;
	}
	cout << "Accepted" << endl;
	char buf[1024] = { 0, };
			while (1)
			{
					memset(buf, 0, 1024);
					ret = recv(nclient, buf, 1024, 0);
					if (ret < 0)
					{
						cout << "Receive Failed" << GetLastError() << endl;
						return -1;
					}
					cout << "Received message from client   :" << buf << endl;
					cout << "Enter message for client" << endl;
					fgets(buf, 1023, stdin);
					send(nclient, buf, sizeof(buf), 0);
			}

	return 0;
}
