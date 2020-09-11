#include "File.h"
#include <fstream>
#include <regex>

File::File() {}
File::~File() {}

std::vector<std::string> File::get_content() { return this->content; }

bool File::File_available()
{
	std::fstream FileIf(this->path, std::ios::app);
	if (!FileIf.good())
		return false;

	FileIf.close();
	return true;
}
bool File::File_create() 
{
	if (!File_available())
	{
	    std::ofstream FileOf(this->path);
	    if (!FileOf.good()) {
	        std::cout << "File not created\n";
	        return false;
	    }
	}
	return true;
}

void File::Write_Content(std::vector<std::string> text)
{
	content.clear();
	for (auto x: text)
	{
		content.push_back(x);
	}
}
bool File::Read_content()
{
	std::ifstream FileIf(path);
	if (!FileIf.good())
		return false;

	std::string tmp;
	while (std::getline(FileIf,tmp))
	{
		this->content.push_back(tmp);
	}
	FileIf.close();
	return true;
}

void File::Open(std::string path)
{	
	Input_parser(path);
	if (File_create())
	{
		std::cout << "Successfully opened " << name << extension << '\n';
		Read_content();
	}
}
void File::Close()
{
	this->content.clear();
	std::cout << "Successfully closed " << name << extension << "\n";	
}
void File::Save()
{
	std::ofstream FileOf(path,std::ios::trunc);
	if (!FileOf.good())
		return;
	for (std::string x : content)
	{
		FileOf << x;
	}
	FileOf.close();
	std::cout << "Successfully saved " << name << extension << "\n";
}
void File::SaveAs(std::string new_path)
{
	std::string new_name = Name_extension_parser(new_path)[0];
	std::string new_extension = Name_extension_parser(new_path)[1];
	std::ofstream FileOf(new_path, std::ios::trunc);
	for (std::string x : content)
	{
		FileOf << x;
	}
	FileOf.close();
	std::cout << "Successfully saved another " << new_name<<new_extension << "\n";
}


void File::Input_parser(std::string path)
{
	this->path = path;
	std::vector<std::string> name_and_extension = Name_extension_parser(path);
	name = name_and_extension[0];
	extension = name_and_extension[1];
}
std::vector<std::string> File::Name_extension_parser(std::string path) {

	std::regex r_extension(".\\w*$");
	std::regex r_name("(\\w+)(?=\\.)");
	/*C:\Users\Damian's PC\Documents\GitHub\CS-SU-OOP\XMLParser\XMLParser\Test.xml*/

	std::smatch m_extension;
	std::smatch m_name;

	std::regex_search(path, m_extension, r_extension);
	std::regex_search(path, m_name, r_name);

	std::vector<std::string> result;

	result.push_back(m_name.str());
	result.push_back(m_extension.str());

	return result;
}
