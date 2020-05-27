#include <iostream>
#include "Repl.h"

int main()
{
	Repl repl;
	repl.REPL();
/* ---Test 1
	//help should be called if there is opened filed

	> help
	Currently there is not file opened! Open file first
	> open Library.txt
	Successfully opened Library.txt
	> help
	The following commands are supported:
	- open <file> --- opens <file>
	- close --- closes currently opened file
	- save --- saves the currently open file
	- saveas <file> --- saves the currently open file in <file>
	- help --- prints this information
	- exit  --- exists the program
	- login <username> <password>
	- logout --- logout only if you are already logged in
	- books all --- prints: title,genre,author,id for every book
	- books find <option> <option_string> --- finds book by given option
	- books sort <option> [desc|asc] --- (options: title,author,year,rating)
	- books info <id> --- full info for book with this id
	- books add --- adds book to the database (admin only)
	- books remove <id> --- removes book by given ID (admin only)
	- users add <username> <password> --- adds user in the database (admin only)
	- users remove --- deletes user from database (admin only)
	>
*/
/*---Test 2
	//you can see books only after login

	> books all
	You have to login first!
	> login
	Enter your username: admin
	Enter your password: ******
	Welcome, admin!
	> books all
	Id: 2
	Title: Midnight Sun
	Authour: Stephenie Meyer
	Genre: Romance
	================================
	Id: 1
	Title: In Search of Lost Time
	Authour: Marcel Proust
	Genre: drama
	================================
	Id: 0
	Title: The Fifth Vital
	Authour: Mike Majlak
	Genre: drama
	================================
	>
*/
/* ---Test 3
	//regular users cannot add users or delete them

	> open Library.txt
	Successfully opened Library.txt
	> login
	Enter your username: damian
	Enter your password: ****
	Wrong password or username.
	> login
	Enter your username: damian
	Enter your password: *****
	Welcome, damian!
	> users add test123 test123	
	Only Admin can add new users!
	> users remove test123
	Only Admin can remove users!
	>
*/
/* ---Test 4
	//sorting shouldn't print, but only change positions in the file("database")
> books sort title desc
> books all
Id: 0
Title: The Fifth Vital
Authour: Mike Majlak
Genre: drama
================================
Id: 2
Title: Midnight Sun
Authour: Stephenie Meyer
Genre: Romance
================================
Id: 1
Title: In Search of Lost Time
Authour: Marcel Proust
Genre: drama
================================
> books sort rating desc
> books all
Id: 0
Title: The Fifth Vital
Authour: Mike Majlak
Genre: drama
================================
Id: 1
Title: In Search of Lost Time
Authour: Marcel Proust
Genre: drama
================================
Id: 2
Title: Midnight Sun
Authour: Stephenie Meyer
Genre: Romance
================================
>
*/
}

