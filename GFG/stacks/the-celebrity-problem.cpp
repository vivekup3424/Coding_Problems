#include <bits/stdc++.h>
using namespace std;

/**
 * Given a square matrix mat[][] of size n x n, 
 * such that mat[i][j] = 1 means ith person knows jth person, 
 * the task is to find the celebrity. A celebrity is a person 
 * who is known to all but does not know anyone. Return the 
 * index of the celebrity, if there is no celebrity return -1.
 * Note: Follow 0-based indexing and mat[i][i] will always be 1.
 */

//first approach using indegree array and outdegree array
int celebrity(vector<vector<int>> mat){
    int num_people = mat.size();
    vector<int> indegree(num_people,0), outdegree(num_people,0);
    for (int i = 0; i < num_people; i++)
    {
        for(int j = 0; j < num_people; j++){
            if(j!=i){
                if(mat[i][j]){
                    //ith person knows the jth person
                    outdegree[i]++;
                    indegree[j]++;
                }
                if(mat[j][i]){
                    outdegree[j]++;
                    indegree[i]++;
                }
            }
        }
    }
    //for a person to be celebrity, everyone needs to know him => indegree = num of nodes - 1
    //outdegree = 0 => he doesn't know anyone
    for(int i = 0; i < num_people; i++){
        if(indegree[i]==num_people-1 && outdegree[i]==0){
            return i;
        }
    }
};

//second approach using stack and mat matrix
/**
 * Some observations are based on Stack Based elimination technique :
 * If A knows B, then A can't be a celebrity. Discard A, and B may be celebrity.
 * If A doesn't know B, then B can't be a celebrity. Discard B, and A may be celebrity.
 * Repeat above two steps till there is only one person.
 * Ensure the remained person is a celebrity. 
 */
int getCelebrity(vector<vector<int>> mat){
    int num_people = mat.size();
    deque<int> dq;
    for(int i = 0; i < num_people; i++){
        dq.push_back(i);
    }
    while(dq.size()>1){
        auto first = dq.front();
        dq.pop_front();
        auto second = dq.back();
        dq.pop_back();
        if(mat[first][second]){
            dq.push_back()
        }
    }
}


    The idea is to use two pointers, one from start and one from the end. Assume the start person is A, and the end person is B. If A knows B, then A must not be the celebrity. Else, B must not be the celebrity. At the end of the loop, only one index will be left as a celebrity. Go through each person again and check whether this is the celebrity. 