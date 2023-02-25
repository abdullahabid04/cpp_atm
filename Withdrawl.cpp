#include "Withdrawl.h"
#include "Screen.h"
#include "BankDatabase.h"
#include "Keypad.h"
#include "CashDispenser.h"

const static int CANCELLED = 6;

Withdrawl::Withdrawl(int userAccountNumber,Screen &atmScreen,BankDatabase &atmBankDatabase,Keypad &atmKeypad,CashDispenser &atmCashDispenser)
: Transaction(userAccountNumber,atmScreen,atmBankDatabase),keypad(atmKeypad),cashDispenser(atmCashDispenser)
{
}

void Withdrawl::execute()
{
	bool cashDispensed = false;
	bool transactionCancelled = false;
	BankDatabase &bankDatabase = getBankDatabase();
	Screen &screen = getScreen();
	do
	{
		int selection = displayMenuOfAmounts();
		if(selection != CANCELLED)
		{
			amount = selection;
			double availableBalance = bankDatabase.getAvailableBalance(getAccountNumber());
			double totalBalance = bankDatabase.getTotalBalance(getAccountNumber());
			if(amount <= availableBalance)
			{
				if(cashDispenser.isSufficientCashAvailable(amount))
				{
					bankDatabase.debit(getAccountNumber(),amount);
					cashDispenser.dispenseCash(amount);
					cashDispensed = true;
					screen.displayMessageLine("\nPlease take youe cash from the cash dispenser");
				}
				else
				{
					screen.displayMessageLine("\nInsufficient cash available in the atm.\n\nPlease choose a smaller amount.");
				}
			}
			else
			{
				screen.displayMessageLine("\nInsufficient funds in your account.\n\nPlease choose a smaller amount");
			}
		}
		else
		{
			screen.displayMessageLine("Cancelling transaction...");
			transactionCancelled = true;
		}
	}while(!cashDispensed && !transactionCancelled);
}

int Withdrawl::displayMenuOfAmounts() const
{
	int userChoice = 0;
	Screen &screen = getScreen();
	int amounts[] = {0,20,40,60,100,200};
	screen.displayMessageLine("\nWithdrawl options");
	screen.displayMessageLine("1 - $20");
	screen.displayMessageLine("2 - $40");
	screen.displayMessageLine("3 - $60");
	screen.displayMessageLine("4 - $100");
	screen.displayMessageLine("5 - $200");
	screen.displayMessageLine("6 - Cancelling transaction");
	screen.displayMessageLine("\n choose a withdrawl opyion(1-6):");
	int input = keypad.getInput();
	switch(input)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			userChoice = amounts[input];
			break;
		case CANCELLED:
			userChoice = CANCELLED;
			break;
		default:
			screen.displayMessageLine("\nInvalid selection.Try again");
			break;
	}
	return userChoice;
}

