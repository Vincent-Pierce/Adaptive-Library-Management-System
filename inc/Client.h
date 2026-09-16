#ifndef CLIENT_H
#define CLIENT_H

#include "Searchable.h"
#include "ReturnTransaction.h"
#include "BorrowTransaction.h"
#include "Library.h"
#include  <string>
class Client
{
public:
	Client(Library _lib) : lib(_lib) {}

	bool borrowBook(Book& b, User& u)
	{
		BorrowTransaction bt = BorrowTransaction(lib, b, u);
		bt.transaction();
	}
	bool returnBook(Book& b, User& u)
	{
		ReturnTransaction rt = ReturnTransaction(lib, b, u);
		rt.transaction();
	}

private:
	Library& lib;
};

#endif // !CLIENT_H