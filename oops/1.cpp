#include <iostream>
using namespace std;
class Shape{
protected:
  int width;
  int height;
public:
  Shape(int a, int b):width(a),height(b){}
  int area(){
    cout<<"Parent class area:"<<endl;
    return 0;
  }
};
class Rectangle: public Shape{
public:
  Rectangle(int a = 0, int b = 0):Shape(a,b){}
  //function overriding 
  int area(){
    cout<<"Rectangle class area: "<< width * height<<endl;
    return 0;
  }
};
class Triangle: public Shape{
public:
  Triangle(int a = 0, int b = 0):Shape(a,b){}
  int area(){
    cout<<"Triangle class area: "<< (width * height)/2 <<endl;
    return 0;
  }
};
int main(){
  Shape *shape;
  Rectangle rec(10,7);
  Triangle tri(10,6);
  shape = &rec;
  shape->area();
}
