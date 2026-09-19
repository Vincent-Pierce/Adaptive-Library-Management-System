#ifndef BOOK_H
#define BOOK_H

#include "Searchable.h"
#include  <string> 
class Book : public Searchable {
public:
	Book(bool _available, std::string _author, std::string _title) : available(_available), author(_author), title(_title)  {};

	bool isAvailable() { return this->available; }
	bool setAvailable(bool _available) { this->available = _available; return true; }

	bool search(const std::string& query) override 
	{ 
		return query == author || query == title;
	} 

	std::string getAuthor() { return this->author; }

private:
	bool available;
	std::string author;
	std::string title;
};

#endif // !BOOK_H