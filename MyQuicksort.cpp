    #include <iostream>
    #include <vector>
    
    // Function to perform partitioning based on the pivot
    std::vector<int> quicksort(const std::vector<int>& arr) {
        // first handle case where array only has one value.
        if(arr.size() <= 1){
            return arr;
        }

        int pivot = arr.back(); // choose last element in array as pivot ( convention std)
        std::vector<int> left, right;


        // partition the elements with respect to the pivot point
        for (int i = 0; i<arr.size()-1;i++){
            if(arr[i] < pivot){
                left.push_back(arr[i]);
            }
            else{
                right.push_back(arr[i]);
            }
        }

        // recursively call quicksort on the partitioned array
        left = quicksort(left);
        right = quicksort(right);

        left.push_back(pivot);
        left.insert(left.end(),right.begin(),right.end());// add the right array to the left(avoids creating new)
    
        return left;
    }
    
    int main() {
        std::vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    
        // Display the original array
        std::cout << "Original Array: ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    
        // Sort the array using Quicksort
        std::vector<int> sortedArray = quicksort(arr);
    
        // Display the sorted array
        std::cout << "Sorted Array: ";
        for (int num : sortedArray) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    
        return 0;
    }
