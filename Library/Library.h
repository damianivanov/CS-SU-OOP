#pragma once
#include <iostream>
#include "Book.h"
#include "User.h"
#include <algorithm>

class Library
{
public:
	Library();	
	Library(const vector<string> content);
	~Library();
	void Clear();

	void Add();
	void Remove(int id);
	void All();
	void Info(int id);
	void Find(string option, string options_string);
	void Sort(string option, bool asc = true);
	void Deserialization(vector<string> content);
	
	vector<string> Serialization();

private:
	void Read_Book_Info(Book& book);
	vector<Book> books;
	int next_id;
};

