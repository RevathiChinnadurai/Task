#include<iostream>
#include<Windows.h>
#include<string.h>

using namespace std;

int main()
{
	LONG reg;
	HKEY Nkey;
	DWORD value = 3456;
	reg = RegCreateKeyEx(
		HKEY_LOCAL_MACHINE,
		L"SYSTEM\\Test\\Newkey",
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS | KEY_WOW64_32KEY,
		NULL,
		&Nkey,
		NULL);

	if (reg != ERROR_SUCCESS)
	{
		cout << "Registry creation Failed" << GetLastError() << endl;
	}
	cout << "Registry Creation success" << endl;
	reg = RegSetValueEx(
		Nkey,
		L"VALUE",
		NULL,
		REG_DWORD, 
		(LPBYTE)&value,
		sizeof(value)
	);
	if (reg != ERROR_SUCCESS)
	{
		cout << "Value Cannot set to subkey" << GetLastError() << endl;
	}
	cout << "Value set successfully" << endl;

	RegCloseKey(Nkey);

	system("pause");
	return 0;
}