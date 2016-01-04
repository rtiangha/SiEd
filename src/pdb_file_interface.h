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
#ifndef PDBFILE_HPP
#define PDBFILE_HPP
#include "file_interface.h"

class pdb_SiFile: public SiFile
{
public:
	pdb_SiFile(const Char * name,const Char * location,const UInt16 volRefNum);
	pdb_SiFile(const Char * name,const Char * location,const UInt16 volRefNum,const UInt32 size);

	virtual ~pdb_SiFile();
	virtual UInt32 get_mod_time() FILE_SECTION;
	;
	virtual void close() FILE_SECTION;
	;
	virtual void delete_file() FILE_SECTION;
	virtual void rename(Char * new_name) FILE_SECTION;
protected:

	void unlock() FILE_SECTION;

	virtual Boolean create_database(const UInt32 size) FILE_SECTION;
	Boolean add_record(const UInt16 size);
	void startup() FILE_SECTION;
	;
	Boolean do_open() FILE_SECTION;
	;
	DmOpenRef m_open_ref;
	MemHandle m_curr_handle;
	Char * m_curr_locked;
	Boolean m_changed;
	LocalID m_id;
	UInt16 curr_record_index;
	UInt16 num_records;
};
#endif
