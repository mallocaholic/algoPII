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

        void cycle(){
            int i = 0;
            Item *tail = this->next; 
            Item *temp = this->next;

            while( tail->next != NULL){
                tail = tail->next;
                i++;
            }

            if( i > 1 ){
                this->next = temp->next;
                tail->next = temp;
                temp->next = NULL;
            }
        };
        
        void toProcessor(Item *headProc){
            
            Item *newItem;
            Item *temp = this->next;
            Item *tail = headProc->next;
            
            newItem = new Item;
            newItem->T = this->next->T;
            newItem->X = this->next->X;
            newItem->next = NULL;
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
            newItem = new Item; // * Criando o novo item
            newItem->X = idenItem;
            newItem->T = procTimeItem;
            newItem->next = NULL;

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

    void push(Item **headProc, Item **pScheduler){

    }
};

int main(){
    int procTime = 0, 
        idenItem = 0, 
        procTimeItem = 0,
        flagQueue = 0;

    string action = "";

    Item *headProc = NULL,
         *headQueue = NULL,
         *tail;

    Pilha pilha; 
    pilha.size = 0;
    pilha.topo = NULL;

    headProc = new Item;
    headProc->next = NULL;
    headQueue = new Item;
    headQueue->next = NULL;

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
            // * 1. Verifica se tem item processado em tail
            // * 2. Verifica se tem item na QUEUE e coloca em tail
            if(headQueue->next != NULL) headQueue->toProcessor(headProc);
            if(headProc->next != NULL){
                // * Trabalha no item
                if(headProc->next->T - procTime > 0) headProc->next->T-=procTime;
                else headProc->next->T = 0;
                // *
                cout << 
            } else if (flagQueue == 1) cout << "PROC -1 -1" << endl;
            
            headProc->cycle(); //RODA
        }
        cin >> action;
    }    
    
    delete headProc;
    delete headQueue;
    return 0;
}
