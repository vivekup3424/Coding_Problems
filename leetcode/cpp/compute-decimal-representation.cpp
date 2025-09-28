#include <bits/stdc++.h>
using namespace std;
class Solution{
    public:
    vector<int> decimalRepresentation(int n){
        vector<int> answer;
        int current = 1;
        while(n>0){
            int remainder = n % 10;
            if(remainder!=0){
                answer.push_back(remainder*current);
            }
            n = n / 10;
            current = current * 10;
        }
        reverse(answer.begin(), answer.end());
        return answer;
    }
};

int main(){
    int n = 537;
    auto A = new Solution();
    A->decimalRepresentation(n);
}