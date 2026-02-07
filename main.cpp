#include "Bank.h"

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
			cin >> name;
			cout << "Initial deposit: $";
			cin >> deposit;
			int accNum = bank.createCheckingAccount(name, deposit);
			cout << "Checking account created! Number: " << accNum << endl;
			break;
		}
		case 3:
		{
			int accNum;
			cout << "Account number to close: ";
			cin >> accNum;
			if (bank.closeAccount(accNum))
				cout << "Account closed." << endl;
			else
				cout << "Account not found." << endl;
			break;
		}
		case 4:
		{
			int accNum;
			double amount;
			cout << "Account number: ";
			cin >> accNum;
			cout << "Amount to deposit: $";
			cin >> amount;
			if (bank.deposit(accNum, amount))
				cout << "Deposit successful!" << endl;
			else
				cout << "Deposit failed." << endl;
			break;
		}
		case 5:
		{
			int accNum;
			double amount;
			cout << "Account number: ";
			cin >> accNum;
			cout << "Amount to withdraw: $";
			cin >> amount;
			if (bank.withdraw(accNum, amount))
				cout << "Withdrawal successful!" << endl;
			else
				cout << "Withdrawal failed." << endl;
			break;
		}
		case 6:
		{
			int fromAcc, toAcc;
			double amount;
			cout << "From account number: ";
			cin >> fromAcc;
			cout << "To account number: ";
			cin >> toAcc;
			cout << "Amount to transfer: $";
			cin >> amount;
			if (bank.transfer(fromAcc, toAcc, amount))
				cout << "Transfer successful!" << endl;
			else
				cout << "Transfer failed." << endl;
			break;
		}
		case 7:
		{
			int accNum;
			cout << "Account number: ";
			cin >> accNum;
			bank.printAccountDetails(accNum);
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
