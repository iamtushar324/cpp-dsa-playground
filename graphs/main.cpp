#include<iostream> 
#include "Graph.h"
#include<string>

using namespace std;

int main(){

  Graph<string> g;

  g.addNode("1");
  g.addNode("2");
  g.addNode("3");
  g.addNode("4");
  g.addNode("5");
  g.addNode("6");
  g.addNode("7");
  g.addNode("8");
  g.addEdge("1","2", 1);
  g.addEdge("2","3", 1);
  g.addEdge("1","3", 5);
  g.addEdge("2","6", 4);
  g.addEdge("3","5", 1);
  g.addEdge("5","6", 1);
  g.addEdge("6","7", 1);
  g.addEdge("5","7", 6);

  for(auto a:g.dfs("1", "7")){
    cout << a << " ";
  }
  cout << endl;

  g.print();

  for(auto a:g.findMinDistancePath("1", "7")){
    cout << a << " ";
  }

  return 0;
}
