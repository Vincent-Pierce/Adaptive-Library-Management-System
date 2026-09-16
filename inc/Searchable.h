#pragma once

class Searchable {
public:
	virtual void search() = 0;
	virtual ~Searchable() = default;
};

