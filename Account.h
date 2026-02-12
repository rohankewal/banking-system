#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <ctime>
#include <functional>
#include <fstream>

using namespace std;

// Account class which Savings and Checking will inherite from
class Account
{
	friend class Bank; // Bank needs access for save/load

private:
	int accountNum;
	string holderName;
	size_t pin;
	int failedAttempts;
	time_t lockoutTime;

protected:
	double balance; // Protected so derived classes can access in withdraw()

	// Loading constructor - pin is already hashed from file
	Account(int an, double bal, string hn, size_t hashedPin, int fa, time_t lt);

public:
	Account(int an, double bal, string hn, int p);

	// Getters
	int getAccountNum();
	double getBalance();
	string getHolderName();
	size_t getPin();
	int getFailedAttempts();
	time_t getLockoutTime();

	// Setter(s)
	void setHolderName(string n);

	bool deposite(double amount);
	virtual bool withdraw(double amount);
	bool verifyPin(int enteredPin);
	bool isLocked();
	void resetLockout();
};

#endif
