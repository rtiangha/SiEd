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
#include <Preferences.h>
#include "sections.h"
#include "resources.h"
#ifndef FILEHANDLER_HH
#define FILEHANDLER_HH
#include "sidocument.h"
class SiEditor;
class SiTextHandler;
class SiFile;
Boolean filelistloop(EventPtr event);

class SiFileHandler
{
public:
	SiFileHandler(SiEditor * editor,SiDocument * doc) FILE_SECTION;
	~SiFileHandler() FILE_SECTION;
	void write_to_scratch(const Int16 index) FILE_SECTION;
	//SiFile* save_file() FILE_SECTION;

	Boolean do_open_file(Char * initial_dir,UInt16 vol) FILE_SECTION;
	Boolean do_file_manage(Char * location,UInt16 vol) FILE_SECTION;
	void clear_open_filename() FILE_SECTION;
	Boolean open_saved_filename() FILE_SECTION;
	Boolean save_file_as(Char * initial_dir,UInt16 vol) FILE_SECTION;
	Boolean save_doc_file(Char * name) FILE_SECTION;
	Boolean open_doc_file(Char * name) FILE_SECTION;
	static Boolean valid_file_name(const char *name)  FILE_SECTION;
	void read_from_scratch(const Int16 index) FILE_SECTION;
	Boolean save_file() FILE_SECTION;
	Boolean read_file() FILE_SECTION;
	Boolean read_file(Char *file,const Int16 type,UInt16 vol_ref) FILE_SECTION;
	SiFile* get_file() FILE_SECTION;
	Char * get_location() FILE_SECTION;
	UInt16 get_vol_ref() FILE_SECTION;
	void clear_curr_file() FILE_SECTION;
	void delete_scratch_file(const Int16 index) FILE_SECTION;
	Boolean file_is_read_only() FILE_SECTION;
#ifdef TEST_OBJECTS
	Boolean perform_tests() FILE_SECTION;
#endif
protected:
	Boolean open_file(SiFile* t_file) FILE_SECTION;
	Boolean check_save_curr_file() FILE_SECTION;
	void set_curr_file(SiFile * file) FILE_SECTION;
	Char * strip_path(Char * location) FILE_SECTION;
	Boolean read_data(SiFile * src) FILE_SECTION;
	Boolean save_if_necessary() FILE_SECTION;
	Boolean handle_button_event(const UInt16 button) FILE_SECTION;

	Int16 file_selected ;
	SiEditor * m_editor ;
	SiFile * curr_file;
	SiDocument * m_document;
	Boolean m_temporary_file;
};

#endif
