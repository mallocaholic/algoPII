#include <bits/stdc++.h>
#define inf 2000000000
#define par pair<int,int>
#define A 0
#define B 1
#define C 2
#define D_ 3
#define E 4
#define F_ 5

using namespace std;

class G {
    public:
    int data;
    int V;
    list<par> *adj;

    G(int V){
        this->V = V;
        adj = new list<par>[V];
    }
    
    void addEdge(int v, int w, int p) { 
        adj[v].push_back( (par) {w, p} ); 
    }

    pair<vector<int>, vector<int>> Dk(int s){ // S = source
        // Incializando D, F e heap.
        vector<int> D(V, inf);
        vector<int> F(V, -1);
        priority_queue< par, vector<par>, greater<par>> heap_;

        D[s] = 0;

        heap_.push( (par) {D[s], s} );
        //push_heap(heap_.begin(), heap_.end());

        for(int i = 0; i  < V; i++){
            //make_heap(heap_.begin(), heap_.end());
            par ext = heap_.top();
            heap_.pop();
            int d = (-1) * ext.first; 
            int u = ext.second;

            list<par>::iterator it;
            for(it = adj[u].begin(); it != adj[u].end(); it++){
                int v = it->first;
                int w = it->second;

                if(D[u] + w < D[v] && D[u] != inf){
                    D[v] = D[u] + w;
                    F[v] = u;
                    heap_.push( (par) {D[v], v} );
                }
            }
        }
        return ((pair<vector<int>, vector<int>>){D, F});
    } 

};

int main(){
    G gr(6);

    gr.addEdge(0, 2, 5);
    gr.addEdge(0, 3, 4);
    gr.addEdge(0, 5, 12);

    gr.addEdge(1, 5, 3);

    gr.addEdge(2, 1, 1);
    gr.addEdge(2, 3, 4);

    gr.addEdge(3, 1, 3);
    gr.addEdge(3, 4, 7);

    gr.addEdge(4, 0, 1);
    gr.addEdge(4, 1, 2);
    
    gr.addEdge(5, 4, 1);
    
    pair<vector<int>, vector<int>> FINAl = gr.Dk(0);

    return 0;
}
 