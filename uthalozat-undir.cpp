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
 ListGraph::Edge	 edges;
 ListGraph::NodeMap<int> label(g);
 ListGraph::NodeMap<double> lat(g);
 ListGraph::NodeMap<double> lon(g);
 ListGraph::EdgeMap<int> length(g);
 ListGraph::EdgeMap<int> maxspeed(g);

 ListGraph::NodeMap<bool> visited(g);
// ListGraph::NodeMap<bool> processed(g);

 string filename = ( (argc < 2)?"hun-undir.lgf":argv[1] )  ;
 cout << "A "<< filename <<" fájlt elkezdem feldolgozni (ez eltarthat egy jódarabig)"<< endl;
 try {
	 graphReader<ListGraph>(g, filename.c_str())
		.edgeMap("length",length)
		.edgeMap("maxspeed",maxspeed)
		.nodeMap("label",label)
		.nodeMap("lat",lat)
		.nodeMap("lon",lon)
		.run();
	 } catch (Exception& error) { // check if there was any error
    cout << "Error: " << error.what() << endl;
    return -1;
  	}
 

 int SumNodes = countNodes(g);

 
 int reached;
 int unreached = SumNodes;
 Bfs<ListGraph> bfs(g);

 vector<int> components;
 ListGraph::NodeIt s(g);
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
