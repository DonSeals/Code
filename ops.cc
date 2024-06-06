#include <iostream>
#include <cstdlib>   
#include <cmath>

using namespace std;

void arith(double x, double n, string a,double &z);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " Insufficient number of arguements" << endl;
        return 1;
    }
    double num1, n;
    double z = 0;
    string a =  argv[1]; // initialize operator
    n = atof(argv[2]); // initialize operand 2

    while(cin >> num1){ //
        arith(num1,n,a,z);
        cout << z << endl;
    }
         
    return 0;
    
}

void arith(double x, double n, string a, double &z)
{
    
    if(a == "+" ){
        z = x + n;
        
    }
    else if(a == "-"){
        z = x - n;
        
    }
    else if(a == "x"){
        z = x*n;
        
    }
    else if(a == "/"){
        z = x/n;
        
    }
    else if(a == "%"){
        z = fmod(x,n); // fmod is used as % for floats
    
    }
    else if(a == "=="){
        if(x == n){
            z = x;
        }
    }
    else if(a == "!="){
        if(x != n){
            z = x;
        }
    }
    else if(a == "le"){
        if(x<=n){
            z = x;
        }
    }
    else if(a == "lt"){
        if(x < n){
            z = x;
        }
    }
    else if(a == "ge"){
        if(x >= n){
            z = x;
        }
    }
    else if(a == "gt"){
        if(x > n){
            z = x;
        }
    }
    else{
        cout << "Error occured" << endl;
    }

}