#pragma once

#include "Searchable.h"
#include "Transaction.h"
#include "Library"
#include "String.h"

class Client
{
public:
	Client(Library _lib) : lib(_lib) {}

	bool borrowBook(Book& b, User& u)
	{
		BorrowTransaction bt = BorrowTransaction(u, b, lib);
		bt.transaction();
	}
	bool returnBook(Book& b, User& u)
	{
		ReturnTransaction rt = ReturnTransaction(u, b, lib);
		rt.transaction();
	}

private:
	Library& lib;
};
