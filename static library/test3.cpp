// test3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "addlib.h"
using namespace std;

int main()
{
    int a, b;
    cout << "Enter the first number:" << endl;
    cin >> a;
    cout << "Enter the second number:" << endl;
    cin >> b;
    cout << "result is : " << add(a, b) << endl;
    return 0;
}
