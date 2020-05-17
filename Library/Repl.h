#pragma once
#include <string>
#include <sstream>
#include "Library.h"
#include "File.h"
#include "User.h"
using namespace std;

class Repl
{
public:
	Repl();
	~Repl();
	void REPL();

private:
	bool file_Opened;
	User user;
	File file;
	Library library;

	string Tokens_to_path(vector<string> tokens);
	void Help();
	void Exit();
};


