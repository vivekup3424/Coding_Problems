#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements to a vector
template <typename T>
void inputVector(vector<T> &v, int n)
{
    v.resize(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }
}

// Template function to output elements of a vector
template <typename T>
void outputVector(const vector<T> &v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}
struct ListNode{
    int data;
    ListNode *next;
    ListNode(int data = 0){
        data = data;
        next = nullptr;
    }
};
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n,q;
        cin>>n>>q;
        ListNode *root  = new ListNode();
        ListNode *current = root;
        for(int i = 0; i < n; i++){
            int temp;
            cin>>temp;
            if(i==0){
                root = new ListNode(temp);
            }
            else{
                ListNode *newNode = new ListNode(temp);
                current->next = newNode;
                current = newNode;
            }
        }
        vector<int> ans;
        while (q--)
        {
            int t;
            cin>>t;
            //find the first occurrence of t
            //traverse the linkedlist
            int count= 0;
            ListNode *temp = 
        }
            

    }
}
