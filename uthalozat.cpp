#include <iostream>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/dim2.h>

using namespace lemon;
//using namespace std;
//using namespace lemon::dim2;

int main()
{
  ListGraph g;
  ListGraph::NodeMap< dim2::Point<int> > coord(g);
  ListGraph::ArcMap<int> length(g);
  ListGraph::Node src;
  std::string title;

  digraphReader(g, "hun.lgf")
    .nodeMap("coordinate", coord)
    .arcMap("length", length)
    .node("source", src)
    .attribute("caption", title)
    .run(); 

  int c;
  std::cin >> c;
  return 0;
}
