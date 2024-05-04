#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        string x, y;
        cin >> x >> y;

        int n = x.size();

        //x is greater than y
        bool smaller_started = false;
        for (int i = 0; i < n; ++i) {
            // If x's digit is smaller than y's digit, swap them
            if(x[i]==y[i])continue;
            else if(smaller_started==false){
                if(x[i]>y[i]){
                    smaller_started = true;
                }
                else if(x[i]<y[i]){
                    swap(x[i],y[i]);
                    smaller_started = true;
                }
            }
            else if (smaller_started == true) {
                if(x[i]<y[i])continue;
                else{
                    swap(x[i],y[i]);
                }
            }
        }

        cout << x << endl;
        cout << y << endl;
    }

    return 0;
}
