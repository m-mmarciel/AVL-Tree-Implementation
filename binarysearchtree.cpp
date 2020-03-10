//File: binarysearchtree.cpp
//authors: Tommy Engels and Maximillian Marciel
//date: 11/1/2018

// Implementation of ADT Dictionary as ADT Binary Search Tree
//     data object: a bunch of texting abbreviations and their meanings 
//     operations: create, destroy
//                 search the dictionary for an item given its text
//                 insert a new item into the dictionary
//                 remove an item from the dictionary given its text
//   associated operations: input and output
// filename binarysearchtree.cpp
// date November 1, 2018


#include "binarysearchtree.h"

//-----------------------------
// recursive helper functions:
//-----------------------------

//usage: recursive helper for inorderTraverse
//pre: treep exists
//post: prints the objects in the tree in order specified
//usage: inorderSearchTree(root,output);  
void inorderSearchTree(TreeNode* treep, ostream& output)
{
    if (treep != nullptr)
	{
		inorderSearchTree(treep -> leftChild, output);
		output << treep -> item;
		inorderSearchTree(treep -> rightChild, output);
	}
}

void readTree(istream& input, TreeNode*& treep, int numberOfEntries)
{
   Item anItem;
   Item emptyItem;
   if (numberOfEntries > 0)
   {
	  treep = new (nothrow) TreeNode(emptyItem, nullptr, nullptr);
	  if (treep == nullptr)
		  throw Exception("Error in adding new entry, no more computer memory is available.");
	  
      readTree(input, treep -> leftChild, numberOfEntries / 2); // / 2
	  input >> anItem;
	  treep -> item = anItem;
      readTree(input, treep -> rightChild, (numberOfEntries - 1) / 2);
   }
}

//uses: operator<< from class Item
//post: prints the objects in the tree in order specified
//usage: tree.inorderTraverse();  
//overwrites binarytree class inorder traversal.
void BinarySearchTree::inorderTraverse (ostream& output) const
{
	inorderSearchTree(root, output);
}

// searches a binary search tree for a certain text
// pre: treep is assigned a pointer to a root node of a binary search tree
//      targetText is assigned
// post: if targetText is found in the tree whose root node is treep
//          then the item in the root node is copied into anItem and
//          returns true; otherwise, returns false
// usage: isFound = searchHelper(root, targetText, anItem);
bool searchHelper(TreeNode* treep, const Key& targetText, Item& anItem)
{
   if (treep != nullptr)
   {
      if (targetText == treep -> item)
      {
         anItem = treep -> item;
         return true;
      } else if (targetText < treep -> item) {
         return searchHelper(treep -> leftChild, targetText, anItem);
      } else {
         return searchHelper(treep -> rightChild, targetText, anItem);
      }
   } else {
      return false;
   }
}

//recursive helper for add new entry.
void addHelper(TreeNode*& treep, const Item& newItem) throw (Exception)
{
   //you need to figure out where to throw if full
   Key targetText = newItem;
   if (treep != nullptr)
   {
      if (targetText == treep -> item)
      {
         throw Exception("Error in adding new entry, adding an entry that's already there.");
		 
      } else if (targetText < treep -> item) {
         return addHelper(treep -> leftChild, newItem);
      } else {
         return addHelper(treep -> rightChild, newItem);
      }
   } else {
      treep = new (nothrow) TreeNode(newItem, nullptr, nullptr);
	  if (treep == nullptr)
		  throw Exception("Error in adding new entry, no more computer memory is available.");
   }
}

// inserts a new text' item into the dictionary
// pre: newItem has been assigned
// post: if there is room in the BinarySearchTree object and newItem's text
//            is not already there then newItem is appropriately added
//       else it throws an exception for either a full dictionary or
//            a message that it is already there
// usage: myDictionary.addNewEntry(myItem, isFull, isAlreadyThere);
void BinarySearchTree::addNewEntry(const Item& newItem) throw (Exception)
{
	addHelper(root, newItem);
	numberOfItems++;
}

// displays a dictionary
// pre: output has been opened if it is a file
//      rightHandSideDictionary has been assigned items
// post: output contains each item on a separate line in the format with headings.

// usage: outfile << myDictionary;    
ostream& operator<< (ostream& output, const BinarySearchTree& rightHandSideDictionary)
{
	output << rightHandSideDictionary.numberOfItems << endl;
	rightHandSideDictionary.inorderTraverse(output);
	return output;
}

// inputs items into a dictionary
// pre: input has been opened if it is a file
//      items are arranged in the following format
//      2
//      lol
//      laugh out loud
//      ttyl
//      talk to you later
// post: if there is room, 
//       all items in the input have been stored in rightHandSideDictionary
// usage: infile >> myDictionary;
istream& operator>> (istream& input, BinarySearchTree& rightHandSideDictionary)
{
	Item newItem;
	int entryNumber;
	input >> entryNumber;
	rightHandSideDictionary.numberOfItems = rightHandSideDictionary.numberOfItems++;
	readTree(input, rightHandSideDictionary.root, entryNumber);
	
	return input;
}

// creates a new dictionary
// post: BinarySearchTree object exists but is empty
// usage: BinarySearchTree myDictionary;	
BinarySearchTree::BinarySearchTree()
{
	numberOfItems = 0;
}

// destroys a dictionary
// pre: BinarySearchTree object exists
// post: all memory for BinarySearchTree object has been freed
// usage: automatically done at the end of scope
BinarySearchTree::~BinarySearchTree()
{
	
}

// searchs for a meaning with a given text
// pre targetText has been assigned a value not already in the hash table
// post if an item with texting abbreviationthe same as targetText is found then
//          isFound is true and theItem is that item
//       else isFound is false
// usage  myDictionary.searchForMeaning(targetText, anItem, isFound);
void BinarySearchTree::searchForMeaning(const Key& targetText, Item& anItem, bool& isFound)
{
	isFound = searchHelper(root, targetText, anItem);
}

// removes the item associated with a given text from the dictionary
// pre: targetText is assigned
// post: if BinarySearchTree object is not empty and 
//           targetText is found in Dictionary object,
//           and the associated Item object (text and meaning) has been 
//           removed from the Dictionary object
//           else an exception is thrown if there is an error.
// usage: myDictionary.deleteEntry(myText);
void BinarySearchTree::deleteEntry(const Key& targetText) throw (Exception)
{
	
}






















