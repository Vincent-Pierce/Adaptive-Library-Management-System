#ifndef USER_H
#define USER_H

#include "Book.h"
#include "Searchable.h"
#include "Transaction.h"
#include <string> 
#include <vector>
#include <memory>
#include <algorithm>
#include <utility>
class User : public Searchable {

public:
	User(std::string _name, int _userId, std::vector<std::weak_ptr<Book>> _borrowedBooks = {})
		: name(_name), userId(_userId), borrowedBooks(std::move(_borrowedBooks)) {}

	bool search(const std::string& query) const override
	{ 
		return !query.empty() &&
			(query == this->name || query == std::to_string(userId));
	}
	
	bool searchAuthor(const std::string& query)  
	{ 
		for(const std::weak_ptr<Book>& weakBook : borrowedBooks)
		{
			const std::shared_ptr<Book> book = weakBook.lock();
			if(book && book->getAuthor() == query)
				return true;
		}
		return false;
	}

	bool addBook(const std::shared_ptr<Book>& book)
	{ 
		if (!book)
			return false;
		borrowedBooks.push_back(book);
		return true; 
	}

	void trackBorrowedBook(const std::shared_ptr<Book>& book)
	{
		if (book)
			borrowedBooks.push_back(book);
	}

	// Remove book from user list
	bool returnBook(const std::shared_ptr<Book>& book)
	{ 
		for (auto it = borrowedBooks.begin(); it != borrowedBooks.end();)
		{
			const std::shared_ptr<Book> borrowedBook = it->lock();
			if (!borrowedBook)
			{
				it = borrowedBooks.erase(it);
				continue;
			}
			if (borrowedBook == book)
			{
				borrowedBooks.erase(it);
				return true;
			}
			++it;
		}
		return false;
	}

	std::vector<std::string> getBookAuthors() const
	{
		std::vector<std::string> authors;
		for (const std::weak_ptr<Book>& weakBook : borrowedBooks)
		{
			if (const std::shared_ptr<Book> book = weakBook.lock())
				authors.push_back(book->getAuthor());
		}
		return authors;
	}
	int getBookCount() const
	{
		return std::count_if(borrowedBooks.begin(), borrowedBooks.end(),
			[](const std::weak_ptr<Book>& book) { return !book.expired(); });
	} // Return the number of books borrowed by the user
	std::string getUserName() const 	{ return this->name; }
	int getUserId() const 				{ return this->userId; }
	void transaction(Transaction *t) 	{ t->transaction(); }			// command design pattern polymorhphism!

private:
	std::string				    name;
	int 						userId;
	std::vector<std::weak_ptr<Book>> borrowedBooks;
};

#endif // !USER_H