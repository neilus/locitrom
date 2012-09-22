#include<iostream>
#include<lemon/list_graph.h>

using namespace std;
using namespace lemon;

int hasNode(const ListDigraph &miben,const ListDigraph::Node &mi){
	int talalt=0;
	for(ListDigraph::NodeIt i(miben); i != INVALID && !talalt; ++i)
		talalt = (mi == i);

	return talalt;

}
int main(){
	ListDigraph g;
	ListDigraph d;
  ListDigraph::Node x = g.addNode();
  ListDigraph::Node y = g.addNode();
  ListDigraph::Node z = g.addNode();

  ListDigraph::Node w;// = d.addNode();
  g.addArc(x,y);
  g.addArc(x,z);
  g.addArc(y,z);
  cout << (w == x) << endl
  	<< (w == y) << endl
  	<< (w == z) <<endl;

return 0;
}