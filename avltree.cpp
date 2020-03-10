//File: binarysearchtree.cpp
//authors: Tommy Engels and Maximillian Marciel
//date: 11/20/2018
//usernames: tengels and mmarciel
//dropped off by: mmarciel

// Implementation of addition of new entries in an AVL Tree
//     data object: An AVL Tree, where an AVL tree is defined as either
//                  being empty or in the form:
//                              r
//                            /   \
//                           TL   TR
//     				Where TL and TR are AVLTrees such that |height(TL) - height(TR)| <= 1

// operations: Adding to the AVL Tree
// filename avltree.cpp
// date November 20, 2018

#include "binarysearchtree.h"
#include "avltree.h"
#include "exception.h"
#include <stdio.h>
#include <iostream>
using namespace std;

const int MAXHEIGHT = 15;


//----------------------------------------------------------------------
//					 	 HELPER FUNCTIONS
//----------------------------------------------------------------------
struct SearchPath
{
     TreeNode* path[MAXHEIGHT];
     int size;
     int pivotIndex;
     SearchPath();   
};


// Helper function that adds new entry to the search tree
//		and creates a search path from root to new entry
// Pre: treeptr points an AVL tree, search is empty SearchPath
//		with size zero and newItem exists. 
// Post: newItem is added to the tree and 
//		search is a search path from root to new entry
//		with appropriate size
//		If newItem is already in the search tree or
//		there was no memory for new TreeNode exception
//		is thrown.
// Usage: addNewEntryAndMakeSearchPath(newItem, root, search);
void addNewEntryAndMakeSearchPath(const Item& newItem, TreeNode*& treeptr, SearchPath& search) throw (Exception)
{
	if (treeptr != nullptr)
	{
		search.path[search.size] = treeptr;
		search.size += 1;
		if (search.size >= MAXHEIGHT)
			throw Exception("Search path size exceeds maximum height");
		
		if (newItem == treeptr -> item)
		{
			throw Exception("That abbreviation is already in the dictionary.");
		} else if ( newItem < treeptr -> item) {
			addNewEntryAndMakeSearchPath(newItem, treeptr -> leftChild, search);
		} else {
			addNewEntryAndMakeSearchPath(newItem, treeptr -> rightChild, search);
		}
	} else {
		treeptr = new (nothrow) TreeNode(newItem, nullptr, nullptr);
		search.path[search.size] = treeptr;
		search.size += 1;
		if (search.size >= MAXHEIGHT)
			throw Exception("Search path size exceeds maximum height");
	} 
	
   
   if ( treeptr == nullptr )
	   throw Exception("There was not enough memory to add a new abbreviation.");
}

// Detects whether the AVLTree has a pivot and assigns pivotIndex to 
//		the location of the node containing the pivot
// Pre: SearchPath has been declared, AVLTree exists
// Post: If there is a pivot, pivot index is assigned in search 
// 			to the location of the node containing the pivot and we return false, 
//			else return true
// usage: bool pivot = hasNoPivot(search);
bool hasNoPivot(SearchPath& search)
{
   int index = search.size - 1;
   while(index >= 0)
   {
      if(search.path[index] -> balance != 0)
	  {
		 search.pivotIndex = index;
	     return false;
	  }
	  index--;		
   }
   return true;
}

/*
  Team Members: Reid Whitson, Mimi Liebrand, Kat Sotelo Jimenez, Cole Donovan
  Description: Rebalance the tree from start index down
  pre: Unbalanced searchPath is passed along with the pivot index.
  post: AVL Tree that was passed has correct index balances
  usage: fixBalances(search, pivotIndex);
*/
void fixBalances(const SearchPath& search, int start){
	for(int i = start; i < search.size - 1; i++){
		if(search.path[i]->rightChild == search.path[i+1]){
			search.path[i]->balance++;
		} else{
			search.path[i]->balance--;
		}
	}
}

// tells whether the new item has been added to the short or tall side
// pre: SearchPath object exists
// post: returns true if added to the short side, false if added to the tall side
// usage: if(isAddedToShortSide(search))
bool isAddedToShortSide(const SearchPath& search)
{
	return ((search.path[search.pivotIndex] -> balance == -1 && search.path[search.pivotIndex + 1] == search.path[search.pivotIndex] -> rightChild)
	      ||(search.path[search.pivotIndex] -> balance ==  1 && search.path[search.pivotIndex + 1] == search.path[search.pivotIndex] -> leftChild));
}

