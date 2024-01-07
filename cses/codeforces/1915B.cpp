#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
typedef std::vector<int> vi; 

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
int main()
{
    fast_io();
    int T;
    cin >> T;
    while (T--)
    {   
        vector<vector<char>> M(3, vector<char>(3));
        int x,y;
        for(int i =0; i < 3;i++){
            for(int j = 0; j <3;j++){
                char c;
                cin>>c;
                if(c == '?'){
                    x = i;
                    y = i;
                }
                M[i][j] = c;
            }
        }
        bool cPresent = false, aPresent = false, bPresent = false;
        for(auto c : M[x]){
            if(c == 'A')aPresent = true;
            else if(c == 'B')bPresent = true;
            else if(c == 'C')cPresent = true;
        }
        if(cPresent ==false)
            cout<<'C'<<endl;
        else if(bPresent ==false)
            cout<<'B'<<endl;
        else if(aPresent ==false)
            cout<<'A'<<endl;
        
    }
}