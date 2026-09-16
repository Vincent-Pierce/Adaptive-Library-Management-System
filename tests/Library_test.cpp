#include <gtest/gtest.h>

#include "Library.h"

TEST(LibraryTest, AddBook) {
    Library* lib = Library::Instance(); 
    Book book(false, "Author", "Title");
    lib->addBook(book);
    EXPECT_EQ(lib->search(book), true);
}