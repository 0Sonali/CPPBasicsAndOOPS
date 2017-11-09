#include <iostream>
#include <string>

using namespace std;

class BankAccount
{
private:
	int m_accnumber;

protected:
	string m_owner;
	string m_acctype;
	double m_balance;

public: 
	BankAccount() = default;

	BankAccount(string owner, string acctype, double balance, int accnumber):
	m_owner(owner),m_acctype(acctype),m_balance(balance),m_accnumber(accnumber)
	{
		cout << "Base class constructor called" ;
	}

	virtual	int displayAccInfo()=0;

	int getAccNumber()
	{
		return m_accnumber;
	}

	virtual	void deposit(double amount)=0; //pure virtual function // BankAccount becomes abstract
	virtual void withdraw(double amount)=0;

	virtual	~BankAccount() //making destrutor virtual so that derived class destrutor will be called the base this will called 
	{
		cout <<"Base class destructor called\n"<<endl;
	}
};

class SavingAccount : public BankAccount
{
	double m_depositinterest;

public:
	
	SavingAccount(string owner, string acctype, double balance, int accnumber, double depositinterest):
	BankAccount(owner, acctype, balance, accnumber),m_depositinterest(depositinterest) //Initializer list and constructor delegation 
	{
		cout << "Derived class constructor called"<<endl;
	} 	

	void deposit (double amount)
	{
		cout << "\nDeposit amount : " <<amount;
		m_balance += amount;
		m_balance += (m_balance*m_depositinterest)/100;
		cout << "Balance with interest is : " << m_balance <<endl;
	}

	void withdraw(double amount)
	{
		cout << "\nBalance : " << m_balance << "  Withdraw amount : " << amount << endl;
		if (amount < m_balance)
		{
			m_balance -= amount;
			cout << "Balance is : " << m_balance <<endl;
		}
		else
		{
			cout << "Can not withdraw funds." <<endl;
		}
	}

	int displayAccInfo()
	{	
		cout<<"\n\nCustomer Name :- "<<m_owner; //Protected members can be accessed directly
		cout<<"\nAccount Number : " << getAccNumber(); //Private members can be accessed via member function
       		cout<<"\nAccount Type :- "<<m_acctype;
		cout<<"\nAccount Balance: "<<m_balance;
		cout<<"\nInterest: "<<m_depositinterest;
	}

	~SavingAccount()
	{
		cout <<"\nDerived class destructor called"<<endl;
	}
};

class CurrentAccount : public BankAccount
{
	double m_insufficientfundfee;

public:

	CurrentAccount(string owner, string acctype, double balance, int accnumber, double insufficientfundfee ):
	BankAccount(owner, acctype, balance, accnumber),m_insufficientfundfee(insufficientfundfee)
	{
		cout << "\nDerived class constructor called"<<endl;
	} 	

	void processCheck()
	{
		if (m_balance < 10000)
		{
			cout << "Deducting 500 as insufficient fund fee" << endl;
			m_balance = m_balance - m_insufficientfundfee;
		}
	}

	void deposit (double amount)
	{
		m_balance += amount;
		cout << "Balance is : " << m_balance << endl;
	}

	void withdraw(double amount)
	{
		cout << "\nBalance : " << m_balance << "  Withdraw amount : " << amount << endl;
		if (amount < m_balance)
		{
			m_balance -= amount;
			processCheck();
			cout << "Balance is : " << m_balance <<endl;
		}
		else
		{
			cout << "Can not withdraw funds." <<endl;
		}
	}

	int displayAccInfo()
	{
		cout<<"\n\nCustomer Name :- "<<m_owner;
		cout<<"\nAccount Number : " << getAccNumber();
       		cout<<"\nAccount Type :- "<<m_acctype;
		cout<<"\nAccount Balance: "<<m_balance;
		cout<<"\nInsufficient fund fee: "<<m_insufficientfundfee;
	}
	
	~CurrentAccount()
	{
		cout <<"Derived class destructor called"<<endl;
	}
};

void transactions(BankAccount &b, char txtype, double amount)
{
	b.displayAccInfo();
	if (txtype == 'w')
		b.withdraw(amount);
	else if (txtype == 'd')
		b.deposit(amount);
	else
	     cout << "Invalid transaction";
}

int main()
{
	//BankAccount b1("sonali","saving",20000,12345); //Compiler error: BankAccount class is abstract

	CurrentAccount c1("Sharad","current",100000,98765,500); //Order of construction, starting with most base to most derived
	SavingAccount s1("sonali","saving",20000,12345,2); 

	//Demonstrate functionality of calling derived class functions with base reference
	transactions(c1,'w',10000);
	transactions(s1,'w',5000);
	transactions(c1,'d',60000);
	transactions(s1,'d',7000);

	//Dynamic allocation and deallocation, virtual destruction
	cout << "\nDynamic Allocation : "<<endl;
	CurrentAccount *c2 = new CurrentAccount("Sandeep","current",700000,87654,500);
	BankAccount *b2 = c2;
	delete b2;
	cout <<"Dynamic Allocation end" <<endl;
}



