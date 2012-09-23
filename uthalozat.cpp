#include <iostream>
#include <lemon/concepts/graph.h>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/dim2.h>

using namespace lemon;
//using namespace std;
//using namespace lemon::dim2;

int main()
{
 ListGraph g;
 ListGraph::Node nodes;
 ListGraph::Arc	 arcs;
 ListGraph::NodeMap<int> label(g);
 ListGraph::NodeMap<double> lat(g);
 ListGraph::NodeMap<double> lon(g);
 ListGraph::ArcMap<int> length(g);
 ListGraph::ArcMap<int> maxspeed(g);

 graphReader(g,"hun.lgf")
	//.arcMap("length",length)
	//.arcMap("maxspeed",maxspeed)
	.nodeMap("label",label)
	.nodeMap("lat",lat)
	.nodeMap("lon",lon)
// valamiert az elek hossza es a sebessegkorlatot 
// nem tudom igy beolvasni, otlet? hogy kene maskepp?
	//.edgeMap("length",length)
	//.edgeMap("maxspeed",maxspeed)
	.run();
 
 std::cerr << "\n\tA beolvasas lefutott...\n";

 graphWriter(g)
	.nodeMap("label",label)
	.nodeMap("lat",lat)
	.nodeMap("lon",lon)
	.run();

 std::cerr << "\n kesz vagyok\n";
 return 0;
}
