#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

// SavingAccount class which will inherite from Account class
class SavingsAccount : public Account
{
private:
	double interestRate;
	int withdrawlLimit;
	int withdrawlCount;

public:
	SavingsAccount(int an, string hn, double initialDeposit, double rate, int p);

	// Loading constructor (pin already hashed)
	SavingsAccount(int an, string hn, double bal, double rate,
				   size_t hashedPin, int fa, time_t lt, int wLimit, int wCount);

	// Getters
	double getInterestRate();
	int getWithdrawLimit();
	int getWithdrawCount();

	// Actions which don't get or set data but are operations
	void applyInterest();
	void resetMonthlyWithdrawls();
	bool withdraw(double amount) override;
};

#endif
