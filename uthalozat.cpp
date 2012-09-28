#include <iostream>
#include <lemon/concepts/graph.h>
#include <lemon/list_graph.h>
#include <lemon/smart_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/dim2.h>
#include <lemon/dfs.h>

using namespace lemon;
using namespace std;

int main(int argc, char*argv[])
{
 ListGraph g;
 ListGraph::Node nodes;
 ListGraph::Arc	 arcs;
 ListGraph::NodeMap<int> label(g);
 ListGraph::NodeMap<double> lat(g);
 ListGraph::NodeMap<double> lon(g);
 ListGraph::EdgeMap<int> length(g);
 ListGraph::EdgeMap<int> maxspeed(g);


 try {
	 graphReader(g, ( (argc != 2)?"hun.lgf":argv[1] ) )
		.edgeMap("length",length)
		.edgeMap("maxspeed",maxspeed)
		.nodeMap("label",label)
		.nodeMap("lat",lat)
		.nodeMap("lon",lon)
		.run();
	 } catch (Exception& error) { // check if there was any error
    cerr << "Error: " << error.what() << endl;
    return -1;
  	}
 
 cerr << "\n\tA beolvasas lefutott...\n";
 cerr << "A digraph is read from 'hun.lgf'." << endl;
 cerr << "Number of nodes: " << countNodes(g) << endl;
 cerr << "Number of arcs: " << countArcs(g) << endl;

 cerr << "We can write it to the standard output:" << endl;
 //SmartDigraph d(g);
 Dfs<ListGraph> dfs(g);
 //Dfs::ReachedMap<ListGraph> reached(dfs);
 // tree.reachedMap();
 dfs.run();
 int reached = 0;
 for (ListGraph::NodeIt i(g); i != INVALID; ++i){
 	if( dfs.reached(i) ) {
		reached ++;
//		cerr << g.id(i) << "\t";
	}
 }

 cerr << "\nWe have reached " << reached << " nodes during DFS" << endl;
//  countNodes( tree.predMap() );


//  graphWriter(tree)
// 	.edgeMap("length",length)
// 	.edgeMap("maxspeed",maxspeed)
// 	.nodeMap("label",label)
// 	.nodeMap("lat",lat)
// 	.nodeMap("lon",lon)
// 	.run();

 cerr << "\n kesz vagyok\n";
 return 0;
}
