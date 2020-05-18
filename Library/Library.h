#pragma once
#include "Book.h"
#include "User.h"
#include <iostream>

class Library
{
public:
	Library();	
	Library(vector<string> content);
	~Library();
	void Clear();

	void Add();
	void Remove(int id);
	void All();
	void Info(int id);
	void Deserialization(vector<string> content);
	vector<string> Serialization();

private:
	void Read_Book_Info(Book& book);
	vector<Book*> books;
	int next_id;
};

