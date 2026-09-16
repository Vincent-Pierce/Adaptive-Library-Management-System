#pragma once

#include "Book.h"
#include "User.h"
#include "Searchable.h"
#include "String.h"

// A singleton design pattern. The entire system will only have a single Library instance
class Library {
public:

	static Library* Instance()
	{
		if (_instance == 0)
			_instance = new Library();
		return _instance;
	}

	bool search(Searchable& s)  { s.search(); } //Todo
	bool addBook(Book& b)		{ return true; }
	bool borrowBook(Book& s)	{ return true; }
	bool returnBook(Book& s)	{ return true; }

protected:
	Library() {}

private:
	static Library* _instance;

	std::List<Book> available_books;
	std::List<Book> borrowed_books;
	std::List<User> users;
};

Library* Library::_instance = 0;

