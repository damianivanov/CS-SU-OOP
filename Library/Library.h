#pragma once
#include "Book.h"
#include "User.h"
#include <iostream>
class Library
{
public:
	Library();	
	~Library();
	void Add(Book& book);
	void Remove(Book& book);
	void All();
	void Info(int id);

private:
	vector<Book*> books;
	int next_id;
};

