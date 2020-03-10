//file binarytree.cpp
//authors: Tommy Engels and Maximillian Marciel
//date: 10/14/18

//Data object: a binary tree which is either empty or
//                  in the form of     r
//                                  /    \
//                                TL     TR
//                  where TL and TR are binary trees.
//data structure: a linked binary tree
//Operations:
//       create, destroy, copy, operator=,
//       traversals (preorder, inorder, postorder)
//       Completion of trees (Height 4 complete, 
//       height 3 full)

#include "binarytree.h"
#include <iostream>
using namespace std;

// ***************** recursive helpers *****************
//Copies one binary tree to another
//pre oldtreep points to the root of a binary tree
//post: newtreep points to the root of a binary tree
//  that has copies of the nodes of oldtreep's tree
//usage: copyTree (newptr, oldptr);
void copyTree (TreeNode*& newtreep, TreeNode* oldtreep) throw (Exception)
{
   if (oldtreep == nullptr)
   {
	   newtreep = nullptr;
   }
   else
   {
	   newtreep = new (nothrow) TreeNode;
       if (newtreep == nullptr)
		   throw Exception("In copytree: No memory grabbed from heap.");
	   newtreep -> item = oldtreep -> item;
	   newtreep -> balance = oldtreep -> balance;
	   copyTree(newtreep -> leftChild, oldtreep -> leftChild);
	   copyTree(newtreep -> rightChild, oldtreep -> rightChild);
   }
}

//Releases memory for a binary tree
//pre: treep points to the root of a binary tree
//post: releases all of the nodes in the tree pointed to by treep
//    and leaves treep empty.
//usage: destroyTree (mroot);
void destroyTree (TreeNode*& treep)
{
	if (treep != nullptr)
	{
		destroyTree(treep -> leftChild);
		destroyTree(treep -> rightChild);
		delete treep;
		treep = nullptr;
	}
}


//Prints a certain amount of tabs according to input
//Pre: integer tabs is given and exists.
//Post: number of tabs specified is printed to screen
//Usage: printTabs(tabNumber);
void printTabs(int tabs)
{
	for (int i = 0; i < tabs; i++)
	{
		cout << "	";
	}
}

// recursive helper. Prints the display
// to be user friendly and readable, horizontally.
// Pre: treep and level are given and exists, treep is the
// top/root of the tree or subtree you wish to print.
// Post: Tree/Subtree beginning with treep as the root is printed.
// Usage: writePretty(treep, level);
void writePretty (TreeNode* treep, int level, ostream& output)
{	
	if (treep != nullptr)
	{
		writePretty(treep -> rightChild, level += 1, output);
		if (treep -> rightChild != nullptr)
		{
			for (int j = 0;j <= level;j++)
				output << '\t';
			output << "/" << endl;
		}
		if (level == 1)
			output << "root ->" ;
		else	
		{			
			for (int i = 0; i < level; i++)
				output << '\t' ;
		}
		Key text = treep -> item;
		output << "  " << text << ": " << treep -> balance << endl;
		 if (treep -> leftChild != nullptr)
        {
            for (int i = 0; i <= level; i++)
                output << '\t';
            output << "\\" << endl;
			writePretty(treep -> leftChild, level, output);
		}
	}		
}

// ********** recursive helpers for the traversals ****************
//pre: treep points to the root of a binary tree to be traversed
//post: prints the item objects in the nodes on the screen in the 
//     specified order. the items are separated by commas
//usage: preorder (mroot);   
//       similarly for the others
void preorder (TreeNode* treep)
{
	if (treep != nullptr)
	{
		cout << treep -> item << endl;
		preorder(treep -> leftChild);
		preorder(treep -> rightChild);
	}
}

void inorder (TreeNode* treep)
{
    if (treep != nullptr)
	{
		inorder(treep -> leftChild);
		cout << treep -> item << endl;
		inorder(treep -> rightChild);
	}
}

void postorder (TreeNode* treep)
{
	if (treep != nullptr)
	{
		postorder(treep -> leftChild);
		postorder(treep -> rightChild);
		cout << treep -> item << endl;
	}
}

// **************************public methods************************

//creates an empty binary tree
//post: object is an empty binary tree
//usage: BinaryTree zags;
BinaryTree::BinaryTree()
{
   root = nullptr;
}

