/*
 * SiEd - A text editor for PalmOS 3.5+ Copyright (C) 2003 Benjamin Roe
 * Contact Email:ben@benroe.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef ROOTDIRNODE_HPP
#define ROOTDIRNODE_HPP
#include "dirnode.h"
#define PDB_TYPE 'DATA'


class root_SiDirNode : public SiDirNode
{
public:
	root_SiDirNode();
	virtual SiFile* get_file(Char * filename) DIALOG_SECTION;
	virtual SiFile* create_file(Char * filename,UInt32 size) DIALOG_SECTION;
	virtual void populate() DIALOG_SECTION;
	virtual SiDirNode * get_copy() DIALOG_SECTION;
	virtual Char * get_path(UInt16 type) DIALOG_SECTION;
protected:
	void add_vfs_volumes() DIALOG_SECTION;
	void add_pdb_files() DIALOG_SECTION;
	void add_doc_files() DIALOG_SECTION;
	void add_databases_by_type(SiDirNode * node,UInt32 creator,UInt32 type) DIALOG_SECTION;

};
#endif
