#include <list>
#include <vector>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

int main(){
	#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
	string Type,Path;
	// Redirect cin to read from a file
	freopen("graph_files/Input_Data.txt", "r", stdin);
	getline(cin,Type);
	getline(cin,Path);
	//cout << Path << endl;
	//Path = "D:/My Files/Projects/Data Structures/Social Media Analysis/Media Analysis/Media Analysis/graph_files/undirected_unweighted_graph.txt";
	const char * cstr = Path.c_str();
	freopen(cstr, "r", stdin);
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
	// Redirect cout to write to a file
	freopen("graph_files/centrality.txt", "w", stdout);
	//Centrality ouput
	for (int i=0; i< n; i++){
		cout << adj_list[i].size() << endl;
	}
	return 0;
}