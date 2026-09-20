#ifndef CLIENT_H
#define CLIENT_H

#include "Searchable.h"
#include "ReturnTransaction.h"
#include "BorrowTransaction.h"
#include "Library.h"
#include  <string>

// Client class participating in command design pattern. Initializes the transaction type and 
// invokes user transaction abstraction
class Client
{
public:
	Client(Library& _lib) : lib(_lib) {}


	bool borrowBook(Book& b, User& u)
	{
		BorrowTransaction bt = BorrowTransaction(lib, b, u);
		u.transaction(&bt);
		return true;
	}
	bool returnBook(Book& b, User& u)
	{
		ReturnTransaction rt = ReturnTransaction(lib, b, u);
		u.transaction(&rt);
		return true;
	}

private:
	Library& lib;
};

#endif // !CLIENT_H