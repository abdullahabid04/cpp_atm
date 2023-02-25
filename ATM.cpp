#include "ATM.h"
#include"Transaction.h"
#include"BalanceInquiry.h"
#include"Withdrawl.h"
#include"Deposit.h"

enum MenuOption {BALANCE_INQUIRY = 1,WITHDRAWL,DEPOSIT,EXIT};

ATM::ATM() : userAuthenticated(false),currentAccountNumber(0)
{
}

void ATM::run()
{
	while(true)
	{
		while(!userAuthenticated)
		{
			screen.displayMessageLine("\nWelcome");
			authenticateUser();
		}
		performTransaction();
		userAuthenticated = false;
		currentAccountNumber = 0;
		screen.displayMessageLine("\nThank You! Good Bye!");
	}
}

void ATM::authenticateUser()
{
	screen.displayMessage("\nPlease enter your account number: ");
	int accountNumber = keypad.getInput();
	screen.displayMessage("\nEnter your PIN: ");
	int pin = keypad.getInput();
	userAuthenticated = bankDatabase.authenticateUser(accountNumber,pin);
	if(userAuthenticated)
	{
		currentAccountNumber = accountNumber;
	}
	else
	{
		screen.displayMessageLine("Invalid account number or pin. Please try again.");
	}
}

void ATM::performTransaction()
{
	Transaction *currentTransactionPtr;
	bool userExited = false;
	while(!userExited)
	{
		int mainMenuSelection = displayMainMenu();
		switch(mainMenuSelection)
		{
			case BALANCE_INQUIRY:
			case WITHDRAWL:
			case DEPOSIT:
				currentTransactionPtr = createTransaction( mainMenuSelection );
				currentTransactionPtr->execute();
				delete currentTransactionPtr;
				break;
			case EXIT:
				screen.displayMessageLine("\nExiting the system...");
				userExited = true;
				break;
			default:
				screen.displayMessageLine("\nYou did not enter a valid selection. try again.");
				break;
		}
	}
}

int ATM::displayMainMenu() const
{
	screen.displayMessageLine("\nMain menu:");
	screen.displayMessageLine("1 - View my balance");
	screen.displayMessageLine("2 - Withdraw cash");
	screen.displayMessageLine("3 - Deposit funds");
	screen.displayMessageLine("4 - Exit\n");
	screen.displayMessageLine("Enter your choice: ");
	return keypad.getInput();
}

Transaction *ATM::createTransaction(int type)
{
	Transaction *tempPtr;
	switch(type)
	{
		case BALANCE_INQUIRY:
			tempPtr = new BalanceInquiry(currentAccountNumber,screen,bankDatabase);
			break;
		case WITHDRAWL:
			tempPtr = new Withdrawl(currentAccountNumber,screen,bankDatabase,keypad,cashDispenser);
			break;
		case DEPOSIT:
			tempPtr = new Deposit(currentAccountNumber,screen,bankDatabase,keypad,depositSlot);
			break;
	}
	return tempPtr;
}

