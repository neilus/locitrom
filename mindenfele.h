#ifndef __MINDENFELE__
#define __MINDENFELE__
#include <iostream> 
#include <lemon/core.h>
#include <lemon/concepts/graph.h>
#include <lemon/concepts/digraph.h>
#include <lemon/list_graph.h>
#include <lemon/smart_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/bfs.h>
#include <lemon/edge_set.h>
#include <stdlib.h>
#include <vector>
using namespace lemon;
using namespace std;
void grafbejaro(const ListDigraph &G, const ListDigraph::NodeMap<int> &d,const ListDigraph::NodeMap<int> &label){

	cout << endl << " Label(i) \t|\tro(i)\t|\td(i)\t|\tide mutatnak elek i-bol "<<endl;
	for(ListDigraph::NodeIt i(G); i!=INVALID;++i){
		cout << endl<< label[i] << "\t|\t" << countInArcs(G,i) << "\t|\t" << d[i] << "\t|";
		for(ListDigraph::OutArcIt j(G,i); j!=INVALID; ++j){
			cout <<"\t"<< label[ G.target(j) ];
		}
	}
}
#endif