#include <iostream> 
#include <cstdlib> 
#include<vector>
#include<algorithm>
#include <string>
#include <queue> 
#include <stack> 
#include<stdlib.h>
#include <limits>
using namespace std;
struct compare
{
  bool operator()(const pair<int,short>& l, const pair<int,short>& r)
  {
      return l > r;
  }
};
template<class VertexType>
class GraphType {
public:
GraphType(int);
~GraphType();
void MakeEmpty();
bool IsEmpty() const;
bool IsFull() const;
void AddVertex(VertexType);
void AddEdge(VertexType, VertexType, int);
int WeightIs(VertexType, VertexType);
//void GetToVertices(VertexType, QueType<VertexType>&);
void ClearMarks();
void MarkVertex(VertexType);
bool IsMarked(VertexType) const;

int numVertices;
int maxVertices;
vector <VertexType> vertices;
vector < vector <int> > edges;
vector<bool> marks;
};
template<class VertexType>
GraphType<VertexType>::GraphType(int maxV)
{
numVertices = 0;
maxVertices = maxV;
vertices.resize(maxV);
edges.resize(maxV);
for(int i = 0; i < maxV; i++)
edges[i].resize(maxV);
marks.resize(maxV);
}
template<class VertexType>
GraphType<VertexType>::~GraphType()
{ 
vertices.clear();
edges.clear();
 marks.clear();
}
template<class VertexType>
int indexIs(vector <VertexType> vertices,VertexType fromVertex)
{
    for (int i=0; i<vertices.size();i++)
    {
        if (vertices[i]==fromVertex)
        return i;
    }
    return -1;
}
template<class VertexType>
void GraphType<VertexType>::AddVertex(VertexType vertex)
{
vertices[numVertices]=vertex;
marks[numVertices]=false;
for(int i=0;i<=numVertices;i++)
{edges[numVertices][i]==NULL;
edges[i][numVertices]==NULL;}
numVertices++;
}
template<class VertexType>
void GraphType<VertexType>::AddEdge(VertexType fromVertex,VertexType toVertex, int weight)
{
    int row ;
    int column;
    row = indexIs(vertices,fromVertex);
    column = indexIs(vertices,toVertex);
    edges[row][column]=weight;
    edges[column][row]=weight;
}
template <class VertexType>
void SSSP(GraphType<VertexType> g,int src, vector <double> &cnt)
{
int weight=0,temp;
double size=0;
stack<short> s;
vector <short> parent_index(g.numVertices);
vector <short> num_paths(g.numVertices,1);
vector < vector <int> > equal(g.numVertices);
pair <int,int>p;
vector <int> dis(g.numVertices,numeric_limits<int>::max());
//priority_queue <pair<int,short>,vector<pair <int,short>>, greater<pair <int,short>>> pq;
priority_queue <pair<int,short>,vector<pair <int,short>>, compare> pq;

int index=src;
dis[index]=0;
g.marks[index]=false;
pq.emplace(make_pair(dis[index],index));
while (!pq.empty())
{
  p=pq.top();
  index=p.second;
  weight=p.first;
  pq.pop();  
for (int i=0;i<g.numVertices;i++)
{
    if (g.marks[index]==0 && g.edges[index][i]>0)
    {
      if (dis[index]+g.edges[index][i] == dis[i])
      {
          equal[i].push_back(index);
          num_paths[i]=num_paths[i]+num_paths[index];
      } 
      if (dis[index]+g.edges[index][i] < dis[i])  
        {
            if (equal[i].size()>0)
            {equal[i].clear();
            num_paths[i]=1;}

            dis[i]=dis[index]+g.edges[index][i];
            pq.emplace(make_pair(dis[i],i));
            parent_index[i]=index;
            num_paths[i]=num_paths[index];
        }
    }
}
g.marks[index]=true;

}
for (int i=0;i<g.numVertices;i++)
{   int temp2;
    if (i!=src)
    {
        s.emplace(i);

        while (!s.empty())
        {
            temp2=s.top();
            s.pop();     
            temp=parent_index[temp2];
            
            if (temp!=src)
            {   
                size= num_paths[temp]/ double(num_paths[i]);
                size=size/2;
                cnt[temp]=cnt[temp]+size;
                s.emplace(temp);
            }

            if (equal[temp2].size()>0)
            {
                for (int j=0;j<equal[temp2].size();j++)
                {
                    temp=equal[temp2][j];
                    if (temp!=src)
                    {   
                        size= num_paths[temp]/ double(num_paths[i]);
                        size=size/2;
                        cnt[temp]=cnt[temp]+size;
                        s.emplace(temp);
                    }

                }
            }
        }

    }
}
}
template <class VertexType>
void centrality(GraphType<VertexType> g, vector <double> &cnt)
{
    for (int i=0;i<g.numVertices;i++)
    {
        SSSP(g,i,cnt);
    }
    for (int i=0;i<g.numVertices;i++)
    {
		cout << fixed;
        cout.precision(12);
        cout<<cnt[i]<<'\n';
    }
}
void Betweenness_Centrality()
{
	int n, m,a,b,c;
	cin>>n>>m; 
	vector <double>cnt(n);
	GraphType<short> g(n);
	for (int i=0; i<n ;i++)
	{
		g.AddVertex(i);
	}
	for (int i=0; i<m ;i++)
	{
		cin>>a>>b>>c;
		g.AddEdge(a,b,c);
	}
	centrality(g,cnt);
}