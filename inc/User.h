#ifndef USER_H
#define USER_H

#include "Searchable.h"
#include "Book.h"
#include "Transaction.h"
#include <string> 
#include <vector>
#include <algorithm>
class User : public Searchable {

public:
	User(std::string _name, int _userId, std::vector<std::string> _book_authors)
		: name(_name), userId(_userId), book_authors(_book_authors) {}

	bool search(const std::string& query) override
	{ 
		return query == this->name;
	}
	
	bool searchAuthor(const std::string& query)  
	{ 
		for(std::string& author : book_authors)
		{
			if(author == query)
				return true;
		}
		return false;
	}

	bool addBook(Book b)
	{ 
		book_authors.push_back(b.getAuthor()); 
		return true; 
	}

	bool returnBook(Book b)
	{ 
		auto it = std::find(book_authors.begin(), book_authors.end(), b.getAuthor());
		if (it == book_authors.end())
			return false;
		else
		{
			book_authors.erase(it);
			return true; 
		}
	}

	int getBookCount() const 			{ return book_authors.size(); }
	std::string getUserName() const 	{ return this->name; }
	int getUserId() const 				{ return this->userId; }
	void transaction(Transaction *t) 	{ t->transaction(); }			// polymorhphism!

private:
	std::string				    name;
	int 						userId;
	std::vector<std::string>	book_authors; // list of authors of books borrowed by the user
};

#endif // !USER_H