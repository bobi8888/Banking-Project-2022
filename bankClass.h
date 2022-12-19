class Bank {
	private:
		long lastAccountNumber = 0;
		int numberOfAccounts = 0;
	public:
		map<long, Account> mapOfAccounts;
		map<long, Account>::iterator itr;
		Bank();
		void mainMenu();
		int getNumberOfAccounts();
		Account openAccount(string fName, string sName, float bal);
		Account getAccount(long accountNumber);
		void withdraw(long accountNumber, float debit);
		void closeAccount(long accountNumber);
		void showAllAccounts();
		void deposit(long accountNumber, float credit);
		long verifyAccountNumber(long accountNumberToTest);
		bool verifyTXT_File();
		void populateMapOfAccountsFromTXTFile();
		float amountToVerify();
};

Bank::Bank() {
	if (verifyTXT_File()) {
		populateMapOfAccountsFromTXTFile();
	}
}
void Bank::mainMenu()
{
	std::cout << "Please enter a number corresponding to the action desired. \n \n";
	std::cout << "   1. Open New Account \n";
	std::cout << "   2. Balance Inquiry \n";
	std::cout << "   3. Deposit \n";
	std::cout << "   4. Withdrawal \n";
	std::cout << "   5. Close an Account \n";
	std::cout << "   6. Show All Accounts \n";
	std::cout << "   7. QUIT \n";
}
int Bank::getNumberOfAccounts(){
	return numberOfAccounts;
}
Account Bank::openAccount(string fName, string sName, float bal) {
	Account account(fName, sName, bal);
	ofstream outFile;

	account.setAccountNumber(lastAccountNumber += 1);
	mapOfAccounts.insert(pair<long, Account>(lastAccountNumber, account));
	outFile.open("Log of accounts.txt", std::ios::app);
	outFile << account;
	outFile.close();
	numberOfAccounts++;
	return account;
}
Account Bank::getAccount(long accountNumber) {
	return mapOfAccounts[accountNumber]; 
}
void Bank::deposit(long accountNumber, float credit) {
	Account account = mapOfAccounts[accountNumber];
	ofstream outFile;
	map<long, Account>::iterator itr;

	mapOfAccounts[accountNumber].creditBalance(credit);
	mapOfAccounts[accountNumber].displayBalance();

	outFile.open("Log of accounts.txt", std::ios::trunc);
	for (itr = mapOfAccounts.begin(); itr != mapOfAccounts.end(); itr++) { outFile << itr->second; }
	outFile.close();
}
void Bank::withdraw(long accountNumber, float debit) {
	Account account = mapOfAccounts[accountNumber];
	ofstream outFile;
	map<long, Account>::iterator itr;

	mapOfAccounts[accountNumber].debitBalance(debit);
	std::cout << "Your new balance is ";
	mapOfAccounts[accountNumber].displayBalance();

	if (account.getBalance() <= 0) {
		std::cout << "Your account now has a negative balance. \n";
	}

	outFile.open("Log of accounts.txt", std::ios::trunc);
	for (itr = mapOfAccounts.begin(); itr != mapOfAccounts.end(); itr++) {
		outFile << itr->second;
	}
	outFile.close();
}
void Bank::closeAccount(long accountNumber) {
	ofstream outFile;
	outFile.open("Log of accounts.txt", std::ios::out);
	auto keyToErase = mapOfAccounts.find(accountNumber);
	mapOfAccounts.erase(keyToErase);
	map<long, Account>::iterator itr;
	for (auto itr = mapOfAccounts.begin(); itr != mapOfAccounts.end(); itr++) { outFile << itr->second; }
	outFile.close();
	std::cout << "Account number " << accountNumber << " has been erased. \n";
	numberOfAccounts = numberOfAccounts -1;
}
void Bank::showAllAccounts() {
	for (itr = mapOfAccounts.begin(); itr != mapOfAccounts.end(); itr++) {
		std::cout << "Account " << itr->first << "\n";
		std::cout << "Owner: " << itr->second.getFirstName() << " " <<
			itr->second.getSurname() << "\n";
		itr->second.displayBalance();
		std::cout << "\n";
	}
}
long Bank::verifyAccountNumber(long accountNumberToTest) {//no while loop, otherwise infinite?
	while(true){
		for (itr = mapOfAccounts.begin(); itr != mapOfAccounts.end(); itr++) {
			if (accountNumberToTest == itr->first){	
			return accountNumberToTest;
			}
		}
		std::cout << "Account number does not exists. Try again. \n";
		std::cin >> accountNumberToTest;
	}
}
bool Bank::verifyTXT_File() {
	logOfAccounts.open("Log of accounts.txt", std::ios_base::in);
	if (logOfAccounts.is_open()) {
		std::cout << "Log of accounts.txt exists. \n";
		logOfAccounts.close();
		return true;
	} else {
		std::cout << "Log of accounts.txt does not currently exist. \n";
		return false;
	}
}
void Bank::populateMapOfAccountsFromTXTFile() {
	Account account; 
	ifstream logOfAccounts;

	logOfAccounts.open("Log of accounts.txt");
	while(true){
		logOfAccounts >> account;
		if (logOfAccounts.eof()) {
			break;
		}
		mapOfAccounts.insert(pair<long, Account>(account.getAccountNumber(), account));
		numberOfAccounts++;
		lastAccountNumber = account.getAccountNumber();
	}
	logOfAccounts.close();
}
float Bank::amountToVerify() {
	float amountFromStringToFloat;
	string amountToTest;
	bool valid = false;

	std::cin >> amountToTest;
	while(!valid){
		for (int i = 0; i < amountToTest.length(); i++) {
			if (isalpha(amountToTest[i]) != 0) {
				std::cout << "Please enter numbers only. \n";
				std::cin >> amountToTest;
			} else {
				amountFromStringToFloat = std::stof(amountToTest);
				if (amountFromStringToFloat < 0) {
					std::cout << "Please enter a positive amount. \n";
					std::cin >> amountToTest;
				} else {
					valid = true;
				}
			}
		}
	}
	return amountFromStringToFloat;
}