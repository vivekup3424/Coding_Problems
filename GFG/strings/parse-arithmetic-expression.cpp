#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

vector<string> getLiterals(string &expression){
    vector<string> ans;
    string temp = "";
    set<char> operators = {'+','/','-','*','(',')'};
    for(auto c : expression){
        if(operators.count(c)){
            if(temp!=""){
                ans.push_back(temp);
            }
            ans.push_back(string(1,c));
            temp = "";
        }else{
            temp.push_back(c);
        }
    }
    if(temp!=""){
        ans.push_back(temp);
    }
    return ans;
}

int main(){
    cout<<"Enter an arithmetic expression:-\n";
    string expression;
    cin>>expression;
    auto literals = getLiterals(expression);
    for(auto literal : literals){
        cout<<literal<<endl;
    }
    return 0;
}
