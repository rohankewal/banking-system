#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <ctime>
#include <functional>

using namespace std;

// Account class which Savings and Checking will inherite from
class Account
{
private:
	int accountNum;
	string holderName;
	size_t pin;
	int failedAttempts;
	time_t lockoutTime;

protected:
	double balance; // Protected so derived classes can access in withdraw()

public:
	Account(int an, double bal, string hn, int p);

	// Getters
	int getAccountNum();
	double getBalance();
	string getHolderName();

	// Setter(s)
	void setHolderName(string n);

	bool deposite(double amount);
	virtual bool withdraw(double amount);
	bool verifyPin(int enteredPin);
	bool isLocked();
	void resetLockout();
};

#endif
