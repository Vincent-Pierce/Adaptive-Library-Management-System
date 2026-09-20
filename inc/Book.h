#ifndef BOOK_H
#define BOOK_H

#include "Searchable.h"
#include  <string> 
#include <BookException.h>
class Book : public Searchable {
public:
	Book(bool _available, std::string _author, std::string _title) : available(_available), author(_author), title(_title)  {};

	// Mark book as borrowed if it is available
	void borrow() 
	{ 
		if (!available)
		{
			throw BookException("Book is not available for borrowing.");
		}
		else
		{
			available = false;
		}
	}

	// Mark book as returned if it is not available
	void returnBook() 
	{ 
		if (available)
		{
			throw BookException("Book is already available in the library.");
		}
		else
		{
			available = true;
		}
	}
	
	// Return if the query matches author or title 
	bool search(const std::string& query) override 
	{ 
		return query == author || query == title;
	} 

	bool isAvailable() const{ return this->available; }
	const std::string getAuthor() const { return this->author; }
	const std::string getTitle() const { return this->title; }

private:
	bool available;
	std::string author;
	std::string title;
};

#endif // !BOOK_H