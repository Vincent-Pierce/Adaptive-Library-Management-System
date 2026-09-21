#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include "Searchable.h"
#include  <string> 
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

	// search for user by name
	bool searchUser(const std::string query)  
	{ 
		if(query.empty())
			throw InputException("Search query cannot be empty.");
		for(User& u : users)
		{
			if(u.search(query))
				return true;
		}
		return false;
	}

	// search for book by author or title
	bool searchBook(const std::string query)  
	{ 
		if(query.empty())
			throw InputException("Search query cannot be empty.");
		for(Book& b : books)
		{
			if(b.search(query))
				return true;
		}
		return false;
	} 

	Book& getBook(const std::string query)  
	{ 
		for(Book& b : books)
		{
			if(b.search(query))
				return b;
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
		if(!searchUser(u.getUserName()))
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
	const std::vector<Book>& getBooks() const { return books; } 
	const std::vector<User>& getUsers() const { return users; } 

	bool addBook(const Book& b)		{ books.push_back(b); return true; }
	Library(const Library&) = delete; 			 // no copies of singleton
	Library& operator=(const Library&) = delete; // no assignment of singleton

private:
	Library() = default; // Private constructor for singleton

	std::vector<Book> books;
	std::vector<User> users;
};


#endif // !LIBRARY_H