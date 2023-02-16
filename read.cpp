#include<iostream>
#include<Windows.h>
#include<string.h>

using namespace std;

int main()
{
	string newkey;
	LONG reg;
	HKEY Ekey;
	//TCHAR value[255];
	//DWORD value_size = 255;
	reg = RegOpenKeyExA(HKEY_CURRENT_USER,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders",NULL,KEY_WOW64_64KEY|KEY_QUERY_VALUE,&Ekey);
	if (reg == ERROR_SUCCESS)
	{
		char buffer[MAX_PATH];
		DWORD bufsize = MAX_PATH;
		LONG result = RegQueryValueExA(Ekey, "Desktop", NULL, NULL, (LPBYTE)&buffer, &bufsize);
		if (result == ERROR_SUCCESS)
		{
			std::string str(buffer);
			cout << "The Registry Key is  :" << str << endl;
			newkey = str;
		}

	}
	RegCloseKey(Ekey);
	system("pause");
	return 0;

}

