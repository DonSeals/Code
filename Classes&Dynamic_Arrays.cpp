
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <iostream>

using namespace std;

class StringVar
{
    public:
    StringVar(int size1);
    //Initializes the object so it can accept string values up to 'size1'
    //in length. Sets the value of the object equal to the empty string.

    StringVar( );
    //Initializes the object so it can accept string values of length 100
    //or less. Sets the value of the object equal to the empty string.

    StringVar(const char a[]);
    //Precondition: The array a contains characters terminated with '\0'.
    //Initializes the object so its value is the string stored in a and
    //so that it can later be set to string values up to strlen(a) in length.

    StringVar(const StringVar& string_object); // takes pointer argument of type StringVar
    //Copy constructor.

    ~StringVar( ); // destructor (~ )
    //Returns all the dynamic memory used by the object to the freestore.

    int length( ) const;
    //Returns the length of the current string value.

    void input_line(istream& ins);
    //Precondition: If ins is a file input stream, then ins has been
    //connected to a file.
    //Action: The next text in the input stream ins, up to '\n', is copied
    //to the calling object. If there is not sufficient room, then
    //only as much as will fit is copied.

    friend ostream& operator <<(ostream& outs, const StringVar& the_string);
    //Overloads the << operator so it can be used to output values
    //of type StringVar
    //Precondition: If outs is a file output stream, then outs
    //has already been connected to a file.

    StringVar copy_piece(int location, int num_chars) const;
    char one_char(int location) const;
    void set_char(int location, char new_char);
    friend bool operator ==(const StringVar& one, const StringVar& two );
    StringVar operator +(const StringVar& one);
    friend istream& operator>>(istream& ins, StringVar& the_string);//overloaded >>
    string getValue(const StringVar& one);
    private:
    char *value; //pointer to dynamic array that holds the string value.
    int max_length; //declared max length of any string value.
};

void conversation(int max_name_size);




    int main( )
    {
        StringVar one, two,four("Test String");
        cout << "what is one?"<<endl;
        one.input_line(cin);
        cout << "what is two?"<<endl;
        cin >> two;
        StringVar three = one + two;
        cout << three << endl;
        if(one==two){
            cout << "equal"<<endl;
        }
        else{
            cout <<"not equal" <<endl;
        }
        
        cout << four.copy_piece(1,3) << endl;
        cout << four.one_char(5) << endl;

    // conversation(30); // at the end of this function, since the declarations were in its scope, the destructor is automatically called. 
    // cout << "End of demonstration.\n";
    return 0;
    }


    string StringVar::getValue(const StringVar& one){
        return this->value;
    }

    //This is only a demonstration function:
    void conversation(int max_name_size)
    {
    StringVar your_name(max_name_size), our_name("Anita");

    cout << "What is your name?\n";
    your_name.input_line(cin);
    cout << "We are " << our_name << endl;
    cout << "We will meet again " << your_name << endl;
    }

    //Uses cstddef and cstdlib:
    StringVar::StringVar(int size1)
    {
    max_length =size1;
    value = new char[max_length + 1];//+1 is for '\0'.
    value[0] = '\0';
    }

    //Uses cstddef and cstdlib:
    StringVar::StringVar( )
    {
    max_length=100;
    value = new char[max_length + 1];//+1 is for '\0'.
    value[0] = '\0';
    }

    //Uses cstring, cstddef, and cstdlib:
    StringVar::StringVar(const char a[])
    {
    max_length = strlen(a);
    value = new char[max_length + 1];//+1 is for '\0'.
    strcpy(value,a);
    }

    //Uses cstring, cstddef, and cstdlib:
    StringVar::StringVar(const StringVar& string_object)
    {
    max_length = string_object.length( );
    value = new char[max_length + 1];//+1 is for '\0'.
    strcpy(value, string_object.value);
    }

    StringVar::~StringVar( )
    {
    delete [] value;
    cout << "Memory Freed\n";
    }

    //Uses cstring:
    int StringVar::length( ) const
    {
    return strlen(value);
    }

    //Uses iostream:
    void StringVar::input_line(istream& ins)
    {
    ins.getline(value, max_length + 1);
    }

    //Uses iostream:
    ostream& operator <<(ostream& outs, const StringVar& the_string)
    {
    outs << the_string.value;
    return outs;
    }

    StringVar StringVar::copy_piece(int start, int len) const {
    StringVar temp(len);
    strncpy(temp.value, this->value + start, len);
    temp.value[len] = '\0';
    return temp;
    }

    char StringVar::one_char(int index) const {
    if (index < 0 || index >= this->length()) {
        return '\0';
    }
    return this->value[index];
    }

    void StringVar::set_char(int index, char new_char) {
    if (index >= 0 && index < this->length()) {
        this->value[index] = new_char;
    }
    }

    bool operator ==(const StringVar& one, const StringVar& two){
        return strcmp(one.value, two.value) == 0;
    }

    StringVar StringVar::operator +(const StringVar& one) {
    int len = this->length() + one.length();//could also use (*this).length() instead of this->length()
    StringVar temp(len);
    strcpy(temp.value, this->value);
    strcat(temp.value, one.value);
    return temp;
    }

    istream& operator>>(istream& ins, StringVar& string) {
    ins >> string.value;
    return ins;
    }




