#ifndef BOOK_H
#define BOOK_H

#include "Searchable.h"
#include  <string> 
class Book : Searchable {
public:
	Book(bool _available, std::string _author, std::string _title) : available(_available), author(_author), title(_title)  {};

	bool isAvailable() { return this->available; }
	void search()      {} //Todo

private:
	bool available;
	std::string author;
	std::string title;
};

#endif // !BOOK_H