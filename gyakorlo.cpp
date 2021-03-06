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

}

void eljavito(ListDigraph &G, const ListDigraph::NodeMap<int> &d, const ListDigraph::NodeMap<int> &label){
	ListDigraph::NodeMap<int> ro(G);
	bool solveable=true;
	/// fel kell bontani a grafot a harom fo reszhalmazra:
	/// ro(i)    < , = , >     d(i)
	vector<int> lt, eq, gt;
	for(ListDigraph::NodeIt i(G); i!= INVALID; ++i){
		ro[i] = countInArcs(G,i);
		cerr << "DEBUG:" << label[i] << endl;
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
			for(Path<ListDigraph>::ArcIt arc(p);arc!=INVALID; ++arc)
				G.reverseArc(arc);
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
int main(int argc, char*argv[])
{
 ListDigraph g;
 ListDigraph::Node nodes;
 ListDigraph::Arc	 arcs;
 ListDigraph::NodeMap<int> label(g);
 ListDigraph::NodeMap<int> d(g);

 string filename = ( (argc < 2)?"teszt-dir.lgf":argv[1] )  ;
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
 
 //szintezo(g,d,label);
 eljavito(g,d,label);
 
 return 0;
}
