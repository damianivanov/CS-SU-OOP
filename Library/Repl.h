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
	bool loggedIn;
	User user;
	File file;
	Library* library;

	vector<string> Input_to_tokens(string line, string& command);
	string Tokens_to_path(vector<string> tokens);
	void Help();
	void Exit();
};


