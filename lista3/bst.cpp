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

Node *leftSpine(Node *root, int *nLeft){
    if(root == nullptr) return root;

    if(root->right != nullptr){ 
        root = leftSpine(root->rotateLeft(), nLeft);
        (*nLeft)++;
    }
    else root->left = leftSpine(root->left, nLeft);

    return root;
}

Node *rightSpine(Node *root){
    if(root == nullptr) return root;

    if(root->left != nullptr) root = rightSpine(root->rotateRight());
    else root->right = rightSpine(root->right);


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

Node *checkLeft(int x, Node *root, int *nRight){
    //First we gonna to do right rotations until we get the first root right
    if (root->value == x)
        return root;
    else{
        (*nRight)++;
        return checkLeft(x, root->rotateRight(), nRight);
    }
}

Node *checkRight(int x, Node *root, int *nLeft){
    if (root->value == x)
        return root;
    else{
        (*nLeft)++;
        return checkRight(x, root->rotateLeft(), nLeft);
    }
}

void getPath(Node *root, int tam, int value, int paths[]){
    int i = 0;
    if(root->value == value) paths[0] = -1;
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
}

Node *E_to_T(int arr[], int min, int max, int *preIndex, Node *root, int vetTam, Node *firstRoot, bool isRight, int *nRight, int *nLeft){

	if (*preIndex >= vetTam || min > max || root == nullptr)
		return root;

    if(root->value != arr[min]) 
    {
        if(isRight == true) root = checkRight(arr[min], root, nLeft);
        else root = checkLeft(arr[min], root, nRight);

        if(min == 0 && arr[0] == root->value) firstRoot = root;
        // *preIndex = 0;
        return E_to_T(arr, min, max, preIndex, root, vetTam, firstRoot, isRight, nRight, nLeft);    
    }

	*preIndex = *preIndex + 1;

	if (min == max)
		return root;

	int i;
	for ( i = min; i <= max; ++i )
		if ( arr[ i ] > root->value )
			break;

	root->left = E_to_T(arr, *preIndex, i - 1, preIndex, root->left, vetTam, firstRoot, false, nRight, nLeft);
	root->right = E_to_T(arr, i, max, preIndex, root->right, vetTam, firstRoot, true, nRight, nLeft);

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

    int value[N];
    for (int i = 0; i < N; i++){
        std::cin >> value[i];
    }

    int pre = 0, nLeft = 0, nRight = 0;
    i = 0;
    rootS = leftSpine(rootS, &nLeft);
    rootS = E_to_T(value, 0, N-1, &pre, rootS, N-1, rootS, false, &nRight, &nLeft);
    rootS->print();
    std::cout << std::endl;

    return 0;
}