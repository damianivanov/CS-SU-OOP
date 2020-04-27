#include "File.h"
#include <fstream>
#include <regex>
File::File() {}
File::~File() {}
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

bool File::Read_content()
{
	std::ifstream FileIf(path);
	if (!FileIf.good())
		return false;

	std::string tmp;
	while (std::getline(FileIf,tmp))
	{//
		this->content.append(tmp);
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

void File::Input_parser(std::string path)
{
	this->path = path;

	std::regex r_extension("\\.\\w+$");
	std::regex r_name("\\\w+\\.\\w+$");

	std::smatch m_extension;
	std::smatch m_name;

	std::regex_search(path, m_extension, r_extension);
	std::regex_search(path, m_name, r_name);

	this->extension = m_extension.str();
	this->name = m_name.str();

	name = name.substr(0, name.size()-extension.size());
}

void File::Close()
{

}