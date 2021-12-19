#include <bits/stdc++.h>
#define inf 2000000000
using namespace std;

class G {
    public:
    int data;
    int V;
    list<pair<int, int>> *adj;

    G(int V){
        this->V = V;
        adj = new list<pair<int, int>>[V];
    }
    
    void addEdge(int v, int w, int p) { 
        adj[v].push_back( (pair<int, int>) {w, p} ); 
    }

    pair<vector<int>, vector<int>> Dk(int s){ // S = source
        // Incializando D, F e heap.
        vector<int> D(V, inf);
        vector<int> F(V, -1);
        vector<pair<int, int>> heap_(V, pair<int, int>{-inf, -inf});

        D[s] = 0;

        heap_.push_back( (pair<int,int>) {D[s]* (-1) , s} );
        push_heap(heap_.begin(), heap_.end());

        for(int i = 0; i  < V; i++){
            
            pair<int, int> ext = heap_.front();
            pop_heap(heap_.begin(), heap_.end());
            int d = (-1) * ext.first; 
            int u = ext.second;

            list<pair<int, int>>::iterator it;
            for(it = adj[u].begin(); it != adj[u].end(); it++){
                int v = it->first;
                int w = it->second;

                if(D[u] + w < D[v]){
                    D[v] = D[u] + w;
                    F[v] = u;
                    heap_.push_back( (pair<int,int>) {(-1) * D[v], v} );
                    push_heap(heap_.begin(), heap_.end());
                }
            }
        }
        return ((pair<vector<int>, vector<int>>){D, F});
    } 


};

int main(){
    G gr(9);
    // 0
    gr.addEdge(0, 1, 1);
    gr.addEdge(0, 2, 5);
    gr.addEdge(0, 4, 8);
    // 1
    gr.addEdge(1, 3, 2);
    // 2
    gr.addEdge(2, 5, 5);
    // 3
    gr.addEdge(3, 4, 4);
    gr.addEdge(3, 6, 9);
    // 4
    gr.addEdge(4, 5, 2);
    gr.addEdge(4, 7, 1);
    // 5
    gr.addEdge(5, 8, 1);
    // 7
    gr.addEdge(7, 6, 2);
    // 8
    gr.addEdge(8, 7, 3);

    pair<vector<int>, vector<int>> FINAl = gr.Dk(0);

    return 0;
}
 