//Tests whether or not the AVL tree needs a right rotation.
//Pre: Search exists/ is initialized
//Post: Returns true if a right rotation is needed in the AVL tree.
//Usage: isSingleRotateRight(mySearchPath);
bool isSingleRotateRight(const SearchPath& search)
{
	return ((search.path[search.pivotIndex + 1] == search.path[search.pivotIndex] -> leftChild) &&
		    (search.path[search.pivotIndex + 2] == search.path[search.pivotIndex + 1] -> leftChild));
}

// from the pivot node, if the search path goes right and then goes right again, returns true
// pre: object of type SearchPath exists
// post: returns true if search path goes right twice, false otherwise
// usage: isSingleRotateLeft(search)
bool isSingleRotateLeft(const SearchPath& search)
{
    return (search.path[search.pivotIndex] -> rightChild == search.path[search.pivotIndex + 1] &&
            search.path[search.pivotIndex + 1] -> rightChild == search.path[search.pivotIndex + 2]);
}

// goes to the pivot and checks to see if the avl tree goes left then right 
// pre: SearchPath exists
// post: returns true if search path goes left then right and false otherwise
// usage: isDoubleRotateLeftRight(SearchPath& mySearchPath);
bool isDoubleRotateLeftRight(const SearchPath& search)
{
	if (search.path[search.pivotIndex] -> leftChild == search.path[search.pivotIndex + 1])
	{
		if(search.path[search.pivotIndex + 1] -> rightChild == search.path[search.pivotIndex + 2])
			return true;
	}
	return false;
}

//Constructor for the Searchpath struct, initializes values and
//Initializes the path array
//Pre: path, size, and pivotIndex are initialized
//Post: Path's indeces point to nullptr, and size begins at zero.
//Usage: SearchPath();
SearchPath::SearchPath()
{
    size = 0;
    pivotIndex = -1;
    for(int i = 0; i < MAXHEIGHT; i++)
	{
		path[i] = nullptr;
	}
}

//Does the cloud pointer assignments for a double rotation, depending on case.
//Pre: root is passed to the function and exists, search path exists and points to the required nodes
//Post: the assignment is made so that the cloud points to the grandchild of the pivot in the
//      way it was originally pointed at the pivot.
//Usage: doDoubleRotationCloudPtrAssignment(myRoot, mySearchPath);
void doDoubleRotationCloudPtrAssignment(TreeNode*& myRoot, SearchPath& search)
{	
	if (search.pivotIndex == 0) //Case where pivot is the root
	{
		myRoot = search.path[search.pivotIndex + 2];
	}
	else if (search.path[search.pivotIndex - 1] -> leftChild == search.path[search.pivotIndex]) //If pivot is a left child
	{
		search.path[search.pivotIndex - 1] -> leftChild = search.path[search.pivotIndex + 2];
	}	
	else //Else pivot is a right child
	{
		search.path[search.pivotIndex - 1] -> rightChild = search.path[search.pivotIndex + 2];
	}
}

//Does the cloud pointer assignments for a single rotation, depending on case.
//Pre: root is passed to the function and exists, search path exists and points to the required nodes
//Post: the assignment is made so that the cloud points to the child of the pivot in the
//      way it was originally pointed at the pivot.
//Usage: doSingleRotationCloudPtrAssignment(myRoot, mySearchPath);
void doSingleRotationCloudPtrAssignment(TreeNode*& myRoot, SearchPath& search)
{	
	if (search.pivotIndex == 0) //Case where pivot is the root
	{ 
		myRoot = search.path[search.pivotIndex + 1];
	}
	else if (search.path[search.pivotIndex - 1] -> leftChild == search.path[search.pivotIndex]) //If pivot is a left child
	{
		search.path[search.pivotIndex - 1] -> leftChild = search.path[search.pivotIndex + 1];
	}
		
	else //Else pivot is a right child
	{
		search.path[search.pivotIndex - 1] -> rightChild = search.path[search.pivotIndex + 1];
	}
}

//Performs a single left rotation on a pivot.
//Pre: search path exists and points to the required nodes,
//     root has been given and exists.
//Post: Performs a single left rotation to the binary search tree
//      based around the pivot.
//Usage: doSingleLeftRotation(root, mySearchPath);
void doSingleLeftRotation(TreeNode*& myRoot, SearchPath& search)
{
	doSingleRotationCloudPtrAssignment(myRoot, search);
	search.path[search.pivotIndex] -> rightChild = search.path[search.pivotIndex + 1] -> leftChild;
	search.path[search.pivotIndex + 1] -> leftChild = search.path[search.pivotIndex];
	search.path[search.pivotIndex] -> balance--;
}

