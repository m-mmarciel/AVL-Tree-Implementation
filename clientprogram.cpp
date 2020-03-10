//File: clientprogram.cpp
//authors: Tommy Engels and Maximillian Marciel
//date: 11/20/2018

//This program is a user input-free display of the
//multiple possible cases and subcases when adding a
//new entry into an AVL Tree.

#include "avltree.h"
#include "exception.h"
#include "item.h"
#include <string>
#include <fstream>
using namespace std;

//opens an input file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file 
//      else an error message is printed
//usage openInputFile(infile, filename);
void openInputFile(ifstream& inputFile, string filename);

//prints an exception message
//pre except has been thrown
//post except is printed to the screen with two newlines before and after
//usage PrintExceptionMessage(except);
void printExceptionMessage(const Exception& except);

//Performs the case where there is no pivot and multiple
//subcases for the case, creating multiple trees and adding
//entries to them to show this. Writes results to file.
//Pre: Output and input file are both opened.
//Post: Outputs the results of the subcases to the file.
//Usage: doCaseNoPivot(infile, outfile);
void doCaseNoPivot(ifstream& inputFile, ofstream& output);

//Performs the case where the entry is added to the short side and many
//subcases for the case, creating multiple trees and adding
//entries to them to show this. Writes results to file.
//Pre: Output and input file are both opened.
//Post: Outputs the results of the subcases to the file.
//Usage: doCaseIsAddedToShortSide(infile, outfile);
void doCaseIsAddedToShortSide(ifstream& inputFile, ofstream& output);

//Performs the case where the entry is rotated left and many
//subcases for the case, creating multiple trees and adding
//entries to them to show this. Writes results to file.
//Pre: Output and input file are both opened.
//Post: Outputs the results of the subcases to the file.
//Usage: doCaseSingleRotateLeft(infile, outfile);
void doCaseSingleRotateLeft(ifstream& inputFile, ofstream& output);

//Performs the case where the entry is rotated right and many
//subcases for the case, creating multiple trees and adding
//entries to them to show this. Writes results to file.
//Pre: Output and input file are both opened.
//Post: Outputs the results of the subcases to the file.
//Usage: doCaseSingleRotateRight(infile, outfile);
void doCaseSingleRotateRight(ifstream& inputFile, ofstream& output);

//Performs the case where the entry is doubled rotated left-right and many
//subcases for the case, creating multiple trees and adding
//entries to them to show this. Writes results to file.
//Pre: Output and input file are both opened.
//Post: Outputs the results of the subcases to the file.
//Usage: doCaseDoubleRotateLeftRight(infile, outfile);
void doCaseDoubleRotateLeftRight(ifstream& inputFile, ofstream& output);

//Performs the case where the entry is doubled rotated right-left and many
//subcases for the case, creating multiple trees and adding
//entries to them to show this. Writes results to file.
//Pre: Output and input file are both opened.
//Post: Outputs the results of the subcases to the file.
//Usage: doCaseDoubleRotateRightLeft(infile, outfile);
void doCaseDoubleRotateRightLeft(ifstream& inputFile, ofstream& output);

//Constructs the pre-trees for use within the cases using
//data extracted from the file.
//Pre: Input file has been opened
//Post: The Pre-Tree is constructed and put into the AVLTree variable.
//Usage: constructPreTree(inputFile, case#Tree);
void constructPreTree(ifstream& input, AVLTree& myTree);

//Outputs the constructed Pre-AVL Tree to the file for whatever AVL
//tree it has been given, then inserts the new item and outputs that to file.
//essentially outputs the entire subcase to the file.
//Pre: Output and input files have been opened
//Post: The subcase is outputted to file
//Usage: outputCase(input, myTree, output);
void outputCase(ifstream& input, AVLTree& myTree, ofstream& output);

int main()
{
	ifstream infile;
	ofstream outfile;
	openInputFile(infile, "in.dat");
	outfile.open("avl.dat");
	doCaseNoPivot(infile, outfile);
	doCaseIsAddedToShortSide(infile, outfile);
	doCaseSingleRotateLeft(infile, outfile);
	doCaseSingleRotateRight(infile, outfile);
	doCaseDoubleRotateLeftRight(infile, outfile);
	doCaseDoubleRotateRightLeft(infile, outfile);
	cout << "All cases and subcases succesfully written to file!" << endl;
	
	return 0;
}

