#pragma once

#include "Transaction.h"
#include "BookException.h"
#include "String.h"

class ReturnTransaction : public Transaction {
public:
	ReturnTransaction(Library& _lib, Book& _book, User& _user)
		: user(_user), book(_book), lib(_lib) {}

	void transaction() override {
		if (user.removeBook(book))
			lib.returnBook(book);
		else
			throw BookException();
	}

private:
	Library& lib;
	Book& book;
	User& user;
};

