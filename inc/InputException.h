#pragma once

#include "BookException.h"
#include "String.h"

class InputException : LibraryException {
public:
	InputException(std::string _msg) : LibraryException(_msg) {}

};
