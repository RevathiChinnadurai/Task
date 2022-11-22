// userfile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	char buf[1024];
	ofstream file1;
	file1.open("Test.txt");
	cout << "Enter the Text to store in file  :"<<endl;
	cin.getline(buf,1024);
	file1 << buf << endl;
	cout << "File write completed" << endl;

	file1.close();
	return 0;

}

