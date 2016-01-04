
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
#include "types.h"
#include "sections.h"
#include "sidocument.h"

#ifndef TEXTHANDLER_HH
#define TEXTHANDLER_HH


enum {INSERTED_TEXT,DELETED_TEXT};

class SiUndoAction
{
public:
	SiUndoAction() TEXT_SECTION;
	~SiUndoAction() TEXT_SECTION;
	SiMemChunk * text;
	Position start_position;
	Position start_undone_position;
	Position end_position;
	UInt8 status;
	SiUndoAction * next;
	SiUndoAction * prev;
};

//forward declare SiEditor here
class SiEditor;

class SiTextHandler
{
public:
	SiTextHandler()  TEXT_SECTION;
	~SiTextHandler()  TEXT_SECTION;
	void initialise()  TEXT_SECTION;

	//document editing functions
	Boolean insert_chars(const Char* c,const BlockInt n_chars,const BlockInt n_bytes,Position  ch,Position & f_cursor_pos) TEXT_SECTION;
	Position delete_chars(Position start,Position end) TEXT_SECTION;

	//Undo functions
	Boolean undo(Position & f_cursor_pos) TEXT_SECTION;
	Boolean redo(Position & f_cursor_pos) TEXT_SECTION ;

	//Document data get functions

	Position get_prev_pos(Position p) TEXT_SECTION;
	Position get_next_pos(Position p) TEXT_SECTION;
	UInt32 get_number_words(UInt32 & alphanum_chars) TEXT_SECTION;

	Position find_prev_word_boundary(Position start,const Boolean ignore_punctuation=true) TEXT_SECTION;
	Position find_next_word_boundary(Position start,const Boolean ignore_punctuation=true) TEXT_SECTION;

	WChar get_charAtpos(Position &p) TEXT_SECTION;
	WChar get_charBeforepos(Position &p) TEXT_SECTION ;
	SiDocument * get_document() TEXT_SECTION;
	
#ifdef TEST_OBJECTS
	Boolean perform_tests() TEXT_SECTION;
#endif

	void enable_undo_history() TEXT_SECTION;
	void disable_undo_history() TEXT_SECTION;


private:
	SiUndoAction * create_undo_action() TEXT_SECTION;
	Boolean ensure_undo_space(const BlockInt n_bytes) TEXT_SECTION;
	//BlockInt paste_efficiency_hack(const BlockInt line,const BlockInt n_chars) TEXT_SECTION;
	Boolean find_delimiter(const SiMemChunk * chunk,BlockInt start_offset)TEXT_SECTION;
	void free_text() TEXT_SECTION;
	Boolean validate_position(Position & p) TEXT_SECTION;

	void remove_text_range(const Int16 line,const BlockInt  start_x,BlockInt  end_x) TEXT_SECTION;
	Boolean remove_blocks(const Int16 start_line,const Int16 end_line) TEXT_SECTION;
	block* insert_new_blocks(const Int16 num) TEXT_SECTION;

	
	//line handling
	//	void remove_block(const Int16 line) TEXT_SECTION;


	Boolean add_undo_action(const Char * text,const BlockInt bytes,Position start_pos,Position end_pos,UInt8 type) TEXT_SECTION;
	Boolean append_text_undo_action(const Char * text,const BlockInt bytes) TEXT_SECTION;
	Boolean remove_last_undo_action() TEXT_SECTION;

	void clear_undo_history() TEXT_SECTION;
	void clear_actions_after(SiUndoAction * action) TEXT_SECTION;
	void perform_action(SiUndoAction * action,Boolean reverse,Position & f_cursor_pos) TEXT_SECTION;
	void change_undo_action_end(Position end_pos) TEXT_SECTION;
	void change_undo_action_start(Position pos) TEXT_SECTION;
	//sloshing
	void invalidate_cache() TEXT_SECTION;
	void add_block_delete_undo(const Int16 line) TEXT_SECTION;
	//Internal state data

	Position undo_position_start;
	Position undo_position_end;
	Boolean undo_undone;
	Int16 undo_action;
	Boolean undo_active;
//	Int16 insert_block_curr_width;

	//document data storage
	//MemHandle block_buffer_array_handle;
	SiUndoAction * undo_action_list;
	SiUndoAction * curr_undo_action;
	SiUndoAction * last_undo_action;
	SiDocument * m_document;
	UInt16 undo_memory_usage;

	DmOpenRef m_database;
	LocalID m_dbID;


};
#endif
