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

	static Library* Instance()
	{
		if (_instance == 0)
			_instance = new Library();
		return _instance;
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

	void borrowBook(User& u)
	{ 
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

	bool addBook(Book& b)		{ books.push_back(b); return true; }

protected:
	Library() {};

private:
	static Library* _instance;

	std::vector<Book> books;
	std::vector<User> users;
};

Library* Library::_instance = 0;

#endif // !LIBRARY_H