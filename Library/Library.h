#pragma once
#include "Book.h"
#include "User.h"
#include <iostream>
#include <algorithm>

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
	void Find(string option, string options_string);
	void Sort(string option, bool asc = true);
	void Deserialization(vector<string> content);
	
	vector<string> Serialization();

private:
	void Read_Book_Info(Book& book);
	vector<Book> books;
	bool By_Year(Book b1, Book b2) {
		return (b1.get_release_year() < b2.get_release_year());
	}
	int next_id;
};

