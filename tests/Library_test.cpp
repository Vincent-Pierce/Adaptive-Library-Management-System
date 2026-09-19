#include <gtest/gtest.h>
#include "Library.h"
#include "BorrowTransaction.h"
#include "ReturnTransaction.h"

TEST(LibraryTest, SearchAddBook) {
    Library* lib = Library::Instance(); 
    Book book(false, "Author", "Title");
    lib->addBook(book);
    EXPECT_EQ(lib->searchBook("Author"), true);
}

TEST(LibraryTest, SearchAddUser) {
    Library* lib = Library::Instance(); 
    User user("John", 1, {});
    lib->borrowBook(user);
    EXPECT_EQ(lib->searchUser("John"), true);
}

TEST(LibraryTest, RemoveUser) {
    Library* lib = Library::Instance(); 
    User user("Jane", 2, {});
    lib->borrowBook(user);
    EXPECT_EQ(lib->removeUser(user), true);
    EXPECT_EQ(lib->searchUser("Jane"), false);
}

TEST(LibraryTest, RemoveNonExistentUser) {
    Library* lib = Library::Instance(); 
    User user("NonExistent", 3, {});
    EXPECT_EQ(lib->removeUser(user), false);
}

TEST(LibraryTest, SearchNonExistentBook) {
    Library* lib = Library::Instance(); 
    EXPECT_EQ(lib->searchBook("NonExistent"), false);
}

TEST(LibraryTest, SearchNonExistentUser) {
    Library* lib = Library::Instance(); 
    EXPECT_EQ(lib->searchUser("NonExistent"), false);
}

TEST(LibraryTest, BorrowBook) {
    Library* lib = Library::Instance(); 
    Book book1(true, "Author1", "Title1");
    Book book2(true, "Author2", "Title2");
    User user1("User1", 4, {});
    User user2("User2", 5, {});

    lib->addBook(book1);
    lib->addBook(book2);

    BorrowTransaction bt1(*lib, book1, user1);
    user1.transaction(&bt1);
    EXPECT_EQ(user1.searchAuthor("Author1"), true);
    EXPECT_EQ(lib->searchUser("User1"), true);
}

TEST(LibraryTest, BorrowUnavailableBook) {
    Library* lib = Library::Instance(); 
    Book book(false, "Author3", "Title3");
    User user("User3", 6, {});

    lib->addBook(book);

    BorrowTransaction bt(*lib, book, user);
    EXPECT_THROW(user.transaction(&bt), BookException);
}

TEST(LibraryTest, ReturnBook) {
    Library* lib = Library::Instance(); 
    Book book(true, "Author4", "Title4");
    User user("User4", 7, {});

    lib->addBook(book);

    BorrowTransaction bt(*lib, book, user);
    user.transaction(&bt);
    EXPECT_EQ(user.searchAuthor("Author4"), true);
    EXPECT_EQ(lib->searchUser("User4"), true);
    EXPECT_EQ(book.isAvailable(), false);

    ReturnTransaction rt(*lib, book, user);
    user.transaction(&rt);
    EXPECT_EQ(user.searchAuthor("Author4"), false);
    EXPECT_EQ(lib->searchUser("User4"), false);
    EXPECT_EQ(book.isAvailable(), true);
}

TEST(LibraryTest, ReturnBookNotBorrowed) {
    Library* lib = Library::Instance(); 
    Book book(true, "Author5", "Title5");
    User user("User5", 8, {});

    lib->addBook(book);

    ReturnTransaction rt(*lib, book, user);
    EXPECT_THROW(user.transaction(&rt), BookException);
    EXPECT_EQ(book.isAvailable(), true);
}