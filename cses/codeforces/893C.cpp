#include<bits/stdc++.h>
using namespace std;

class Graph
{
    private :
        int V;
        list<int> *adj;
    public :
        Graph(int V);
        void add_edge(int m,int n);
        int BFS(int s,bool *v,int a[]);
};
Graph::Graph(int v)
{
    V = v;
    adj = new list<int>[V+1];
}
void Graph::add_edge(int m,int n)
{
    adj[m].push_back(n);
    adj[n].push_back(m);
}
int Graph::BFS(int s,bool *v,int a[])
{
    list<int> q;
    q.push_back(s);
    v[s] = true;
    int val = a[s];

    while(!(q.empty()))
    {
        int x = q.front();
        q.pop_front();

        for(list<int> :: iterator i = adj[x].begin();i != adj[x].end();++i)
        {
            if(!(v[*i]))
            {
                v[*i] = true;
                q.push_back(*i);
                if(val > a[*i])
                {
                    val = a[*i];
                }
            }

        }
    }
    return val;

}
int main()
{
    int n,m,a[100000],f[100000];
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    Graph g(n);
    while(m--)
    {
        int a,b;
        cin>>a>>b;
        g.add_edge(a,b);
    }
    bool *v = (bool *)malloc((n+1)*sizeof(bool));
    for(int i=1;i<=n;i++)
    {
        v[i] = false;
    }
    int r = 0;
    for(int i=1;i<=n;i++)
    {
        if(!v[i])
            r += g.BFS(i,v,a);
    }
    cout<<r<<endl;
    return 0;
}