#pragma once
#include <string>
#include "File.h"
#include "XPath.h"

using namespace std;

class Repl
{
public:
	Repl();
	~Repl();
	void REPL();

private:
	bool file_Opened;
	File file;
	XML* xml;
	XPath* xpath;

	string Tokens_to_path(vector<string> tokens);
	void Help();
	void Exit();
};


