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
 ListGraph::Edge edges;
 ListGraph::NodeMap<int> label(g);
 ListGraph::NodeMap<double> lat(g);
 ListGraph::NodeMap<double> lon(g);
 ListGraph::EdgeMap<int> length(g);
 ListGraph::EdgeMap<int> maxspeed(g);
 ListGraph::NodeMap<bool> visited(g);

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
 cout << "\nA gráfban taállható csúcsok száma: \t\t\t" << SumNodes << endl;
 
 vector<int> components;
 int max=0;
 Bfs<ListGraph> bfs(g);
 bfs.reachedMap(visited);

 bfs.init();
 for(ListGraph::NodeIt i(g);i!=INVALID;++i){
 	
 	if(!bfs.reached(i)){
 		bfs.addSource(i); 		
 		int reached=0; // a komponens merete
 		// bfs.start();
 		while(!bfs.emptyQueue() ){
 			bfs.processNextNode();
 			reached++;
 		}
 		components.push_back(reached);
 		max = (components[max] < components[components.size()-1])? components.size()-1 : max;
 	}
 }
  
 cout << endl << components.size() << " komponenst találtam a gráfban, melyek közül a legnagyonbb " << components[max] << " csúcsot tartalmaz\n";
 return 0;
}
