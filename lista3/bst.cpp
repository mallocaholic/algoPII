#include <iostream> 

class Node {
    public:
    Node *right, *left;
    int h, bf, value;

    explicit Node(const int &x) : right(nullptr), left(nullptr), h(0), bf(0){
        value = x;
    };

    Node *rotateLeft(){

        Node *rR = right;
        Node *rL = rR->left;
        right = rL;
        rR->left = this;
        return rR;
    }
};

// Node *E_to_T(Node *root){ 
    // if(root->left != nullptr) 
    // if(root->left->right != nullptr){ 
        // root->left = E_to_T(root->left->rotateLeft()); 
    // } 
    // else if (root->left != nullptr) 
        // root = E_to_T(root->left); 
    // return root;
// }

bool shouldRotate(Node *root){
    if(root->right != nullptr) return true;
    else return false;
}

Node *E_to_T(Node *root, Node *saveFirstRoot, bool isSaved){

    if(isSaved == false) saveFirstRoot = root;
    std::cout << "OK!";
    if(root->right != nullptr){

        root = root->rotateLeft();
        E_to_T(root, saveFirstRoot, isSaved);

    } else if (root->left != nullptr){

        if( root->left->right != nullptr )
            root->left = root->left->rotateLeft();
        E_to_T(root->left, saveFirstRoot, true);

    }
    
    else return saveFirstRoot;
}

Node *insert(Node *root, int x){

    if(root == nullptr){
        Node *newNode = new Node(x);
        return newNode;
    }
    else if(x > root->value) 
        root->right = insert(root->right, x); 
    else if(x < root->value) 
        root->left = insert(root->left, x);
    else return root;

    return root;
}

Node *createPreOrder(int arr[], int i, int j){

    if(i > j) return nullptr;
    
    Node *newNode = new Node(arr[i]);

    int p = i+1;
    while( p <= j && arr[p] <= newNode->value)
        p++;

    newNode->left = createPreOrder(arr, i + 1, i - 1);
    newNode->right = createPreOrder(arr, i, j);

    return newNode;
}

int main()
{

    int N, i, j;
    Node *rootS = nullptr; 
    Node *rootT = nullptr;
    std::cin >> N;

    /*for (int i = 0; i < N; i++){
        int x;
        std::cin >> x;
        rootS = insert(rootS, x);
    }*/

    int value[N];
    for (int i = 0; i < N; i++){
        std::cin >> value[i];
    }
    rootT = createPreOrder(value, 0, N-1);



    printf("Done bro");
    //rootS = E_to_T(rootS, rootS, false);
    // int value[N];
    // for( i = 0; i < N-1; i++)
    //     std::cin >> value[i];
    // rootT = createPreOrder(value, 0, N);    

    return 0;
}