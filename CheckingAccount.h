#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

class CheckingAccount : public Account
{
private:
	double overdraftLimit;
	double overdraftFee;

public:
	CheckingAccount(int an, double bal, string hn, double odLimit, double odFee, int p);

	// Loading constructor (pin already hashed)
	CheckingAccount(int an, double bal, string hn, double odLimit, double odFee,
					size_t hashedPin, int fa, time_t lt);

	// Getters
	double getOverdraftLimit();
	double getOverdraftFee();

	bool withdraw(double amount) override;
};

#endif
