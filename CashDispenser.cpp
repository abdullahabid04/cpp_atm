#include "CashDispenser.h"

CashDispenser::CashDispenser()
{
	count = INITIAL_COUNT;
}

void CashDispenser::dispenseCash(int amount)
{
	int billsRequired = amount/20;
	count -= billsRequired;
}

bool CashDispenser::isSufficientCashAvailable(int amount) const
{
	int billsRequired = amount/20;
	if(count >= billsRequired)
	{
		return true;
	}
	else
	{
		return false;
	}
}
