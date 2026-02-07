#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

class CheckingAccount : public Account
{
private:
	double overdraftLimit;
	double overdraftFee;

public:
	CheckingAccount(int an, double bal, string hn, double odLimit, double odFee);

	// Getters
	double getOverdraftLimit();
	double getOverdraftFee();

	bool withdraw(double amount) override;
};

#endif
