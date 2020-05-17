#include "User.h"
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
			return true;
		}
	}
	return false;
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