#include "Book.h"

Book::Book(){
	release_year = 0;
	rating = 0.0;
	id = -1;
}
Book::~Book(){}

string Book::get_keywords_as_string() 
{
	string result;
	size_t size = keywords.size();
	for(size_t i=0;i<size-1;++i)
	{
		result.append(keywords[i]);
		result += " ";
	}
	result.append(keywords[size - 1]);
	return result;
}

string Book::To_String() {
	string sbuilder;
	sbuilder.append("Id: ");
	sbuilder.append(to_string(id));
	sbuilder.append("\nTitle: ");
	sbuilder.append(title);
	sbuilder.append("\nAuthour: ");
	sbuilder.append(author);
	sbuilder.append("\nGenre: ");
	sbuilder.append(genre);
	return sbuilder;
}
string Book::FullInfo() {
	string fullInfo = To_String();
	fullInfo.append("\nRating: ");
	fullInfo.append(to_string(rating));
	fullInfo.append("\nDescription: ");
	fullInfo.append(description);
	fullInfo.append("\nRelease Year: ");
	fullInfo.append(to_string(release_year));
	fullInfo.append("\nKeywords: ");
	for (auto keyword : keywords)
	{
		fullInfo.append(keyword);
		fullInfo.append("| ");
	}
	return fullInfo;
}