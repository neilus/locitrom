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
#include <string>
using namespace lemon;
using namespace std;
void grafbejaro(const ListDigraph &G, const ListDigraph::NodeMap<int> &d,const ListDigraph::NodeMap<string> &label){

	cout << endl << " Label(i) \t|\tro(i)\t|\td(i)\t|\tide mutatnak elek i-bol "<<endl;
	for(ListDigraph::NodeIt i(G); i!=INVALID;++i){
		cout << endl<< label[i] << "\t\t|\t" << countInArcs(G,i) << "\t|\t" << d[i] << "\t|";
		for(ListDigraph::OutArcIt j(G,i); j!=INVALID; ++j){
			cout <<"\t"<< label[ G.target(j) ];
		}
	}
}
void grafbejaro(const ListDigraph &G,const ListDigraph::NodeMap<string> &label, const ListDigraph::NodeMap<string> &halmaz){

	cout << endl << " Label(i) \t|\thalmaz\t|\tide mutatnak elek i-bol "<<endl;
	for(ListDigraph::NodeIt i(G); i!=INVALID;++i){
		cout << endl<< "\t"<<label[i] << "\t|\t" <<halmaz[i] << "\t|\t";
		for(ListDigraph::OutArcIt j(G,i); j!=INVALID; ++j){
			cout <<"\t"<< label[ G.target(j) ];
		}
	}
}
void preParositarosit(ListDigraph &G, ListDigraph::NodeMap<string> &label, ListDigraph::NodeMap<string> &halmaz, ListDigraph::NodeMap<int> &d){
	
	ListDigraph::Node s = G.addNode();
	ListDigraph::Node t = G.addNode();
	label[s] = " s-> ";
	label[t] = " ->t ";
	d[s] = 0;
	d[t] = 0;
	string a="",b="";
	for (ListDigraph::NodeIt i(G); i!=INVALID; ++i){
		if( i!= s && i!=t){
			d[i] = 0;
			if(a == "")
				a = halmaz[i];
			else if (b == "")
				b = halmaz[i];

			if(halmaz[i] == a){
				G.addArc(s,i);
			}else
			{
				G.addArc(i,t);
				d[t] ++;				
			}
			d[i] = 1;
		}

		cerr << label[i] <<"\t" << halmaz[i] <<"\t"<< d[i] <<"\t"<< d[t]<<endl;
	}
	
}

#endif
