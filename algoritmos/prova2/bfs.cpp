#include <bits/stdc++.h>
using namespace std;
#define n 10

class G {
public:
  int data;
  int V;
  list<int> *adj;

  G(int V){
    this->V = V;
    adj = new list<int>[V];
  }
  
  void addEdge(int v, int w) { adj[v].push_back(w); }

  vector<bool> BFS_visit(vector<bool> visited, int S){
    
    visited[S] = true;

    list<int> q_;
    list<int>::iterator i;
    q_.push_back(S);

    while(q_.empty() == false){

      S = q_.front();

      cout << S << " ";

      q_.pop_front();

      for(i = adj[S].begin(); i != adj[S].end(); i++){
        if(visited[*i] != true)
        {
          visited[*i] = true;
          q_.push_back(*i);
        }
      }
    }

    return visited;
  }

  void BFS(){
    vector<bool> visited(V, 0);
    
    for(int i = 0; i < V; i++)
      if(visited[i] != true)
        visited = BFS_visit(visited, i);
    
  }
};

int main() { 
  G graph(5); 
  graph.addEdge(0, 3);
  graph.addEdge(1, 0);
  graph.addEdge(1, 2);
  graph.addEdge(1, 3);
  graph.addEdge(2, 3);
  graph.addEdge(4, 0);
  graph.addEdge(4, 1);
  graph.BFS();
  return 0; 
  
}
