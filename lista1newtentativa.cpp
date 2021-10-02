#include <iostream>
#include <string>
#define load "LOAD"
#define unload "UNLD"
#define processing "PROC"
#define end "END"

using namespace std;

class Item{
  public:
        int X; //Identificador (0,1,2 etc)
        int T; //Tempo de processamento
        Item *next;
        
        Item(int T, int X){
            this->X = X;
            this->T = T;
            this->next = NULL;
        };

        void cycle(){
            int i = 0;
            Item *tail = this->next; 
            Item *temp = this->next;

            while( tail->next != NULL){
                tail = tail->next;
                i++;
            }
            if( i > 0 ){
                this->next = temp->next;
                tail->next = temp;
                temp->next = NULL;
            }
        };
        
        void toProcessor(Item *headProc){
            
            //Item *newItem;
            Item *temp = this->next;
            Item *tail = headProc->next;
            
            Item *newItem = new Item(this->next->T, this->next->X);
            // newItem->T = this->next->T;
            // newItem->X = this->next->X;
            // newItem->next = NULL;
            //Colocando a queue pra frente
            if(temp->next != NULL)
            this->next = this->next->next;
            else this->next = NULL;
            delete temp;
            
            // Adicionando o novo item ao processador
            if(tail == NULL) headProc->next = newItem;
            else
            { 
                while(tail->next != NULL)
                    tail = tail->next;
                tail->next = newItem;
            }
        };

        void toQueue(int idenItem, int procTimeItem){
            Item *newItem;
            newItem = new Item(idenItem, procTimeItem); // * Criando o novo item
            // newItem->X = idenItem;
            // newItem->T = procTimeItem;
            // newItem->next = NULL;

            if(this->next == NULL) this->next = newItem; // * Se a lista está vazia, retorna o novo elemento.
            else {
                Item *pointer = this; // * Salvando pQueue

                while( pointer->next != NULL) // * Achar o ultimo elemento
                    pointer = pointer->next;

                pointer->next = newItem; // * Adicionando o novo item a lista
            }
        };
    
};

class Pilha{
    public:
    int size;
    Item *topo;

    void push(Item *tail){
        
        //Item *newItem;
        //newItem = new Item(tail->X, tail->T, NULL);
        // newItem->X = tail->X;
        // newItem->T = tail->T; 
        //while(){

        //}
    }
};

int main(){
    int procTime = 0, 
        idenItem = 0, 
        procTimeItem = 0,
        flagQueue = 0;

    string action = "";

    Item *headProc = new Item(0, 0),
         *headQueue = new Item(0, 0),
         *tail = headProc->next;

    Pilha pilha; 
    pilha.size = 0;
    pilha.topo = NULL;

    //headProc = new Item(0, 0);
    // headProc->next = NULL;
    //headQueue = new Item(0, 0);
    // headQueue->next = NULL;

    //Recebendo input
    cin >> procTime;
    cin >> action;
    
    while( action.compare(end) ){
        // ! LOAD
        if( !action.compare(load) ){
            cin >> idenItem >> procTimeItem;
            headQueue->toQueue(idenItem, procTimeItem);
        // ! UNLD
        }else if( !action.compare(unload) ){

        // ! PROC
        }else if( !action.compare(processing) ){
            tail = headProc->next;
            if(headProc->next != NULL){ 
                if(tail->next != NULL ) while(tail->next != NULL) tail = tail->next;
            // * 1. Verifica se tem item processado em tail
                if(tail->T = 0) pilha.push(tail);
            }
            // * 2. Verifica se tem item na QUEUE e coloca em tail
            if(headQueue->next != NULL) headQueue->toProcessor(headProc);
            if(headProc->next != NULL){
                // * Trabalha no item
                if(headProc->next->T - procTime > 0) headProc->next->T-=procTime;
                else headProc->next->T = 0;
                // *
                cout << "PROC " << headProc->next->X << " " << headProc->next->T << endl;
            } else if (flagQueue == 1) cout << "PROC -1 -1" << endl;
            
            headProc->cycle(); //RODA
        }
        cin >> action;
    }    
    
    delete headProc;
    delete headQueue;
    return 0;
}
