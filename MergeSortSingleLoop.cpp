    #include <iostream>
    #include <vector>
    
    // Function to merge two sorted arrays and return the merged sorted array
    std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) {
        std::vector<int> merged;
        size_t i = 0, j = 0;
    
        // Merge sorted arrays 'left' and 'right' into 'merged'
        while (i < left.size() || j < right.size()) {
            if ((i < left.size() && left[i] <= right[j]) || j >= right.size()) {
                merged.push_back(left[i]);
                ++i;
            } else {
                merged.push_back(right[j]);
                ++j;
            }
        }

        return merged;
    }
    
    // Function to perform Merge Sort on an array
    void mergeSort(std::vector<int>& arr) {
        if (arr.size() <= 1) {
            return; // Base case: array is already sorted or empty
        }
    
        // Divide the array into two halves
        size_t mid = arr.size() / 2;
        std::vector<int> left(arr.begin(), arr.begin() + mid);
        std::vector<int> right(arr.begin() + mid, arr.end());
    
        // Recursively sort the left and right halves
        mergeSort(left);
        mergeSort(right);
    
        // Merge the sorted halves back into 'arr'
        arr = merge(left, right);
    }
    
    int main() {
        std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8};
    
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
