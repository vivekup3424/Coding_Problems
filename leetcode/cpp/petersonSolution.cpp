#include <bits/stdc++.h>
using namespace std;

//peterson's solution for two process

bool flags[2] = {false,false}
int turn = 0;
void thread(int i){
    flag[i] = true;
    int j = 1 - i;
    turn = j; //give priority for the first process to complete
    while(flag[j]==true and turn == j){
        //wait for the first process to complete
    }
    flags[i] = false;
    cout<<"Process i is in remainder section now."
}
