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
 ListGraph::NodeMap<bool> visited(g);


 string filename = ( (argc < 2)?"hun.lgf":argv[1] )  ;
 cout << "A "<< filename <<" fájlt elkezdem feldolgozni (ez eltarthat egy jódarabig)"<< endl;
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
 ListGraph::NodeIt s(g);
 int max = 0;
 while( unreached > 0 && s != INVALID ){
 	bfs.init();
	bfs.addSource(s);
 	reached = 1;
 //	bfs.run(s);
 	ListGraph::Node i;
	for(ListGraph::EdgeIt j; j !=INVALID;++j)
		cout <<endl<<g.id(j)<<": "  << g.id(g.u(j)) << "\t-\t" << g.id(g.v(j));
		
	cout << endl  << g.id(s) << "-"<< ((visited[s])?"visited":"lonely") << "\t";
	while( bfs.nextNode() != INVALID ){
		i = bfs.processNextNode();
		reached ++;
		visited[i]=bfs.reached(i);
		cout << g.id(i) << "-"<< ((visited[i])?"visited":"lonely") << "\t";
	}
		
	while(bfs.reached(s) && s != INVALID)
		++ s;
	unreached -= reached;
	components.push_back(reached);
	max = ( max < reached)? reached:max;
//	cout << "\n\t" << reached << " nodes reached,\t"<< unreached <<" nodes to go\t";
}
// SumNodes = countNodes(g);
// cout << "\nA gráfban található csúcsok száma: \t\t\t" << SumNodes << endl;
// cout << endl << components.size() << " komponenst találtam a gráfban, melyek közül a legnagyonbb " << max << " csúcsot tartalmaz\n";
 return 0;
}
