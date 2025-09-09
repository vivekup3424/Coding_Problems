#include <bits/stdc++.h>
using namespace std;

int josephus(int n, int k){
    int base = log(n)/log(2);
    int l = n - pow(2, base);
    return 2*l + 1;
}