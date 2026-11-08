#ifndef SEARCH_STRATEGIES_H
#define SEARCH_STRATEGIES_H

#include "Book.h"
#include "Searchable.h"
#include "User.h"
#include <memory>
#include <string>
#include <vector>

class BookSearchStrategy : public SearchStrategy
{
public:
	explicit BookSearchStrategy(const std::vector<std::shared_ptr<Book>>& books)
		: books(books) {}

	bool search(const std::string& query) const override
	{
		if (query.empty())
			return false;

		for (const std::shared_ptr<Book>& book : books)
		{
			if (book->search(query))
				return true;
		}
		return false;
	}

private:
	const std::vector<std::shared_ptr<Book>>& books;
};

class UserSearchStrategy : public SearchStrategy
{
public:
	explicit UserSearchStrategy(const std::vector<User>& users)
		: users(users) {}

	bool search(const std::string& query) const override
	{
		if (query.empty())
			return false;

		for (const User& user : users)
		{
			if (user.search(query))
				return true;
		}
		return false;
	}

private:
	const std::vector<User>& users;
};

#endif // !SEARCH_STRATEGIES_H
