#ifndef TRANSACTION_H
#define TRANSACTION_H

class Screen;
class BankDatabase;

class Transaction
{
	public:
		Transaction(int,Screen &,BankDatabase &);
		virtual ~Transaction() {}
		int getAccountNumber() const;
		Screen &getScreen() const;
		BankDatabase &getBankDatabase() const;
		virtual void execute() = 0;
	private:
		int accountNumber;
		Screen &screen;
		BankDatabase &bankDatabase;
};

#endif
