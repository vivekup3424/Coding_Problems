#include <bits/stdc++.h>
using namespace std;

void generateSentencesUtil(vector<vector<string>>& dictionaries, vector<string>& currentSentence, int index) {
    // Base case: If we've reached the last list, print the sentence
    if (index == dictionaries.size()) {
        for (const string& word : currentSentence) {
            cout << word << " ";
        }
        cout << endl;
        return;
    }

    // Recursive case: Go through each word in the current list and recurse
    for (const string& word : dictionaries[index]) {
        currentSentence.push_back(word);           // Choose a word
        generateSentencesUtil(dictionaries, currentSentence, index + 1); // Recurse for the next list
        currentSentence.pop_back();                // Backtrack to try the next word
    }
}

// Function to initiate sentence generation
void generateSentences(vector<string> sentences) {
    vector<vector<string>> dictionaries;

    // Parse each sentence to form a list of word lists
    for (const string& sentence : sentences) {
        vector<string> words;
        stringstream ss(sentence);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        dictionaries.push_back(words);
    }

    vector<string> currentSentence;
    generateSentencesUtil(dictionaries, currentSentence, 0);
}

// Main function
int main() {
    vector<string> sentences = {
        "I He She",
        "love suck play",
        "to of in",
        "C Java Python"
    };

    generateSentences(sentences);
    return 0;
}
