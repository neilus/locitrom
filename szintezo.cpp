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

using namespace lemon;
using namespace std;


void szintezo(ListDigraph &G, const ListDigraph::NodeMap<int> &d , const ListDigraph::NodeMap<int> &label){
	ListDigraph::NodeMap<int> l(G);
	ListDigraph::NodeMap<int> ro(G);
	ListDigraph::NodeIt hungry(G);
	const int N = countNodes(G);
	int maxL = 0;

	cerr <<"INFO:\tlabel[i]\tro[i]\td[i]\tl[i]" << endl;
	
	for( ListDigraph::NodeIt i(G);i!=INVALID;++i){
		l[i]=0;
		ro[i] = countInArcs(G,i);
		if(ro[i] < d[i])
			hungry = i;
		cerr <<"INFO:\t"<< label[i] <<"\t\t"<< ro[i]<<"\t" <<d[i] << "\t"<< l[i]<<endl;
	}
	if(ro[hungry] >= d[hungry])
		hungry = INVALID;

	ListArcSet<ListDigraph> arcs(G);
	cout << "\tN is:" << N <<endl;
	
	
	while( maxL < N && hungry != INVALID ){
		cerr <<"INFO:\tlabel[i]\tro[i]\td[i]\tl[i]" << endl;
		for(ListDigraph::NodeIt i(G); i!=INVALID; ++i){
			
			for (ListDigraph::OutArcIt a(G,i); a!= INVALID ; ++a)
				{
					//cerr <<"\t" << label[G.target(a)];
					if( (ro[i] < d[i]) && ( abs( l[G.target(a)] - l[i] ) <= 1  ) ){  
					/// ha i ehes meg es a szomszedja nincs 1-nel messzebb akkor cserelhetnek elet
						//megtalaltam a rohadekot, most ha jo csucsba vezet akkor meg is kene forditani...
						cerr << "\tDEBUG:" << label[i] << " es " << label[G.target(a)] << "kozott elet forditok" <<endl;
						G.reverseArc(a); /// megforditom az elet, ezert ...
						ro[i] ++; /// most bele egyel tobb el mutat
						ro[G.target(a)]--; /// bele pedig egyel kevesebb
					}
					else{
						l[i] ++; /// ha nincs megfelelo szomszedja, akkor szintet lephet
						if(maxL < l[i]) /// ha o van most a legmagasabban akkor megjegyezzuk a szintet amin van
							maxL = l[i];
					}
				}
			cerr <<"DEBUG:\t" << label[i] <<"\t\t"<< ro[i]<<"\t" <<d[i] << "\t"<< l[i]<<endl;					
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



int main(int argc, char*argv[])
{
 ListDigraph g;
 ListDigraph::Node nodes;
 ListDigraph::Arc	 arcs;
 ListDigraph::NodeMap<int> label(g);
 ListDigraph::NodeMap<int> d(g);

 string filename = ( (argc < 2)?"teszt-szintezo.lgf":argv[1] )  ;
 cout << "A "<< filename <<" fájlt elkezdem feldolgozni (ez eltarthat egy jódarabig)"<< endl;
 try {
	 DigraphReader<ListDigraph>(g, filename.c_str())
		.nodeMap("label",label)
		.nodeMap("d",d)
		.run();
	 } catch (Exception& error) { // check if there was any error
    cout << "Error: " << error.what() << endl;
    return -1;
  	}
 

 int SumNodes = countNodes(g);
 cout << "\nA gráfban található csúcsok száma: \t\t\t" << SumNodes << endl;
 
 szintezo(g,d,label);
 
 return 0;
}
