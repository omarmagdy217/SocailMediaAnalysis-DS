#include <cstdio>
#include <string>
#include <iostream>
#include "Centrality.h"

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
	// Redirect cout to write to a file
	freopen("graph_files/centrality.txt", "w", stdout);
	if (Type == "Degree")
		Degree_Centrality();
	else if(Type == "Closeness")
		Closeness_Centrality();
	else
		Betweenness_Centrality();
	return 0;
}