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

        Item *toProcessor(Item *pProc, Item *pScheduler, Item *headQueue){ // ? Retorna o headQueue sem o item que foi para o processador
            
            Item *aux = this->next;

            Item *newItem;
            newItem = new Item; // * Criando o novo item
            newItem->X = headQueue->next->X;
            newItem->T = headQueue->next->T;
            newItem->next = NULL;

            if(aux != NULL){
                if(aux != pScheduler && pScheduler->next != NULL){ // ! CASO O ITEM ESTEJA NO MEIO DA LISTA DO PROC
                    while(aux->next != pScheduler)
                        aux = aux->next;
                    newItem->next = aux->next;
                    aux->next = pScheduler;
                    pScheduler = newItem;
                } 
                else if (aux == pScheduler && pScheduler->next != NULL){ // ! CASO O ITEM ESTEJA NO COMEÇO DO PROC
                    while(aux->next != NULL)
                        aux = aux->next;
                    aux->next = newItem;
                }
                else {
                    newItem->next = aux;
                    this->next = newItem;
                }
            } else this->next = newItem; // ! CASO NAO TENHA ITEM NA LISTA DO PROC

            if(headQueue->next->next != NULL) headQueue->next = headQueue->next->next; // * Limpando o item da QUEUE
            else headQueue->next = NULL;
            
            return headQueue->next;
        };

};

int main(){
    int procTime = 0, 
        idenItem = 0, 
        procTimeItem = 0,
        flagQueue = 0;

    string action = "";

    Item *headProc = NULL,
         *pProc = NULL,
         *headQueue = NULL,
         *pScheduler= NULL;

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
            // * 1. Verifica se tem item processado em pSchedule e manda pra pilha.
            
            // * 2. Verifica se tem item na QUEUE e coloca na lista  PROC
            if(headQueue->next != NULL) headQueue->next = headProc->toProcessor(pProc, pScheduler, headQueue);
            flagQueue = 1;
        
            if(headProc->next != NULL){
                if(pProc == NULL) pProc = headProc->next;
                
                // * Trabalha no item
                if(pProc->T != 0) pProc->T-=procTime;
                if(pProc->T < 0 ) pProc->T = 0;
                cout << processing << " " << pProc->X << " " << pProc->T << endl;
                
                // * Passa o ponteiro do processador
                Item *temp = headProc->next;
                while(temp != pProc)
                    temp = temp->next;
                pScheduler = temp;    

                if(pProc->next != NULL) pProc = pProc->next;
                else pProc = headProc->next;
            
            } else if (flagQueue == 1) cout << "PROC -1 -1" << endl;
        }
        cin >> action;
    }    
    
    delete headProc;
    delete headQueue;
    return 0;
}
