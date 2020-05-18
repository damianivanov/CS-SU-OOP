#include "Library.h"

Library::Library() { next_id = 0; }
Library::Library(vector<string> content) { this->Deserialization(content); }
Library::~Library() {}


void Library::Add()
{
	Book book;
	Read_Book_Info(book);
	this->books.push_back(book);
	cout << book.get_title() << " by: " << book.get_author() << " was added to the database.\n";
}
void Library::Remove(int id)
{
	int size = books.size();
	for (int i = 0; i < size ; i++)
	{
		if (id == books.at(i).get_id())
		{
			this->books.erase(books.begin() + i); 
			cout << "Book with Id: " << id << " was deleted!\n";
			return;
		}
	}
	cout << "There is no book with Id: " << id << "!\n";
}
void Library::All() {
	for (auto book : books)
	{
		cout << book.To_String() << endl;
	}
}
void Library::Info(int id) {
	
	for (auto book:books)
	{
		if (book.get_id()==id)
			cout << book.FullInfo()<<endl;
	}
}

void Library::Clear() 
{
	this->books.clear();
	next_id = 0;
}
void Library::Read_Book_Info(Book& book)
{
	string tmp;

	cout << "Author: ";
	getline(cin, tmp);
	book.set_author(tmp);
	
	cout << "Title: ";
	getline(cin, tmp);
	book.set_title(tmp);

	cout << "Genre: ";
	getline(cin, tmp);
	book.set_genre(tmp);

	cout << "Short description: ";
	getline(cin, tmp);
	book.set_description(tmp);

	cout << "Year of release: ";
	getline(cin, tmp);
	book.set_release_year(stoul(tmp));

	cout << "Keywords(separeted by space): ";
	getline(cin, tmp);
	vector<string> keywords;
	istringstream iss(tmp);
	while(iss >> tmp) 
	{
		keywords.push_back(tmp);
	}
	book.set_keywords(keywords);

	cout << "Rating: ";
	getline(cin, tmp);
	book.set_rating(stod(tmp));

	book.set_id(next_id++);
	
}
void Library::Deserialization(vector<string> content) {
	for (size_t i=0;i<content.size();)
	{
		Book book;
		book.set_id(stoi(content[i++]));
		book.set_author(content[i++]);
		book.set_title(content[i++]);
		book.set_genre(content[i++]);
		book.set_description(content[i++]);
		book.set_release_year(stoul(content[i++]));
		istringstream iss(content[i++]);
		vector<string> keywords;
		string tmp;
		while (iss>>tmp)
			keywords.push_back(tmp);
		book.set_keywords(keywords);
		book.set_rating(stod(content[i++]));
		books.push_back(book);
	}
	next_id = books[books.size() - 1].get_id()+1;
}
vector<string> Library::Serialization()
{
	vector<string> content;
	for (auto book : books)
	{
		content.push_back(to_string(book.get_id()));
		content.push_back(book.get_author());
		content.push_back(book.get_title());
		content.push_back(book.get_genre());
		content.push_back(book.get_description());
		content.push_back(to_string(book.get_release_year()));
		content.push_back(book.get_keywords_as_string());
		content.push_back(to_string(book.get_rating()));
	}
	return content;
}