//Constructs the pre-trees for use within the cases using
//data extracted from the file.
//Pre: Input file has been opened
//Post: The Pre-Tree is constructed and put into the AVLTree variable.
//Usage: constructPreTree(inputFile, case#Tree);
void constructPreTree(ifstream& input, AVLTree& myTree)
{
	Item newItem;
	int entryNumber;
	input >> entryNumber;
	try
	{
		for (int i = 0; i < entryNumber; i++)
		{
			input >> newItem;
			myTree.addNewEntry(newItem);
		}
	}
	catch (Exception except) {printExceptionMessage(except);}
}

//Outputs the constructed Pre-AVL Tree to the file for whatever AVL
//tree it has been given, then inserts the new item and outputs that to file.
//essentially outputs the entire subcase to the file.
//Pre: Output and input files have been opened
//Post: The subcase is outputted to file
//Usage: outputCase(input, myTree, output);
void outputCase(ifstream& inputFile, AVLTree& myTree, ofstream& output)
{
	Item newItem;
    output << "Pre-AVLTree:" << endl << endl;
	constructPreTree(inputFile, myTree);
	myTree.prettyDisplay(output);
	output << endl;
	output << "Post-AVLTree:" << endl << endl;
	inputFile >> newItem;
	output << "Inserting item: " << newItem;
	try
	{
		myTree.addNewEntry(newItem);
	}
	catch (Exception except) {printExceptionMessage(except);}
	myTree.prettyDisplay(output);
	output << endl;
}

