#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include "SearchStrategies.h"
#include  <string> 
#include <memory>
#include <vector>
#include <InputException.h>

// A singleton design pattern. The entire system will only have a single Library instance
class Library {
public:

	static Library& Instance()
	{
		static Library instance; // Only constructed on first call, basically invokes Library() constructor
		return instance;
	}

	bool search(const SearchStrategy& strategy, const std::string& query) const
	{
		if(query.empty())
			return false;
		return strategy.search(query);
	}

	Book& getBook(const std::string query)  
	{ 
		for(const std::shared_ptr<Book>& b : books)
		{
			if(b->search(query))
				return *b;
		}
		throw InputException("Book not found.");
	}

	std::shared_ptr<Book> getBookPointer(const Book& book) const
	{
		for(const std::shared_ptr<Book>& storedBook : books)
		{
			if(storedBook.get() == &book ||
				(storedBook->getAuthor() == book.getAuthor() &&
				 storedBook->getTitle() == book.getTitle()))
				return storedBook;
		}
		throw InputException("Book not found.");
	}

	User& getUser(const std::string query)  
	{ 
		for(User& u : users)
		{
			if(u.search(query))
				return u;
		}
		throw InputException("User not found.");
	}

	void addUser(const User& u)
	{ 
		const UserSearchStrategy userSearch(users);
		if(!search(userSearch, u.getUserName()))
			users.push_back(u);
	}

	// delete user from user list
	bool removeUser(User& _u)
	{ 
		for(auto it = users.begin(); it != users.end(); ++it)
		{
			if(it->getUserId() == _u.getUserId())
			{
				users.erase(it);
				return true;
			}
		}
		return false; 
	}

	void clear() { users.clear(); books.clear(); } 
	const std::vector<std::shared_ptr<Book>>& getBooks() const { return books; }
	const std::vector<User>& getUsers() const { return users; } 

	bool addBook(const Book& b)
	{
		for (const std::shared_ptr<Book>& book : books) // Do not allow duplicated books
		{
			if (book->getAuthor() == b.getAuthor() &&
				book->getTitle() == b.getTitle())
				return false;
		}
		books.push_back(std::make_shared<Book>(b));
		return true;
	}
	Library(const Library&) = delete; 			 // no copies of singleton
	Library& operator=(const Library&) = delete; // no assignment of singleton

private:
	Library() = default; // Private constructor for singleton

	std::vector<std::shared_ptr<Book>> books;
	std::vector<User> users;
};


#endif // !LIBRARY_H