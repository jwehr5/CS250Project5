#ifndef FILESYSTEMTREE
#define FILESYSTEMTREE

#include <iostream>
#include <memory> // for smart pointers
#include <utility> // for pair class
#include <iostream>
#include "FSNode.h"

// The name of the root node is enforced to be unique, no other file/directory
// may have this name.  It MAY contain non-alpha and non-digit characters,
// but it MUST NOT contain SEPARATING_CHAR.
const std::string ROOT_NAME = "C:";

// Separating char defines what separates entities in a path. It MUST be 
// non-alpha and non-digit or chaos will ensue.
const char SEPARATING_CHAR = '/';

class FilesystemTree
{

public:

	/*
	* Constructor which creates an empty filesystem consisting only of root.
	*/
	FilesystemTree();

	/*
	* Copy constructor.
	*/
	FilesystemTree(const FilesystemTree& treeToCopy);

	/*
	* Constructor which reads file structure from a text file to construct the
	* filesystem. Each line in the text file should have this format for files:
	* filename pathtoparentdirectory
	*
	* An asterisk at the beginning of the line indicates a directory:
	* * directoryname pathtoparentdirectory
	*
	* Paths should always begin with ROOT_NAME and be delimited with 
	* SEPARATING_CHAR. Root will be created automatically and should not be 
	* listed in the file.
	*
	* @param fileName Name of the file to import from.
	*/
	FilesystemTree(const std::string& fileName);

	/*
	* create() adds a new file or directory to the filesystem.
	*
	* @param pName Name of the new file/directory to create.
	* @param pType Sets the type of the newly created item.
	*        DIR_TYPE = directory, FILE_TYPE = file.
	* @param parentPath Path to the directory where the new item should be
	*        created. Must begin with ROOT_NAME and be delimited by 
	*        SEPARATING_CHAR.
	*/
	bool create(const std::string& pName, int pType,
		const std::string& parentPath);

	/*
	* display() writes the tree structure to the given ostream.
	*
	* @param outStream The output stream the tree structure should be written
	*                  to. 
	*/
	void displayTree(std::ostream& outStream) const;

	/*
	* remove() removes a file/directory. DOES NOT allow the removal of ROOT_NAME.
	*
	* @param pName Name of the file/directory to remove.
	* @param parentPath Path to the parent directory of pName. Must begin with 
	*                   ROOT_NAME and be delimited by SEPARATING_CHAR.
	* @return True if pName was removed, false if not.
	*/
	bool remove(const std::string& pName, const std::string& parentPath);

	/*
	* move() moves a file/directory. When used with a directory moves the 
	* directory and all its contents. DOES NOT allow ROOT_NAME to be moved. 
	*
	* @param pName Name of the file/directory to move.
	* @param sourcePath Path to the parent directory of pName. Must begin with 
	*                   ROOT_NAME and be delimited by SEPARATING_CHAR.
	* @param destPath Path of the directory to move pName to. Must begin with 
	*                 ROOT_NAME and be delimited by SEPARATING_CHAR.
	* @return True if pName was moved, false if not.
	*/
	bool move(const std::string& pName, const std::string& sourcePath,
		const std::string& destPath);

	/*
	* copy() copies a file/directory. When used with a directory copies the
	* directory and all its contents. DOES NOT allow ROOT_NAME to be copied.
	*
	* @param pName Name of the file/directory to copy.
	* @param sourcePath Path to the parent directory of pName. Must begin with 
	*                   ROOT_NAME and be delimited by SEPARATING_CHAR.
	* @param destPath Path of the directory to copy pName to. Must begin with 
	*                 ROOT_NAME and be delimited by SEPARATING_CHAR.
	* @return True if pName was copied, false if not.
	*/
	bool copy(const std::string& pName, const std::string& sourcePath,
		const std::string& destPath);

	/*
	* find() searches for a file or directory in a given directory and its
	* subdirectories. For each match found it writes the full path to the
	* match to the specified ostream.
	*
	* @param pName Name of file/directory to search for.
	* @param startPath Path to the directory where search begins. Must begin 
	*                  with ROOT_NAME and be delimited by SEPARATING_CHAR.
	* @param outStream The output stream where the path for each match will be
	*                  written.
	* @return The total number of matches found (the same as the
	*         number of lines written to outStream).
	*/
	int find(const std::string& pName, const std::string& startPath, 
		std::ostream& outStream) const;

	/*
	* displayStats() displays the total file and directory counts. DOES NOT
	* count ROOT_NAME as a directory.
	*
	*@param outStream The output stream where the counts will be written.
	*/
	void displayStats(std::ostream& outStream) const;

	/*
	* format() erases all files and directories EXCEPT ROOT_NAME.
	*
	* @return True if successful, false if not.
	*/
	bool format();

	/*
	* Overloaded assignment operator which does a deep copy.
	*
	* @param rTree The tree to be copied.
	*/
	FilesystemTree& operator=(const FilesystemTree& rTree);

	~FilesystemTree();

private:

	/*
	* recursiveDisplay() is a recursive helper function for the public 
	* displayTree().
	*
	* @param nodePtr The file/directory to write out in this call.
	* @param preSpace The characters to display on the line in front of
	*                 the name of this file/directory. Used for formatting.
	* @param outStream The stream to write the output to.
	*/
	void recursiveDisplay(std::shared_ptr<FSNode> nodePtr, std::string preSpace,
		std::ostream& outStream) const;

	/*
	* recursiveStats() is a recursive helper function for the public
	* displayStats(). Recursively counts the total number of files/directories.
	*
	* @param startPtr Begin counting files/directores at this node plus all
	*                 subdirectoris.
	* @return Returns a pair object whose first value is the total directory
	*         count and second value is the total file count.
	*/
	std::pair<int, int> recursiveStats(std::shared_ptr<FSNode> startPtr) const;

	/*
	* Helper function to make an independent copy of a subtree recursively
	* beginning at a given node. If called on the root then it copies
	* the entire tree.
	*
	* @param rootPtr Pointer to the root node of the subtree to copy.
	* @return A pointer to an independent copy of the subtree.
	*/
	std::shared_ptr<FSNode> copySubTree(std::shared_ptr<FSNode> rootPtr) const;

	/*
	* Helper funciton to convert a full path to a file/directory to a pointer
	* to that file directory.  For example, given root/dir1/file3 it returns
	* a pointer to the node named file3.
	*
	* @param path Full path to a file or directory. Must begin with ROOT_NAME
	*             and be delimited by SEPARATING_CHAR.
	* @return A pointer to the node at the given path, or nullptr if the path
	*         is invalid.
	*/
	std::shared_ptr<FSNode> pathToPointer(const std::string& path) const;

	std::shared_ptr<FSNode> rootPtr; // pointer to the root of the filesystem
	
}; // end FilesystemTree

#endif
