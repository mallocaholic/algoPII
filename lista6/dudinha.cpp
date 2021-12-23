#include <iostream>

using namespace std;

int** ssback(int** A, int**X, int i, int P, int n, int qtd_min, int ultimo_valor, int premio, int* count, int t){
    int** R = NULL;

    if(premio >= P && t >= qtd_min && ultimo_valor!=P){
        *count = *count + 1;
        ultimo_valor = P;
    }

   if(i==n || premio < P || t + n-i < qtd_min) 
        return NULL;

    else {
        for(int b=1; b>=0; b--){
            if(P + (*A)[i] > premio)
                b = 0;
            (*X)[i] = b;
            R = ssback(A, X, i+1, P + b*(*A)[i], n, qtd_min, ultimo_valor, premio, count, t+b);

            if(R != NULL)
                return R;
        }
    }
    return NULL;
}

int main(){
    int testes;
    cin >> testes;
    int aux = 0;

    while(testes){
        int num_itens, qtd_min, premio, count=0;
        cin >> num_itens;
        int* A;
        int* X;

        A = new int[num_itens];
        X = new int[num_itens];

        for(int i=0; i < num_itens; i++){
            X[i] = 0;
            cin >> A[i];
        }

        cin >> qtd_min >> premio;

        ssback(&A, &X, 0, 0, num_itens, qtd_min, 0, premio, &count, 0);
        
        if(qtd_min == 0) 
            count++;
        
        cout << "caso " << aux << ": " << count << endl;
        
        testes--;
        aux++;
    }

    return 0;   
}