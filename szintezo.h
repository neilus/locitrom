#ifndef __SZINTEZO__
#define __SZINTEZO__

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
#include <string>


using namespace lemon;
using namespace std;

int maxL = 0;

inline bool resSzint(ListDigraph &G, ListDigraph::NodeMap<int> &l, ListDigraph::NodeMap<int> &ro,const ListDigraph::NodeMap<int> &d,const ListDigraph::NodeMap<string> &label, ListDigraph::NodeIt &i){
	
	for (ListDigraph::OutArcIt a(G,i); a!= INVALID ; ++a){
		//cerr <<"\t" << label[G.target(a)];
		while( (ro[i] < d[i]) && (  ( l[G.target(a)] == l[G.source(a)] - 1 ) ) ){  
			/// ha i ehes meg es a szomszedja nincs 1-nel messzebb akkor cserelhetnek elet
			//megtalaltam a rohadekot, most ha jo csucsba vezet akkor meg is kene forditani...
			cerr << "DEBUG:\t\t" << label[G.source(a)] << " es " << label[G.target(a)] << " kozott elet forditok" <<endl;
			G.reverseArc(a); /// megforditom az elet, ezert ...
			ro[G.source(a)] --; /// most felcserelodott a source es a target azaz
			ro[G.target(a)] ++; /// az uj source atad az uj targetnak egy bemeno elet...
		}
	}
	if(ro[i] < d[i])
		l[i] ++; /// ha nincs megfelelo szomszedja, akkor szintet lephet
	cerr <<"DEBUG:\t" << label[i] <<"\t\t"<< ro[i]<<"\t" <<d[i] << "\t"<< l[i]<<endl;	
	return maxL <= l[i];
}
	


void szintezo(ListDigraph &G, const ListDigraph::NodeMap<int> &d , const ListDigraph::NodeMap<string> &label){
	ListDigraph::NodeMap<int> l(G);
	ListDigraph::NodeMap<int> ro(G);
	ListDigraph::NodeIt hungry(G);
	const int N = countNodes(G);
	cerr <<"INFO:\tlabel[i]\tro[i]\td[i]\tl[i]" << endl;
	
	for( ListDigraph::NodeIt i(G);i!=INVALID;++i){
		l[i]=0;
		ro[i] = countInArcs(G,i);
		if(ro[i] < d[i] && (d[hungry]-ro[hungry]<d[i]-ro[i]))
			hungry = i;
		cerr <<"INFO:\t"<< label[i] <<"\t\t"<< ro[i]<<"\t" <<d[i] << "\t"<< l[i]<<endl;
	}
	cerr << "\tN is:" << N <<endl;

	while( maxL < N && ( ro[hungry] < d[hungry]) ){
		cerr <<"INFO:\tlabel[i]\tro[i]\td[i]\tl[i]" << endl;
		while(resSzint(G,l,ro,d,label,hungry))
			maxL = (ro[hungry]<d[hungry])?l[hungry]:l[hungry]+1;
		for(ListDigraph::NodeIt i(G); i!=INVALID ; ++i){
			if( resSzint(G,l,ro,d,label,i)){
				maxL = l[i];
				hungry = i;
			}
			


		}
	}
	
	if(maxL >= N ){
		cerr<<endl<< "nincs megoldas :( \na serto csucshalmaz:\n";
		ListDigraph::NodeIt i(G);
		for(;i!=INVALID && l[i]!=maxL;++i)
			;
		Bfs<ListDigraph> bfs(G);
		 
		 bfs.init();
		 bfs.addSource(i);
		 // bfs.start();
		 while(!bfs.emptyQueue() ){
		 	cerr << label[bfs.processNextNode()] << "\t";
		 	
		 	}		 
		 cerr << endl;
	}
	
}

#endif
