class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        //this is same as cycle detection
        //if the courses are represented as directed graph
        //then of there is a cycle in prerequisites hence we can't finish
        //hence use topological sort Kahn's algo for cycle detection
        vector<vector<int>> adj(numCourses);
        for(auto edge: prerequisites){
            adj[edge[0]].push_back(edge[1]);
        }

        vector<int> indegree(numCourses, 0);
        for(int i = 0; i < numCourses; i++)
        {
            for(auto it: adj[i])
            {
                indegree[it]++;
            }
        }

        queue<int> q;
        for(int i = 0; i < numCourses; i++)
        {
            if(indegree[i]==0){
                q.push(i);
            }
        }
        vector<int> topo;
        //now main Kahn's algo
        while(!q.empty())
        {
            int node = q.front(); //FITO
            q.pop();
            topo.push_back(node);
            for(auto it : adj[node]){
                indegree[it]--;
                if(indegree[it]==0)q.push(it);
            }
        }
        if(topo.size()==numCourses)return true;
        else return false;
    }
};
