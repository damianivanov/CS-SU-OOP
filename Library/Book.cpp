#include "Book.h"

Book::Book(){
	release_year = 0;
	rating = 0.0;
	id = -1;
}
Book::~Book(){}

string Book::To_String() {
	string sbuilder;
	sbuilder.append(" -");
	sbuilder.append(title);
	sbuilder.append("\n  -");
	sbuilder.append(author);
	sbuilder.append("\n  -");
	sbuilder.append(genre);
	sbuilder.append("\n  -");
	sbuilder.append(to_string(id));
	sbuilder.append("\n");
	return sbuilder;
}
string Book::FullInfo() {
	string fullInfo = To_String();
	fullInfo.append(" -");
	fullInfo.append(to_string(rating));
	fullInfo.append("\n  -");
	fullInfo.append(description);
	fullInfo.append("\n  -");
	fullInfo.append(to_string(release_year));
	fullInfo.append("\n  -");
	for (auto keyword : keywords)
	{
		fullInfo.append(keyword);
		fullInfo.append("|");
	}
	fullInfo.append("\n");
	return fullInfo;
}