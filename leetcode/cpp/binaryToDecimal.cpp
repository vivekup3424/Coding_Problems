#include <bits/stdc++.h>
#include <string>
using namespace std;

int ToDecimel(string binaryString){
    int n = 0;
    for (int i = binaryString.size()-1; i>=0; i--) {
        n = 2 * n + (binaryString[i]=='1');
    }
    return n;
}
int main (int argc, char *argv[]) {
    cout<<"Enter the number of testcases:-\t";
    int t;
    cin>>t;
    while (t--) {
        cout<<"Enter the binary string:-\t";
        string num;
        cin>>num;
        cout<<"Number:-\t"<<ToDecimel(num)<<endl;
    }
    return 0;
}

