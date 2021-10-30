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
        int size;

        Item(int X, int T){
            this->X = X;
            this->T = T;
            this->next = NULL;
            this->size = 0;
        }

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
        
        void toProc(Item *headProc){
            
            Item *newItem = new Item(this->next->X, this->next->T);
            Item *temp = this->next;
            Item *tail = headProc->next;
            
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
            Item *newItem = new Item(idenItem, procTimeItem); // * Criando o novo item

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
    Pilha(){
        this->size = 0;
        this->topo = NULL;
    }

    void push(Item *tail, Item *headProc){
        Item *p = headProc;
        int i = 0;    
        (this->size)++;
        
        while(p->next != tail){ 
            p = p->next;
            i++;
        }
        
        if(i>=0){
            tail->next = this->topo;
            this->topo = tail;
            p->next = NULL;
        }
    }

    void pop(){
        int X = this->topo->X;
        Item *temp = this->topo;
        
        if( this->size > 1 ) {
            this->topo = this->topo->next;
            //delete temp;
        }
        else {
            this->topo = NULL;
            //delete temp;
        }
        cout << "UNLD " << X << endl;
        (this->size)--;
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
         *tail = NULL;

    Pilha *pilha = new Pilha();

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
            pilha->pop();
        // ! PROC
        }else if( !action.compare(processing) ){
            tail = headProc->next; 
            
            if(headProc->next != NULL){
                if(tail->next != NULL ) while(tail->next != NULL) tail = tail->next;
            // * 1. Verifica se tem item processado em tail
                if(tail->T == 0) pilha->push(tail, headProc);
            }
            // * 2. Verifica se tem item na QUEUE e coloca em tail
            if(headQueue->next != NULL) headQueue->toProc(headProc);
            flagQueue = 1;
            if(headProc->next != NULL){
                
                // * Trabalha no item
                if(headProc->next->T - procTime > 0) headProc->next->T-=procTime;
                else headProc->next->T = 0;
                
                if(headProc->next->X == 102 && headProc->next->T == 0)
                int x = 0;// DEBUGANDO 
                // *
                cout << "PROC " << headProc->next->X << " " << headProc->next->T << endl;
                headProc->cycle(); //RODA
            
            } else if (flagQueue == 1) cout << "PROC -1 -1" << endl;
            
        }
        cin >> action;
    }    
    
    delete headProc;
    delete headQueue;
    return 0;
}