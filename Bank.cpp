#include "Bank.h"
#include <cstdlib>
#include <ctime>

Bank::Bank(string name)
{
	bankName = name;
	nextAccountNum = 1000;
	srand(time(0));
	adminPasswordHash = hash<string>{}("admin123"); // Default admin password
}

// Getters
string Bank::getBankName()
{
	return bankName;
}

// Account management
int Bank::createSavingsAccount(string holderName, double initialDeposit)
{
	double rate = 0.02; // Bank sets 2% interest rate
	int accNum = nextAccountNum++;
	// Create PIN
	int pin = rand() % 9000 + 1000;
	accounts[accNum] = new SavingsAccount(accNum, holderName, initialDeposit, rate, pin);
	cout << "Your PIN is: " << pin << " - NOTE: WRITE THIS DOWN AS YOU WON'T SEE THIS AGAIN AND DO NOT SHARE THIS WITH ANYONE" << endl;
	saveData();
	return accNum;
}

int Bank::createCheckingAccount(string holderName, double initialDeposit)
{
	double odLimit = 500.0; // Bank sets $500 overdraft limit
	double odFee = 35.0;	// Bank sets $35 overdraft fee
	int accNum = nextAccountNum++;
	// Create PIN
	int pin = rand() % 9000 + 1000;
	accounts[accNum] = new CheckingAccount(accNum, initialDeposit, holderName, odLimit, odFee, pin);
	cout << "Your PIN is: " << pin << " - NOTE: WRITE THIS DOWN AS YOU WON'T SEE THIS AGAIN AND DO NOT SHARE THIS WITH ANYONE" << endl;
	saveData();
	return accNum;
}

bool Bank::closeAccount(int accountNum)
{
	Account *acc = findAccount(accountNum);
	if (acc == nullptr)
	{
		return false;
	}
	delete acc;
	accounts.erase(accountNum);
	saveData();
	return true;
}

Account *Bank::findAccount(int accountNum)
{
	if (accounts.find(accountNum) != accounts.end())
	{
		return accounts[accountNum];
	}
	return nullptr;
}

// Operations (these use Account's public methods internally)
bool Bank::deposit(int accountNum, double amount)
{
	Account *acc = findAccount(accountNum);
	if (acc == nullptr)
	{
		return false;
	}
	bool result = acc->deposite(amount);
	if (result)
		saveData();
	return result;
}

bool Bank::withdraw(int accountNum, double amount)
{
	Account *acc = findAccount(accountNum);
	if (acc == nullptr)
	{
		return false;
	}
	bool result = acc->withdraw(amount);
	if (result)
		saveData();
	return result;
}

bool Bank::transfer(int fromAccNum, int toAccNum, double amount)
{
	Account *from = findAccount(fromAccNum);
	Account *to = findAccount(toAccNum);
	if (from == nullptr || to == nullptr)
	{
		return false;
	}
	if (from->withdraw(amount))
	{
		to->deposite(amount);
		saveData();
		return true;
	}
	return false;
}

// Admin
bool Bank::verifyAdmin(string password)
{
	return hash<string>{}(password) == adminPasswordHash;
}

void Bank::unlockAccount(int accountNum)
{
	Account *acc = findAccount(accountNum);
	if (acc == nullptr)
	{
		cout << "Account not found." << endl;
		return;
	}
	acc->resetLockout();
	cout << "Account " << accountNum << " has been unlocked." << endl;
}

