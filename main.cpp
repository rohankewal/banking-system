#include "Bank.h"

// Wrote this function to make the pin auth code less repetitive in the switch statements
Account *authenticateUser(Bank &bank)
{
	int accNum;
	int pin;
	cout << "Account number: ";
	cin >> accNum;
	cout << "Enter your 4 digit PIN: ";
	cin >> pin;

	Account *acc = bank.findAccount(accNum);
	if (acc == nullptr || !acc->verifyPin(pin))
	{
		cout << "Invalid account or PIN." << endl;
		return nullptr;
	}
	return acc;
}

int main()
{
	Bank bank("K Trust");
	int userChoice = 0;

	while (true)
	{
		cout << "\n===== " << bank.getBankName() << " =====" << endl;
		cout << "1. Open Savings Account" << endl;
		cout << "2. Open Checking Account" << endl;
		cout << "3. Close Account" << endl;
		cout << "4. Deposit" << endl;
		cout << "5. Withdraw" << endl;
		cout << "6. Transfer" << endl;
		cout << "7. Check Balance" << endl;
		cout << "8. Print All Accounts" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter choice: ";
		cin >> userChoice;

		switch (userChoice)
		{
		case 1:
		{
			string name;
			double deposit;
			cout << "Enter name: ";
			cin.ignore();
			getline(cin, name);
			cout << "Initial deposit: $";
			cin >> deposit;
			int accNum = bank.createSavingsAccount(name, deposit);
			cout << "Savings account created! Number: " << accNum << endl;
			break;
		}
		case 2:
		{
			string name;
			double deposit;
			cout << "Enter name: ";
			cin.ignore();
			getline(cin, name);
			cout << "Initial deposit: $";
			cin >> deposit;
			int accNum = bank.createCheckingAccount(name, deposit);
			cout << "Checking account created! Number: " << accNum << endl;
			break;
		}
		case 3:
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
		case 4:
		{
			Account *acc = authenticateUser(bank);
			if (acc == nullptr)
				break;

			double amount;
			cout << "Amount to deposit: $";
			cin >> amount;
			if (bank.deposit(acc->getAccountNum(), amount))
				cout << "Deposit successful!" << endl;
			else
				cout << "Deposit failed." << endl;
			break;
		}
		case 5:
		{
			Account *acc = authenticateUser(bank);
			if (acc == nullptr)
				break;

			double amount;
			cout << "Amount to withdraw: $";
			cin >> amount;
			if (bank.withdraw(acc->getAccountNum(), amount))
				cout << "Withdrawal successful!" << endl;
			else
				cout << "Withdrawal failed." << endl;
			break;
		}
		case 6:
		{
			// Authenticate the sender
			cout << "--- From Account ---" << endl;
			Account *from = authenticateUser(bank);
			if (from == nullptr)
				break;

			int toAcc;
			double amount;
			cout << "To account number: ";
			cin >> toAcc;
			cout << "Amount to transfer: $";
			cin >> amount;
			if (bank.transfer(from->getAccountNum(), toAcc, amount))
				cout << "Transfer successful!" << endl;
			else
				cout << "Transfer failed." << endl;
			break;
		}
		case 7:
		{
			Account *acc = authenticateUser(bank);
			if (acc == nullptr)
				break;

			bank.printAccountDetails(acc->getAccountNum());
			break;
		}
		case 8:
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
