#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

class A{
private:
  int a;
public:
  A(int x = 0){
    a = x;
  }
  friend void helloA();
};
void helloA(){
  A obj(10);
  printf("A.a = %d\n",obj.a);
}
void noFriendA(){
  A obj(20);
  printf("A.a = %d\n",obj.a);
}


