#include "Bank.h"
#include <cstdlib>
#include <ctime>

Bank::Bank(string name)
{
	bankName = name;
	nextAccountNum = 1000;
	srand(time(0));
	adminPasswordHash = hash<string>{}("admin123"); // Default admin password
}

// Getters
string Bank::getBankName()
{
	return bankName;
}

// Account management
int Bank::createSavingsAccount(string holderName, double initialDeposit)
{
	double rate = 0.02; // Bank sets 2% interest rate
	int accNum = nextAccountNum++;
	// Create PIN
	int pin = rand() % 9000 + 1000;
	accounts[accNum] = new SavingsAccount(accNum, holderName, initialDeposit, rate, pin);
	cout << "Your PIN is: " << pin << " - NOTE: WRITE THIS DOWN AS YOU WON'T SEE THIS AGAIN AND DO NOT SHARE THIS WITH ANYONE" << endl;
	return accNum;
}

int Bank::createCheckingAccount(string holderName, double initialDeposit)
{
	double odLimit = 500.0; // Bank sets $500 overdraft limit
	double odFee = 35.0;	// Bank sets $35 overdraft fee
	int accNum = nextAccountNum++;
	// Create PIN
	int pin = rand() % 9000 + 1000;
	accounts[accNum] = new CheckingAccount(accNum, initialDeposit, holderName, odLimit, odFee, pin);
	cout << "Your PIN is: " << pin << " - NOTE: WRITE THIS DOWN AS YOU WON'T SEE THIS AGAIN AND DO NOT SHARE THIS WITH ANYONE" << endl;
	return accNum;
}

bool Bank::closeAccount(int accountNum)
{
	Account *acc = findAccount(accountNum);
	if (acc == nullptr)
	{
		return false;
	}
	delete acc;
	accounts.erase(accountNum);
	return true;
}

Account *Bank::findAccount(int accountNum)
{
	if (accounts.find(accountNum) != accounts.end())
	{
		return accounts[accountNum];
	}
	return nullptr;
}

// Operations (these use Account's public methods internally)
bool Bank::deposit(int accountNum, double amount)
{
	Account *acc = findAccount(accountNum);
	if (acc == nullptr)
	{
		return false;
	}
	return acc->deposite(amount);
}

bool Bank::withdraw(int accountNum, double amount)
{
	Account *acc = findAccount(accountNum);
	if (acc == nullptr)
	{
		return false;
	}
	return acc->withdraw(amount);
}

bool Bank::transfer(int fromAccNum, int toAccNum, double amount)
{
	Account *from = findAccount(fromAccNum);
	Account *to = findAccount(toAccNum);
	if (from == nullptr || to == nullptr)
	{
		return false;
	}
	if (from->withdraw(amount))
	{
		to->deposite(amount);
		return true;
	}
	return false;
}

// Admin
bool Bank::verifyAdmin(string password)
{
	return hash<string>{}(password) == adminPasswordHash;
}

void Bank::unlockAccount(int accountNum)
{
	Account *acc = findAccount(accountNum);
	if (acc == nullptr)
	{
		cout << "Account not found." << endl;
		return;
	}
	acc->resetLockout();
	cout << "Account " << accountNum << " has been unlocked." << endl;
}

// Reporting
void Bank::printAccountDetails(int accountNum)
{
	Account *acc = findAccount(accountNum);
	if (acc == nullptr)
	{
		cout << "Account not found." << endl;
		return;
	}
	cout << "Account #: " << acc->getAccountNum() << endl;
	cout << "Holder: " << acc->getHolderName() << endl;
	cout << "Balance: $" << acc->getBalance() << endl;
}

void Bank::printAllAccounts()
{
	if (accounts.empty())
	{
		cout << "No accounts." << endl;
		return;
	}
	for (auto &pair : accounts)
	{
		printAccountDetails(pair.first);
		cout << "---" << endl;
	}
}
