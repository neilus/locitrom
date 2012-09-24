#include <iostream>
#include <lemon/concepts/graph.h>
#include <lemon/list_graph.h>
#include <lemon/smart_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/dim2.h>

using namespace lemon;
//using namespace std;
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
    std::cerr << "Error: " << error.what() << std::endl;
    return -1;
  	}
 
 std::cerr << "\n\tA beolvasas lefutott...\n";
  std::cerr << "A digraph is read from 'hun.lgf'." << std::endl;
  std::cerr << "Number of nodes: " << countNodes(g) << std::endl;
  std::cerr << "Number of arcs: " << countArcs(g) << std::endl;

  std::cerr << "We can write it to the standard output:" << std::endl;

 graphWriter(g)
	.edgeMap("length",length)
	.edgeMap("maxspeed",maxspeed)
	.nodeMap("label",label)
	.nodeMap("lat",lat)
	.nodeMap("lon",lon)
	.run();

 std::cerr << "\n kesz vagyok\n";
 return 0;
}
