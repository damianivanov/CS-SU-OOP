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
    xml.Deserialization();
    xml.Delete("1", "id");
    xml.Children("0");
    xml.Child("1", 1);
    xml.NewChild("1");
    xml.Select("0", "id");
    xml.Set("0", "id", "5");
    xml.Select("5", "id");
    xml.Text("5");
    file.Close();

}

