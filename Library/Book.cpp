#include "Book.h"

Book::Book(){
	release_year = 0;
	rating = 0.0;
	id = -1;
}
Book::~Book(){}

void Book::set_author(string author) {this->author = author;}
void Book::set_title(string title) { this->title = title; }
void Book::set_genre(string genre) { this->genre = genre; }
void Book::set_description(string description) { this->description = description; }
void Book::set_release_year(unsigned release_year) { this->release_year = release_year; }
void Book::set_keywords(vector<string> const &keywords) { this->keywords = keywords; }
void Book::set_rating(double rating) { this->rating = rating; }
void Book::set_id(int id) { this->id = id; }