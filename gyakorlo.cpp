#include<iostream>
#include<lemon/list_graph.h>

using namespace std;
using namespace lemon;

int main(){
	ListDigraph g;

  ListDigraph::Node x = g.addNode();
  ListDigraph::Node y = g.addNode();
  ListDigraph::Node z = g.addNode();
/*
  g.addArc(x,y);
  g.addArc(y,z);
  g.addArc(z,x);
  */
  ListDigraph::Arc arc = g.addArc(x,z);
  ListDigraph::Arc parallel = g.addArc(x,y);
  ListDigraph::Arc loop = g.addArc(x,x);
  cout << endl;
  if (g.source(parallel) == g.target(parallel))
    std::cout << "This is a loop arc" << std::endl;
  else
  	cout << "nem hurokel" << endl;

  cout << endl;
  for( ListDigraph::NodeIt i(g); i != INVALID; ++i)
  	cout <<"\t" << g.id(i);
  cout << endl;
  
return 0;
}