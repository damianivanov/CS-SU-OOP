#include "Library.h"

Library::Library() { next_id = 0; }
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
void Library::All() {
	for (auto book : books)
	{
		cout << book->To_String() << endl;
	}
}
void Library::Info(int id) {
	
	for (auto book:books)
	{
		if (book->get_id()==id)
			cout << book->FullInfo()<<endl;
	}
}