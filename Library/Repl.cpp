#include "Repl.h"

void Repl::REPL() {
	while (true)
	{
		string line;
		string command;
		cout << "> ";
		getline(cin, line);
		vector<string> tokens = Input_to_tokens(line, command);

		//You have to open file first
		if (!file_Opened && (command != "open" && command != "exit"))
		{
			cout << "Currently there is not file opened! Open file first " << endl;
			continue;
		}

		if (strcmp(command.c_str(), "open") == 0)
		{
			if (file_Opened != false)
			{
				cout << "File is already opened" << endl;
				continue;
			}
			//path have space in the name
			if (tokens.size() > 2)
			{
				string path = Tokens_to_path(tokens);
				file.Open(path);
			}
			else if (tokens.size() == 2)
				file.Open(tokens[1]);
			else
			{
				cout << "Wrong format: open <path>\n";
				break;
			}
			vector<string> filecontent = file.get_content();
			library = new Library(filecontent);
			file_Opened = true;

		}
		else if (strcmp(command.c_str(), "close") == 0)
		{
			library->Clear();
			file.Close();
			file_Opened = false;
		}
		else if (strcmp(command.c_str(), "save") == 0)
		{
				vector<string> serialized = library->Serialization();
			file.Write_Content(serialized);
			file.Save();
		}
		else if (strcmp(command.c_str(), "saveas") == 0)
		{
			string path;
			file.Write_Content(library->Serialization());
			//file.Write_Content();
			if (tokens.size() > 1)
			{
				string path = Tokens_to_path(tokens);
				file.SaveAs(path);
			}
			else 
				file.SaveAs(tokens[0]);
		}
		else if (strcmp(command.c_str(), "help") == 0)
		{
			Help();
		}
		else if (strcmp(command.c_str(), "exit") == 0)
		{
			Exit();
		}

		else if (strcmp(command.c_str(), "login") == 0)
		{
			if (loggedIn)
				cout << "You are already logged in." << endl;
			else {
				if (user.Login())
					loggedIn = true;
				//because of hidden password there is one \n left in the buffer
				//Enter is \r\n, but i'm capturing only \r
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		else if (strcmp(command.c_str(), "logout") == 0)
		{
			if (loggedIn)
			{
				user.Loggout();
				loggedIn = false;
			}
			else
				cout << "No logged in user!" << endl;
		}
		else if (strcmp(command.c_str(), "all") == 0)
		{
			if (loggedIn)
			{
				library->All();
			}
			else
				cout << "You have to login first!\n";
		}
		else if (strcmp(command.c_str(), "info") == 0)
		{
			if (loggedIn)
			{
				if (tokens.size() >= 2)
				{
					library->Info(stoi(tokens[2]));
				}
				else
					cout << "Invalid Command!\n";
			}
			else
				cout << "You have to login first!\n";
		}
		else if (strcmp(command.c_str(), "find") == 0)
		{
			if (loggedIn)
			{
				string option_string;
				for (size_t i = 3; i < tokens.size()-1; i++)
				{
					option_string += tokens[i] + " ";
				}
				option_string += tokens[tokens.size()-1];
				transform(option_string.begin(), option_string.end(),option_string.begin(), ::tolower);
				transform(tokens[2].begin(), tokens[2].end(), tokens[2].begin(), ::tolower);
				library->Find(tokens[2],option_string);
			}
			else
				cout << "You have to login first!\n";
		}
		else if (strcmp(command.c_str(), "sort") == 0)
		{
			if (loggedIn)
			{
				transform(tokens[2].begin(), tokens[2].end(), tokens[2].begin(), ::tolower);
				bool type = true;
				if (tokens.size()>3)
				{
					transform(tokens[3].begin(), tokens[3].end(), tokens[3].begin(), ::tolower);
					type = tokens[3] == "asc";
				}
				library->Sort(tokens[2], type);	
			}
			else
				cout << "You have to login first!\n";

		}

		else if (strcmp(command.c_str(), "add") == 0 && tokens[0] == "books")
		{
			if (loggedIn && user.get_IsAdmin())
			{
				library->Add();
				
			}
			else if (!loggedIn)
			{
				cout << "You have to login first!\n";
			}
			else
				cout << "Only Admin can remove books!\n";
		}
		else if (strcmp(command.c_str(), "remove") == 0 && tokens[0] == "books")
		{
			if (loggedIn && user.get_IsAdmin())
			{
				library->Remove(stoi(tokens[2]));
			}
			else if (!loggedIn)
			{
				cout << "You have to login first!\n";
			}
			else
				cout << "Only Admin can remove books!\n";
		}
		else if (strcmp(command.c_str(), "add") == 0 && tokens[0] == "users")
		{
			if (loggedIn && user.get_IsAdmin())
			{
				user.Add(tokens[2], tokens[3]);

			}
			else if (!loggedIn)
			{
				cout << "You have to login first!\n";
			}
			else {
				cout << "Only Admin can add new users!\n";
			}
		}
		else if (strcmp(command.c_str(), "remove") == 0 && tokens[0] == "users")
		{
			if (loggedIn && user.get_IsAdmin())
			{
				user.Remove(tokens[2]);

			}
			else if (!loggedIn)
			{
				cout << "You have to login first!\n";
			}
			else {
				cout << "Only Admin can remove users!\n";
			}
		}

		else
			cout << "Invalid Command!" << endl;

	}
}

void Repl::Help() {
	cout << "The following commands are supported:" << endl;
	cout << "- open <file> --- opens <file>" << endl;
	cout << "- close --- closes currently opened file" << endl;
	cout << "- save --- saves the currently open file" << endl;
	cout << "- saveas <file> --- saves the currently open file in <file>" << endl;
	cout << "- help --- prints this information" << endl;
	cout << "- exit	--- exists the program" << endl;
	cout << "- login <username> <password>"<< endl;
	cout << "- logout --- logout only if you are already logged in"<<endl;
	cout << "- books all --- prints: title,genre,author,id for every book "<<endl;
	cout << "- books find <option> <option_string> --- finds book by given option"<<endl;
	cout << "- books sort <option> [desc|asc] --- (options: title,author,year,rating)\n";
	cout << "- books info <id> --- full info for book with this id"<<endl;
	cout << "- books add --- adds book to the database (admin only)\n";
	cout << "- books remove <id> --- removes book by given ID (admin only)" << endl;
	cout << "- users add <username> <password> --- adds user in the database (admin only)\n";
	cout << "- users remove --- deletes user from database (admin only)\n";
}
void Repl::Exit() {
	cout << "Exiting the program..." << endl;
	exit(0);
}

vector<string> Repl::Input_to_tokens(string line,string& command) {
	vector<string> tokens;
	istringstream iss(line);
	string s;
	for (int i = 0; iss >> s; i++)
		tokens.push_back(s);

	if (tokens.size()>0)
	{
		if (tokens[0] == "open" || tokens[0] == "saveas" || tokens.size() < 2)
			command = tokens[0];
		else if (tokens.size() > 1)
			command = tokens[1];
	}

	return tokens;
}
string Repl::Tokens_to_path(vector<string> tokens)
{
	string path;
	for(size_t i=1;i<tokens.size();++i)
	{	
			path += tokens[i] + " ";
	}
	return path.substr(0, path.size() - 1);
}
Repl::Repl() {	
	file_Opened = false; 
	loggedIn = false;
	library = new Library();
}
Repl::~Repl() { delete library; }