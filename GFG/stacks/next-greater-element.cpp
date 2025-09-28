#include <vector>
#include <stack>
using std::vector;
using std::stack;

class Solution{
public:
    vector<int> nextGreaterElement(vector<int> &arr){
        int n = arr.size();
        vector<int> result(n,-1);
        stack<int> indexStack;
        for(int i = 0; i < arr.size(); i++){
            while(indexStack.size() > 0 && arr[indexStack.top()] < arr[i]){
                result[indexStack.top()] = arr[i];
                indexStack.pop();
            }
            if(indexStack.empty() || arr[indexStack.top()] > arr[i]){
                indexStack.push(i);
            }
        }
        return result;
    }
};