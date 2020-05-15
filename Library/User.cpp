#include "User.h"
User& User::operator=(const User other)
{
	this->username = other.username;
	this->password = other.password;
	this->IsAdmin = other.IsAdmin;
	return *this;
}
User::User() { IsAdmin = false; }
User::~User(){}
User::User(string username, string password, bool isAdmin):
	username(username),
	password(password),
	IsAdmin(isAdmin){}