// File persistence
void Bank::saveData()
{
	ofstream file(dataFile, ios::binary);
	if (!file)
	{
		cout << "Error: Could not save data." << endl;
		return;
	}

	// Write bank header
	size_t nameLen = bankName.size();
	file.write(reinterpret_cast<char *>(&nameLen), sizeof(nameLen));
	file.write(bankName.c_str(), nameLen);
	file.write(reinterpret_cast<char *>(&nextAccountNum), sizeof(nextAccountNum));
	file.write(reinterpret_cast<char *>(&adminPasswordHash), sizeof(adminPasswordHash));

	// Write account count
	size_t count = accounts.size();
	file.write(reinterpret_cast<char *>(&count), sizeof(count));

	// Write each account
	for (auto &pair : accounts)
	{
		Account *acc = pair.second;

		// Determine and write account type
		int type;
		SavingsAccount *sa = dynamic_cast<SavingsAccount *>(acc);
		CheckingAccount *ca = dynamic_cast<CheckingAccount *>(acc);
		if (sa != nullptr)
			type = 1;
		else
			type = 2;
		file.write(reinterpret_cast<char *>(&type), sizeof(type));

		// Write base Account fields
		int accNum = acc->getAccountNum();
		file.write(reinterpret_cast<char *>(&accNum), sizeof(accNum));

		string name = acc->getHolderName();
		size_t holderLen = name.size();
		file.write(reinterpret_cast<char *>(&holderLen), sizeof(holderLen));
		file.write(name.c_str(), holderLen);

		double bal = acc->getBalance();
		file.write(reinterpret_cast<char *>(&bal), sizeof(bal));

		size_t pin = acc->getPin();
		file.write(reinterpret_cast<char *>(&pin), sizeof(pin));

		int fa = acc->getFailedAttempts();
		file.write(reinterpret_cast<char *>(&fa), sizeof(fa));

		time_t lt = acc->getLockoutTime();
		file.write(reinterpret_cast<char *>(&lt), sizeof(lt));

		// Write derived class fields
		if (sa != nullptr)
		{
			double rate = sa->getInterestRate();
			file.write(reinterpret_cast<char *>(&rate), sizeof(rate));
			int wLimit = sa->getWithdrawLimit();
			file.write(reinterpret_cast<char *>(&wLimit), sizeof(wLimit));
			int wCount = sa->getWithdrawCount();
			file.write(reinterpret_cast<char *>(&wCount), sizeof(wCount));
		}
		else
		{
			double odLimit = ca->getOverdraftLimit();
			file.write(reinterpret_cast<char *>(&odLimit), sizeof(odLimit));
			double odFee = ca->getOverdraftFee();
			file.write(reinterpret_cast<char *>(&odFee), sizeof(odFee));
		}
	}

	file.close();
}

void Bank::loadData()
{
	ifstream file(dataFile, ios::binary);
	if (!file)
	{
		// No file yet - first run, nothing to load
		return;
	}

	// Read bank header
	size_t nameLen;
	file.read(reinterpret_cast<char *>(&nameLen), sizeof(nameLen));
	bankName.resize(nameLen);
	file.read(&bankName[0], nameLen);
	file.read(reinterpret_cast<char *>(&nextAccountNum), sizeof(nextAccountNum));
	file.read(reinterpret_cast<char *>(&adminPasswordHash), sizeof(adminPasswordHash));

	// Read account count
	size_t count;
	file.read(reinterpret_cast<char *>(&count), sizeof(count));

	// Read each account
	for (size_t i = 0; i < count; i++)
	{
		int type;
		file.read(reinterpret_cast<char *>(&type), sizeof(type));

		// Read base Account fields
		int accNum;
		file.read(reinterpret_cast<char *>(&accNum), sizeof(accNum));

		size_t holderLen;
		file.read(reinterpret_cast<char *>(&holderLen), sizeof(holderLen));
		string holderName(holderLen, ' ');
		file.read(&holderName[0], holderLen);

		double bal;
		file.read(reinterpret_cast<char *>(&bal), sizeof(bal));

		size_t pin;
		file.read(reinterpret_cast<char *>(&pin), sizeof(pin));

		int fa;
		file.read(reinterpret_cast<char *>(&fa), sizeof(fa));

		time_t lt;
		file.read(reinterpret_cast<char *>(&lt), sizeof(lt));

		if (type == 1) // SavingsAccount
		{
			double rate;
			file.read(reinterpret_cast<char *>(&rate), sizeof(rate));
			int wLimit;
			file.read(reinterpret_cast<char *>(&wLimit), sizeof(wLimit));
			int wCount;
			file.read(reinterpret_cast<char *>(&wCount), sizeof(wCount));

			accounts[accNum] = new SavingsAccount(
				accNum, holderName, bal, rate, pin, fa, lt, wLimit, wCount);
		}
		else // CheckingAccount
		{
			double odLimit;
			file.read(reinterpret_cast<char *>(&odLimit), sizeof(odLimit));
			double odFee;
			file.read(reinterpret_cast<char *>(&odFee), sizeof(odFee));

			accounts[accNum] = new CheckingAccount(
				accNum, bal, holderName, odLimit, odFee, pin, fa, lt);
		}
	}

	file.close();
}

// Reporting
void Bank::printAccountDetails(int accountNum)
{
	Account *acc = findAccount(accountNum);
	if (acc == nullptr)
	{
		cout << "Account not found." << endl;
		return;
	}
	cout << "Account #: " << acc->getAccountNum() << endl;
	cout << "Holder: " << acc->getHolderName() << endl;
	cout << "Balance: $" << acc->getBalance() << endl;
}

void Bank::printAllAccounts()
{
	if (accounts.empty())
	{
		cout << "No accounts." << endl;
		return;
	}
	for (auto &pair : accounts)
	{
		printAccountDetails(pair.first);
		cout << "---" << endl;
	}
}
