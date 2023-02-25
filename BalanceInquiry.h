#ifndef BALANCEINQUIRY_H
#define BALANCEINQUIRY_H

#include "Transaction.h"

class BalanceInquiry : public Transaction
{
	public:
		BalanceInquiry(int,Screen &,BankDatabase &);
		virtual void execute();
};

#endif
