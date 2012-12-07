#include <iostream> 
#include <lemon/concepts/graph.h>
#include <lemon/list_graph.h>
#include <lemon/smart_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/bfs.h>

using namespace lemon;
using namespace std;
/*** 
	Itt akarom az adott elet megforditani a grafban
*/
void elforditas(ListDigraph &G, ListDigraph::Arc &el){
	///TODO: writeme please!
	cerr<<endl<<"elforditas"<<endl;
}


void szintezo(ListDigraph &G, const ListDigraph::NodeMap<int> &d , const ListDigraph::NodeMap<int> &label){
	ListDigraph::NodeMap<int> l(G);
	ListDigraph::NodeMap<int> ro(G);
	const int N = countNodes(G);
	for( ListDigraph::NodeIt i(G);i!=INVALID;++i){
		l[i]=0;
		ro[i] = countInArcs(G,i);
		cerr <<"INFO:\t" << ro[i] <<endl;
	}
	
	bool itis=true; /// van-e olyan csucs amit meg forgatnank?
	bool isNth=false; /// felert-e mar valamelyik csucs az N. szintre?
	cout << "\tN is:" << N <<endl;
	while( itis && !isNth ){
		itis=false;
		for(ListDigraph::NodeIt i(G); i!=INVALID; ++i){
			if(ro[i] < d[i]){	
				// ConArcIt<Graph> e(G);			
				// elforditas(G,e);
				ro[i] +=1;
				l[i]  +=1;
				itis = itis || ( ro[i] < d[i] );
				isNth =  ( l[i] >=  N );
				cerr << "DEBUG szintezo:\t" << label[i] << "nek elet akarunk forditani, magassaga:"<<l[i]<<"\t"<<isNth<<endl;
			}
			
		}
				

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
 
 szintezo(g,d,label);
 
 return 0;
}
