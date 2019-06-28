#include <list>
#include <vector>
#include <iostream>

using namespace std;

void Degree_Centrality()
{
	int n, m;
	cin>>n>>m;
	// Initialize the rows as empty lists.
	vector<list<pair<int, int>> > adj_list(n, list<pair<int, int>>());
	int a, b, c;
	for (int i=0; i<m ;i++){
		cin>>a>>b>>c;
		adj_list[a].push_back(make_pair(b,c));
		adj_list[b].push_back(make_pair(a,c));
	}
	//Centrality ouput
	for (int i=0; i< n; i++){
		cout << adj_list[i].size() << endl;
	}
}