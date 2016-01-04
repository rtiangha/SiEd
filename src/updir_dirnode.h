#ifndef UPDIRDIRNODE_HPP
#define UPDIRDIRNODE_HPP
#include "dirnode.h"

class updir_SiDirNode : public SiDirNode
{
public:
	updir_SiDirNode() DIALOG_SECTION;
	~updir_SiDirNode() DIALOG_SECTION;
	virtual SiFile * get_file(Char * filename) DIALOG_SECTION;
	virtual SiFile * create_file(Char * filename,UInt32 size) DIALOG_SECTION;
	virtual SiDirNode* get_copy() DIALOG_SECTION;
};
#endif
