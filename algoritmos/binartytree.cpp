#include <iostream>

class Tree{
    
    public:

    class Node{
        public:
        int data, bf;
        Node *left, *right;
        bool hc; // has changed the height

        explicit Node(int x) : data(x) {
            left = nullptr;
            right = nullptr;
            bf = 0; 
        }
    
        ~Node(){
            std::cout << "BOOOM, bye Node!" << std::endl;
        }
        
        // And here the rotation part
        Node *rotateLeft(Node *ptr){
            
            Node *rRight = right; 
            Node *rRightLeftChild = rRight->left;
            rRight->left = this;
            right = rRightLeftChild;
            
            if(rRight->bf <= 0) bf = bf -1;
                       else bf = bf - 1 - rRight->bf; 

            if(bf >= 0) rRight->bf = rRight->bf -1;
                   else rRight->bf = rRight->bf + bf;

            return this;
        }

        // Node *rotateRight(){
            
        //     Node *rRight = left; 
        //     Node *rRightLeftChild = rRight->left;
        //     rRight->left = this;
        //     right = rRightLeftChild;
            
        //     if(rRight->bf <= 0) bf = bf -1;
        //                else bf = bf - 1 - rRight->bf; 

        //     if(bf >= 0) rRight->bf = rRight->bf -1;
        //            else rRight->bf = rRight->bf + bf;

        //     return this;
        // }

        Node *insertNode(Node *r, Node *newNode){

            if (r == nullptr){
                r = newNode;
                hc = true;
                return r;
            }
            else if (newNode->data == r->data){
                hc = false;
                return r;
            }
            else if (newNode->data < r->data){
                left = left->insertNode(left, newNode); 
                bf -= left->hc;
            }
            else{
                right = right->insertNode(right, newNode);
                bf += right->hc;
            }

            if(hc == 0){
                return r;
            }
            else if(bf = 0){
                hc = false;
                return r;
            }
            else if(bf == 1 || bf == -1){
                hc = true;
                return r;
            }
            //Agora aqui as rotações
            else if(bf == -2){
                if( left->bf == 1) left = left->rotateLeft();
            }
            return(right->rotateRight());
        }

    };
    Node *root;
    bool hc;
    
    public:
    Tree() : root(nullptr), hc(0) {}

    
     
};

int main(){


    return 0;
}