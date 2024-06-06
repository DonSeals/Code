#include<iostream>
#include <vector>


void checkHeap(std::vector<int> heap){
    bool maxHeap = false;
    bool minHeap= false;
    int size = heap.size();
    if (heap.size() == 0)
    {
        std::cout << "The heap is empty" << std::endl;
        return;
    }
    for (int i = 0; i < size-1; i++)
    {
       
        if (heap[i] > heap[i + 1])
        {
            
            maxHeap = true;
        
        }
        else if (heap[i] < heap[i + 1])
        {
            minHeap = true;
        }
    }
    
    if (maxHeap==true && minHeap==false)
    {
        std::cout << "The array is a max heap" << std::endl;
    }
    else if (minHeap==true && maxHeap==false)
    {
        std::cout << "The array is a min heap" << std::endl;
    }
    else
    {
        std::cout << "The array is neither a max heap nor a min heap" << std::endl;
    }
}

int main() {

    std::vector<int> A;
    A.push_back(1);
    A.push_back(2);
    A.push_back(3);
    A.push_back(4);
    A.push_back(5);
    A.push_back(6);
    A.push_back(7);
    A.push_back(8);
    A.push_back(9);
    A.push_back(10);
    std::vector<int> B;
    B.push_back(11);
    B.push_back(9);
    B.push_back(7);
    B.push_back(5);
    B.push_back(3);
    B.push_back(1);
    B.push_back(-1);
    B.push_back(-3);
    B.push_back(-5);
    B.push_back(-7);
    std::vector<int> C;
    C.push_back(6);
    C.push_back(7);
    C.push_back(8);
    C.push_back(9);
    C.push_back(10);
    C.push_back(1);
    C.push_back(2);
    C.push_back(3);
    C.push_back(4);
    C.push_back(5);
    checkHeap(A);
    checkHeap(B);
    checkHeap(C);


    return 0;
}