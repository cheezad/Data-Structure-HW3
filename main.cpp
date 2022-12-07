#include <iostream>
#include <string>
#include <queue>
#include <fstream>
using namespace std;
ifstream my_file;
ofstream output;

class BST; // declare BST
class TreeNode{ // make a treenode
    private:
        TreeNode *leftchild;
        TreeNode *rightchild;
        TreeNode *parent;
        int value;
    public:
        TreeNode(): leftchild(0), rightchild(0), parent(0), value(0){}; // init a treenode with current value is 0
        TreeNode(int a): leftchild(0), rightchild(0), value(a){}; // init a treenode with a as the current value
        friend class BST; // make it avaliable to access the private class from BST
};

class BST{ // make a binary search tree
    public:
        TreeNode *root; // the root of the tree
        TreeNode* Leftmost(TreeNode *current);
        TreeNode* Successor(TreeNode *current);
        BST():root(0){}; // init a BST with root = 0
        TreeNode* Search(int key); // search function for the tree
        void Insert(int value); // insert value into BST
        void Delete(int value); // delete value from BST
        // print functions
        void PrefixPrint(TreeNode *current); 
        void InfixPrint(TreeNode *current);
        void PostPrint(TreeNode *current);
        void LevelPrint();
        // end of print functions
};

TreeNode* BST::Search(int svalue){ // search function (Done)
    TreeNode* current = root; // searches from the root
    // if current is smaller than target value, go to left, else go to right
    while(current != NULL && svalue != current->value){ 
        if(svalue < current->value){
            current = current->leftchild;
        }else{
            current = current->rightchild;
        }
    }
    return current;
}

TreeNode* BST::Leftmost(TreeNode *current){ // find the leftmost child of current node
    
    while (current->leftchild != NULL){
        current = current->leftchild;
    }
    return current;
}

TreeNode* BST::Successor(TreeNode *current){ // find the successor of current node 
    
    if (current->rightchild != NULL){
        return Leftmost(current->rightchild);
    }
    
    TreeNode *new_node = current->parent; 
    
    while (new_node != NULL && current == new_node->rightchild) {
        current = new_node;
        new_node = new_node->parent;
    }
    
    return new_node;
}

void BST::Insert(int value){ // inserts node into BST（Done)
    if(Search(value) != NULL){
        output << "Error! Number " << value << " exists." << endl;
        cout << "Error! Number " << value << " exists." << endl;
        return;
    }
    TreeNode* fast = 0;
    TreeNode* slow = 0;
    TreeNode* insertNode = new TreeNode(value);
    // let fast be at root and slow be at null
    fast = root;
    while(fast != NULL){
        slow = fast;
        if(insertNode->value < fast->value){
            fast = fast->leftchild;
        }else{
            fast = fast->rightchild;
        }
    }
    insertNode->parent = slow;
    if(slow == NULL){
        this->root = insertNode;
    }else if(insertNode->value < slow->value){
        slow->leftchild = insertNode;
    }else{
        slow->rightchild = insertNode;
    }
    output << "Number " << value << " is inserted." << endl;
    cout << "Number " << value << " is inserted." << endl;
}

void BST::Delete(int value){ // Delete a node in BST (Done)
    TreeNode *DelNode = Search(value);
    if(DelNode == NULL){
        output << "Number " << value << " is not exist." << endl;
        return;
    }
    TreeNode *Del = 0; // the position of the node that will be deleted
    TreeNode *DelChild = 0; // the child of the deleted node 

    if(DelNode -> leftchild == NULL || DelNode -> rightchild == NULL){
        Del = DelNode; // if the node deleted doesn't have left or right child, it deletes the position
    }else{
        Del = Successor(DelNode); // else it deletes the successor's memory
    }

    if(Del -> leftchild != NULL){ // change the pointer of the Deleted child's parent 
        DelChild = Del -> leftchild; 
    }else{
        DelChild = Del -> rightchild;
    }

    if(DelChild != NULL){
        DelChild -> parent = Del -> parent;
    }
    
    if(Del -> parent == NULL){ // change the pointer of the Deleted pointer to its child 
        this->root = DelChild;
    }else if(Del == Del -> parent -> leftchild){
        Del -> parent -> leftchild = DelChild;
    }else{
        Del -> parent -> rightchild = DelChild; 
    }

    if ( Del != DelNode){
        DelNode -> value = Del -> value;
    }
    delete Del;
    Del = 0;
    output << "Number " << value << " is deleted." << endl;
    cout << "Number " << value << " is deleted." << endl;
}

