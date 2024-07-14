#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
* @author Vivek Upadhyay(vivekup3424)
* @date 14/07/2024
*/
bool isAlpha(char c){
    if(c >= 'A' && c <= 'Z') return true;
    if(c >= 'a' && c <= 'z') return true;
    return false;
}
bool isNum(char c){
    if(c >= '0' && c <= '9'){
        return true;
    }
    return false;
}

class Solution {
public:
    /**
     * A function to count atoms in the given formula.
     *
     * @param formula the input formula to count atoms from
     *
     * @return a string representing the count of atoms
     *
     * @throws None
     */
    string countOfAtoms(string formula) {
        map<string,int> freqHashMap;
        stack<pair<string,int>> stk; //stores the atom and its valency
        int n = formula.size();
        for(int i = 0; i < n; i++){
            if(formula[i]=='('){
               stk.push({"(",1});
               continue;
            }
            else if(formula[i]==')'){
               //check to see, if any number follow ")" 
               if(i<n and isNum(formula[i])){
                string num = "";
                while(i < n and isNum(formula[i])){
                    num.push_back(formula[i]);
                }
                int val = 1;
                if(num!=""){
                    val = atoi(num);
                }
                //pop all the previous atoms inside the braces from
                //stack
                while(stk.size()>0 and stk.top().first !="("){
                    auto p = stk.top();
                    freqHashMap[p.first] += p.second * val;
                }
                if(stk.size()>0 and stk.top().first =="("){
                    stk.pop();
                }
               }
            }
            string atom = "", num = "";
            bool smallCase = false;
            while(i<n and isAlpha(formula[i])){
                if(smallCase==true and 'A'<=formula[i]<='Z'){
                    break;
                }
                else if('a' <= formula[i] <= 'z'){
                    smallCase = true;
                } 
                atom.push_back(formula[i]);
            }
            while(i<n and isNum(formula[i])){
                num.push_back(formula[i]);
            }
            int val = 1;
            if(num != ""){
                val = atoi(num);
            }
            stk.push({aton,val});
        }         
        while(stk.size()>0){
            auto p = stk.top();
            freqHashMap[p.first] += p.second;
        }
        //creating the frequency strings from hashmap
        string ans = "";
        for(auto it: freqHashMap){
            ans.push_back(it.first);
            ans.push_back(to_string(it.second));
        }
        return ans;
    }
};

main() {
    Solution s;
    cout << s.countOfAtoms("H2O") << endl;
    cout << s.countOfAtoms("Mg(OH)2") << endl;
    cout << s.countOfAtoms("K4(ON(SO3)2)2") << endl;
}