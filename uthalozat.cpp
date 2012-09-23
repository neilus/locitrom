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
 ListGraph::NodeMap<int> lat(g);
 ListGraph::NodeMap<int> lon(g);
 ListGraph::Node nodes;
 ListGraph::ArcMap<int> length(g);
 ListGraph::ArcMap<int> maxspeed(g);

 graphReader(g,"hun.lgf")
	.nodeMap("lat",lat)
	.nodeMap("lon",lon)
	.arcMap("lengh",length)
	.arcMap("mazspeed",maxspeed)
	.run();

 int c;
 std::cin >> c;
 return 0;
}
