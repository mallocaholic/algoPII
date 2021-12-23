#include <bits/stdc++.h>

using namespace std;

#define A_ 0
#define B_ 1
#define C_ 2
#define D_ 3
#define E_ 4
#define F_ 5

class graph{
    public:
    list<pair<int, int>> *adj;
    int V, inf;

    graph(int V){
        adj = new list<pair<int, int>>[V];
        this->V = V;
        inf = numeric_limits<int>::max() - 12345678;
    }

    void add_edge(int src, int dest, int peso){
        pair<int, int> temp(dest, peso);
            adj[src].push_back(temp);
    }

    void BF(){
        //incializando
        vector<vector<int>> D(V, vector<int>(V));
        vector<int> F(V, -1);
        fill(D[0].begin(), D[0].end(), inf);
        D[0][0] = 0;

        //
        list<pair<int, int>>::iterator it;
        int v, w;
        bool loop = false;
        //

        for(int k = 1; k < V; k++){
            D[k] = D[k-1];
            for(int u = 0; u < V; u++){
                for(it = adj[u].begin(); it != adj[u].end(); it++){
                    v = it->first;
                    w = it->second;
                    
                    if( (D[k-1][u] + w) < (D[k][v]) ){
                        D[k][v] = D[k-1][u] + w;
                        F[v] = u;
                    } 
                }
            } 
        }

        for(int u = 0; u < V && loop == false; u++){
            for(it = adj[u].begin(); it != adj[u].end() && loop == false; it++){
                v = it->first;
                w = it->second;

                if( D[V-1][u] != inf && (D[V-1][u] + w) < (D[V-1][v]) ){
                    cout << "LOOP" << endl;
                    loop = true;
                }
            }
        } 

        /*
        if(loop == false){
            int print[V];
            int a = V - 1;
            int y = V - 1;
            int ite = 0;
            while( y != -1 ){
                print[a] = y;
                y = F[y];
                a--;
            }
            cout << D[V-1][V-1];
            for(a = a + 1; a < V; a++){
                cout << " ";
                cout << print[a];
            }
            cout << endl;
        }
        */
        
    }
    
};

int main(){

    graph G(5);
    // G.add_edge();
    G.add_edge(A_, B_, 6);
    G.add_edge(A_, E_, 7);

    G.add_edge(B_, D_, -4);
    G.add_edge(B_, C_, 5);
    G.add_edge(B_, E_, 8);

    G.add_edge(C_, B_, -2);

    G.add_edge(D_, C_, 7);
    G.add_edge(D_, A_, 2);

    G.add_edge(E_, D_, 9);
    G.add_edge(E_, C_, -3);

    G.BF();
    return 0;
}