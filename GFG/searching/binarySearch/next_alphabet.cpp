// Smallest alphabet greater than a given character

/***************************************/
// Given a list of sorted characters consisting of both Uppercase
// and Lowercase Alphabets and a particular target value, say K,
// the task is to find the smallest element in the list that is larger than K.
// Letters also wrap around. For example, if K = ‘z’
// and letters = [‘A’, ‘r’, ‘z’], then the answer would be ‘A’.

// Approach : Binary Search can be applied to find the index of the
// smallest character in the given Set of Letters such that the
// character at that index is greater than K.If the element at
// the current mid is smaller than or equal to K, binary search
// is applied on the Right half, else it is applied on the left half.

#include <bits/stdc++.h>
using namespace std;
// returns the least alphabet greater than the given alphabet
char next_alphabet(string s, char k)
{
    int low = 0, high = s.size() - 1, mid;
    char result = '0';
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (s[mid] == k)
        {
            result = k;
            break;
        }
        else if (s[mid] > k)
        {
            result = s[mid];
            high = high - 1;
        }
        else if (s[mid] < k)
        {
            low = mid + 1;
        }
    }
    return result;
}
int main()
{
    string S;
    cin >> S;
    char K;
    cin >> K;
    char result = next_alphabet(S, K);
    cout << result << "\n";
    return 0;
}