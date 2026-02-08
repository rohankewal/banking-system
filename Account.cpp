#include "Account.h"

Account::Account(int an, double bal, string hn, int p)
{
	accountNum = an;
	balance = bal;
	holderName = hn;
	pin = p;
}

// Getters
int Account::getAccountNum()
{
	return accountNum;
}

double Account::getBalance()
{
	return balance;
}

string Account::getHolderName()
{
	return holderName;
}

// Setter(s)
void Account::setHolderName(string n)
{
	holderName = n;
}

bool Account::deposite(double amount)
{
	if (amount <= 0)
	{
		return false;
	}
	balance += amount;
	return true;
}

bool Account::withdraw(double amount)
{
	if (amount <= 0 || amount > balance)
	{
		return false;
	}
	balance -= amount;
	return true;
}

bool Account::verifyPin(int enteredPin)
{
	if (enteredPin != pin)
	{
		return false;
	}
	return true;
}
