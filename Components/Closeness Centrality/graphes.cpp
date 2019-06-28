#include <stdio.h>
#include <limits.h>
#include<iostream>
#include<vector>
using namespace std;

 //needs modification
int V;

int minDistance(int dist[], bool sptSet[] )
{
   int min = INT_MAX, min_index;

   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}


 int calc(int dist[],int n){
	 int x=0;
	 for (int i =0;i<n;i++){
		 x+=dist[i];
	 }
	 return x;
 }

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
int closness_dijkstra(vector< vector<int> >& graph, int src)
{
     int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i

     bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized

     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

     // Distance of source vertex from itself is always 0
     dist[src] = 0;

     // Find shortest path for all vertices
     for (int count = 0; count < V-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in the first iteration.
       int u = minDistance(dist, sptSet);

       // Mark the picked vertex as processed
       sptSet[u] = true;

       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < V; v++)

         // Update dist[v] only if is not in sptSet, there is an edge from
         // u to v, and total weight of path from src to  v through u is
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
int x=calc (dist,V);

return x;
}

int main()
{cin >>V;
int m;
cin>>m;
	int x[V];
	vector<vector<int>>graph(V,vector<int>(V,0));
	for(int j=0;j<m;j++){
		int a,b,c;
		cin>>a>>b>>c;
		graph[a][b]=c;
		graph[b][a]=c;

	}
double centrality[V];


   for(int i=0;i<V;i++){

    x[i]= closness_dijkstra(graph, i);
    centrality[i]=(double)(V-1)/(double)x[i];
    cout<<centrality[i]<<"\n";
   }

    return 0;
}
