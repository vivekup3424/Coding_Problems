#include <stdio.h>

int climbStairs(int A) {
    int steps[A+1];
    for(int i = 1; i <= A; i++){
        if(i==1){
            steps[i] = 1;
        }
        else if(i==2){
            steps[i] = 2;
        }
        else{
            steps[i] = steps[i-1] + steps[i-2];
        }
    }
}
int constSpace(int A){
    int oneStepBack = 0, twoStepBack = 0;
    int total = 0;
    for(int i = 1; i <= A; i++){
        if(i==1){
            oneStepBack = 1;
            total = oneStepBack + twoStepBack;
            twoStepBack = oneStepBack;
            oneStepBack = total;
        }
        else{
            total = twoStepBack + oneStepBack;
            twoStepBack = oneStepBack;
            oneStepBack = total;
        }
    }
}

