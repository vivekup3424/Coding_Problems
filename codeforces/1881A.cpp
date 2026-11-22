/*
 * 1881A. Don't Try to Count
 * https://codeforces.com/problemset/problem/1881/A
 * Time limit: 2 seconds | Memory limit: 256 megabytes
 *
 * Given a string x of length n and a string s of length m, consisting of
 * lowercase Latin letters, you can apply any number of operations to the
 * string x.
 *
 * In one operation, you append the current value of x to the end of the
 * string x. Note that the value of x will change after this.
 *
 * For example, if x = "aba", then after applying operations, x will change
 * as follows: "aba" -> "abaaba" -> "abaabaabaaba".
 *
 * After what minimum number of operations s will appear in x as a
 * substring? A substring of a string is defined as a contiguous segment
 * of it.
 *
 * Input:
 *   The first line of the input contains a single integer t
 *   (1 <= t <= 10^4) - the number of test cases.
 *
 *   The first line of each test case contains two numbers n and m
 *   (1 <= n * m <= 25) - the lengths of strings x and s, respectively.
 *
 *   The second line of each test case contains the string x of length n.
 *
 *   The third line of each test case contains the string s of length m.
 *
 * Output:
 *   For each test case, output a single number - the minimum number of
 *   operations after which s will appear in x as a substring. If this is
 *   not possible, output -1.
 *
 * Example 1:
 *   Input:
 *     12
 *     1 5
 *     a
 *     aaaaa
 *     5 5
 *     eforc
 *     force
 *     2 5
 *     ab
 *     ababa
 *     3 5
 *     aba
 *     ababa
 *     4 3
 *     babb
 *     bbb
 *     5 1
 *     aaaaa
 *     a
 *     4 2
 *     aabb
 *     ba
 *     2 8
 *     bk
 *     kbkbkbkb
 *     12 2
 *     fjdgmujlcont
 *     tf
 *     2 2
 *     aa
 *     aa
 *     3 5
 *     abb
 *     babba
 *     1 19
 *     m
 *     mmmmmmmmmmmmmmmmmmm
 *   Output:
 *     3
 *     1
 *     2
 *     -1
 *     1
 *     0
 *     1
 *     3
 *     1
 *     0
 *     2
 *     5
 *
 * Note:
 *   In the first test case of the example, after 2 operations, the string
 *   will become "aaaa", and after 3 operations, it will become "aaaaaaaa",
 *   so the answer is 3.
 *
 *   In the second test case of the example, after applying 1 operation, the
 *   string will become "eforceforc", where the substring "force" appears.
 *
 *   In the fourth test case of the example, it can be shown that it is
 *   impossible to obtain the desired string as a substring.
 */
#include <bits/stdc++.h>
using namespace std;

string returnSubstring(string t, string s){
    // if s present in t return it
    for(int i = 0; i < t.size(); i++){
        if(t[i]==s[0]){
            bool matched = true;
            for(int j = 0; j < s.size(); j++){
                if(t[i+j]==s[j])continue;
                else{
                    matched = false;
                    break;
                }
            }
            if(matched){
                return s;
            }
        }
    }
    return "";
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        string x; //n
        cin>>x;
        string s; //m
        cin>>s;
        int ans = -1;
        for(int count = 0; count <= 6; count++){
            if(returnSubstring(x,s).length()>0){
                ans = count;
                break;
            }
            x+=x;
        }
        cout<<ans<<endl;
    }
}