#include <iostream>
#include <thread>
#include <vector>

// Function to merge two sorted arrays into a single sorted array
std::vector<int> merge(std::vector<int> left, std::vector<int> right)
{
    std::vector<int> result;
    while (left.size() > 0 && right.size() > 0)
    {
        if (left[0] < right[0])
        {
            result.push_back(left[0]);
            left.erase(left.begin());
        }
        else
        {
            result.push_back(right[0]);
            right.erase(right.begin());
        }
    }

    while (left.size() > 0)
    {
        result.push_back(left[0]);
        left.erase(left.begin());
    }

    while (right.size() > 0)
    {
        result.push_back(right[0]);
        right.erase(right.begin());
    }

    return result;
}
// Function to perform the merge sort algorithm in a separate thread
void mergeSort(std::vector<int>& arr, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        std::vector<int> left(arr.begin() + start, arr.begin() + mid + 1);
        std::vector<int> right(arr.begin() + mid + 1, arr.begin() + end + 1);

        std::thread t1(mergeSort, std::ref(left), 0, left.size() - 1);
        std::thread t2(mergeSort, std::ref(right), 0, right.size() - 1);
        std::thread t3(mergeSort, std::ref(right), 0, right.size() - 1);
        std::thread t4(mergeSort, std::ref(right), 0, right.size() - 1);

        t1.join();
        t2.join();
        t3.join();
        t4.join();

        arr = merge(left, right);
    }
}

int main()
{
    std::cout << "Enter the size of the array: ";
    int size;
    std::cin >> size;

    std::cout << "Enter the elements of the array: ";
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++)
    {
        std::cin >> arr[i];
    }

    // Perform the merge sort algorithm in a separate thread
    std::thread t(mergeSort, std::ref(arr), 0, arr.size() - 1);
    t.join();

    std::cout << "Sorted array: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

   return 0;
}