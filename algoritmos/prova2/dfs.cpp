#include <bits/stdc++.h>
using namespace std;
#define n 10

class G {
public:
  int data;
  map<int, bool> visited;
  map<int, list<int>> adj;

  void addEdge(int v, int w) { adj[v].push_back(w); }

  void DFS_visit(int v) {
    visited[v] = true;

    cout << v << " ";

    list<int>::iterator i;

    for (i = adj[v].begin(); i != adj[v].end(); i++)
      if (visited[*i] == 0)
        DFS_visit(*i);
  }

  void DFS() {
    for (auto i : adj)
      if (visited[i.first] == false)
        DFS_visit(i.first);
  }

};

int main() { 

  G graph;
  graph.addEdge(0, 3);
  graph.addEdge(1, 0);
  graph.addEdge(1, 2);
  graph.addEdge(1, 3);
  graph.addEdge(2, 3);
  graph.addEdge(4, 0);
  graph.addEdge(4, 1);
  graph.DFS(); 

  return 0; 
}
