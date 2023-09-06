#include <iostream>
#include <memory>
#include <vector>
#include "FSNode.h"
#include "FilesystemTree.h"

// All functions below used for FilesystemTree class testing
void FSTInitialTest(std::shared_ptr<FilesystemTree> treePtr);
void FSTRemoveTest(std::shared_ptr<FilesystemTree> treePtr);
void FSTFindTest(std::shared_ptr<FilesystemTree> treePtr);
void FSTCCTest(std::shared_ptr<FilesystemTree> treePtr);
void FSTMoveTest(std::shared_ptr<FilesystemTree> treePtr);
void FSTCopyTest(std::shared_ptr<FilesystemTree> treePtr);

int main()
{
	/* Uncomment below to test the FilesystemTree class. Note that these
	* test functions are specifically written to work in the order they're
	* listed. So you should complete the required functions and uncomment the
	* test functions from top to bottom.
	*/

	// Line below requires create() to be complete.
	std::shared_ptr<FilesystemTree> treePtr = std::make_shared<FilesystemTree>("C:\\Users\\jayde\\OneDrive\\Documents\\Data Structures in C++\\Project 5\\Starter Files\\input.txt");

	// Tests displayTree() and displayStats().
	FSTInitialTest(treePtr);

	// Tests remove().
	FSTRemoveTest(treePtr);

	// Tests move().
	FSTMoveTest(treePtr);

	// Tests copy() which requires copySubTree().
	FSTCopyTest(treePtr);

	// Tests find().
	FSTFindTest(treePtr);

	// Tests copy constructor and overloaded = and displays final stats. These
	// require copySubTree().
	FSTCCTest(treePtr);
}

void FSTCCTest(std::shared_ptr<FilesystemTree> treePtr)
{
	// Test copy constructor (which uses overloaded =)
	std::shared_ptr<FilesystemTree> aTreePtr
		= std::make_shared<FilesystemTree>(*treePtr);

	std::cout << "** FINAL TREE **" << std::endl << std::endl;
	aTreePtr->displayTree(std::cout);

	std::cout << std::endl << "** FINAL TREE STATS **" << std::endl
		<< std::endl << "Should be 8 directories, 21 files:" << std::endl;
	aTreePtr->displayStats(std::cout);
}

void FSTFindTest(std::shared_ptr<FilesystemTree> treePtr)
{
	std::cout << std::endl << "** TESTING FIND() **" << std::endl << std::endl;
	std::cout << "Searching for dir6 starting at " << ROOT_NAME << ":" << std::endl;
	std::cout << treePtr->find("dir6", ROOT_NAME, std::cout) << " matches found. [should be 2]"
		<< std::endl << std::endl;
	std::cout << "Searching for file13 starting at " << ROOT_NAME << ":/dir1/dir2/dir8: "
		<< std::endl;
	std::cout << treePtr->find("file13", ROOT_NAME + "/dir1/dir2/dir8", std::cout) << " matches found. [should be 1]"
		<< std::endl << std::endl;
	std::cout << "Searching for file22 starting at " << ROOT_NAME << ":" << std::endl;
	std::cout << treePtr->find("file22", ROOT_NAME, std::cout) << " matches found. [should be 4]"
		<< std::endl << std::endl;
	std::cout << "Searching for file99 starting at " << ROOT_NAME << ":" << std::endl;
	std::cout << treePtr->find("file99", ROOT_NAME, std::cout) << " matches found. [should be 0]"
		<< std::endl << std::endl;
}

void FSTInitialTest(std::shared_ptr<FilesystemTree> treePtr)
{
	std::cout << "** INITIAL TREE LOADED FROM FILE **" << std::endl << std::endl;
	treePtr->displayTree(std::cout);

	std::cout << std::endl << "** INITIAL TREE STATS **" << std::endl
		<< std::endl << "Should be 10 directories, 25 files:" << std::endl;
	treePtr->displayStats(std::cout);
}

