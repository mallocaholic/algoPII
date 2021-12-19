#include <iostream>

using namespace std;

int **ssbt(int **A, int **X, int V, int M, int i, int P, int n, int *q, int qbool, int lastvalue){
    
    int **R = nullptr; 
 
    if(qbool >= M && V >= P && lastvalue != P){
        (*q)++;
        lastvalue = P;
    }

    //if( V == P) return (X);

    if( i == n || V < P || qbool + n - i < M) return nullptr;

    else {
        int s = P + (*A)[i];

        if(s <= V){
            (*X)[i] = 1;
            R = ssbt(A, X, V, M, i + 1, s, n, q, qbool+1, lastvalue);
            if(R != nullptr) return R;
        }

        (*X)[i] = 0;
        R = ssbt(A, X, V, M, i + 1, P, n, q, qbool, lastvalue);
        if(R != nullptr) return R;
    }

    return nullptr;
}

int main(){
    int N;
    cin >> N;
    
    for(int i = 0; i < N; i++){
    
        int n, maxval, m, q = 0, qbool = 0;
        int *A, *X;
        cin >> n;

        A = new int[n];
        X = new int[n];

        for(int i = 0; i < n; i++){
            cin >> A[i];
            X[i] = 0;
        }

        cin >> maxval >> m;
    
        ssbt(&A, &X, m, maxval, 0, 0, n, &q, 0, -1);


        cout << "caso " << i << ": " << q << endl;
        
    }
}