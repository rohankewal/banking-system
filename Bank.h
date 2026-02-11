#ifndef BANK_H
#define BANK_H

#include <map>
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include <functional>

class Bank
{
private:
	string bankName;
	map<int, Account *> accounts;
	int nextAccountNum;
	size_t adminPasswordHash;

public:
	Bank(string name);

	// Getters
	string getBankName();

	// Account management
	int createSavingsAccount(string holderName, double initialDeposit);
	int createCheckingAccount(string holderName, double initialDeposit);
	bool closeAccount(int accountNum);
	Account *findAccount(int accountNum);

	// Operations (these use Account's public methods internally)
	bool deposit(int accountNum, double amount);
	bool withdraw(int accountNum, double amount);
	bool transfer(int fromAccNum, int toAccNum, double amount);

	// Admin
	bool verifyAdmin(string password);
	void unlockAccount(int accountNum);

	// Reporting
	void printAccountDetails(int accountNum);
	void printAllAccounts();
};

#endif
