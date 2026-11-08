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

	// Postcondition: on success, the book is available and no longer tracked by
	// the user; the user is removed from the library if no books remain.
	// Throws LibraryException (including BookException or InputException) when
	// the book cannot be returned or is not in the library.
	void transaction() override {
		const std::shared_ptr<Book> managedBook = lib.getBookPointer(book);
		if (user.returnBook(managedBook))
		{
			managedBook->returnBook();
			if(user.getBookCount() == 0)
				lib.removeUser(user);
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