#ifndef INPUTEXCEPTION_H
#define INPUTEXCEPTION_H

#include "LibraryException.h"
#include  <string> 
class InputException : public LibraryException {
public:
	InputException(std::string _msg) : LibraryException(_msg) {}

};

#endif // !INPUTEXCEPTION_H