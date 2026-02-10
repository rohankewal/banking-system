#include "Bank.h"

// Wrote this function to make the pin auth code less repetitive in the switch statements
Account *authenticateUser(Bank &bank)
{
	int accNum;
	int pin;
	cout << "Account number: ";
	cin >> accNum;

	Account *acc = bank.findAccount(accNum);
	if (acc == nullptr)
	{
		cout << "Account not found." << endl;
		return nullptr;
	}

	if (acc->isLocked())
		return nullptr;

	int attempts = 3;
	while (attempts > 0)
	{
		cout << "Enter your 4 digit PIN: ";
		cin >> pin;

		if (acc->verifyPin(pin))
			return acc;

		attempts--;
		if (attempts > 0)
			cout << "Incorrect PIN. " << attempts << " attempt(s) remaining." << endl;
	}

	cout << "Account has been locked for 5 minutes." << endl;
	return nullptr;
}

// Check for proper amount entered
double getValidAmount(string prompt)
{
	double amount;
	cout << prompt;
	while (!(cin >> amount))
	{
		cout << "That is not a valid ammount.  Please try again: $";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return amount;
}

int main()
{
	Bank bank("K Trust");
	int userChoice = 0;

	while (true)
	{
		cout << "\n===== " << bank.getBankName() << " =====" << endl;
		cout << "1. Open Account" << endl;
		cout << "2. Close Account" << endl;
		cout << "3. Deposit" << endl;
		cout << "4. Withdraw" << endl;
		cout << "5. Transfer" << endl;
		cout << "6. Check Balance" << endl;
		cout << "7. Print All Accounts" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter choice: ";
		cin >> userChoice;

		switch (userChoice)
		{
		case 1:
		{
			int accType;
			cout << "1. Savings Account" << endl;
			cout << "2. Checking Account" << endl;
			cout << "Select account type: ";
			cin >> accType;

			if (accType != 1 && accType != 2)
			{
				cout << "Invalid account type." << endl;
				break;
			}

			string name;
			cout << "Enter name: ";
			cin.ignore();
			getline(cin, name);
			double deposit = getValidAmount("Initial deposite: $");

			int accNum;
			if (accType == 1)
				accNum = bank.createSavingsAccount(name, deposit);
			else
				accNum = bank.createCheckingAccount(name, deposit);

			cout << "Account created! Number: " << accNum << endl;
			break;
		}
		case 2:
		{
			Account *acc = authenticateUser(bank);
			if (acc == nullptr)
				break;

			if (bank.closeAccount(acc->getAccountNum()))
				cout << "Account closed." << endl;
			else
				cout << "Account not found." << endl;
			break;
		}
		case 3:
		{
			Account *acc = authenticateUser(bank);
			if (acc == nullptr)
				break;

			double amount = getValidAmount("Amount to deposit: $");
			if (bank.deposit(acc->getAccountNum(), amount))
				cout << "Deposit successful!" << endl;
			else
				cout << "Deposit failed." << endl;
			break;
		}
		case 4:
		{
			Account *acc = authenticateUser(bank);
			if (acc == nullptr)
				break;

			double amount = getValidAmount("Amount to withdraw: $");
			if (bank.withdraw(acc->getAccountNum(), amount))
				cout << "Withdrawal successful!" << endl;
			else
				cout << "Withdrawal failed." << endl;
			break;
		}
		case 5:
		{
			// Authenticate the sender
			cout << "--- From Account ---" << endl;
			Account *from = authenticateUser(bank);
			if (from == nullptr)
				break;

			int toAcc;
			cout << "To account number: ";
			cin >> toAcc;
			double amount = getValidAmount("Amount to transfer: $");
			if (bank.transfer(from->getAccountNum(), toAcc, amount))
				cout << "Transfer successful!" << endl;
			else
				cout << "Transfer failed." << endl;
			break;
		}
		case 6:
		{
			Account *acc = authenticateUser(bank);
			if (acc == nullptr)
				break;

			bank.printAccountDetails(acc->getAccountNum());
			break;
		}
		case 7:
			bank.printAllAccounts();
			break;
		case 0:
			cout << "Goodbye!" << endl;
			return 0;
		default:
			cout << "Invalid choice." << endl;
		}
	}
}
