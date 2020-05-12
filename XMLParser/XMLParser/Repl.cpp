#include "Repl.h"

void Repl::REPL() {
	string command;
	while (true)
	{
		cout << "> ";
		string line;
		std::getline(cin, line);
		
		vector<std::string> tokens;
		istringstream iss(line);
		string s;
		for (int i = 0; iss >> s; i++) {
			if (i==0)
			{
				command = s;
			}
			else
				tokens.push_back(s);
		}
		cin.sync();
		//You have to open file first
		if (!file_Opened && (command!="open" && command != "exit"))
		{
			cout << "Currently there is not file opened! Open file first " << endl;
			continue;
		}

		if (tokens.size()==0)
		{
			if (strcmp(command.c_str(), "close") == 0)
			{				
				xml->Clear();
				file.Close();
				file_Opened = false;
			}
			else if (strcmp(command.c_str(), "save") == 0)
			{
				xml->Serialization();
				file.Write_Content(xml->get_Content());
				file.Save();
			}
			else if (strcmp(command.c_str(), "help") == 0)
			{
				Help();
			}
			else if (strcmp(command.c_str(), "exit") == 0)
			{
				Exit();
			}
			else if (strcmp(command.c_str(), "print") == 0)
			{
				xml->Print();
			}
		}
		else
		{
			if (strcmp(command.c_str(), "open") == 0)
			{
				if (file_Opened!=false)
				{
					cout << "File is already opened" << endl;
					continue;
				}
				//path have space in the name
				if (tokens.size() > 1)
				{
					string path = Tokens_to_path(tokens);
					file.Open(path);
					xml = new XML(file.get_content());
					xpath = new XPath(xml->get_Deserialized());
				}
				else
					file.Open(tokens[0]);
				file_Opened = true;
				
			}
			else if (strcmp(command.c_str(), "saveas") == 0)
			{
				string path;
				xml->Serialization();
				file.Write_Content(xml->get_Content());
				if (tokens.size() > 1)
				{
					string path = Tokens_to_path(tokens);
					file.SaveAs(path);
				}
				else			
					file.SaveAs(tokens[0]);
			}
			else if (strcmp(command.c_str(), "select") == 0)
			{
				xml->Select(tokens[0], tokens[1]);
			}
			else if (strcmp(command.c_str(), "set") == 0)
			{
				xml->Set(tokens[0], tokens[1], tokens[2]);
			}
			else if (strcmp(command.c_str(), "children") == 0)
			{
				xml->Children(tokens[0]);
			}
			else if (strcmp(command.c_str(), "child") == 0)
			{
				xml->Child(tokens[0], stoi(tokens[1]));
			}
			else if (strcmp(command.c_str(), "text") == 0)
			{
				xml->Text(tokens[0]);
			}
			else if (strcmp(command.c_str(), "delete") == 0)
			{
				xml->Delete(tokens[0], tokens[1]);
			}
			else if (strcmp(command.c_str(), "newchild") == 0)
			{
				xml->NewChild(tokens[0]);
			}
			else if (strcmp(command.c_str(), "xpath") == 0)
			{
				if (tokens.size()<2)
				{
					cout << "Invalid XPath" << endl;
					continue;
				}
				auto result = xpath->Parser(tokens[0], tokens[1]);
				for (auto x : result)
				{
					if (x!="")
					{
						cout <<" - " << x << endl;
					}
				}
			}
		}
	}
}

void Repl::Help() {
	cout << "The following commands are supported:" << endl;
	cout << "- open <file>				opens <file>" << endl;
	cout << "- close					closes currently opened file" << endl;
	cout << "- save						saves the currently open file" << endl;
	cout << "- saveas <file>			saves the currently open file in <file>" << endl;
	cout << "- help						prints this information" << endl;
	cout << "- exit						exists the program" << endl;
	cout << "  - print						prints the content of XML file" << endl;
	cout << "  - select <id> <key>			prints the value of an attribute with <key> of element with <id> " << endl;
	cout << "  - set <id> <key> <value>		sets <value> with <key> of element with <id>" << endl;
	cout << "  - children <id>				list with attributes of nested elements" << endl;
	cout << "  - child <id> <n>				<n>-th child of element <id>" << endl;
	cout << "  - text <id>					text of element with Id = <id>" << endl;
	cout << "  - delete <id> <key>			deletes attribute with key of element <id>" << endl;
	cout << "  - newchild <id>				adds New child to element <id>" << endl;
	cout << "  - xpath <id> <XPath>			<XPath> to element with <id>" << endl;

}
void Repl::Exit() {
	cout << "Exiting the program..." << endl;
	exit(0);
}
string Repl::Tokens_to_path(vector<string> tokens)
{
	string path;
	for (auto x : tokens) {
		path += x + " ";
	}
	return path.substr(0, path.size() - 1);
}
Repl::Repl() {	
	file_Opened = false;
	xml = new XML();
	xpath = new XPath();
}
Repl::~Repl(){}