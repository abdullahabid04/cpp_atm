#ifndef CASHDISPENSER_H
#define CASHDISPENSER_H

class CashDispenser
{
	public:
		CashDispenser();
		void dispenseCash(int);
		bool isSufficientCashAvailable(int) const;
	private:
		const static int INITIAL_COUNT = 500;
		int count;
};

#endif