void BST::PrefixPrint(TreeNode *current){ // preorder print
    if(current){
        output <<  " " << current -> value;
        cout <<  " " << current -> value;
        PrefixPrint(current -> leftchild);
        PrefixPrint(current -> rightchild);
    }
}

void BST::InfixPrint(TreeNode *current){ // inorder print
    if(current){
        InfixPrint(current -> leftchild);
        output << " " << current -> value;
        cout << " " << current -> value;
        InfixPrint(current -> rightchild);
    }
}

void BST::PostPrint(TreeNode *current){ // postorder print 
    if(current){
        PostPrint(current -> leftchild);
        PostPrint(current -> rightchild);
        output << " " << current -> value;
        cout << " " << current -> value;
    }
}

void BST::LevelPrint(){ // levelorder print
    queue<TreeNode*> level;
    level.push(this -> root);
    while (!level.empty()){
        TreeNode *current = level.front();
        level.pop();
        output << current -> value << " ";
        cout << current -> value << " ";
        if(current -> leftchild != NULL) level.push(current -> leftchild);
        if(current -> rightchild != NULL)level.push(current -> rightchild);
    }
}

int main() {
    string filename;
    cout << "Input file name: ";
    cin >> filename;
	my_file.open(filename.c_str());
    output.open("output.txt");
	if (!my_file.is_open() || !output.is_open()) {
        return 1;
	}
    output << "File name: " << filename << endl;
    BST bst;
    string option = "";
    while(option != "-1"){
        output << "(I)nsert a number.\n(D)elete a number.\n(S)earch a number.\n(P)rint 4 kinds of orders.\n(E)xit\n";
        cout << "(I)nsert a number.\n(D)elete a number.\n(S)earch a number.\n(P)rint 4 kinds of orders.\n(E)xit\n";
        my_file >> option;
        // insert 
        if(option == "i" || option == "I"){
            int number = 0;
            output << "Insert: " << endl;
            cout << "Insert: " << endl;
            do{
                my_file >> number;
                if(number != -1) bst.Insert(number);
            }while(number != -1);
            output << endl;
            cout << endl;
        }
        // delete
        if(option == "d" || option == "D"){
            int number;
            output << "Delete: " << endl;
            cout << "Delete: " << endl;
            my_file >> number;
            while(number != -1){
                bst.Delete(number);
                my_file >> number;
            }
            output << endl;
        }
        // search
        if(option == "s" || option == "S"){
            int number;
            output << "Search: " << endl;
            cout << "Search: " << endl;
            my_file >> number;
            while (number != -1){
                if(bst.Search(number) != NULL){
                    output << "Bingo! " << number << " is found." << endl;
                    cout << "Bingo! " << number << " is found." << endl;
                }else{
                    output << "Sorry! " << number << " is not found." << endl;
                    cout << "Sorry! " << number << " is not found." << endl;
                }
                my_file >> number;
            }
            output << endl;
            cout << endl;
        }
        // print
        if(option == "p" || option == "P"){
            output << "Print: " << endl;
            cout << "Print: " << endl;
            output << "The tree in prefix order:";
            cout << "The tree in prefix order:";
            bst.PrefixPrint(bst.root);
            output << endl;
            cout << endl;
            output << "The tree in infix:";
            cout << "The tree in infix:";
            bst.InfixPrint(bst.root);
            output << endl;
            cout << endl;
            output << "The tree in post order:";
            cout << "The tree in post order:";
            bst.PostPrint(bst.root);
            output << endl;
            cout << endl;
            output << "The tree in level order:";
            cout << "The tree in level order:";
            bst.LevelPrint();
            cout << endl;
            cout << endl;
            output << endl;
            output << endl;
        }
        // exit
        if(option == "e" || option == "E"){
            output << "Exit" << endl;
            cout << "Exit" << endl;
            break;
        }
    }
    cout << "Exited" << endl;
    output << "Exited" << endl;
    return 0;
}