import numpy as np
import pandas as pd
import time
import heapq
from statistics import mean

# Generate datasets
small_data_set = np.random.randint(0, 1000, 100)
medium_data_set = np.random.randint(0, 1000, 1000)
large_data_set = np.random.randint(0, 10000, 10000)

nearly_sorted_data_set = np.arange(1000)
np.random.shuffle(nearly_sorted_data_set)
for _ in range(10):
    i, j = np.random.randint(0, 1000, 2)
    nearly_sorted_data_set[i], nearly_sorted_data_set[j] = nearly_sorted_data_set[j], nearly_sorted_data_set[i]

reversed_data_set = np.flip(np.arange(1000))

few_unique_data_set = np.random.choice([1, 2, 3, 4, 5], 1000)

unique_data_set = np.random.permutation(1000)


# Create dataframes for better readability
def create_dataframe(data, name):
    df = pd.DataFrame(data, columns=['Value']).reset_index()
    df.columns = ['Index', name]
    return df


small_data_df = create_dataframe(small_data_set, 'Small Data Set')
medium_data_df = create_dataframe(medium_data_set, 'Medium Data Set')
large_data_df = create_dataframe(large_data_set, 'Large Data Set')
nearly_sorted_data_df = create_dataframe(nearly_sorted_data_set, 'Nearly Sorted Data Set')
reversed_data_df = create_dataframe(reversed_data_set, 'Reversed Data Set')
few_unique_data_df = create_dataframe(few_unique_data_set, 'Few Unique Data Set')
unique_data_df = create_dataframe(unique_data_set, 'Unique Data Set')


# Sorting Algorithms
def quicksort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quicksort(left) + middle + quicksort(right)


def mergesort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = mergesort(arr[:mid])
    right = mergesort(arr[mid:])
    return merge(left, right)


def merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result


def heapsort(arr):
    arr = list(arr)  # Ensure the input is a list
    heapq.heapify(arr)
    return [heapq.heappop(arr) for _ in range(len(arr))]


def radixsort(arr):
    if len(arr) == 0:
        return arr
    max_num = max(arr)
    exp = 1
    while max_num // exp > 0:
        counting_sort(arr, exp)
        exp *= 10
    return arr


def counting_sort(arr, exp):
    n = len(arr)
    output = [0] * n
    count = [0] * 10
    for i in range(n):
        index = arr[i] // exp
        count[index % 10] += 1
    for i in range(1, 10):
        count[i] += count[i - 1]
    i = n - 1
    while i >= 0:
        index = arr[i] // exp
        output[count[index % 10] - 1] = arr[i]
        count[index % 10] -= 1
        i -= 1
    for i in range(len(arr)):
        arr[i] = output[i]


# Measure and print performance metrics
def measure_performance(sort_func, data, name):
    start_time = time.time()
    sorted_data = sort_func(data.copy())
    end_time = time.time()
    duration = end_time - start_time
    return duration


# List of datasets and their names
datasets = [
    (small_data_set, "Small Data Set"),
    (medium_data_set, "Medium Data Set"),
    (large_data_set, "Large Data Set"),
    (nearly_sorted_data_set, "Nearly Sorted Data Set"),
    (reversed_data_set, "Reversed Data Set"),
    (few_unique_data_set, "Few Unique Data Set"),
    (unique_data_set, "Unique Data Set")
]

# Number of test runs
num_runs = 10

# Apply sorting algorithms and measure performance
for data, name in datasets:
    print(f"\nDataset: {name}")
    durations = {'quicksort': [], 'mergesort': [], 'heapsort': [], 'radixsort': []}

    for _ in range(num_runs):
        durations['quicksort'].append(measure_performance(quicksort, data, name))
        durations['mergesort'].append(measure_performance(mergesort, data, name))
        durations['heapsort'].append(measure_performance(heapsort, data, name))
        durations['radixsort'].append(measure_performance(radixsort, data, name))

    avg_durations = {k: mean(v) for k, v in durations.items()}

    best_algorithm = min(avg_durations, key=avg_durations.get)
    worst_algorithm = max(avg_durations, key=avg_durations.get)

    print(
        f"Best performance for {name}: {best_algorithm} with {avg_durations[best_algorithm]:.6f} seconds (average over {num_runs} runs)")
    print(
        f"Worst performance for {name}: {worst_algorithm} with {avg_durations[worst_algorithm]:.6f} seconds (average over {num_runs} runs)")
