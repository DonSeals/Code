    
    #include <iostream>
    #include <vector>
    
    // Function to perform partitioning based on the pivot
    std::vector<int> quicksort(const std::vector<int>& arr) {
        if (arr.size() <= 1) {
            return arr; // Base case: array is already sorted or empty
        }
    
        int pivot = arr.back(); // Choose the last element as the pivot
        std::vector<int> left, right;
    
        // Partition elements into left (less than pivot) and right (greater than or equal to pivot)
        for (size_t i = 0; i < arr.size() - 1; ++i) {
            if (arr[i] < pivot) {
                left.push_back(arr[i]);
            } else {
                right.push_back(arr[i]);
            }
        }
    
        // Recursively sort left and right partitions
        left = quicksort(left);
        right = quicksort(right);
    
        // Combine sorted partitions and pivot
        left.push_back(pivot);
        left.insert(left.end(), right.begin(), right.end());
    
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
