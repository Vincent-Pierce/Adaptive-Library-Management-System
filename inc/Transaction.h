#ifndef TRANSACTION_H
#define TRANSACTION_H

// Command Design pattern
class Transaction {
public:
	virtual void transaction() = 0;
	virtual ~Transaction() = default;
};

#endif // !TRANSACTION_H