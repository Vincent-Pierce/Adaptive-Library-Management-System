#ifndef SEARCHABLE_H
#define SEARCHABLE_H
class Searchable {
public:
	virtual void search() = 0;
	virtual ~Searchable() = default;
};

#endif // !SEARCHABLE_H