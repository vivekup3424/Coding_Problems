// Minimum number of insertions to make a string palindrome
// Given a string, find the minimum number of characters to be inserted to form Palindrome string out of given string
//
// Examples:
// ab: Number of insertions required is 1. bab
// aa: Number of insertions required is 0. aa

#include <bits/stdc++.h>
using namespace std;

// Solution
// 1.First find the lcs of string and its reverse
// 2.Then add the extra content to string to make it palindrome
