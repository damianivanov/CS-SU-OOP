// XMLParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "File.h"
using namespace std;

int main()
{
    string command;
    cin >> command;
    string path;
    cin.ignore();
    cin.sync();
    getline(cin,path);
    File file;
    file.Open(path);

}