void FSTRemoveTest(std::shared_ptr<FilesystemTree> treePtr)
{
	std::cout << std::endl << "** TESTING REMOVE() **" << std::endl << std::endl;

	std::cout << "Remove file17 from " << ROOT_NAME << "/dir1/dir2/dir8: "
		<< treePtr->remove("file17", ROOT_NAME + "/dir1/dir2/dir8")
		<< " [should be 1]" << std::endl;
	std::cout << "Remove dir3 from " << ROOT_NAME << "/dir1/dir2: "
		<< treePtr->remove("dir3", ROOT_NAME + "/dir1/dir2")
		<< " [should be 1]" << std::endl;
	std::cout << "Remove dir3 from " << ROOT_NAME << "/dir1/dir2: "
		<< treePtr->remove("dir3", ROOT_NAME + "/dir1/dir2")
		<< " [should be 0]" << std::endl;
	std::cout << "Remove " << ROOT_NAME << ": "
		<< treePtr->remove(ROOT_NAME, "")
		<< " [should be 0]" << std::endl;
}

void FSTMoveTest(std::shared_ptr<FilesystemTree> treePtr)
{
	std::cout << std::endl << "** TESTING MOVE() **" << std::endl << std::endl;
	std::cout << "Move dir6 from " << ROOT_NAME << " to " << ROOT_NAME
		<< "/dir1/dir2: "
		<< treePtr->move("dir6", ROOT_NAME, ROOT_NAME + "/dir1/dir2")
		<< " [should be 1]" << std::endl;
	std::cout << "Move file5 from " << ROOT_NAME << "/dir1/dir2 to "
		<< ROOT_NAME << "/dir1: "
		<< treePtr->move("file5", ROOT_NAME + "/dir1/dir2", ROOT_NAME + "/dir1")
		<< " [should be 1]" << std::endl;
	std::cout << "Move file5 from " << ROOT_NAME << "/dir1 to " << ROOT_NAME
		<< "/dir1: "
		<< treePtr->move("file5", ROOT_NAME + "/dir1", ROOT_NAME + "/dir1")
		<< " [should be 0]" << std::endl;
	std::cout << "Move dir99 from " << ROOT_NAME << "/dir1/dir2/dir6 to "
		<< ROOT_NAME << "/dir1: "
		<< treePtr->move("dir99", ROOT_NAME + "/dir1/dir2/dir6", ROOT_NAME + "/dir1")
		<< " [should be 0]" << std::endl;
	std::cout << "Move file15 from " << ROOT_NAME << "/dir1/dir7 to "
		<< ROOT_NAME << "/dir6: "
		<< treePtr->move("file15", ROOT_NAME + "/dir1/dir7", ROOT_NAME + "/dir6")
		<< " [should be 0]" << std::endl;
}

void FSTCopyTest(std::shared_ptr<FilesystemTree> treePtr)
{
	std::cout << std::endl << "** TESTING COPY() **" << std::endl << std::endl;

	std::cout << "Copy file15 from " << ROOT_NAME << "/dir1/dir7 to "
		<< ROOT_NAME << "/dir1/dir2/dir6: "
		<< treePtr->copy("file15", ROOT_NAME + "/dir1/dir7",
			ROOT_NAME + "/dir1/dir2/dir6")
		<< " [should be 1]" << std::endl;
	std::cout << "Copy file15 from " << ROOT_NAME << "/dir1/dir7 to "
		<< ROOT_NAME << "/dir1/dir2/dir6: "
		<< treePtr->copy("file15", ROOT_NAME + "/dir1/dir7",
			ROOT_NAME + "/dir1/dir2/dir6")
		<< " [should be 0]" << std::endl;
	std::cout << "Copy dir2 from " << ROOT_NAME << "/dir1 to " << ROOT_NAME
		<< "/dir1/dir2/dir8: "
		<< treePtr->copy("dir2", ROOT_NAME + "/dir1",
			ROOT_NAME + "/dir1/dir2/dir8")
		<< " [should be 1]" << std::endl;

	std::cout << "Copy file99 from " << ROOT_NAME << " to " << ROOT_NAME
		<< "/dir1: "
		<< treePtr->copy("file99", ROOT_NAME, ROOT_NAME + "/dir1")
		<< " [should be 0]" << std::endl;

	std::cout << "Copy file3 from " << ROOT_NAME << "/dir1 to " << ROOT_NAME
		<< "/dir1: "
		<< treePtr->copy("file3", ROOT_NAME + "/dir1", ROOT_NAME + "/dir99")
		<< " [should be 0]" << std::endl;
}