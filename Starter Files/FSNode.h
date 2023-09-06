#ifndef FSNODE
#define FSNODE

#include <memory>
#include <vector>
#include <string>

const int DIR_TYPE = 1; // Constant used to indicate node is a directory
const int FILE_TYPE = 0; // Constant used to indicate node is a file

class FSNode
{
public:

	/*
	* Parameterized constructor that sets the name and type (file or directory)
	* of the node. Note the type can only be set via constructor.
	*
	* @param pName The name of the file/directory. Can only contain alpha and
	*              numeric characters.
	* @param pType Sets whether the node is a file/directory. 
	*              DIR_TYPE = directory, FILE_TYPE = file.
	*/
	FSNode(const std::string& pName, int pType);

	/*
	* setName() changes the name of the node. Names may ONLY contain alpha and
	*           digit characters.
	*
	* @param pName The name of the file/directory. 
	*/
	void setName(const std::string& pName);
	
	/*
	* getName() returns the name of the node.
	*
	* @return The name of the node.
	*/
	std::string getName() const;

	/*
	* @return true if the node is a file.
	*/
	bool isFile() const;

	/*
	* @return true if the node is a directory.
	*/
	bool isDirectory() const;

	/*
	* addChild() adds an existing file/directory as as a child to this directory. 
	* Does not allow children with duplicate names nor children of files.
	*
	* @param childPtr A shared pointer to the node to add as a child.
	* @return true if successful.
	*/
	bool addChild(std::shared_ptr<FSNode> childPtr);

	/*
	* getChild() returns pointer to child by index (starting at 0). Allows for 
	* iteration through all children.
	*
	* @param index Index of the child to return a pointer to.
	* @return pointer to a child at the given index, nullptr if no child exists
	*        at the given index.
	*/
	std::shared_ptr<FSNode> getChild(int index) const;

	/*
	* getChild() returns pointer to child with matching name.

	* @param pName Name of the child to return a pointer to.
	* @return pointer to a child with the given name, nullptr if no child exists
	*        with the given name.
	*/
	std::shared_ptr<FSNode> getChild(std::string pName) const;

	/*
	* getNumChildren() returns the total number of children.
	*
	* @return 0 if this is a file, number if children if this is a directory
	*/
	int getNumChildren() const;

	/*
	* getType() returns the node type.
	*
	* @return DIR_TYPE if this is a file, FILE_TYPE if this is a directory
	*/
	int getType() const;

	/*
	* removeChild() removes the child with the given name from the directory. 
	*
	* @param pName Name of the child to remove.
	* @return True if the child was successfully removed.
	*/
	bool removeChild(const std::string& pName);

private:
	std::string name; // file or directory name
	int type; // 1 = directory, 0 = file

	/* If this is a directory it may contain other files and directories.
	These are linked to in the vector of pointers named children. */
	std::vector<std::shared_ptr<FSNode>> children;

	/*
	* FilesystemTree is a friend to allow direct access to name. This allows
	* the root node to be given a name containing non-alpha characters such as
	* "C:" which FSNode does not allow.
	*/
	friend class FilesystemTree;

}; // end FSNode

#endif 
