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
#include "dirnode.h"
#ifndef PDB_SIDIRNODE_HPP
#define PDB_SIDIRNODE_HPP

class pdb_SiDirNode : public SiDirNode
{
public:
	pdb_SiDirNode(Char * filename);
//	virtual SiFile * get_file(Char * filename)  DIALOG_SECTION;
	virtual SiFile * create_file(Char * filename,UInt32 size)  DIALOG_SECTION;
	virtual UInt32 get_file_size()  DIALOG_SECTION;
	virtual UInt32 get_file_date()  DIALOG_SECTION;
	virtual SiDirNode * get_copy() DIALOG_SECTION;
	virtual Int16 get_position_index() DIALOG_SECTION;
};

#endif
