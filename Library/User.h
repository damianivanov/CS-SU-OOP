#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include "File.h"

using namespace std;

class User
{
public:
	User();
	User(string username, string password, bool isAdmin);
	User& operator=(const User& other);
	~User();

	string get_username() { return this->username; }
	string get_password() { return this->password; }
	bool get_IsAdmin() { return this->IsAdmin; }

	void set_username(string username) { this->username = username; }
	void set_password(string password) { this->password = password; }
	void set_IsAdmin(bool isAdmin) { this->IsAdmin = isAdmin; }

	bool Add(string username, string password);
	void Loggout();
	bool Login();
	bool Remove(string username);
private:

	string username;
	string password;
	bool IsAdmin;
	string Hidden_password();
	bool Username_Available(string username);
};

