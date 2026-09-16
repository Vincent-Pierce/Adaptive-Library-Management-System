#pragma once

#include "Searchable.h"
#include "Book.h"
#include "Transaction.h"
#include "String.h"

class User : public Searchable {

public:
	User(std::String _name, int _userId, float _balance, std::List<Book> _books)
		: name(_name), userId(_userId), balance(_balance), books(_books) {}

	void search()					{}							//Todo
	void addBook(Book b)			{ books.push_back(b); }
	void removeBook(Book b)			{ std::erase(books, b); }
	void transaction(Transaction t) { t->transaction }			// polymorhphism!
	bool charge(void)				{ balance++; }

private:
	std::String		name;
	int				userId;
	float			balance;
	std::List<Book>	books;
};
