#include "Library.h"

Library::Library() {}
Library::~Library() {}

void Library::Add(Book& book)
{
	this->books.push_back(&book);
}
void Library::Remove(Book& book)
{
	int size = books.size();
	for (int i = 0; i < size ; i++)
	{
		if (book.get_id()== books.at(i)->get_id())
		{
			this->books.erase(books.begin() + i); 
		}
	}
}