class Account {
	private:
		string firstName, surname, balanceToShow;
		float balance;
		long accountNumber;

	public:
		Account(){}; 
		Account(string fName, string sName, float bal);
		string getFirstName();
		void setFirstName(string newName);
		string getSurname();
		void setSurname(string newName);
		float getBalance();
		void creditBalance(float credit);
		void debitBalance(float debit); 
		void displayBalance();
		long getAccountNumber();
		void setAccountNumber(long newAccountNumber);
		string verifyName(string fNameToTest);
		void welcomeMessage();
		friend ofstream& operator <<(ofstream& outStream, Account& account);
		friend ifstream& operator >>(ifstream& inFile, Account& account);
};

Account::Account(string fName, string sName, float bal){
	firstName = fName;
	surname = sName;
	balance = bal * 100;
}
string Account::getFirstName() { 
return firstName; 
}
void Account::setFirstName(string newName) { 
firstName = newName; 
}
string Account::getSurname() {
return surname; 
}
void Account::setSurname(string newName) { 
surname = newName; 
}
float Account::getBalance() { 
	return balance; 
}
void Account::creditBalance(float credit){
	balance = balance + credit * 100;
}
void Account::debitBalance(float debit){
	balance = balance - debit * 100;
}
void Account::displayBalance() {
	stringStream.imbue(std::locale(""));
	stringStream << std::showbase << std::put_money(getBalance());
	balanceToShow = stringStream.str();
	std::cout << balanceToShow << "\n";
	stringStream.str(std::string());
}
long Account::getAccountNumber() { 
	return accountNumber; 
}
void Account::setAccountNumber(long newAccountNumber) { 
	accountNumber = newAccountNumber; 
}
string Account::verifyName(string nameToTest) {
	int validMarks = 0;
	string validName;
	vector <char> validChars = { ' ','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
		'M','N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
								'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
		'm','n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','-' };

	for (int i = 0; i < nameToTest.length(); i++) {
		for (int j = 0; j < validChars.size(); j++) {
			if (nameToTest[i] == validChars.at(j)) {
				validMarks++;
				break;
			}
		}
	}

	if (validMarks == nameToTest.length()) {
		validName = nameToTest;
	}
	else {
		std::cout << "Please enter a name using letters only. \n";
		std::cin >> nameToTest;
		return verifyName(nameToTest);
	}
	return validName;
}
void Account::welcomeMessage() {
	std::cout << "\n";
	std::cout << "Welcome, " << getFirstName() << " " << getSurname() << "! \n";
	std::cout << "Your account number is " << getAccountNumber() << "\n";
	displayBalance();
	std::cout << "\n";
}