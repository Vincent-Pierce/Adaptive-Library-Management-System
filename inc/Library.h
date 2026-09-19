#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include "Searchable.h"
#include  <string> 
#include <vector>

// A singleton design pattern. The entire system will only have a single Library instance
class Library {
public:

	static Library& Instance()
	{
		static Library instance; // Only constructed on first call 
		return instance;
	}

	bool searchUser(const std::string query)  
	{ 
		for(User& u : users)
		{
			if(u.search(query))
				return true;
		}
		return false;
	}

	bool searchBook(const std::string query)  
	{ 
		for(Book& b : books)
		{
			if(b.search(query))
				return true;
		}
		return false;
	} 

	void addUser(User& u)
	{ 
		if(!searchUser(u.getUserName()))
			users.push_back(u);
	}

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

	void clear() { users.clear(); books.clear(); } // For testing purposes only
	const std::vector<Book>& getBooks() const { return books; } 
	const std::vector<User>& getUsers() const { return users; } 

	bool addBook(Book& b)		{ books.push_back(b); return true; }
	Library(const Library&) = delete; 			 // no copies of singleton
	Library& operator=(const Library&) = delete; // no assignment of singleton

private:
	Library() = default; // Private constructor for singleton

	std::vector<Book> books;
	std::vector<User> users;
};


#endif // !LIBRARY_H