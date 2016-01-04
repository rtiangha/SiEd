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
#include <PalmOS.h>
#include <PalmTypes.h>
#ifndef SIFILE_HPP
#define SIFILE_HPP
#include <Preferences.h>
#include "resources.h"
#include "dirnode.h"
#include "memhandler.h"
#include <VFSMgr.h>
class SiFilePlugin;

#define FILE_WRITE (vfsModeWrite|vfsModeTruncate|vfsModeCreate)
#define FILE_READ vfsModeRead

enum {FORWARDS,BACKWARDS,MOVE_TO};
enum {AT_END,AT_START};
#define NON_VFS 65000

class SiFile
{
public:
	SiFile(const Char * name,const Char * location,const UInt16 volRefNum)  FILE_SECTION;
	SiFile(const Char * name,const Char * location,const UInt16 volRefNum,const UInt32 size) FILE_SECTION;

	virtual ~SiFile();
	void add_plugin(SiFilePlugin * trans,const Int16 position)  FILE_SECTION;
	void delete_plugin(const Int16 position) FILE_SECTION;
	Char * get_name()  FILE_SECTION;
	Char * get_location()  FILE_SECTION;
	virtual UInt32 get_size()  FILE_SECTION;
	Boolean is_open()  FILE_SECTION;
	UInt16 get_type()  FILE_SECTION;

	virtual UInt32 get_mod_time() FILE_SECTION;
	virtual void open() FILE_SECTION;
	virtual void close() FILE_SECTION;
	virtual void set_access_mode(const Int16 mode) FILE_SECTION;

	void write_data(const SiMemChunk* const chunk) FILE_SECTION;
	SiMemChunk* read_data(BlockInt &n_chars) FILE_SECTION;

	virtual void move_cursor(const Int32 distance,const Int16 dir) FILE_SECTION;
	virtual void resize(const UInt32 size) FILE_SECTION;
	virtual void rename(Char * new_name) FILE_SECTION;
	virtual void delete_file() FILE_SECTION;

	//files actions bypassing plugins
	//should only be called by plugin classes
	virtual UInt16 get_vol_ref() FILE_SECTION;
	virtual void initialise(const Int16 file_mode) FILE_SECTION;
	virtual Int16 read_direct(SiMemChunk * chunk) FILE_SECTION;
	virtual void write_direct(const SiMemChunk * const chunk) FILE_SECTION;
	SiFilePlugin * is_encrypted() FILE_SECTION;
	static Boolean display_warnings;
	Boolean is_read_only();
protected:	
	void change_name(const Char * new_name)  FILE_SECTION;
	void change_location(const Char * new_location)  FILE_SECTION;
	void init(const Char * name,const Char * p_location)  FILE_SECTION;

	UInt32 m_file_size;
	UInt16 m_open_mode;
	Boolean m_is_read_only;
	UInt32 m_cursor;
	Char * m_name;
	Char * m_location;
	Boolean m_file_open;
	SiFilePlugin * m_trans;
	UInt16 m_type;

};
#endif
