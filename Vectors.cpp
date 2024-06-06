#include <iostream>
#include <vector>
using namespace std;


int main( )
{

vector<int> v;

cout << "Enter a list of positive numbers.\n"
<< "Place a negative number or zero at the end.\n";

int next;
cin >> next;

while (next > 0)
{
v.push_back(next);
cout << next << " added. ";
cout << "v.size( ) = " << v.size( ) << endl;
cin >> next;
}

cout << "You entered:\n";

for (unsigned int i = 0; i <v.size( ); i++)
cout << v[i] << " ";
cout << endl;

vector<int> u;
u = v;

cout << "Now printing a replica of vector v (testing assignment operator):\n";
for (unsigned int i = 0; i <u.size( ); i++)
cout << u[i] << " ";
cout << endl;

cout <<u.capacity();
return 0;
}
// declare vector and 2 ways to add size
// vector <double> v(10); 
// v.reserve(v.size()+10); adds 10 spaces in the vector
//v.reserve(40); holds at least 40 spaces