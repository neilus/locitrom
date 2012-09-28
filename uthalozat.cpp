#include <iostream>
#include <lemon/concepts/graph.h>
#include <lemon/list_graph.h>
#include <lemon/smart_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/dim2.h>
#include <lemon/dfs.h>

using namespace lemon;
using namespace std;
//using namespace lemon::dim2;

int main()
{
 SmartGraph g;
 SmartGraph::Node nodes;
 SmartGraph::Arc	 arcs;
 SmartGraph::NodeMap<int> label(g);
 SmartGraph::NodeMap<double> lat(g);
 SmartGraph::NodeMap<double> lon(g);
 SmartGraph::EdgeMap<int> length(g);
 SmartGraph::EdgeMap<int> maxspeed(g);



 try {
	 graphReader(g,"hun.lgf")
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
 Dfs<SmartGraph> dfs(g);
 //Dfs::ReachedMap<SmartGraph> reached(dfs);
 // tree.reachedMap();
 dfs.run();
 int reached = 0;
 for (SmartGraph::NodeIt i(g); i != INVALID; ++i){
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
