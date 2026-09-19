#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "Library.h"

class FileManager {
public:
    static void saveLibrary()
    {
        Library& lib = Library::Instance(); // Access the singleton Library instance
        std::filesystem::create_directories("log");
        std::filesystem::path filepath = "log/log.txt";
        std::ofstream file(filepath);
        for(const Book& b : lib.getBooks())
        {
            file << "Book: " << b.getAuthor() << ", " << b.getTitle() << ", Available: " << (b.isAvailable() ? "Yes" : "No") << std::endl;
        }        

        for(const User& u : lib.getUsers())
        {
            file << "User: " << u.getUserName() << ", ID: " << u.getUserId() << std::endl;
        }
    }

    static void loadLibrary()
    {
        Library& lib = Library::Instance(); // Access the singleton Library instance
        lib.clear(); // Clear existing data before loading
        std::filesystem::path filepath = "log/log.txt";
        if (!std::filesystem::exists(filepath)) {
            std::cerr << "File does not exist: " << filepath << std::endl;
            return;
        }

        std::ifstream file(filepath);
        std::string line;
        while (std::getline(file, line))
        {
            // Assuming the format is consistent with the saveLibraryToFile method
            if (line.rfind("Book: ", 0) == 0) // Check if line starts with "Book: "
            {
                size_t authorStart = line.find(": ") + 2;
                size_t authorEnd = line.find(", ", authorStart);
                std::string author = line.substr(authorStart, authorEnd - authorStart);

                size_t titleStart = authorEnd + 2;
                size_t titleEnd = line.find(", Available: ", titleStart);
                std::string title = line.substr(titleStart, titleEnd - titleStart);

                bool available = (line.substr(titleEnd + 13) == "Yes");

                Book book(available, author, title);
                lib.addBook(book);
            }
            else if (line.rfind("User: ", 0) == 0) // Check if line starts with "User: "
            {
                size_t nameStart = line.find(": ") + 2;
                size_t nameEnd = line.find(", ID: ", nameStart);
                std::string name = line.substr(nameStart, nameEnd - nameStart);

                size_t idStart = nameEnd + 6;
                int userId = std::stoi(line.substr(idStart));

                User user(name, userId, {});
                lib.addUser(user);
            }
        }
    }

private:
    FileManager() = default; // Private constructor to prevent instantiation
};

#endif // !FILEMANAGER_H
