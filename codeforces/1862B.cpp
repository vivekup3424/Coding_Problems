#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> b(n);
        for (int i = 0; i < n; i++)
        {
            cin >> b[i];
        }
        vector<int> answer;
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                answer.push_back(b[i]);
            }
            else
            {
                if(b[i]>=answer.back()){
                    answer.push_back(b[i]);
                }else{
                    answer.push_back(1);
                    answer.push_back(b[i]);
                }
            }
        }
        cout<<answer.size()<<endl;
        for(int i = 0; i < answer.size(); i++){
            cout<<answer[i]<<" ";
        }
        cout<<endl;
    }
}