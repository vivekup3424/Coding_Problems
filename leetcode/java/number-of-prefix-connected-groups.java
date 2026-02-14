/*
You are given an array of strings words and an integer k.

Two words a and b at distinct indices are prefix-connected if a[0..k-1] == b[0..k-1].

A connected group is a set of words such that each pair of words is prefix-connected.

Return the number of connected groups that contain at least two words, formed from the given words.

Note:

    Words with length less than k cannot join any group and are ignored.
    Duplicate strings are treated as separate words.
    A prefix of
     */

import java.util.HashMap;
import java.util.Map;

class Solution {
    public int prefixConnected(String[] words, int k) {
        Map<String, Integer> prefixCount = new HashMap<>();

        for (String word : words) {
            if (word.length() >= k) {
                String prefix = word.substring(0, k);
                prefixCount.put(prefix, prefixCount.getOrDefault(prefix, 0) + 1);
            }
        }

        int groups = 0;
        for (int count : prefixCount.values()) {
            if (count >= 2) {
                groups++;
            }
        }

        return groups;
    }
}