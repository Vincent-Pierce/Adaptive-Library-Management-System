#ifndef BOOKEXCEPTION_H
#define BOOKEXCEPTION_H

#include "LibraryException.h"
#include  <string>
class BookException : LibraryException {
public:
	BookException(std::string _msg) : LibraryException(_msg) {}
};

#endif // !BOOKEXCEPTION_H