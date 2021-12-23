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

                if(w < D[v]){
                    D[v] = w;
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

    gr.addEdge(A, F_, 4);
    gr.addEdge(A, D_, 10);

    gr.addEdge(B, F_, 4);

    gr.addEdge(C, E, 2);
    gr.addEdge(C, D_, 1);

    gr.addEdge(D_, E, 4);
    gr.addEdge(D_, C, 1);
    gr.addEdge(D_, A, 10);
    
    gr.addEdge(E, F_, 11);
    gr.addEdge(E, C, 2);
    gr.addEdge(E, D_, 4);
    
    gr.addEdge(F_, A, 4);
    gr.addEdge(F_, B, 4);
    gr.addEdge(F_, E, 11);
    gr.addEdge(F_, C, 8);
    
    pair<vector<int>, vector<int>> FINAl = gr.Dk(0);

    return 0;
}
 