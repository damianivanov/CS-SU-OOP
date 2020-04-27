#pragma once
#include <iostream>
#include <string>
class File
{
public:
	File();
	void Open(std::string path);
	void Save();
	void SaveAs();
	void Close();
	~File();

private:
	std::string content;
	std::string path;
	std::string extension;
	std::string name;

	bool File_available();
	bool File_create();
	bool Read_content();
	void Input_parser(std::string path);
};
