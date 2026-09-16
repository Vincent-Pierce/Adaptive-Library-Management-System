#pragma once

// Command Design pattern
class Transaction {
public:
	virtual void transaction() = 0;
	virtual ~Transaction() = default;
};

