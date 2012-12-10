#ifndef __ELJAVITO__
#define __ELJAVITO__

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


void eljavito(ListDigraph &G, const ListDigraph::NodeMap<int> &d, const ListDigraph::NodeMap<int> &label){
	ListDigraph::NodeMap<int> ro(G);
	bool solveable=true;
	/// fel kell bontani a grafot a harom fo reszhalmazra:
	/// ro(i)    < , = , >     d(i)
	vector<int> lt, eq, gt;
	for(ListDigraph::NodeIt i(G); i!= INVALID; ++i){
		ro[i] = countInArcs(G,i);
		if( ro[i] < d[i] )
			lt.push_back( G.id(i) );
		else if( ro[i] > d[i] )
			gt.push_back( G.id(i) );
		else if( ro[i] == d[i] )
			eq.push_back( G.id(i) );
	}

	// itt mar nem Digraph::NodeIt az i hanem sima integer, amivel a vektorokon iteralunk
	cerr << "A deficitesek: ";
	for(int i=0; i < lt.size(); i++)
		cerr << label[ G.nodeFromId( lt[i] ) ] << "\t";
	cerr << endl;
	cerr << "A jok: ";
	for (int i=0; i < eq.size(); i++)
		cerr << label[ G.nodeFromId( eq[i] ) ] << "\t";
	cerr << endl;
	cerr << "A tobbletesek: ";
	for (int i=0; i < gt.size(); i++)
		cerr << label[ G.nodeFromId( gt[i] ) ] << "\t";
	cerr << endl;
	/// miutan megvan a 3 csucsosztalyunk meg kell vizsgalni a szukseges felteteleket...
	solveable = lt.size() <= gt.size();
	while( solveable && lt.size()>0 ){
	/// BFS-el utat kell talalni <-bol >-be
		ListDigraph::NodeIt s(G,G.nodeFromId( lt[lt.size()-1] ));


		Bfs<ListDigraph> bfs(G);
		bfs.addSource(s);
		bfs.run();		
		int i=0;
		for (i=0; i < gt.size() && !bfs.reached( G.nodeFromId( gt[i]) ); ++i)
			;// keresek egy tobbletes csucsot a bejart csucsok kozott
		ListDigraph::NodeIt t(G,G.nodeFromId( gt[i] )); 
		if( t!=INVALID && bfs.reached(t) ){ 
			// hogyha bejartam a legutobbit akkor eljutottam a gt-be			
			Path<ListDigraph> p = bfs.path(t);
			
			/// 	annak az utnak az iranyitasat meg kell forditani amit igy talaltam
			for(Path<ListDigraph>::ArcIt arc(p);arc!=INVALID; ++arc){
				cerr << "\n megforditom az elt" << label[ G.source(arc) ]<< " es " << label[ G.target(arc) ]<< " kozott\n";
				G.reverseArc(arc);
			}
			///		update-elni kell a csucsok hova-tartozasat (melyik osztaly)
			lt[G.id(s)]++;
			gt[G.id(t)]++;
			if( ro[s] >= d[s] ){
				lt.pop_back();
				if(ro[s] > d[s] ){
					gt.push_back(G.id(s));
				}else if(ro[s] == d[s] ){
					eq.push_back(G.id(s));
				}
			}
			if(ro[t]==d[t]){
				eq.push_back(G.id(t));
				int i;
				for(i=0;i<gt.size() && gt[i]!= G.id(t);i++)
					;
				gt.erase(gt.begin() + i);
			}
		}
		solveable = gt.size() >= lt.size();	

	}	/// amig ki nem urul a < osztaly, vagy nem talalunk egyaltalan utat a <-bol >-be
	if(!solveable){
		cerr<<endl<< "nincs megoldas :( \na serto csucshalmaz:\n";
		for(int i=0; i<lt.size();i++){
			cerr << label[ G.nodeFromId( lt[i] ) ] << "\t";
		}
		cerr << endl;
	}
}
#endif