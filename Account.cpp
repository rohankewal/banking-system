#include "Account.h"

Account::Account(int an, double bal, string hn, int p)
{
	accountNum = an;
	balance = bal;
	holderName = hn;
	pin = p;
	failedAttempts = 0;
	lockoutTime = 0;
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
		failedAttempts++;
		if (failedAttempts >= 3)
		{
			lockoutTime = time(0); // Record when the lockout started
			failedAttempts = 0;
		}
		return false;
	}
	failedAttempts = 0; // Reset on successful login
	return true;
}

bool Account::isLocked()
{
	if (lockoutTime == 0)
		return false;

	double secondsPassed = difftime(time(0), lockoutTime);
	if (secondsPassed < 300) // 300 seconds = 5 minutes
	{
		int remaining = 300 - (int)secondsPassed;
		cout << "Account is locked. Try again in " << remaining / 60 << " min " << remaining % 60 << " sec." << endl;
		return true;
	}

	// Lockout expired, reset
	lockoutTime = 0;
	return false;
}
