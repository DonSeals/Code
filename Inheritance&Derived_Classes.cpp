//SavingAccount and CDAccount are derived from the class BankAccount.
//Taken from "Problem Solving with C++", by W. Savitch


#include <iostream>
using namespace std;



//Class for a bank account:
class BankAccount    // base class, parent class, it's not necessary useful on its own
{
public:
 BankAccount(int dollars, int cents, double rate);            //constructor
  //Initializes the account balance to $dollars.cents and
  //initializes the interest rate to rate percent.

 BankAccount(int dollars, double rate);
 //Initializes the account balance to $dollars.00 and
 //initializes the interest rate to rate percent.

 BankAccount( );  //default constructor
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


protected:     //child classes have access to protected members. debate on whether you should use protected members
 double balance;
 double interest_rate;


private:          //private members are private to the derived class
 double fraction(double percent);  //any function that helps with computations should be private
 //Converts a percentage to a fraction. For example, fraction(50.3)
 //returns 0.503.
};




//Derived class: BankAccount
class SavingsAccount : public BankAccount
{
public:
    SavingsAccount(int dollars, int cents, double rate);
    void deposit(int dollars, int cents);
    //Adds $dollars.cents to the account balance
    void withdraw(int dollars, int cents);
    //Subtracts $dollars.cents from the account balance
};


//************** CDAccount does not have any functions defined and written out*******************************
//****************COMPLETE THE FUNCITON DEFINITIONS FOR CDAccount
//Derived class: CDAccount
class CDAccount : public SavingsAccount
{
public:
CDAccount(int dollars, int cents, double rate, int maturity);
int get_days_to_maturity( );
//Returns the number of days until the CD matures
void decrement_days_to_maturity( );
//Subtracts one from the days_to_maturity variable
void output(ostream& outs);

private:
int days_to_maturity; //Days until the CD matures
};

int main()
{
    SavingsAccount account(100, 50, 5.5);
    account.output(cout);
    cout << endl;
    cout << "Depositing $10.25." << endl;
    account.deposit(10,25);
    account.output(cout);
    cout << endl;
    cout << "Withdrawing $11.80." << endl;
    account.withdraw(11,80);
    account.output(cout);
    account.update();

    account.output(cout);
    //cout << account << endl;


//    //Create a new CD with $1000, 6% interest, 180 days to maturity
    CDAccount newCD(1000, 0, 6.0, 180);
    cout << "\nthis is the cd account:\n";
    newCD.output(cout);
    newCD.deposit(100,50);         //invoking a function from SavingsAccount

    newCD.decrement_days_to_maturity();
    newCD.BankAccount::output(cout);

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


//constructor invokes the BankAccount constructor
SavingsAccount::SavingsAccount(int dollars, int cents, double rate): BankAccount(dollars, cents, rate)
{
    //empty
}

//The deposit function adds the new
//amount to the balance and changes the
//member variables via the set function
void SavingsAccount::deposit(int dollars, int cents)
{
    //double balance = get_balance();
    balance += dollars;
    balance += (double)cents / 100;
    //int new_dollars = int(balance);
    //int new_cents = int((balance - new_dollars) * 100);
    //set(new_dollars, new_cents, get_rate());
}

void SavingsAccount::withdraw(int dollars, int cents)
{
    double balance = get_balance();
    balance -= dollars;
    balance -= double(cents) / 100;
    int new_dollars = int(balance);
    int new_cents = int((balance - new_dollars) * 100);
    set(new_dollars, new_cents, get_rate());
}

CDAccount::CDAccount(int dollars, int cents, double rate, int maturity):SavingsAccount(dollars, cents, rate)
{
    days_to_maturity = maturity;
}

int CDAccount::get_days_to_maturity()
{
    return days_to_maturity;
}

void CDAccount::decrement_days_to_maturity( )
{
    days_to_maturity--;
}

void CDAccount::output(ostream& outs)
{
outs.setf(ios::fixed);
outs.setf(ios::showpoint);
outs.precision(2);
outs << "Account balance $" << balance << endl;
outs << "Interest rate " << interest_rate << "%" << endl;
outs << "Days to Maturity "<<days_to_maturity << endl;
}
