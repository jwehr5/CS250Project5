#include <cstddef>
#include <cctype>
#include "FSNode.h"

int FSNode::getType() const
{
	return type;
}

FSNode::FSNode(const std::string& pName, int pType) : type(pType)
{ 
	setName(pName);
}  // end constructor


void FSNode::setName(const std::string& pName)
{
	std::string goodName;

	// Only allow alpha and digits in name. No spaces or special char.
	for (unsigned int i = 0; i < pName.length(); i++)
	{
		if (isalpha(pName[i]) || isdigit(pName[i]))
		{
			goodName += pName[i];
		}
	}

	name = goodName;
}  // end setName


std::string FSNode::getName() const
{
	return name;
}  // end getName

bool FSNode::isFile() const
{
	return (type == FILE_TYPE);
} // end isFile

bool FSNode::isDirectory() const
{
	return (type == DIR_TYPE);
} // end isDirectory

bool FSNode::addChild(std::shared_ptr<FSNode> childPtr)
{
	bool rValue = false;

	if (childPtr != nullptr 
		&& isDirectory() // can't add child to directory
		&& getChild(childPtr->getName()) == nullptr) // don't allow duplicate children
	{
		// Keep children sorted
		unsigned int pos = 0;
		while ((pos < children.size()) && (children[pos]->getName() < childPtr->getName()))
		{
			pos++;
		}
		children.insert(children.begin() + pos, childPtr);

		rValue = true;
	}

	return rValue;
}  // end addChild


std::shared_ptr<FSNode> FSNode::getChild(int index) const
{

	if (index >= 0 && index < static_cast<int>(children.size()))
	{
		return children[index];
	}

	return nullptr;
}  // end getChild	

std::shared_ptr<FSNode> FSNode::getChild(std::string pName) const
{

	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i]->getName() == pName)
			return children[i];
	}

	return nullptr;
}  // end getChild

int FSNode::getNumChildren() const
{
	return children.size();
} // end getNumChildren

bool FSNode::removeChild(const std::string& pName)
{
	if (isDirectory())
	{
		for (unsigned int i = 0; i < children.size(); i++)
		{
			if (children[i]->getName() == pName)
			{
				children.erase(children.begin() + i);
				return true;
			}
		}
	}

	return false;
} // end removeChild
