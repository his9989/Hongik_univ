#include<iostream>
#include<string>
using namespace std;

class Account {
private:
	string name;
	int money;
public:
	Account(string name, int money);
	void deposit(int deposit);
	string getOwner();
	int getBalance();
	int withdraw(int withdraw);
};

Account::Account(string _name, int money) {
	name = _name;
	this->money = money;
}

void Account::deposit(int money) {
	this->money = this->money + money;
}

string Account::getOwner() {
	return this->name;
}

int Account::getBalance() {
	return this->money;
}

int Account::withdraw(int withdraw) {
	money = money - withdraw;
	return withdraw;
}

int main() {
	Account a("Michael", 5000);
	a.deposit(50000);
	cout << a.getOwner() << "'s account balance is $" << a.getBalance() << "\n";
	int money = a.withdraw(20000);
	cout << a.getOwner() << " withdrew $" << money << "from the account\n";
	cout << a.getOwner() << "'s account balance is $" << a.getBalance() << "\n";
}
