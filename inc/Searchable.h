#ifndef SEARCHABLE_H
#define SEARCHABLE_H

#include <string>

class Searchable {
public:
	// Contract:
	// Pre-Condition:query cannot be an empty string otherwise return false
	// The query string must be checked for any string attributes or integer attributes
	virtual bool search(const std::string& query) const = 0;
	virtual ~Searchable() = default;
};

class SearchStrategy {
public:
	// Contract:
	// Pre-Condition:query cannot be an empty string otherwise return false
	virtual bool search(const std::string& query) const = 0;
	virtual ~SearchStrategy() = default;
};
#endif // !SEARCHABLE_H