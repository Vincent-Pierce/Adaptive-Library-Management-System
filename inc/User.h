#ifndef USER_H
#define USER_H

#include "Searchable.h"
#include "Book.h"
#include "Transaction.h"
#include  <string> 
class User : public Searchable {

public:
	User(std::string _name, int _userId, float _balance, std::vector<Book> _books)
		: name(_name), userId(_userId), books(_books) {}

	void search()					{}							//Todo
	bool addBook(Book b)			{ books.push_back(b); return true; }
	bool removeBook(Book b)			{ return true; }
	void transaction(Transaction t) { t.transaction; }			// polymorhphism!

private:
	std::string		    name;
	int				    userId;
	std::vector<Book>	books;
};

#endif // !USER_H