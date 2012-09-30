#include <iostream> 
#include <lemon/concepts/graph.h>
#include <lemon/list_graph.h>
#include <lemon/smart_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/bfs.h>

using namespace lemon;
using namespace std;

int main(int argc, char*argv[])
{
 ListDigraph g;
 ListDigraph::Node nodes;
 ListDigraph::Arc	 arcs;
 ListDigraph::NodeMap<int> label(g);
 ListDigraph::NodeMap<double> lat(g);
 ListDigraph::NodeMap<double> lon(g);
 ListDigraph::ArcMap<int> length(g);
 ListDigraph::ArcMap<int> maxspeed(g);

 ListDigraph::NodeMap<bool> visited(g);
// ListDigraph::NodeMap<bool> processed(g);

 string filename = ( (argc < 2)?"hun.lgf":argv[1] )  ;
 cout << "A "<< filename <<" fájlt elkezdem feldolgozni (ez eltarthat egy jódarabig)"<< endl;
 try {
	 DigraphReader<ListDigraph>(g, filename.c_str())
		.arcMap("length",length)
		.arcMap("maxspeed",maxspeed)
		.nodeMap("label",label)
		.nodeMap("lat",lat)
		.nodeMap("lon",lon)
		.run();
	 } catch (Exception& error) { // check if there was any error
    cout << "Error: " << error.what() << endl;
    return -1;
  	}
 
// cout << "\n\tthe graph has been read from the file...\n";
// adding a 1-node island in to the graph we just read ... for fun and control
// ListDigraph::Node island = g.addNode();
 int SumNodes = countNodes(g);
// cout << "Number of arcs: " << countArcs(g) << endl;
// cout << "\tNumber of nodes: \t" << SumNodes << endl;
// for (ListDigraph::NodeIt i(g); i != INVALID; ++i)
//	visited[i]=false;
 
 int reached;
 int unreached = SumNodes;
 Bfs<ListDigraph> bfs(g);
// bfs.reachedMap(visited);
// bfs.processedMap(processed);
 vector<int> components;
 ListDigraph::NodeIt s(g);
 int max = 0;
 do{
 	reached = 1;
 	bfs.run(s);
	visited[s]=true;
	for (ListDigraph::NodeIt i(g); unreached > 0 && i != INVALID; ++i){
		if( bfs.reached(i) && !visited[i] ) {
			reached ++;
			visited[i] = true;
		}else 
		if(!bfs.reached(i) && !visited[i] )
			s = i;
			
	 }
	unreached -= reached;
	components.push_back(reached);
	max = ( max < reached)? reached:max;
//	cout << "\n\t" << reached << " nodes reached,\t"<< unreached <<" nodes to go\t";
 } while( !visited[s] );
 SumNodes = countNodes(g);
 cout << "\nA gráfban található csúcsok száma: \t\t\t" << SumNodes << endl;
 cout << endl << components.size() << " komponenst találtam a gráfban, melyek közül a legnagyonbb " << max << " csúcsot tartalmaz\n";
 return 0;
}
