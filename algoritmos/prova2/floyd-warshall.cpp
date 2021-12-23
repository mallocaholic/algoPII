// C++ Program for Floyd Warshall Algorithm
#include <bits/stdc++.h>
using namespace std;
  
#define V 6
#define graph g
  
#define INF 99999

void printSolution(int dist[][V]);
 
void floydWarshall(int graph[][V])
{
    int dist[V][V], i, j, k;
  
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
  
    for (k = 0; k < V; k++) {
        cout << "------ITERACAO--------" << k << endl;
        printSolution(dist);
        cout << endl;
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != INF && dist[i][k] != INF)) 
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    printSolution(dist);
}
  
void printSolution(int dist[][V])
{
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF"
                     << "     ";
            else
                cout << dist[i][j] << "     ";
        }
        cout << endl;
    }
}
  
// Driver code
int main()
{
    int graph[V][V];
    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++){
            graph[i][j] = INF;
            if(i == j) graph[i][j] = 0;
        }

    //Inicializa aqui
    
    ///g[ De ][ Para ] = peso
    g[0][1] = 30;
    g[0][5] = 60;

    g[1][2] = 60;
    g[1][0] = 30;
    g[1][4] = 60;

    g[2][4] = 80;
    g[2][1] = 60;
    g[2][3] = 90;
    g[2][5] = 10;

    g[3][4] = 30;
    g[3][2] = 90;

    g[4][3] = 30;
    g[4][2] = 80;
    g[4][1] = 60;
    g[4][5] = 70;

    g[5][4] = 70;
    g[5][0] = 60;
    g[5][2] = 10;
   
    floydWarshall(graph);
    return 0;
}
