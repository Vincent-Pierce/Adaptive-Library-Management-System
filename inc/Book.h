#pragma once

#include "Searchable"
#include "String.h"

class Book : Searchable {
public:
	Book(bool _available, std::String _author, std::String _title) : available(_available), author(_author), title(_title)  {};

	bool isAvailable() { return this->available; }
	void search()      {} //Todo

private:
	bool available;
	std::String author;
	std::String title;
};

