#include "CheckingAccount.h"

CheckingAccount::CheckingAccount(int an, double bal, string hn, double odLimit, double odFee)
	: Account(an, bal, hn)
{
	overdraftLimit = odLimit;
	overdraftFee = odFee;
}

// Getters
double CheckingAccount::getOverdraftLimit()
{
	return overdraftLimit;
}

double CheckingAccount::getOverdraftFee()
{
	return overdraftFee;
}

bool CheckingAccount::withdraw(double amount)
{
	if (amount <= 0)
	{
		return false;
	}
	// Allow overdraft up to the limit
	if (balance - amount < -overdraftLimit)
	{
		cout << "Exceeds overdraft limit." << endl;
		return false;
	}
	// Apply overdraft fee if going negative
	if (balance - amount < 0 && balance >= 0)
	{
		balance -= overdraftFee;
		cout << "Overdraft fee of $" << overdraftFee << " applied." << endl;
	}
	balance -= amount;
	return true;
}