//Performs a single right rotation on a pivot.
//Pre: search path exists and points to the required nodes,
//     root has been given and exists.
//Post: Performs a single right rotation to the binary search tree
//      based around the pivot.
//Usage: doSingleLeftRotation(root, mySearchPath);
void doSingleRightRotation(TreeNode*& myRoot, SearchPath& search)
{
	doSingleRotationCloudPtrAssignment(myRoot, search);
	search.path[search.pivotIndex] -> leftChild = search.path[search.pivotIndex + 1] -> rightChild;
	search.path[search.pivotIndex + 1] -> rightChild = search.path[search.pivotIndex];
	search.path[search.pivotIndex] -> balance++;
}

//Performs a double left-right rotation on a pivot.
//Pre: search path exists and points to the required nodes,
//     root has been given and exists.
//Post: Performs a double left-right rotation to the binary search tree
//      based around the pivot.
//Usage: doDoubleRotateLeftRightRotation(root, mySearchPath);
void doDoubleRotateLeftRight(TreeNode*& myRoot, SearchPath& search)
{
	doDoubleRotationCloudPtrAssignment(myRoot, search);
	search.path[search.pivotIndex + 1] -> rightChild = search.path[search.pivotIndex + 2] -> leftChild;
	search.path[search.pivotIndex] -> leftChild = search.path[search.pivotIndex + 2] -> rightChild;
	search.path[search.pivotIndex + 2] -> leftChild = search.path[search.pivotIndex + 1];
	search.path[search.pivotIndex + 2] -> rightChild = search.path[search.pivotIndex];
	search.path[search.pivotIndex] -> balance++;
}

//Performs a double right-left rotation on a pivot.
//Pre: search path exists and points to the required nodes,
//     root has been given and exists.
//Post: Performs a double right-left rotation to the binary search tree
//      based around the pivot.
//Usage: doDoubleRotateRightLeftRotation(root, mySearchPath);
void doDoubleRotateRightLeft(TreeNode*& myRoot, SearchPath& search)
{
    doDoubleRotationCloudPtrAssignment(myRoot, search);
	search.path[search.pivotIndex + 1] -> leftChild = search.path[search.pivotIndex + 2] -> rightChild;
	search.path[search.pivotIndex] -> rightChild = search.path[search.pivotIndex + 2] -> leftChild;
	search.path[search.pivotIndex + 2] -> rightChild = search.path[search.pivotIndex + 1];
	search.path[search.pivotIndex + 2] -> leftChild = search.path[search.pivotIndex];
	search.path[search.pivotIndex] -> balance--;
}


//----------------------------------------------------------------------
//					 	 MEMBER FUNCTIONS
//----------------------------------------------------------------------
	
AVLTree::AVLTree()
{
	//Constructor empty, relying on binarytree's constructor.
}


AVLTree::~AVLTree()
{
	//Destructor empty, relying on binarytree's destructor.
}

//Adds a new entry into the tree and automatically adjusts as the entries
//are added using rotations to maintain the AVL structure.
//Pre: left hand side tree is declared, newItem exists.
//Post: a new entry is placed into the tree and adjustments to the tree
//      are performed as is appropriate to the situation.
//Usage: myTree.addNewEntry(myItem);
void AVLTree::addNewEntry(const Item& newItem) throw (Exception)
{
   SearchPath search;
   addNewEntryAndMakeSearchPath(newItem, root, search);
   if(hasNoPivot(search))
   {
      fixBalances(search, 0);
   }
   else if (isAddedToShortSide(search))
   {
      fixBalances(search, search.pivotIndex);
   }
   else if (isSingleRotateLeft(search))
   {
      doSingleLeftRotation(root, search);
	  fixBalances(search, search.pivotIndex + 2);
   }
   else if (isSingleRotateRight(search))
   {
      doSingleRightRotation(root, search);
	  fixBalances(search, search.pivotIndex + 2);
   }
   else if (isDoubleRotateLeftRight(search))
   {
      doDoubleRotateLeftRight(root, search);
	  fixBalances(search, search.pivotIndex + 3);
   }
   else
   {
      doDoubleRotateRightLeft(root, search);
	  fixBalances(search, search.pivotIndex + 3);
   }
}