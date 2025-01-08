#include <iostream>
using namespace std;
int main(){
	//there are only lowercase characters
	for(char c = 'a'; c <= 'z'; c++){
		cout<<c<<"=>"<<(char)(25-(c-'a')+'a')<<endl;
	}
}
