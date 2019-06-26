#include <iostream> 
#include <cstdlib> 
#include<vector>
#include<algorithm>
#include <string>
#include <queue> 
#include <stack> 
#include<tuple>
#include <limits>
using namespace std ;
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