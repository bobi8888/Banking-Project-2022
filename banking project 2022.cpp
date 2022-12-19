#include "utils.h"
#include "accountClass.h"
#include "bankClass.h"

int main() {
	Bank bank;
	Account account;
	string  firstName, surName, nameToTest, amountToTest;
	float balance, amount;
	int input = 0;
	long accountNumber;

	while (input != 7) {
		if (bank.getNumberOfAccounts() < 1) {
			input = 1;
			std::cout << "No accounts found. \n";
		}
		else {
			bank.mainMenu();
			cin >> input;
		}
		switch (input) {
			case 1://Open Account
				cout << "Please enter your first name. \n";
				std::getline(std::cin >> std::ws, nameToTest);
				firstName = account.verifyName(nameToTest);

				std::cout << "Please enter your Surname. \n";
				std::getline(std::cin >> std::ws, nameToTest);
				surName = account.verifyName(nameToTest);

				std::cout << "Please enter your initial balance. \n";
				balance = bank.amountToVerify();

				account = bank.openAccount(firstName, surName, balance);
				account.welcomeMessage();
				break;

			case 2://Balance Inquiry
				std::cout << "Please enter your account number. \n";
				std::cin >> accountNumber;
				accountNumber = bank.verifyAccountNumber(accountNumber);

				bank.getAccount(accountNumber).displayBalance();
				std::cout << "\n";
				break;

			case 3://Deposit
				std::cout << "Please enter your account number. \n";
				std::cin >> accountNumber;
				accountNumber = bank.verifyAccountNumber(accountNumber);

				std::cout << "How much would you like to deposit? \n";
				amount = bank.amountToVerify();

				bank.deposit(accountNumber, amount);
				std::cout << "\n";
				break;

			case 4://Withdraw
				std::cout << "Please enter your account number. \n";
				std::cin >> accountNumber;
				accountNumber = bank.verifyAccountNumber(accountNumber);

				if (bank.getAccount(accountNumber).getBalance() <= 0) {
					std::cout << "Funds cannot be withdrawn. \nYour balance is ";
					bank.getAccount(accountNumber).displayBalance();
					std::cout << "\n";
					break;
				}

				std::cout << "How much would you like to withdraw? \n";
				std::cin >> amount;
				while (amount < 0) {
					std::cout << "Please withdraw a positive amount \n";
					std::cin >> amount;
				}

				bank.withdraw(accountNumber, amount);
				std::cout << "\n";
				break;

			case 5://Close An Account
				std::cout << "Please enter the account number of the account you wish to close: ";
				std::cin >> accountNumber;
				accountNumber = bank.verifyAccountNumber(accountNumber);
				bank.closeAccount(accountNumber);
				break;

			case 6://Show All Accounts
				bank.showAllAccounts();
				break;
		}
	}
	std::cout << "Have a great day! \n";
}

ofstream& operator <<(ofstream& outStream, Account& account) {

	outStream << account.getAccountNumber() << "\n";
	outStream << account.getFirstName() << "\n";
	outStream << account.getSurname() << "\n";
	outStream << account.getBalance() << "\n";
	return outStream;
}
ifstream& operator >>(ifstream& inFile, Account& account) {
	inFile >> account.accountNumber;
	inFile >> account.firstName;
	inFile >> account.surname;
	inFile >> account.balance;
	return inFile;
}