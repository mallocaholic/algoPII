#include <bits/stdc++.h>

using namespace std;

class point{
    public:
    int coordx, coordy;
    bool coin;
    
    point(){
       cin >> coordx >> coordy; 
       coin = false;
    };

};

class graph{
    public:
    point *points;
    list<pair<int, int>> *adj;
    int V, inf;

    graph(int V){
        points = new point[V];
        adj = new list<pair<int, int>>[V];
        this->V = V;
        inf = numeric_limits<int>::max() - 12345678;
    }

    void add_edge(int src, int dest){
        int x_diff = (points[src].coordx-points[dest].coordx);
        int y_diff = (points[src].coordy-points[dest].coordy);
        int energy = x_diff*x_diff + y_diff*y_diff;
        if(points[dest].coin == true) 
            energy *= -1;
        pair<int, int> temp(dest, energy);
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
        
        

    }
    
};

int main(){
    int N, N_p, N_c; 
    cin >> N;

    for(int i = 0; i < N; i++){
        
        cin >> N_p;
        graph G(N_p); // Cria o grafo

        cin >> N_c; 
        for(int a = 0; a < N_c; a++){ // Parte das moedas
            int index;
            cin >> index;
            G.points[index].coin = true;
        }
        
        for(int p = 0; p < N_p; p++){
            cin >> N_c;
            for(int a = 0; a < N_c; a++){
                int dest;
                cin >> dest;
                G.add_edge(p, dest);
            }
        }

        G.BF();
        // G.print_adj(); Everything is fine here
    }

    return 0;
}