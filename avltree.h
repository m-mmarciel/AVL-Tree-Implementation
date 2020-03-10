//avltree.h

#include "binarysearchtree.h"
#include "exception.h"

class AVLTree: public BinarySearchTree
{
public:
	
AVLTree();

~AVLTree();	

void addNewEntry(const Item& newItem) throw (Exception);

};