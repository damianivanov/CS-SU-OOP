#pragma once
#include <time.h>
#include <string>
#include <vector>

using namespace std;

class Book
{
public:
	Book();
	~Book();

	//getters
	string get_author() { return this->author; }
	string get_title() { return this->title; }
	string get_genre() { return this->genre; }
	string get_description() { return this->description; }
	unsigned int get_release_year() { return this->release_year; }
	string get_keywords_as_string();
	vector<string> const &get_keywords() { return this->keywords; }
	double get_rating() { return this->rating; }
	int get_id() {return this->id; }

	//setter																		
	void set_author(string author) { this->author = author; }
	void set_title(string title) { this->title = title; }
	void set_genre(string genre) { this->genre = genre; }
	void set_description(string description) { this->description = description; }
	void set_release_year(unsigned release_year) { this->release_year = release_year; }
	void set_keywords(vector<string> const& keywords) { this->keywords = keywords; }
	void set_rating(double rating) { this->rating = rating; }
	void set_id(int id) { this->id = id; }

	string To_String();
	string FullInfo();
private:
	string author;
	string title;
	string genre;
	string description;
	unsigned int release_year;
	vector<string> keywords;
	double rating;
	int id;	
};
