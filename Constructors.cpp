//Program to demonstrate the class BankAccount.
//This class stores the balance and adds interest to the balance
//Taken from "Problem Solving with C++", by W. Savitch


#include <iostream>
using namespace std;



//Class for a bank account:
class BankAccount
{
public:
 BankAccount(int dollars, int cents, double rate);            //constructor
  //Initializes the account balance to $dollars.cents and
  //initializes the interest rate to rate percent.

 BankAccount(int dollars, double rate);
 //Initializes the account balance to $dollars.00 and
 //initializes the interest rate to rate percent.

 BankAccount( );
 //Initializes the account balance to $0.00
 //and the interest rate to 0.0%.

 void set(int dollars, int cents, double rate);
 //Postcondition: The account balance has been set to $dollars.cents;
 //The interest rate has been set to rate percent.
 void set(int dollars, double rate);
 //Postcondition: The account balance has been set to $dollars.00.
 //The interest rate has been set to rate percent.
 void update( );
 //Postcondition: One year of simple interest has been
 //added to the account balance.
 double get_balance( );
 //Returns the current account balance.
 double get_rate( );
 //Returns the current account interest rate as a percentage.
 void output(ostream& outs);
 //Precondition: If outs is a file output stream, then
 //outs has already been connected to a file.
 //Postcondition: Account balance and interest rate have
 //been written to the stream outs.


private:
 double balance;
 double interest_rate;
 double fraction(double percent);  //any function that helps with computations should be private
 //Converts a percentage to a fraction. For example, fraction(50.3)
 //returns 0.503.
};

int main( )
{

 //only uses the default constructor
 //then uses the set functions to change values
 BankAccount account1, account2, account3,account55;
 account3 = BankAccount();  //valid call to constructor
 cout <<"HERE COMES OUR TEST IN CLASS: ";
 account3.output(cout);
// account55 = BankAccount;   //invalid call to constructor
 cout << "Start of Test:\n";
 account1.set(123, 99, 3.0);
 cout << "account1 initial statement:\n";
 account1.output(cout);
 account1.set(100, 5.0);
 cout << "account1 with new setup:\n";
 account1.output(cout);
 account1.update( );
 cout << "account1 after update:\n";
 account1.output(cout);
 account2 = account1;
 cout << "account2:\n";
 account2.output(cout);

//uses the constructors to generate and initialize values
 BankAccount account4(100, 2.3), account5;
cout << "account4 initialized as follows:\n";
account4.output(cout);
cout << "account5 initialized as follows:\n";
account5.output(cout);
account4 = BankAccount(999, 99, 5.5);           //invoke a special function here. the constructor
cout << "account1 reset to the following:\n";
account4.output(cout);

 return 0;
}

void BankAccount::set(int dollars, int cents, double rate)
{
if ((dollars < 0) || (cents < 0) || (rate < 0))
{
cout << "Illegal values for money or interest rate.\n";
exit(1);
}
balance = dollars + 0.01*cents;
interest_rate = rate;
}

void BankAccount::set(int dollars, double rate)
{
if ((dollars < 0) || (rate < 0))
{
cout << "Illegal values for money or interest rate.\n";
exit(1);
}
balance = dollars;
interest_rate = rate;
}

void BankAccount::update( )
{
balance = balance + fraction(interest_rate)*balance;
}

double BankAccount::fraction(double percent_value)
{
return (percent_value / 100.0);
}

double BankAccount::get_balance( )
{
return balance;
}

double BankAccount::get_rate( )
{
return interest_rate;
}

//Uses iostream:
void BankAccount::output(ostream& outs)
{
outs.setf(ios::fixed);
outs.setf(ios::showpoint);
outs.precision(2);
outs << "Account balance $" << balance << endl;
outs << "Interest rate " << interest_rate << "%" << endl;
}

BankAccount::BankAccount(int dollars, int cents, double rate)
{
if ((dollars < 0) || (cents < 0) || (rate < 0))
{
cout << "Illegal values for money or interest rate.\n";
exit(1);
}
balance = dollars + 0.01*cents;
interest_rate = rate;
}

BankAccount::BankAccount( ) : balance(0), interest_rate(0.0)
{
//Body intentionally empty
}

BankAccount::BankAccount(int dollars, double rate)
{
if ((dollars < 0) || (rate < 0))
{
cout << "Illegal values for money or interest rate.\n";
exit(1);
}
balance = dollars;
interest_rate = rate;
}
