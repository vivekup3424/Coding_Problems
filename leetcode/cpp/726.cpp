#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isAlpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool isNum(char c)
{
    return c >= '0' && c <= '9';
}

class Solution
{
public:
    string countOfAtoms(string formula)
    {
        map<string, int> freqHashMap;
        vector<pair<string, int>> stk;
        int n = formula.size();

        for (int i = 0; i < n;)
        {
            if (formula[i] == '(')
            {
                stk.push_back({"(", 1});
                i++;
            }
            else if (formula[i] == ')')
            {
                i++;
                string num = "";
                while (i < n && isNum(formula[i]))
                {
                    num.push_back(formula[i]);
                    i++;
                }
                int val = num.empty() ? 1 : stoi(num);
                stk.push_back({")", val});
            }
            else
            {
                string atom = "";
                if (isAlpha(formula[i]) && isupper(formula[i]))
                {
                    atom += formula[i];
                    i++;
                    while (i < n && isAlpha(formula[i]) && islower(formula[i]))
                    {
                        atom += formula[i];
                        i++;
                    }
                }
                string num = "";
                while (i < n && isNum(formula[i]))
                {
                    num += formula[i];
                    i++;
                }
                int val = num.empty() ? 1 : stoi(num);
                stk.push_back({atom, val});
            }
        }

        // while (!stk.empty())
        //{
        //     auto p = stk.top();
        //     stk.pop();
        //     freqHashMap[p.first] += p.second;
        // }

        string ans = "";
        for (auto &it : freqHashMap)
        {
            ans += it.first;
            if (it.second > 1)
            {
                ans += to_string(it.second);
            }
        }
        return ans;
    }
};

int main()
{
    Solution s;
    cout << s.countOfAtoms("H2O") << endl;           // H2O
    cout << s.countOfAtoms("Mg(OH)2") << endl;       // H2MgO2
    cout << s.countOfAtoms("K4(ON(SO3)2)2") << endl; // K4N2O14S4
    return 0;
}
