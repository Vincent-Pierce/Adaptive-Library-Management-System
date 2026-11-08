#ifndef TRANSACTION_H
#define TRANSACTION_H

// Command Design pattern
class Transaction {
public:
	// Postcondition: normal return means the requested operation completed.
	// A library/domain failure is reported by throwing LibraryException or a
	// derived exception. Implementations do not promise rollback on failure.
	virtual void transaction() = 0;
	virtual ~Transaction() = default;
};

#endif // !TRANSACTION_H