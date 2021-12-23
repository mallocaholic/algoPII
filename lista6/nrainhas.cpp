#include <bits/stdc++.h>
#define N 3
using namespace std;

vector<vector<int>> ssbt(vector<vector<int>> matriz, int i, int R){

    
    vector<vector<int>> X; 
    
    if(R == N) return matriz; //Sucesso

    if( i == N ) return nullptr;

    for(int j = 0; j < N; j++){
        if(m[i][j] == 0){ 
            X = ssbt(matriz, i, N, R+1);
        }
    }

    return nullptr;
}

int main(){
    vector<vector<int>> matriz(N, vector<int>(N));

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            matriz[i][j] = 0; 

    ssbt(matriz, 0, N, 0);
}