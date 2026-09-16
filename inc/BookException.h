#pragma once

#include "LibraryException.h"
#include "String.h"

class BookException : LibraryException {
public:
	BookException(std::string _msg) : LibraryException(_msg) {}
};
