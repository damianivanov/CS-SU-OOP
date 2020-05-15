#pragma once
#include "Book.h"
#include "User.h"
class Library
{
public:
	Library();	
	~Library();
	void Add(Book& book);
	void Remove(Book& book);

private:
	vector<Book*> books;
};

