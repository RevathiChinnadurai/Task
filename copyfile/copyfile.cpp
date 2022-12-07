#include<iostream>
#include<fstream>
#include<string>


using namespace std;

int main()
{
	ifstream f1;
	ofstream f2;

	string line;

	f1.open("File1.txt",ios::in);
	f2.open("File2.txt", ios::out);

	while (!f1.eof())
	{
		cout << "Reading from file 1" << endl;
		getline(f1, line);
		cout << "Writing to file 2" << endl;
		f2 << line << endl;

	}
	f1.close();
	f2.close();

	return 0;
}