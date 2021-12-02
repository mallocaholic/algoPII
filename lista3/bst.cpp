#include <iostream>
#include <string> 
#define spc " "
#define jump std::cout << std::endl
class Node {
    public:
    Node *right, *left;
    int value, h, bf;

    explicit Node(const int &x) : right(nullptr), left(nullptr), h(0){
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

    void print(bool *isAVL, int x){
        if(left != nullptr)
            left->print(isAVL, x);
        if(right != nullptr) 
            right->print(isAVL, x);
        // checar balanceamento
        if(abs(bf) > 1) *isAVL = false;

        if(value != x) std::cout << value << spc;
        else std::cout << value;
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

int max(int x, int y){
    if(x >= y) return x;
    else return y;
}

int getH(Node *root){
    if(root == nullptr) return 0;
 
    root->h = 1 + max(getH(root->right), getH(root->left));

    if(root->h == 1) root->bf = 0;
    else if(root->right != nullptr || root->left != nullptr){
        if(root->right == nullptr) root->bf = -(root->left->h);
        else if(root->left == nullptr) root->bf = root->right->h; 
        else root->bf = root->right->h - root->left->h;
    }

    return root->h;
}

Node *E_to_T(int arr[], int min, int max, int *index, Node *root, int vetTam, Node *firstRoot, bool isRight, int *nRight, int *nLeft){

	if (*index >= vetTam || min > max || root == nullptr)
		return root;

    if(root->value != arr[min]) 
    {
        if(isRight == true) root = checkRight(arr[min], root, nLeft);
        else root = checkLeft(arr[min], root, nRight);

        if(min == 0 && arr[0] == root->value) firstRoot = root;
        // *index = 0;
        return E_to_T(arr, min, max, index, root, vetTam, firstRoot, isRight, nRight, nLeft);    
    }

	*index = *index + 1;

	if (min == max)
		return root;

	int i;
	for ( i = min; i <= max; ++i )
		if ( arr[ i ] > root->value )
			break;

	root->left = E_to_T(arr, *index, i - 1, index, root->left, vetTam, firstRoot, false, nRight, nLeft);
	root->right = E_to_T(arr, i, max, index, root->right, vetTam, firstRoot, true, nRight, nLeft);

    return root;
}

int main()
{
    std::string l;
    int N;

    while ( std::cin >> N ){

        int i, j;
        Node *rootS = nullptr; 
        Node *rootT = nullptr;

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
        bool isAVL = true;
        i = 0;

        rootS = leftSpine(rootS, &nLeft);
        rootS = E_to_T(value, 0, N - 1, &pre, rootS, N - 1, rootS, false, &nRight, &nLeft);
        rootS->h = getH(rootS);

        std::cout << nLeft << spc << nRight << std::endl;
        rootS->print(&isAVL, value[0]);
        jump;
        if (isAVL == true)
            std::cout << "true" << std::endl;
        else
            std::cout << "false" << std::endl;
        jump;

    }

    return 0;
}