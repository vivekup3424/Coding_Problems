class Solution {
  public:
    void inorder(vector<int> &v, Node *root){
        if(root->left != nullptr){
            inorder(v,root->left);
        }
        v.push_back(root->data);
        if(root->right != nullptr){
            inorder(v,root->right);
        }
    }
    vector<int> merge(Node *root1, Node *root2) {
        vector<int> v1,v2;
        inorder(v1,root1);
        inorder(v2,root2);
        vector<int> v(v1.size()+v2.size());
        int n = 0, m = 0, k = 0;
        while(n<v1.size() and m < v2.size()){
            if(v1[n]<=v2[m]){
                v[k++] = v1[n++];
            }else{
                v[k++] = v2[m++];
            }
        }
        while(n<v1.size()){
            v[k++] = v1[n++];
        }
        while(m<v2.size()){
            v[k++] = v2[m++];
        }
        return v;
    }
};
