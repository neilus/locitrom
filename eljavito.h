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
#include "mindenfele.h"
using namespace lemon;
using namespace std;


void eljavito(ListDigraph &G, const ListDigraph::NodeMap<int> &d, const ListDigraph::NodeMap<string> &label){
	ListDigraph::NodeMap<int> ro(G);
	
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
	cerr << endl;
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
	bool solveable = lt.size() <= gt.size();
	while( solveable &&  lt.size() > 0 ){
		/// BFS-el utat kell talalni <-bol >-be		
		int _s = lt.size()-1;
		ListDigraph::NodeIt s(G,G.nodeFromId( lt[_s] ));
		Bfs<ListDigraph> bfs(G);
		bfs.run(s);		
		
		int _t=0;
		for ( int i=0;i < gt.size() && !bfs.reached( G.nodeFromId( gt[i]) ); i++){
			_t=i;// keresek egy tobbletes csucsot a bejart csucsok kozott
			//cerr << "DEBUG: " << i << endl;
		}
		solveable = _s != _t;
		ListDigraph::NodeIt t(G,G.nodeFromId( gt[_t] )); 
		if( t!=INVALID && bfs.reached(t) ){ 
			// hogyha bejartam a legutobbit akkor eljutottam a gt-be			
			Path<ListDigraph> p = bfs.path(t);
			
			/// 	annak az utnak az iranyitasat meg kell forditani amit igy talaltam
			
			for(Path<ListDigraph>::ArcIt arc(p);arc!=INVALID; ++arc){
				cerr << "\n megforditom az elt " << label[ G.source(arc) ]<< " es " << label[ G.target(arc) ]<< " kozott"<<endl;
				G.reverseArc(arc);
			}/**/
			///		update-elni kell a csucsok hova-tartozasat (melyik osztaly)
			ro[s]++;
			ro[t]--;

			
			if(ro[s] == d[s] ){
				lt.erase(lt.begin() + _s -1 );
				eq.push_back(_s);
			}
			if(ro[t] == d[t] ){
				gt.erase(lt.begin() + _t -1 );
				eq.push_back(_t);
			}

			cerr << "\t" <<lt.size() << "\t" << gt.size();
			
		}

		solveable = solveable || ( lt.size() <= gt.size() );

	}	/// amig ki nem urul a < osztaly, vagy nem talalunk egyaltalan utat a <-bol >-be
	
	if(!solveable){
		cerr<<endl<< "nincs megoldas :( \na serto csucshalmaz:\n";
		for(int i=0; i<lt.size();i++){
			cerr << label[ G.nodeFromId( lt[i] ) ] << "\t";
		}
		cerr << endl;
	}

}
void parosit(ListDigraph &G, ListDigraph::NodeMap<string> &label, ListDigraph::NodeMap<string> &halmaz){
	ListDigraph::NodeMap<int> d(G);
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
	grafbejaro(G,d,label);
	eljavito(G,d,label);
	grafbejaro(G,d,label);
}

#endif