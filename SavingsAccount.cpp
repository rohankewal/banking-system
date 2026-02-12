#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(int an, string hn, double initialDeposit, double rate, int pin)
	: Account(an, initialDeposit, hn, pin)
{
	interestRate = rate;
	withdrawlLimit = 6; // Standard limit
	withdrawlCount = 0;
}

// Loading constructor - for restoring from binary file
SavingsAccount::SavingsAccount(int an, string hn, double bal, double rate,
							   size_t hashedPin, int fa, time_t lt, int wLimit, int wCount)
	: Account(an, bal, hn, hashedPin, fa, lt)
{
	interestRate = rate;
	withdrawlLimit = wLimit;
	withdrawlCount = wCount;
}

// Getters
double SavingsAccount::getInterestRate()
{
	return interestRate;
}

int SavingsAccount::getWithdrawLimit()
{
	return withdrawlLimit;
}

int SavingsAccount::getWithdrawCount()
{
	return withdrawlCount;
}

// Actions which don't get or set data but are operations
void SavingsAccount::applyInterest()
{
	balance += balance * interestRate;
}

void SavingsAccount::resetMonthlyWithdrawls()
{
	withdrawlCount = 0;
}

bool SavingsAccount::withdraw(double amount)
{
	if (withdrawlCount >= withdrawlLimit)
	{
		cout << "Monthly withdrawal limit reached." << endl;
		return false;
	}
	if (amount <= 0 || amount > balance)
	{
		return false;
	}
	balance -= amount;
	withdrawlCount++;
	return true;
}
