// All the Tree / Graph Terminologies Explained | CP Course | EP 68

// Tree = Graph with no cycle

//ACP -JD  02/02/2023
Ajacency List :
	vector<int> adj[N];
	adj[1].push_back(2);
	adj[1].push_back(3);
	adj[2].push_back(3);
	adj[3].push_back(4);

//For weighted directed graph:
	vector<pair<int,int>> adj[N]; //(pair(vertex,weight))
	adj[1].push_back(2,3);

//We can also go for
//Edge List :
	vector<tuple<int,int,int>> edges: //first vertex,second vertex,cost of edge)
	edges.push_back((1,2,3));

//DFS:
vector<int> adj[N];
bool visited[N];
void DFS(int s) //s is the source
{
	if(visited[s))return;
	v
visited[s] =true
	for(auto u : adj[s])
	{
		dfs(u);
	}
}

