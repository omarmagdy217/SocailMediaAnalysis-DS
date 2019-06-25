#include "graphs.h"
#include <iostream> 
#include <cstdlib> 
#include<vector>
#include<algorithm>
#include <string>
#include <queue> 
#include<stdlib.h>
#include <limits>
using namespace std;
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
void SSSP(GraphType<VertexType> g,int src, vector <float> &cnt)
{
int weight=0,temp;
float size=0;
stack<int> s;
vector <int> parent_index(g.numVertices);
vector <int> num_paths(g.numVertices,1);
vector < vector <int> > equal(g.numVertices);
pair <int,int>p;
vector <int> dis(g.numVertices,numeric_limits<int>::max());
priority_queue <pair<int,int>,vector<pair <int,int>>, greater<pair <int,int>>> pq;
int index=src;
//num_paths[src]=0;
//int index=g.vertices.IndexIs(src);
dis[index]=0;
//g.marks.clear();
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
          num_paths[i]++;
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
            
            
            size= num_paths[temp]/ float(num_paths[i]);
            cnt[temp]=cnt[temp]+size;
            //if (parent_index[temp]!=src)
            s.emplace(temp);
        }
        
        if (equal[temp2].size()>0)
        {
            for (int j=0;j<equal[temp2].size();j++)
            {
                temp=equal[temp2][j];
                if (temp!=src)
                {
                    size= num_paths[temp]/ float(num_paths[i]);
                    cnt[temp]=cnt[temp]+size;
                    //if (parent_index[temp]!=src)
                    s.emplace(temp);
                }
                
            }
        }
        }
        
    }
}
}
template <class VertexType>
void centrality(GraphType<VertexType> g, vector <float> &cnt)
{
    for (int i=0;i<g.numVertices;i++)
    {
        SSSP(g,i,cnt);
    }
}
int main()
{vector<char> span;
pair<short,bool> temp;
temp={5,5};
vector <float>cnt(10);
GraphType<int> g(5);
    g.AddVertex('0');
    g.AddVertex('1');
    g.AddVertex('2');
    g.AddVertex('3');
    g.AddVertex('4');
    g.AddEdge('0','1',1);
    g.AddEdge('0','2',1);
    g.AddEdge('2','3',1);
    g.AddEdge('2','4',3);
    g.AddEdge('3','4',1);
    g.AddEdge('1','3',1);
   /* GraphType<int> g(10);
    g.AddVertex('1');
    g.AddVertex('2');
    g.AddVertex('3');
    g.AddVertex('4');
    g.AddVertex('5');
    g.AddVertex('6');
    g.AddVertex('7');
    g.AddVertex('8');
    g.AddEdge('1','2',9);
    g.AddEdge('1','6',14);
    g.AddEdge('1','7',15);
    g.AddEdge('2','3',24);
    g.AddEdge('6','3',18);
    g.AddEdge('6','5',30);
    g.AddEdge('6','7',5);
    g.AddEdge('7','5',20);
    g.AddEdge('7','8',44);
    g.AddEdge('3','8',19);
    g.AddEdge('4','3',6);
    g.AddEdge('4','8',11);
    g.AddEdge('5','4',11);
    g.AddEdge('5','8',16);
    g.AddEdge('3','5',2);*/
 //min_spanning(g,span);
 //SSSP( g, 1,cnt);
 centrality(g,cnt);
 cout<<"done";
 return 0;
}