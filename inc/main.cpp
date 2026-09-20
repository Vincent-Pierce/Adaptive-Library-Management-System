#include "LibraryException.h"
#include "Library.h"
#include "Transaction.h"
#include "Client.h"
#include <iostream>

int main() {
	// Example usage of the Library Management System view tests folder for in depth testing

	Library& lib = Library::Instance(); // get or init singleton
	Client c	 = Client(lib);
	Book   b	 = Book(false, "George Orwell", "Nineteen Eighty-Four");
	User   u	 = User("VP", 132610241, {});
	try {
		c.borrowBook(b, u);
	}
	catch (const BookException& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;

}