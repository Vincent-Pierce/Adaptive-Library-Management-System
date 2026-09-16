#pragma once

#include <exception>
#include "String.h"

class LibraryException : public std::exception {

public:
	explicit LibraryException(std::string _msg) : message(_msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
private:
	std::string message;

};
