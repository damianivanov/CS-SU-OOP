#pragma once
#include <iostream>
#include <string>
#include <vector>
class File
{
public:
	File();
	void Open(std::string path);
	void Save();
	void SaveAs(std::string new_path);
	void Close();
	std::vector<std::string> get_content();
	~File();

private:
	std::vector<std::string> content;
	std::string path;
	std::string extension;
	std::string name;

	bool File_available();
	bool File_create();
	bool Read_content();
	void Input_parser(std::string path);
	std::vector<std::string> Name_extension_parser(std::string path);
};
