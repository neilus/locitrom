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
// ListGraph::NodeMap<bool> visited(g);

// Bfs<ListGraph>::SetReachedMap<ListGraph::NodeMap<bool> > visited(g);
// Bfs<ListGraph>::SetReachedMap<ListGraph::NodeMap<bool> > lastvisited(g);

 string filename = ( (argc < 2)?"hun.lgf":argv[1] )  ;
 cerr << "A "<< filename <<" fájlt elkezdem feldolgozni (ez eltarthat egy jódarabig)"<< endl;
 try {
	 graphReader<ListGraph>(g, filename.c_str())
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
// bfs(g).setReachedMap(visited);
 int max = 0;
 while( unreached > 0 ){
 	ListGraph::NodeIt s(g),i(g);
 	bfs.init();
	bfs.addSource(s);
 	reached = 1;
 	while( !bfs.emptyQueue() ){
		i = ListGraph::NodeIt( g, bfs.processNextNode() );
		g.erase(s);
		s = i;
		reached ++;
	}
	g.erase(s);
	unreached -= reached;
	components.push_back(reached);
	max = ( max < reached)? reached:max;
	cout << "\n\t" << reached << " nodes reached,\t"<< unreached <<" nodes to go\t";
 }
 cout << "\n\nA gráfban található csúcsok száma: " << SumNodes << endl;
 cout << components.size() << " komponenst találtam a gráfban, melyek közül a legnagyonbb " << max << " csúcsot tartalmaz\n";
 return 0;
}
