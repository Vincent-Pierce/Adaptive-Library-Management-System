#ifndef RETURNTRANSACTION_H
#define RETURNTRANSACTION_H

#include "Transaction.h"
#include "Library.h"
#include "Book.h"
#include "User.h"
#include "BookException.h"
#include  <string> 
class ReturnTransaction : public Transaction {
public:
	ReturnTransaction(Library& _lib, Book& _book, User& _user)
		: user(_user), book(_book), lib(_lib) {}

	void transaction() override {
		if (user.returnBook(book))
		{
			lib.removeUser(user);
			book.setAvailable(true);
		}
		else
			throw BookException("User does not have this book to return.\n");
	}

private:
	Library& lib;
	Book& book;
	User& user;
};

#endif // !RETURNTRANSACTION_H