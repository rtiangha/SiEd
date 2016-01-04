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
#ifndef DOCFILE_HPP
#define DOCFILE_HPP
#include "pdb_file_interface.h"



class doc_SiFile: public pdb_SiFile
{
public:
	doc_SiFile(const Char * name,const Char * location,const UInt16 volRefNum);
	doc_SiFile(const Char * name,const Char * location,const UInt16 volRefNum,const UInt32 size);
	virtual ~doc_SiFile();

	virtual void open() ;
	virtual void resize(const UInt32 size) FILE_SECTION;

	virtual UInt32 get_size() FILE_SECTION;
	virtual void move_cursor(const Int32 amount,const Int16 dir) FILE_SECTION;
	virtual void set_access_mode(const Int16 mode) FILE_SECTION;
protected:
	void remove_last_record() FILE_SECTION;
	UInt16 last_record_remaining_space() FILE_SECTION;
	UInt16 last_record_size() FILE_SECTION;
	void update_record_cursor(const UInt16 amount,const Int16 dir) FILE_SECTION;
	void resize_last_record(const Int32 size_to_add) FILE_SECTION;
	Boolean read_header() FILE_SECTION;
	Boolean write_header() FILE_SECTION;

	Boolean add_records(const UInt32 total_size) FILE_SECTION;
	Boolean remove_records(const UInt32 total_size) FILE_SECTION;
	virtual Boolean create_database(const UInt32 size) FILE_SECTION;

	virtual void write_direct(const SiMemChunk * const chunk);
	virtual Int16 read_direct(SiMemChunk * chunk);
	void lock_next_record() FILE_SECTION;
	void lock(const UInt16 text_record)
		FILE_SECTION;

	UInt16 header_size;
	UInt16 curr_record_size;
	UInt16 curr_record_cursor;
};
#endif
