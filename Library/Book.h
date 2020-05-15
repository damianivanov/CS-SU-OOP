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
	unsigned get_release_year() { return this->release_year; }
	vector<string> const &get_keywords() { return this->keywords; }
	double get_rating() { return this->rating; }
	int get_id() {return this->id; }

	//setter
	void set_author(string author);
	void set_title(string title);
	void set_genre(string genre);
	void set_description(string description);
	void set_release_year(unsigned release_year);
	void set_keywords(vector<string> const &keyword);
	void set_rating(double rating);
	void set_id(int id);

private:
	string author;
	string title;
	string genre;
	string description;
	unsigned release_year;
	vector<string> keywords;
	double rating;
	int id;	
};
