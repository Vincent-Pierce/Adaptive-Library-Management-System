#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include "Searchable.h"
#include  <string> 
#include <vector>

// A singleton design pattern. The entire system will only have a single Library instance
class Library {
public:

	static Library* Instance()
	{
		if (_instance == 0)
			_instance = new Library();
		return _instance;
	}

	bool search(Searchable& s)  { s.search(); return true; } //Todo
	bool addBook(Book& b)		{ available_books.push_back(b); return true; }
	bool borrowBook(Book& s)	{ return true; }
	bool returnBook(Book& s)	{ return true; }

protected:
	Library() {}

private:
	static Library* _instance;

	std::vector<Book> available_books;
	std::vector<Book> borrowed_books;
	std::vector<User> users;
};

Library* Library::_instance = 0;

#endif // !LIBRARY_H