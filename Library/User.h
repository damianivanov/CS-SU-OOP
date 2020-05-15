#pragma once
#include <string>
using namespace std;
class User
{
public:
	User();
	User(string username, string password, bool isAdmin);
	User& operator=(const User other);
	~User();

	string get_username() { return this->username; }
	string get_password() { return this->password; }
	bool get_IsAdmin() { return this->IsAdmin; }

	void set_username(string username) { this->username = username; }
	void set_password(string password) { this->password = password; }
	void set_IsAdmin(bool isAdmin) { this->IsAdmin = isAdmin; }
private:

	string username;
	string password;
	bool IsAdmin;
};

