#ifndef WITHDRAWL_H
#define WITHDRAWL_H

#include "Transaction.h"

class Keypad;
class CashDispenser;

class Withdrawl : public Transaction
{
	public:
		Withdrawl(int,Screen &,BankDatabase &,Keypad &,CashDispenser &);
		virtual void execute();
	private:
		int amount;
		Keypad &keypad;
		CashDispenser &cashDispenser;
		int displayMenuOfAmounts() const;
};

#endif
