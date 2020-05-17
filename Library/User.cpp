#include "User.h"
const string Admin_Name = "admin";
User::User() { 
	username = "";
	password = "";
	IsAdmin = false; 
}
User::User(string username, string password, bool isAdmin):
	username(username),
	password(password),
	IsAdmin(isAdmin){}
User& User::operator=(const User& other)
{
	this->username = other.username;
	this->password = other.password;
	this->IsAdmin = other.IsAdmin;
	return *this;
}
User::~User(){}

void User::Loggout() {
	cout << "Successfully logged out of " << username << ".\n";
	username = "";
	password = "";
	IsAdmin = false;
}
bool User::Login()
{
	File file;
	file.Open("Users.txt");
	vector<string> users = file.get_content();
	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter your password: ";
	password = Hidden_password();
	for (auto user:users)
	{
		istringstream iss(user);
		string curr_user;
		string curr_password;
		
		iss >> curr_user;
		iss >> curr_password;
		
		if (curr_user==username && curr_password == password)
		{
			cout << "Welcome, " << username << "!\n";	
			if (username == Admin_Name)
			{
				IsAdmin = true;
			}
			return true;
		}
	}
	cout << "Wrong password or username.\n";
	return false;
}
bool User::Add(string username, string password)
{
	if (!Username_Available(username))
	{
		cout << "This username is taken.\n";
		return false;
	}
	else
	{
		File file;
		file.Open("Users.txt");
		vector<string> content = file.get_content();
		content.push_back(username + " " + password);
		file.Write_Content(content);
		file.Save();
		cout << "Added new user with username: " << username << "\n";
		return true;
	}
}
bool User::Remove(string username)
{
	if (Username_Available(username))
	{
		cout << "There is no user with username - "<<username<<"\n";
		return false;
	}
	else
	{
		File file;
		file.Open("Users.txt");
		vector<string> content = file.get_content();
		for (size_t i = 0; i < content.size(); i++)
		{
			istringstream iss(content[i]);
			string curr_username;
			iss >> curr_username;
			if (curr_username == username)
			{
				content.erase(content.begin() + i);
				break;
			}
		}
		file.Write_Content(content);
		file.Save();
		cout << "Removed user with username: " << username << "\n";
		return true;
	}
}

bool User::Username_Available(string username)
{
	File file;
	file.Open("Users.txt");
	vector<string> users = file.get_content();
	for (string user:users)
	{
		istringstream iss(user);
		string curr_user;
		iss >> curr_user;
		if (username==curr_user)
			return false;
	}
	return true;
}
string User::Hidden_password()
{
	string pass;
	char c;
	while (c=_getch())
	{
		if (c=='\r')
			break;
		if (c!='\t' && c!='\r' && c!='\b')
		{
			cout << "*";
			pass += c;
		}
		else if (c == '\b')
		{
			if (pass.size()!=0)
			{
				pass.pop_back();
				cout << "\b \b";
			}
		}
	}
	cout << endl;
	return pass;
}