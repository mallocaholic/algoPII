#include <iostream> 
#define spc " "
class Node {
    public:
    Node *right, *left;
    int value;

    explicit Node(const int &x) : right(nullptr), left(nullptr){
        value = x;
    };

    Node *rotateLeft(){
        if(right == nullptr) return this;
        Node *R = right;
        Node *rL = R->left;
        right = rL;
        R->left = this;
        return R;
    }

    Node *rotateRight(){
        if(left == nullptr) return this;
        Node *L = left;
        Node *lR = L->right;
        left = lR;
        L->right = this;
        return L;
    }

    void print(){
        if(this->left != nullptr) left->print();
        if(this->right != nullptr) right->print();
        std::cout << this->value << spc;
    }

};

Node *leftSpine(Node *root){
    if(root == nullptr) return root;

    if(root->left == nullptr) return root;

    if(root->right != nullptr) root = leftSpine(root->rotateLeft());
    else if(root->left != nullptr) root->left = leftSpine(root->left);


    return root;
}

Node *rightSpine(Node *root){
    if(root == nullptr) return root;

    if(root->right == nullptr) return root;

    if(root->left != nullptr) root = rightSpine(root->rotateRight());
    else if(root->right != nullptr) root->right = rightSpine(root->right);


    return root;
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

Node *checkLeft(int x, Node *root){
    //First we gonna to do right rotations until we get the first root right
    if (root->value == x)
        return root;
    else
        return checkLeft(x, root->rotateRight());
}

Node *checkRight(int x, Node *root){
    if (root->value == x)
        return root;
    else
        return checkRight(x, root->rotateLeft());

    return root; //coloquei depois
}

int *getPath(Node *root, int tam, int value){
    int *paths = new int[tam];
    int i = 0;

    while(root->value != value)
        if(root->right != nullptr && value > root->value){
            root = root->right;
            paths[i++] = true;
            std::cout << "Foi para direita! ";
        } 
        else if(root->left != nullptr){
            root = root->left;
            paths[i++] = false;
            std::cout << "Foi para esquerda! ";
        }

    paths[i] = -1; 
    return paths;
}

Node *E_to_T(int arr[], int min, int max, int *preIndex, Node *root, int vetTam){

    if(root->value = arr[min]) return root;

	if (*preIndex >= vetTam || min > max)
		return nullptr;

    if(root == nullptr) return nullptr;

    int *paths = getPath(root, max, arr[min]);

	*preIndex = *preIndex + 1;

	if (min == max)
		return root;

	int i;
	for ( i = min; i <= max; ++i )
		if ( arr[ i ] > root->value )
			break;

	root->left = E_to_T(arr, *preIndex, i - 1, preIndex, root, vetTam);
	root->right = E_to_T(arr, i, max, preIndex, root, vetTam);

    return root;
}

int main()
{

    int N, i, j;
    Node *rootS = nullptr; 
    Node *rootT = nullptr;
    std::cin >> N;

    for (int i = 0; i < N; i++){
        int x;
        std::cin >> x;
        rootS = insert(rootS, x);
    }
    /*
    */
    int value[N];
    for (int i = 0; i < N; i++){
        std::cin >> value[i];
    }
    // rootT = createPreOrder(value, 0, N-1);*/

    int pre = 0;
    // Node *result = rootS->search(4);
    //rootS = leftSpine(rootS);
    rootS = E_to_T(value, 0, N-1, &pre, rootS, N-1);
    rootS->print();
    std::cout << std::endl;

    //int value[N];
    //for( i = 0; i < N-1; i++)
    //    std::cin >> value[i];
    //rootT = createPreOrder(value, 0, N);    

    return 0;
}