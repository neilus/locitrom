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
#include "eljavito.h"
#include "mindenfele.h"

using namespace lemon;
using namespace std;




int main(int argc, char*argv[])
{
 ListDigraph g;
 ListDigraph::Node nodes;
 ListDigraph::Arc	 arcs;
 ListDigraph::NodeMap<string> label(g);
 ListDigraph::NodeMap<string> halmaz(g);

 string filename = ( (argc < 2)?"teszt-parosito.lgf":argv[1] )  ;
 cout << "A "<< filename <<" fájlt elkezdem feldolgozni (ez eltarthat egy jódarabig)"<< endl;
 try {
	 DigraphReader<ListDigraph>(g, filename.c_str())
		.nodeMap("label",label)
		.nodeMap("halmaz",halmaz)
		.run();
	 } catch (Exception& error) { // check if there was any error
    cout << "Error: " << error.what() << endl;
    return -1;
  	}
 

 int SumNodes = countNodes(g);
 cout << "\nA gráfban található csúcsok száma: \t\t\t" << SumNodes << endl;
 grafbejaro(g,label,halmaz);
 preParositarosit(g,label,halmaz,d);
 grafbejaro(G,d,label);
 eljavito(g,d,label);
 grafbejaro(G,d,label);
 grafbejaro(g,label,halmaz);
 return 0;
}
