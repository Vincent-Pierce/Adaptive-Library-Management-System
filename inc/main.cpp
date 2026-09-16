#include "LibraryException.h"
#include "Library.h"
#include "Transaction.h"
#include "client.h"

int main() {
	Library& lib = Library::Instance(); // get or init singleton
	Client c	 = Client(lib);
	Book   b	 = Book(false, "George Orwell", "Nineteen Eighty-Four");
	User   u	 = User("VP", 132610241, 0.0, {});
	try {
		c.borrowBook(b, u);
	}
	catch (const BookException& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;

}