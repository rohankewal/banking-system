#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

using namespace std;

// Account class which Savings and Checking will inherite from
class Account
{
private:
	int accountNum;
	string holderName;

protected:
	double balance; // Protected so derived classes can access in withdraw()

public:
	Account(int an, double bal, string hn);

	// Getters
	int getAccountNum();
	double getBalance();
	string getHolderName();

	// Setter(s)
	void setHolderName(string n);

	bool deposite(double amount);
	virtual bool withdraw(double amount);
};

#endif