//creates a new binary tree that is a copy of an existing tree
//post: object is a copy of rightHandSideTree
//throws an exception if there is not enough room in the
//       heap to make the copied tree
//usage: BinaryTree zags (bulldog);
BinaryTree::BinaryTree(const BinaryTree& rightHandSideTree) throw (Exception)
{
   root = nullptr;
   copyTree(root, rightHandSideTree.root);
}

//releases the memory of a binary tree
//pre: object exists
//post: memory for the object has been released. object theoretically does not exist
//       but in practice, it is empty.
BinaryTree::~BinaryTree()
{
   destroyTree(root);
}

// ******************** member functions ********************************************
//@pre: binary tree object exists
// **********************************************************************************

//checks for an empty tree
//post: returns true if the object is empty; else returns false
//usage: if (tree.isEmpty())
bool BinaryTree::isEmpty() const
{
   return (root == nullptr);
}

//copies one tree to another
//pre: rightHandSideTree is an assigned tree.
//post: object is a copy of rightHandSideTree
//throws an exception if there is not enough room in the
//       heap to make the copied tree
//usage: atree = btree = ctree;
BinaryTree& BinaryTree::operator=(const BinaryTree& rightHandSideTree) throw (Exception)
{
	if (root != nullptr)
		destroyTree(root);
	copyTree(root, rightHandSideTree.root);
	return *this;
}

//prints the tree to look like a computer science tree
//post: outputs the tree as in the example below
//
//                        bar
//                  foo 
//                        geeU
//  root ->  queue
//                        stack
//                  list
//                        array
//nodes at the same level are indented the same.
//Viewer must rotate head 90 degrees in order to look like a cs tree
//usage: tree.prettyDisplay();
void BinaryTree::prettyDisplay(ostream& output)
{
	writePretty(root, 0, output);
}

// *************** on the following traversals

//post: prints the objects in the tree in order specified
//usage: tree.preorderTraverse();  
//similarly for the other traversals
// *****************************************************
void BinaryTree::preorderTraverse()
{
   preorder(root);
}

void BinaryTree::inorderTraverse()
{
	inorder(root);
}

void BinaryTree::postorderTraverse()
{
	postorder(root);
}

//makes a full binary tree of height 3
//pre input is either cin or an open file
//    input's pointer is before the first item
//post: object is a full binary tree of height 3
//throws an exception if there is not enough room in the
//       heap to make the tree
//usage: myTree.makeFullTreeHeight3(infile);
void BinaryTree::makeFullTreeHeight3(istream& input) throw (Exception)
{
   Item newguy;
   
   input >> newguy;
   root = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
   
   input >> newguy;
   root -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> leftChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	   
   input >> newguy;
   root -> leftChild -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> leftChild -> leftChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	   
   input >> newguy;
   root -> leftChild -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> leftChild -> rightChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	   
   input >> newguy;
   root -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> rightChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");

   input >> newguy;
   root -> rightChild -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> rightChild -> leftChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	   
   input >> newguy;
   root -> rightChild -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> rightChild -> rightChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	
}

//makes a complete binary tree of height 4
//pre input is either cin or an open file
//post: object is a complete binary tree of height 4
//throws an exception if there is not enough room in the
//       heap to make the tree
//usage: tree.makeCompleteTreeHeight4(infile);
void BinaryTree::makeCompleteTreeHeight4(istream& input) throw (Exception)
{
   Item newguy;
   
   input >> newguy;
   root = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
   
   input >> newguy;
   root -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> leftChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	   
   input >> newguy;
   root -> leftChild -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> leftChild -> leftChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	   
   input >> newguy;
   root -> leftChild -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> leftChild -> rightChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	   
   input >> newguy;
   root -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> rightChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");

   input >> newguy;
   root -> rightChild -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> rightChild -> leftChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	   
   input >> newguy;
   root -> rightChild -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> rightChild -> rightChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	   
   input >> newguy;
   root -> leftChild -> leftChild -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> leftChild -> leftChild -> leftChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	   
   input >> newguy;
   root -> leftChild -> leftChild -> rightChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> leftChild -> leftChild -> rightChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	   
   input >> newguy;
   root -> leftChild -> rightChild -> leftChild = new (nothrow) TreeNode(newguy, nullptr, nullptr);
   if (root -> leftChild -> rightChild -> leftChild == nullptr) //No memory from heap!
	   throw Exception("In BinaryTree: No memory from heap available.");
	
   throw Exception("I am throwing an exception at you, Dr. Y. Do you have your catcher’s mitt ready?");
}
