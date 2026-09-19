#include <gtest/gtest.h>
#include "Library.h"
#include "BorrowTransaction.h"
#include "ReturnTransaction.h"
#include "FileManager.h"

class LibraryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear the library before each test
        Library::Instance().clear();
    }
};

TEST(LibraryTest, SearchAddBook) {
    Library& lib = Library::Instance(); 
    Book book(false, "Author", "Title");
    lib.addBook(book);
    EXPECT_EQ(lib.searchBook("Author"), true);
}

TEST(LibraryTest, SearchAddUser) {
    Library& lib = Library::Instance(); 
    User user("John", 1, {});
    lib.addUser(user);
    EXPECT_EQ(lib.searchUser("John"), true);
}

TEST(LibraryTest, RemoveUser) {
    Library& lib = Library::Instance(); 
    User user("Jane", 2, {});
    lib.addUser(user);
    EXPECT_EQ(lib.removeUser(user), true);
    EXPECT_EQ(lib.searchUser("Jane"), false);
}

TEST(LibraryTest, RemoveNonExistentUser) {
    Library& lib = Library::Instance(); 
    User user("NonExistent", 3, {});
    EXPECT_EQ(lib.removeUser(user), false);
}

TEST(LibraryTest, SearchNonExistentBook) {
    Library& lib = Library::Instance(); 
    EXPECT_EQ(lib.searchBook("NonExistent"), false);
}

TEST(LibraryTest, SearchNonExistentUser) {
    Library& lib = Library::Instance(); 
    EXPECT_EQ(lib.searchUser("NonExistent"), false);
}

TEST(LibraryTest, BorrowBook) {
    Library& lib = Library::Instance(); 
    Book book1(true, "Author1", "Title1");
    Book book2(true, "Author2", "Title2");
    User user1("User1", 4, {});
    User user2("User2", 5, {});

    lib.addBook(book1);
    lib.addBook(book2);

    BorrowTransaction bt1(lib, book1, user1);
    user1.transaction(&bt1);
    EXPECT_EQ(user1.searchAuthor("Author1"), true);
    EXPECT_EQ(lib.searchUser("User1"), true);
}

TEST(LibraryTest, BorrowUnavailableBook) {
    Library& lib = Library::Instance(); 
    Book book(false, "Author3", "Title3");
    User user("User3", 6, {});

    lib.addBook(book);

    BorrowTransaction bt(lib, book, user);
    EXPECT_THROW(user.transaction(&bt), BookException);
}

TEST(LibraryTest, ReturnBook) {
    Library& lib = Library::Instance(); 
    Book book(true, "Author4", "Title4");
    User user("User4", 7, {});

    lib.addBook(book);

    BorrowTransaction bt(lib, book, user);
    user.transaction(&bt);
    EXPECT_EQ(user.searchAuthor("Author4"), true);
    EXPECT_EQ(lib.searchUser("User4"), true);
    EXPECT_EQ(book.isAvailable(), false);

    ReturnTransaction rt(lib, book, user);
    user.transaction(&rt);
    EXPECT_EQ(user.searchAuthor("Author4"), false);
    EXPECT_EQ(lib.searchUser("User4"), false);
    EXPECT_EQ(book.isAvailable(), true);
}

TEST(LibraryTest, ReturnBookNotBorrowed) {
    Library& lib = Library::Instance(); 
    Book book(true, "Author5", "Title5");
    User user("User5", 8, {});

    lib.addBook(book);

    ReturnTransaction rt(lib, book, user);
    EXPECT_THROW(user.transaction(&rt), BookException);
    EXPECT_EQ(book.isAvailable(), true);
}

TEST(LibraryTest, LibrarySingleton) {
    Library& lib1 = Library::Instance();
    Library& lib2 = Library::Instance();
    EXPECT_EQ(&lib1, &lib2); // Both references should point to the same instance
}

TEST(LibraryTest, UserBookCount) {
    Library& lib = Library::Instance(); 
    Book book(true, "Author6", "Title6");
    User user("User6", 9, {});

    lib.addBook(book);

    BorrowTransaction bt(lib, book, user);
    user.transaction(&bt);
    EXPECT_EQ(user.getBookCount(), 1);

    ReturnTransaction rt(lib, book, user);
    user.transaction(&rt);
    EXPECT_EQ(user.getBookCount(), 0);
}

TEST(LibraryTest, RemoveUserAfterReturningAllBooks) {
    Library& lib = Library::Instance(); 
    Book book1(true, "Author7", "Title7");
    Book book2(true, "Author8", "Title8");
    User user("User7", 10, {});

    lib.addBook(book1);
    lib.addBook(book2);

    BorrowTransaction bt1(lib, book1, user);
    BorrowTransaction bt2(lib, book2, user);
    user.transaction(&bt1);
    user.transaction(&bt2);
    EXPECT_EQ(user.getBookCount(), 2);

    ReturnTransaction rt1(lib, book1, user);
    ReturnTransaction rt2(lib, book2, user);
    user.transaction(&rt1);
    user.transaction(&rt2);
    
    EXPECT_EQ(user.getBookCount(), 0);
    EXPECT_EQ(lib.searchUser("User7"), false); 
}

TEST(LibraryTest, FileManagerSaveLoad) {
    Library& lib = Library::Instance(); 
    Book book1(true, "Author9", "Title9");
    Book book2(false, "Author10", "Title10");
    User user1("User8", 11, {});
    User user2("User9", 12, {});

    lib.addBook(book1);
    lib.addBook(book2);
    lib.addUser(user1);
    lib.addUser(user2);

    FileManager::saveLibrary();
    
    // Clear the library and load from file
    lib.clear();
    FileManager::loadLibrary();

    EXPECT_EQ(lib.searchBook("Author9"), true);
    EXPECT_EQ(lib.searchBook("Author10"), true);
    EXPECT_EQ(lib.searchUser("User8"), true);
    EXPECT_EQ(lib.searchUser("User9"), true);
}