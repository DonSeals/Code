/*
Code taken from: "Problem Solving with C++", Savitch
*/

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>


using namespace std;


//Class for amounts of money in U.S. currency.
class Money
{
public:
friend Money operator +(const Money& amount1, const Money& amount2);
//Precondition: amount1 and amount2 have been given values.
//Returns the sum of the values of amount1 and amount2.
friend bool operator ==(const Money& amount1, const Money& amount2);
//Precondition: amount1 and amount2 have been given values.
//Returns true if amount1 and amount2 have the same value;
//otherwise, returns false.
friend Money operator -(const Money& amount1, const Money& amount2);
//Precondition: amount1 and amount2 have been given values.
//Returns amount1 minus amount2.
friend Money operator -(const Money& amount);
//Precondition: amount has been given a value.
//Returns the negative of the value of amount.
friend bool operator <(const Money& amount1,const Money& amount2);
//Precondition: amount1 and amount2 have been given values.
//Return true if amount1 < amount2
friend bool operator <=(const Money& amount1, const Money& amount2);
//Precondition: amount1 and amount2 have been given values.
//Returns true if amount1 <= amount2
friend bool operator >(const Money& amount1,const Money& amount2);
//Precondition: amount1 and amount2 have been given values.
//Returns true if amount1 > amount2
friend bool operator >=(const Money& amount1,const Money& amount2);
//Precondition: amount1 and amount2 have been given values.
//Returns true if amount1 >= amount2
friend istream& operator >>(istream& ins, Money& amount);
//Overloads the >> operator so it can be used to input values of type Money.
//Notation for inputting negative amounts is as in −$100.00.
//Precondition: If ins is a file input stream, then ins has already been
//connected to a file.
friend ostream& operator <<(ostream& outs, const Money& amount);
//Overloads the << operator so it can be used to output values of type Money.
//Precedes each output value of type Money with a dollar sign.
//Precondition: If outs is a file output stream,
//then outs has already been connected to a file.


Money(long dollars, int cents);
Money(long dollars);
Money( );
Money (double amount);

double get_value( ) const;
void input(istream& ins);
void output(ostream& outs) const;
Money percent(int percent_figure) const;
//Returns a percentage of the money amount in the
//calling object. For example, if percent_figure is 10,
//then the value returned is 10% of the amount of
//money represented by the calling object.

private:

long all_cents;
};

//test out the classes with operator overloading
int main( )
{
Money cost(1, 50), tax(0, 15), total;
Money test(1.23);
total = cost + tax + 1.2;  //test worked for objects of class type + double type
cout << "cost = ";
cost.output(cout);
cout << endl;
cout << "tax = ";
tax.output(cout);
cout << endl;
cout << "total bill = ";
total.output(cout);
cout << endl;
if (cost == tax)
cout << "Move to another state.\n";
else
cout << "Things seem normal.\n";

total = total - 1.2;
cout << "\nThe bill is now corrected: ";
total.output(cout);   //stick to an output function
cout << total;    //overload the << operator and enjoy the rest of your life!
cout << endl;


total = -total;                 //test case for unary - sign
cout<< "negating the total";
total.output(cout);
cout << endl;

Money iphone(1199,99), samsung(1100,0), pixel(500.50);

cout << "is iphone the most expensive? " << (iphone > samsung && iphone > pixel ) << endl;
// all of this is achievable using our hard work and effort we put into generating overloaded operations!
cout << "is samsung price >= iphone price? " << (samsung >= iphone) << endl;

cout << "is iphone the least expensive? " << (iphone < samsung && iphone < pixel ) << endl;
// all of this is achievable using our hard work and effort we put into generating overloaded operations!
cout << "is samsung price <= iphone price? " << (samsung <= iphone) << endl;

cout << "is iphone price <= iphone price? " << (iphone <= iphone) << endl;


//testing percent function
cout << "iphone's value in 1 year is : " << iphone.percent(90) << "!" <<endl;
cout << "That is a drop of : " << iphone.percent(10) << endl;

//second test with more operators overloaded
Money amount;
ifstream in_stream;
ofstream out_stream;

in_stream.open("infile.txt");
if (in_stream.fail( ))
{
cout << "Input file opening failed.\n";
exit(1);
}

out_stream.open("outfile.txt");
if (out_stream.fail( ))
{
cout << "Output file opening failed.\n";
exit(1);
}

Money amount1;
cout << "\ninput the cost of that computer: ";
cin >> amount;
cout << amount;

//in_stream.close( );
//out_stream.close( );


return 0;
}



