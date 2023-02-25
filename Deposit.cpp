#include "Deposit.h"
#include "Screen.h"
#include "BankDatabase.h"
#include "Keypad.h"
#include "DepositSlot.h"

const static int CANCELLED = 0;

Deposit::Deposit(int userAccountNumber,Screen &atmScreen,BankDatabase &atmBankDatabase,Keypad &atmKeypad,DepositSlot &atmDepositSlot)
: Transaction(userAccountNumber,atmScreen,atmBankDatabase),keypad(atmKeypad),depositSlot(atmDepositSlot)
{
}

void Deposit::execute()
{
	BankDatabase &bankDatabase = getBankDatabase();
	Screen &screen = getScreen();
	amount = promptForDepositAmount();
	if(amount != CANCELLED)
	{
		screen.displayMessage("\nPlease insert a deposit envelope containing ");
		screen.displayDollarAmount(amount);
		screen.displayMessageLine("in the deposit slot");
		bool envelopeRecieved = depositSlot.isEnvelopeRecieved();
		if(envelopeRecieved)
		{
			screen.displayMessageLine("Your envelope has been recieved.\nNOTE: the money just will not be available untill we \nverify the amount of any enclosed cash and any enclosed checks clear");
			bankDatabase.credit(getAccountNumber(),amount);
		}
		else
		{
			screen.displayMessageLine("\nYou did not insert an envelope so that the ATM has cancelled your transaction.");
		}
	}
	else
	{
		screen.displayMessageLine("\nCancelling transaction...");
	}
}

double Deposit::promptForDepositAmount() const
{
	Screen &screen = getScreen();
	screen.displayMessage("\nPlease enter a deposit amount in CENTS (or 0 to quit): ");
	int input = keypad.getInput();
	if(input == CANCELLED)
	{
		return CANCELLED;
	}
	else
	{
		return static_cast<double>(input)/100;
	}
}

