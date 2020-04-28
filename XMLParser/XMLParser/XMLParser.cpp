// XMLParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "File.h"
#include "XML.h"
using namespace std;

int main()
{
    string command;
    string path;
    File file;

    cin >> command;
    cin.ignore();
    cin.sync();
    getline(cin,path);
    //open C:\Users\Damian's PC\Documents\GitHub\CS-SU-OOP\XMLParser\XMLParser\file.xml
    //string new_path = "C:\\Users\\Damian's PC\\Documents\\GitHub\\CS-SU-OOP\\XMLParser\\XMLParser\\Newfile.xml";

    file.Open(path);
    //file.SaveAs(new_path);
    XML xml(file.get_content());
    xml.Print();
    file.Close();

}

