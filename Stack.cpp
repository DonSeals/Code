#include <iostream>

using namespace std;

const int capacity = 100; // constant to allow you to adjust the capacity

class Stack {
private:
    int elements[capacity];
    int t; //variable to track the top element

public:
    // Constructor
    Stack() : t(-1) {}


    // Push element onto the stack
    void push(int element) {
        
        //check if the array is full
        if (t+1 < capacity) {
            t++; //increment the pointer to the next available space to insert new element
            elements[t] = element; 
        } else {
            cout << "Stack overflow!" << endl; 
        }
    }

    // Remove and return the top element from the stack
    int pop() {
        //make sure the stack is not empty
        if (t >=0) {
            return elements[t--]; //returns t and THEN decrements the value of t(because -- is after t). current code does NOT delete
            remove[t]; 
        } else {
            cout << "Stack is empty!" << endl;
            return -1;
        }
    }

    // Return the top element from the stack
    int top(int n) {
        if (t >= 0) {
            int c = n-1;
            return elements[t-c];
        }
        // Return 0 if the stack is empty
        return -1;
    }

    // Check if the stack is empty
    bool empty() {
        return t == -1;
    }

    // Return the number of elements in the stack
    size_t size() {
        return t+1;
    }
};

int main() {
    // Create a stack of integers
    Stack myStack;
    
    // Check if the stack is empty
    cout << "Is the stack empty? " << (myStack.empty() ? "Yes" : "No") << endl;
    
    // Push elements onto the stack
    myStack.push('a');
     // Print the top element
    cout << "Top element: " << myStack.top(1) << endl;
    
    myStack.push('b');
     // Print the top element
    cout << "Top element: " << myStack.top(1) << endl;
    
    myStack.push('c');
     // Print the top element
    cout << "Top element: " << myStack.top(1) << endl;

    // Check if the stack is empty
    cout << "Is the stack empty? " << (myStack.empty() ? "Yes" : "No") << endl;

    // Print the number of elements in the stack
    cout << "Stack size: " << myStack.size() << endl;
    
    //Pop the top element off the stack
    cout << "The element that was popped off is " << myStack.pop() << endl;
    
    //Pop the top element off the stack
    cout << "The element that was popped off is " << myStack.pop() << endl;
    
    //Pop the top element off the stack
    cout << "The element that was popped off is " << myStack.pop() << endl;

    cout << "Stack size: " << myStack.size() << endl;
    

    return 0;
}
