#ifndef BANKDATABASE_H
#define BANKDATABASE_H

#include "Account.h"
#include<cstdlib>
#include<vector>
using namespace std;

class BankDatabase
{
	public:
		BankDatabase();
		bool authenticateUser(int,int);
		double getAvailableBalance(int);
		double getTotalBalance(int);
		void credit(int,double);
		void debit(int,double);		
	private:
		vector<Account> accounts;
		Account *getAccount(int);
};

#endif
