#include <bits/stdc++.h>
#include <cstring>
using namespace std;

/**
 * Given two string s1 and s2 of same length, the task is to check whether s2 is a rotation of s1.

Examples: 

    Input: s1 = “abcd”, s2 = “cdab”
    Output: true
    Explanation: After 2 right rotations, s1 will become equal to s2.

    Input: s1 = “aab”, s2 = “aba”
    Output: true
    Explanation: After 1 left rotation, s1 will become equal to s2.

    Input: s1 = “abcd”, s2 = “acbd”
    Output: false
    Explanation: Strings are not rotations of each other.

*/

//Naive Approach
//Generating all possible rotation of s1 and comparing it with s2
//Time Complexity = O(n^2) (n - for comparing and another n for generating all rotations)
//Space Complexity = O(n) linear to store the temporary variable

bool areRotations(string &s1, string &s2){
    strlen(s1);
}
