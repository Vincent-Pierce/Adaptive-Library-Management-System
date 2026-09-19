#ifndef SEARCHABLE_H
#define SEARCHABLE_H
class Searchable {
public:
	virtual bool search(const std::string& query) = 0;
	virtual ~Searchable() = default;
};

#endif // !SEARCHABLE_H