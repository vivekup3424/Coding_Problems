bool recurse(string pattern, string str, int i, int j)
{
    // i = current index of pattern
    // j = current index of str

    // If we reach the end of both the pattern and the string, it's a match
    if (i == pattern.size() && j == str.size())
    {
        return true;
    }

    // If only pattern is exhausted but string is not, it's not a match
    if (i == pattern.size() && j != str.size())
    {
        return false;
    }

    // If only string is exhausted, ensure remaining pattern characters are all '*'
    if (j == str.size())
    {
        while (i < pattern.size() && pattern[i] == '*')
        {
            i++;
        }
        return i == pattern.size();
    }

    // If the current character in pattern is '*'
    if (pattern[i] == '*')
    {
        // Match the current character or skip '*'
        return recurse(pattern, str, i, j + 1) || recurse(pattern, str, i + 1, j);
    }

    // If the current character in pattern is '?'
    else if (pattern[i] == '?')
    {
        return recurse(pattern, str, i + 1, j + 1);
    }

    // If the current character in pattern matches the current character in the string
    else if (pattern[i] == str[j])
    {
        return recurse(pattern, str, i + 1, j + 1);
    }

    // If characters don't match
    return false;
}

int wildCard(string pattern, string str)
{
    // Call the recursive function starting from the first characters of both pattern and string
    return recurse(pattern, str, 0, 0);
}
