#pragma once

#include "Searchable.h"
#include "Book.h"
#include "User.h"
#include "Transaction.h"
#include "Library.h"
#include "BookException.h"
#include "String.h"

class BorrowTransaction : public Transaction {
public:
	BorrowTransaction(Library& _lib, Book& _book, User& _user)
		: user(_user), book(_book), lib(_lib) {}

	void transaction() override {
		if (book.isAvailable())
		{
			user.addBook(book);
			user.charge();
			lib.borrowBook(book);
		}
		else
			throw BookException();
	}

private:
	Library& lib;
	Book& book;
	User& user;
};

