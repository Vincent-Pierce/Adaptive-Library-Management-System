#ifndef BORROW_TRANSACTION_H
#define BORROW_TRANSACTION_H

#include "Searchable.h"
#include "Book.h"
#include "User.h"
#include "Transaction.h"
#include "Library.h"
#include "BookException.h"
#include  <string> 

class BorrowTransaction : public Transaction {
public:
	BorrowTransaction(Library& _lib, Book& _book, User& _user)
		: user(_user), book(_book), lib(_lib) {}

	// Implementation of transaction for borrowing book. 
	void transaction() override {
		const std::shared_ptr<Book> managedBook = lib.getBookPointer(book);
		if (managedBook->isAvailable())
		{
			managedBook->borrow();
			user.addBook(managedBook);
			lib.addUser(user);
		}
		else
			throw BookException("Book is not available for borrowing.\n");
	}

private:
	Library& lib;
	Book& book;
	User& user;
};

#endif // !BORROW_TRANSACTION_H