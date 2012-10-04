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
 ListGraph g;
 ListGraph::Node nodes;
 ListGraph::Arc	 arcs;
 ListGraph::NodeMap<int> label(g);
 ListGraph::NodeMap<double> lat(g);
 ListGraph::NodeMap<double> lon(g);
 ListGraph::ArcMap<int> length(g);
 ListGraph::ArcMap<int> maxspeed(g);

 //ListGraph::NodeMap<bool> visited(g);
 Bfs<ListGraph>::SetReachedMap<ListGraph::NodeMap<bool> > visited(g);
// ListGraph::NodeMap<bool> processed(g);



 string filename = ( (argc < 2)?"hun.lgf":argv[1] )  ;
 cout << "A "<< filename <<" fájlt elkezdem feldolgozni (ez eltarthat egy jódarabig)"<< endl;
 try {
	 DigraphReader<ListGraph>(g, filename.c_str())
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
// ListGraph::Node island = g.addNode();
 int SumNodes = countNodes(g);
// cout << "Number of arcs: " << countArcs(g) << endl;
// cout << "\tNumber of nodes: \t" << SumNodes << endl;
// for (ListGraph::NodeIt i(g); i != INVALID; ++i)
//	visited[i]=false;
 
 int reached;
 int unreached = SumNodes;
 Bfs<ListGraph> bfs(g);
// bfs.reachedMap(visited);
// bfs.processedMap(processed);
 vector<int> components;
 ListGraph::NodeIt s(g);
 bsf(g).setReachedMap(visited).run(s);
 int max = 0;
 do{
 	reached = 1;
 	bfs.run(s);
	visited[s]=true;
	for (ListGraph::NodeIt i(g); unreached > 0 && i != INVALID; ++i){
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
