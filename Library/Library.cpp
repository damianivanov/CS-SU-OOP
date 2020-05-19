#include "Library.h"

Library::Library() { next_id = 0; }
Library::Library(const vector<string> content) { this->Deserialization(content); }
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
		cout << "================================" << endl;
	}
}
void Library::Info(int id) {
	
	for (auto book : books)
	{
		if (book.get_id() == id) {
			cout << book.FullInfo() << endl;
			break;
		}
	}
	cout << "No book with Id: " << id << " was found" << endl;	

}
void Library::Find(string option ,string options_string)
{
	bool found = false;
	for (auto book : books) 
	{
		string title=book.get_title();
		string author=book.get_author();

		transform(title.begin(), title.end(), title.begin(), ::tolower);
		transform(author.begin(), author.end(), author.begin(), ::tolower);

		if (option=="title" && options_string==title)
		{
			cout << book.To_String() << endl;
			found = true;
		}
		else if(option=="author"&& options_string == author)
		{
			cout << book.To_String() << endl;
			found = true;
		}
		else if (option == "tag")
		{
			vector<string> keywords = book.get_keywords();
			if (count(keywords.begin(), keywords.end(), options_string))
			{
				cout << book.To_String() << endl;
				found = true;
			}
		}
	}
	if (!found)
	{
		cout << "Book with " << option << ": " << options_string << " wasn't found" << endl;
	}
}
void Library::Sort(string option, bool asc)
{
	if (option=="author")
	{
		sort(books.begin(), books.end(), [](Book& b1, Book& b2)
			{
				return b1.get_author() < b2.get_author();
			});
	}
	else if (option=="title")
	{
		sort(books.begin(), books.end(), [](Book& b1, Book& b2)
			{
				return b1.get_title() < b2.get_title();
			});
	}
	else if (option == "year")
	{
		sort(books.begin(), books.end(), [](Book& b1, Book& b2) 
			{
			return b1.get_release_year() < b2.get_release_year();
			});
	}
	else if (option == "rating")
	{
		sort(books.begin(), books.end(), [](Book& b1, Book& b2)
			{
				return b1.get_rating() < b2.get_rating();
			});
	}

	if (!asc)
	{
		reverse(books.begin(), books.end());
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
		transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		keywords.push_back(tmp);
	}
	book.set_keywords(keywords);

	cout << "Rating: ";
	getline(cin, tmp);
	book.set_rating(stod(tmp));

	book.set_id(next_id++);
	
}

void Library::Deserialization(vector<string> content) {
	if (content.size()%8!=0)
	{
		cout << "The file might be corrupted!" << endl;
		return;
	}
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