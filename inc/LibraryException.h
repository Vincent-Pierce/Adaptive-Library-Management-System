#ifndef LIBRARYEXCEPTION_H
#define LIBRARYEXCEPTION_H

#include <exception>
#include  <string>
class LibraryException : public std::exception {

public:
	explicit LibraryException(std::string _msg) : message(_msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
private:
	std::string message;

};

#endif // !LIBRARYEXCEPTION_H