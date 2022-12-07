===Description===
This is the HW3 of the class Data Structure (Deadline - 2022/12/9)
This program is written in C++11.
Name of file : HW3_F74106270.zip
Structure :
|-HW3_F74106270.rar (.zip) 
| |-HW3_F74016270 (Folder)
| | |-main.cpp
| | |-main.exe
| | |-output.txt
| | |-sample.txt
| | |-Readme.txt

This program creates a Binary Search Tree and allows you to 
(1) Insert Nodes (2) Delete Nodes (3) Search Nodes (4) Print Tree (5) Exit Program

Functions / Class / Input Output File in the program : 
* TreeNode : Makes a treenode which have leftchild, rightchild, parent, and the value of the node.
* BST : Makes a Binary Search Tree that has a few functions.
        - Leftmost : Returns the leftmost child of the node sent in.
        - Successor : Returns the successor of the node sent in.
        - Search : Searches if there is the value in the BST.
        - Insert : Inserts the number into the BST.
        - Delete : Deletes if there is the value in the BST.
        - PrefixPrint : Prints the BST in preorder.
        - InfixPrint : Prints the BST in inorder.
        - PostPrint : Prints the BST in postorder.
        - LevelPrint : Prints the BST in levelorder.
* main : Asks user to input file name and reads it. Later printing the output into "output.txt".
         After entering the file name, the program asks the user to enter one of the five function and executes it until the user exits.