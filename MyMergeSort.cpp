    #include <iostream>
    #include <vector>
    
    // Function to merge two sorted arrays and return the merged sorted array
    std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) {
        std::vector<int> merged;
        size_t i = 0, j = 0;

        // merge sorted smaller arrays into the larger arry by comparing the numbers one by one
        while (i < left.size() && j < right.size()){
            if(left[i]<=right[j]){
                merged.push_back(left[i]);
                ++i;
            }
            else{
                merged.push_back(right[j]);
                ++j;
            }
        }
        //append remaining values from left
        while(i < left.size()){
            merged.push_back(left[i]);
            ++i;
        }
        while(j < right.size()){
            merged.push_back(right[j]);
            ++j;
        }
    
        return merged;
    }
    
    // Function to recurseively perform Merge Sort on an array that is not already sorted.
    void mergeSort(std::vector<int>& arr) {
        // first handle case where array only has one value.
        if(arr.size() <= 1){
            return;
        }
        // divide array into 2 halves
        size_t mid = arr.size()/2;
        std::vector<int> left(arr.begin(),arr.begin()+mid);
        std::vector<int> right(arr.begin()+mid, arr.end());

        // recursively sort the 2 halves
        mergeSort(left);
        mergeSort(right);

        // merge the sorted halves back into arr
        arr = merge(left,right);
        
    }
    
    int main() {
        std::vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    
        // Display the original array
        std::cout << "Original Array: ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    
        // Sort the array using Merge Sort
        mergeSort(arr);
    
        // Display the sorted array
        std::cout << "Sorted Array: ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    
        return 0;
    }
