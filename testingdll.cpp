// testingdll.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "sampledll/dllsample.h"

using namespace std;
using namespace calculator;
int main()
{
    int a, b;
    cout << "Enter the first number:" << endl;
    cin >> a;
    cout << "Enter the second number:" << endl;
    cin >> b;
    cout << "The result  = " << calc::add(a, b);
    return 0;
}
