#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> arr = {1, 2, 3, 4};

    // Sort the array to start with the smallest permutation
    std::sort(arr.begin(), arr.end());

    do
    {
        // Print the current permutation
        for (int num : arr)
        {
            std::cout << num << " ";
        }
        std::cout << "\n";
    } while (std::next_permutation(arr.begin(), arr.end()));

    return 0;
}