//Performs the case where the entry is doubled rotated right-left and many
//subcases for the case, creating multiple trees and adding
//entries to them to show this. Writes results to file.
//Pre: Output and input file are both opened.
//Post: Outputs the results of the subcases to the file.
//Usage: doCaseDoubleRotateRightLeft(infile, outfile);
void doCaseDoubleRotateRightLeft(ifstream& inputFile, ofstream& output)
{
	AVLTree case1Tree;
	AVLTree case2Tree;
	AVLTree case3Tree;
	AVLTree case4Tree;
	AVLTree case5Tree;
	AVLTree case6Tree;
	AVLTree case7Tree;
	Item newItem;
	
	output << "******************************************************************************" << endl;
	output << "\t\t\t CASE OF DOUBLE ROTATE RIGHT LEFT" << endl;
	output << "-----------------------------------------------------------------" << endl;
	output << "Test1: CASE OF PIVOT IS THE ROOT" << endl << endl;
    outputCase(inputFile, case1Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test2: CASE OF PIVOT IS A RIGHT CHILD" << endl << endl;
	outputCase(inputFile, case2Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test3: CASE OF PIVOT IS A LEFT CHILD" << endl << endl;
	outputCase(inputFile, case3Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test4: CASE OF T1, T4 ARE HEIGHT 2 - T2, T3 ARE HEIGHT 1." << endl << endl;
	outputCase(inputFile, case4Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test5: CASE OF NEW ITEM IS ADDED TO T2" << endl << endl;
	outputCase(inputFile, case5Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test6: CASE OF NEW ITEM IS ADDED TO T3" << endl << endl;
	outputCase(inputFile, case6Tree , output);
	
}

//Performs the case where the entry is doubled rotated left-right and many
//subcases for the case, creating multiple trees and adding
//entries to them to show this. Writes results to file.
//Pre: Output and input file are both opened.
//Post: Outputs the results of the subcases to the file.
//Usage: doCaseDoubleRotateLeftRight(infile, outfile);
void doCaseDoubleRotateLeftRight(ifstream& inputFile, ofstream& output)
{
	AVLTree case1Tree;
	AVLTree case2Tree;
	AVLTree case3Tree;
	AVLTree case4Tree;
	AVLTree case5Tree;
	AVLTree case6Tree;
	AVLTree case7Tree;
	Item newItem;
	
	output << "******************************************************************************" << endl;
	output << "\t\t\t CASE OF DOUBLE ROTATE LEFT RIGHT" << endl;
	output << "-----------------------------------------------------------------" << endl;
	output << "Test1: CASE OF PIVOT IS THE ROOT" << endl << endl;
    outputCase(inputFile, case1Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test2: CASE OF PIVOT IS A RIGHT CHILD" << endl << endl;
	outputCase(inputFile, case2Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test3: CASE OF PIVOT IS A LEFT CHILD" << endl << endl;
	outputCase(inputFile, case3Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test4: CASE OF T1, T4 ARE HEIGHT 2 - T2, T3 ARE HEIGHT 1." << endl << endl;
	outputCase(inputFile, case4Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test5: CASE OF NEW ITEM IS ADDED TO T2" << endl << endl;
	outputCase(inputFile, case5Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test6: CASE OF NEW ITEM IS ADDED TO T3" << endl << endl;
	outputCase(inputFile, case6Tree , output);

	
}

//Performs the case where the entry is rotated left and many
//subcases for the case, creating multiple trees and adding
//entries to them to show this. Writes results to file.
//Pre: Output and input file are both opened.
//Post: Outputs the results of the subcases to the file.
//Usage: doCaseSingleRotateLeft(infile, outfile);
void doCaseSingleRotateLeft(ifstream& inputFile, ofstream& output)
{
	AVLTree case1Tree;
	AVLTree case2Tree;
	AVLTree case3Tree;
	AVLTree case4Tree;
	AVLTree case5Tree;
	AVLTree case6Tree;
	AVLTree case7Tree;
	Item newItem;

    output << "******************************************************************************" << endl;
	output << "\t\t\t CASE OF SINGLE ROTATE LEFT" << endl;
	output << "-----------------------------------------------------------------" << endl;
	output << "Test1: CASE OF PIVOT IS THE ROOT" << endl << endl;
    outputCase(inputFile, case1Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test2: CASE OF PIVOT IS A RIGHT CHILD" << endl << endl;
	outputCase(inputFile, case2Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test3: CASE OF PIVOT IS A LEFT CHILD" << endl << endl;
	outputCase(inputFile, case3Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test4: CASE OF T1, T2, T3 ARE HEIGHT ZERO" << endl << endl;
	outputCase(inputFile, case4Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test5: CASE OF T1, T2, T3 ARE HEIGHT ONE" << endl << endl;
	outputCase(inputFile, case5Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test6: CASE OF T1, T2, T3 ARE HEIGHT TWO" << endl << endl;
	outputCase(inputFile, case6Tree, output);
}

//Performs the case where the entry is rotated right and many
//subcases for the case, creating multiple trees and adding
//entries to them to show this. Writes results to file.
//Pre: Output and input file are both opened.
//Post: Outputs the results of the subcases to the file.
//Usage: doCaseSingleRotateRight(infile, outfile);
void doCaseSingleRotateRight(ifstream& inputFile, ofstream& output)
{
	AVLTree case1Tree;
	AVLTree case2Tree;
	AVLTree case3Tree;
	AVLTree case4Tree;
	AVLTree case5Tree;
	AVLTree case6Tree;
	AVLTree case7Tree;
	Item newItem;

    output << "******************************************************************************" << endl;
	output << "\t\t\t CASE OF SINGLE ROTATE RIGHT" << endl;
	output << "-----------------------------------------------------------------" << endl;
	output << "Test1: CASE OF PIVOT IS THE ROOT" << endl << endl;
    outputCase(inputFile, case1Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test2: CASE OF PIVOT IS A RIGHT CHILD" << endl << endl;
	outputCase(inputFile, case2Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test3: CASE OF PIVOT IS A LEFT CHILD" << endl << endl;
	outputCase(inputFile, case3Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test4: CASE OF T1, T2, T3 ARE HEIGHT ZERO" << endl << endl;
	outputCase(inputFile, case4Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test5: CASE OF T1, T2, T3 ARE HEIGHT ONE" << endl << endl;
	outputCase(inputFile, case5Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test6: CASE OF T1, T2, T3 ARE HEIGHT TWO" << endl << endl;
	outputCase(inputFile, case6Tree, output);
	
	
}

//Performs the case where the entry is added to the short side and many
//subcases for the case, creating multiple trees and adding
//entries to them to show this. Writes results to file.
//Pre: Output and input file are both opened.
//Post: Outputs the results of the subcases to the file.
//Usage: doCaseIsAddedToShortSide(infile, outfile);
void doCaseIsAddedToShortSide(ifstream& inputFile, ofstream& output)
{
	AVLTree case1Tree;
	AVLTree case2Tree;
	AVLTree case3Tree;
	AVLTree case4Tree;
	Item newItem;
	
    output << "******************************************************************************" << endl;
	output << "\t\t\t CASE OF IS ADDED TO SHORT SIDE" << endl;
	output << "-----------------------------------------------------------------" << endl;
	output << "Test1: CASE OF ADDING TO THE RIGHT, HEIGHT 2" << endl << endl;
    outputCase(inputFile, case1Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test2: CASE OF ADDING TO THE LEFT, HEIGHT 2" << endl << endl;
    outputCase(inputFile, case2Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test3: CASE OF ADDING TO THE RIGHT, HEIGHT 3" << endl << endl;
    outputCase(inputFile, case3Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test4: CASE OF ADDING TO THE LEFT, HEIGHT 3" << endl << endl;
    outputCase(inputFile, case4Tree , output);
}

//Performs the case where there is no pivot and multiple
//subcases for the case, creating multiple trees and adding
//entries to them to show this. Writes results to file.
//Pre: Output and input file are both opened.
//Post: Outputs the results of the subcases to the file.
//Usage: doCaseNoPivot(infile, outfile);
void doCaseNoPivot(ifstream& inputFile, ofstream& output)
{
	AVLTree case1Tree;
	AVLTree case2Tree;
	AVLTree case3Tree;
	AVLTree case4Tree;
	AVLTree case5Tree;
	Item newItem;
	
	output << "******************************************************************************" << endl;
	output << "\t\t\t CASE OF NO PIVOT" << endl;
	output << "-----------------------------------------------------------------" << endl;
	//This test doesn't need to call writePretty in order to print
	//an empty tree and thus does not call the outputCase function.
	output << "Test1: CASE OF EMPTY TREE" << endl << endl;
	output << "Pre-AVLTree:" << endl << endl;
	output << "(Empty tree has no nodes)" << endl << endl;
	output << "Post-AVLTree:" << endl;
	inputFile >> newItem;
	output << "Inserting item: " << newItem;
	try
	{
		case1Tree.addNewEntry(newItem);
	}
	catch (Exception except) {printExceptionMessage(except);}
	case1Tree.prettyDisplay(output);
	output << endl;
	
	output << "-----------------------------------------------------------------" << endl;
	output << "Test2: HEIGHT 2 TREE" << endl << endl;
	outputCase(inputFile, case2Tree , output);
	output << "-----------------------------------------------------------------" << endl;
	output << "Test3: ADDING TO THE LEFT" << endl << endl;
	outputCase(inputFile, case3Tree , output);

	//These use specific assignments to construct their trees
	//and thus do not call on the outputCase function
	output << "-----------------------------------------------------------------" << endl;
	output << "Test4: ADDING ACROSS NODES, TO THE RIGHT" << endl << endl;
	output << "Pre-AVLTree:" << endl << endl;
	case4Tree = case3Tree;
	case4Tree.prettyDisplay(output);
	output << endl;
	output << "Post-AVLTree:" << endl << endl;
	inputFile >> newItem;
	output << "Inserting Item: " << newItem;
	try
	{
		case4Tree.addNewEntry(newItem);
	}
	catch (Exception except) {printExceptionMessage(except);}
	case4Tree.prettyDisplay(output);
	output << endl;
	output << "-----------------------------------------------------------------" << endl;
	output << "Test5: ADDING ACROSS NODES, TO THE LEFT" << endl << endl;
	output << "Pre-AVLTree:" << endl << endl;
	case5Tree = case3Tree;
	case5Tree.prettyDisplay(output);
	output << endl;
	output << "Post-AVLTree:" << endl << endl;
	inputFile >> newItem;
	output << "Inserting Item: " << newItem;
	try
	{
		case5Tree.addNewEntry(newItem);
	}
	catch (Exception except) {printExceptionMessage(except);}
	case5Tree.prettyDisplay(output);
	output << endl;
	
}


//opens an input file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file 
//      else an error message is printed
//usage openInputFile(infile, filename);
void openInputFile(ifstream& inputFile, string filename) 
{
   inputFile.open(filename);
   if (inputFile.fail())
   {
      cout << "File failed to open!!!!" << endl;
      exit(1);
   }
}

//prints an exception message
//pre except has been thrown
//post except is printed to the screen with two newlines before and after
//usage PrintExceptionMessage(except);
void printExceptionMessage(const Exception& except)
{
   cout << endl << endl;
   cout << except.what();
   cout << endl << endl;
}