Money operator +(const Money& amount1, const Money& amount2)
{
Money temp;
temp.all_cents = amount1.all_cents + amount2.all_cents;
return temp;
}

bool operator ==(const Money& amount1, const Money& amount2)
{
    return (amount1.all_cents == amount2.all_cents);
}

bool operator <(const Money& amount1,const Money& amount2)
{
    return (amount1.all_cents < amount2.all_cents);
}

bool operator <=(const Money& amount1, const Money& amount2)
{
    return(amount1.all_cents <= amount2.all_cents);
}

bool operator >(const Money& amount1, const Money& amount2)
{
   return(amount1.all_cents > amount2.all_cents);
}

bool operator >=(const Money& amount1, const Money& amount2)
{
   return(amount1.all_cents >= amount2.all_cents);
}

Money::Money(long dollars, int cents)
{
if (dollars * cents < 0) //If one is negative and one is positive
{
cout << "Illegal values for dollars and cents.\n";
exit(1);
}
all_cents = dollars * 100 + cents;
}

Money::Money(long dollars) : all_cents(dollars * 100)
{
//Body intentionally blank.
}

Money::Money( ) : all_cents(0)
{
 //Body intentionally blank.
}

double Money::get_value( ) const
{
return (all_cents * 0.01);
}

Money::Money (double amount)
{
    all_cents = amount * 100;
}


Money Money :: percent(int percent_figure) const
{
    int cents = all_cents * percent_figure/100;
    long dollars = cents / 100;
    cents %= 100;
    Money temp(dollars,cents);
    return temp;
}



int digit_to_int(char c)
{
return (int)(c) -(int) ('0');    //ASCII codes revisit  this function return 8 from input '8'
}



//Uses iostream, cctype, cstdlib:
void Money::input(istream& ins)
{
    char one_char, decimal_point, digit1, digit2;
    //digits for the amount of cents
    long dollars;
    int cents;
    bool negative;//set to true if input is negative.

    ins >> one_char;
    if (one_char == ' ')
    {
    negative = true;
    ins >> one_char; //read '$'
    }
    else
    negative = false;
    //if input is legal, then one_char == '$'

    ins >> dollars >> decimal_point >> digit1 >> digit2;

    if (one_char != '$' || decimal_point != '.' || !isdigit(digit1) || !isdigit(digit2))
    {
    cout << "Error illegal form for money input\n";
    exit(1);
    }
    cents = digit_to_int(digit1) * 10 + digit_to_int(digit2);
    all_cents = dollars * 100 + cents;
    if (negative)
    all_cents = -all_cents;
}

//Uses cstdlib and iostream:
void Money::output(ostream& outs) const
{
long positive_cents, dollars, cents;
positive_cents = labs(all_cents);
dollars = positive_cents / 100;
cents = positive_cents % 100;

if (all_cents < 0)
    outs << "-$" << dollars << '.';
else
    outs << "$" << dollars << '.';

if (cents < 10)
    outs << '0';
outs << cents;
}


Money operator -(const Money& amount1, const Money& amount2)
{
Money temp;
temp.all_cents = amount1.all_cents - amount2.all_cents;
return temp;
}

Money operator -(const Money& amount)
{
Money temp;
temp.all_cents = -amount.all_cents;
return temp;
}


//Uses iostream, cctype, cstdlib:
istream& operator >>(istream& ins, Money& amount)
{ 
char one_char, decimal_point, digit1, digit2; //digits for the amount of cents
long dollars;
int cents;
bool negative;//set to true if input is negative.
ins >> one_char;
if (one_char == '-')
{
    negative = true;
    ins >> one_char; //read '$'
}
else
    negative = false;

//if input is legal, then one_char == '$'
ins >> dollars >> decimal_point >> digit1 >> digit2;
if (one_char != '$' || decimal_point != '.' || !isdigit(digit1) || !isdigit(digit2))
{
    cout << "Error illegal form for money input\n";
exit(1);
}
cents = digit_to_int(digit1) * 10 + digit_to_int(digit2);
amount.all_cents = dollars * 100 + cents;
if (negative)
    amount.all_cents = -amount.all_cents;
return ins;
}


//Uses cstdlib and iostream:
ostream& operator <<(ostream& outs, const Money& amount)
{
long positive_cents, dollars, cents;
positive_cents = labs(amount.all_cents);
dollars = positive_cents/100;
cents = positive_cents%100;

if (amount.all_cents < 0)
outs << "-$" << dollars << '.';
else
outs << "$" << dollars << '.';

if (cents < 10)
outs << '0';
outs << cents;

return outs;
}
