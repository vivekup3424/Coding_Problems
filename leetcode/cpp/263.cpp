//An ugly number is a positive integer whose prime factors are 
//limited to 2, 3, and 5.
class Solution {
public:
    bool isUgly(int n) {
        if(n<=0) return false;
        while(n > 0 && n%2==0){
            n = n/2;
        }       
        while(n > 0 && n%3==0){
            n = n/3;
        }
        while(n > 0 && n%5==0){
            n = n/5;
        }
        return n == 0 || n==1;
    }
};