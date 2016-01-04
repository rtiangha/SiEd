//
// C++ Interface: sidocument
//
// Description:
//
//
// Author: Benjamin Roe <sied@benroe.com>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SIDOCUMENT_H
#define SIDOCUMENT_H
#include <PalmOS.h>
#include <PalmTypes.h>
#include "types.h"
#include "sections.h"
#define NOT_CALC -1

class SiTextView;
/**
@author Benjamin Roe
*/
enum {TEXT_MODIFIED,TEXT_DELETED,LINE_DELETED,LINE_INSERTED};

class SiTextChange
{
public:
	Position start;
	Position end;
	Int16 type;
};

class SiDocument
{
public:
	SiDocument() TEXT_SECTION;

	~SiDocument() TEXT_SECTION;
	block * get_line(const Int16 line,Int16 & b_b_index) TEXT_SECTION;
	void release_line(Int16 b_b_index) TEXT_SECTION;

	Int16 get_number_blocks() const TEXT_SECTION;
	UInt32 get_doc_length() TEXT_SECTION;
	UInt32 get_number_chars() TEXT_SECTION;
	Boolean insert_block_at_end(SiMemChunk * chunk,BlockInt n_chars) TEXT_SECTION;
	void made_change(const Position start,const Position end) TEXT_SECTION;
	Int16 get_start_index(block_buffer * b_buffer)  TEXT_SECTION;
	//Cursor positioning
	void move_position(Position & pos,Int16 amount,Boolean new_line=true,Boolean is_cursor=true) TEXT_SECTION;
	void make_valid_pos(Position & p) TEXT_SECTION;
	void remove_block_buffer(block_buffer* b_buffer)  TEXT_SECTION;
	void move_to_prev_block(const Int16 line, block * src_block,block * dst_block,const BlockInt byte_offset,const BlockInt char_offset) TEXT_SECTION;
	inline Boolean wrap_back(Position  start_pos,Position & first_change_pos,Position & cursor_pos,Boolean & increase_redraw) TEXT_SECTION;
	void correct_position(Position & p) TEXT_SECTION;
	void remove_empty_lines() TEXT_SECTION;
	void move_up_data(block * b,const Position pos,const BlockInt bytes) TEXT_SECTION;
	void move_down_data(block * b,const Position pos,const BlockInt bytes) TEXT_SECTION;
	void check_eff_insert_line(Int16 start_line,BlockInt char_offset) TEXT_SECTION;
	Boolean move_to_next_block(const BlockInt char_offset,const BlockInt byte_offset,const Int16 start_line) TEXT_SECTION;
	void free_text()  TEXT_SECTION;
	
	Position tidy_lines(const Position start_pos,const BlockInt byte_offset,Position & first_change_pos,Position & cursor_pos) TEXT_SECTION;
	
	Boolean tidy_line_too_long(Position start_pos,BlockInt  byte_offset,Int16 & curr_width,Boolean & changed,Boolean * increase_redraw) TEXT_SECTION;
	
	Position tidy_line_too_short(const Int16 line,Int16 & curr_width,Boolean & changed,Boolean & increase_redraw) TEXT_SECTION;
	BlockInt find_prev_delimiter(const Char * data,const BlockInt start_offset,BlockInt & char_offset) TEXT_SECTION;
	Boolean find_delimiter(const SiMemChunk * chunk,BlockInt start_offset) TEXT_SECTION;
	void check_new_broken_word( Position start_pos,Position & cursor_pos,Boolean & changed,Position & first_change_pos) TEXT_SECTION;
	void check_final_block_allocated() TEXT_SECTION;
	Char * get_char_bound(const Int16 index,Char* data,const BlockInt char_offset,BlockInt *offset) TEXT_SECTION;
	WChar get_char(Int16 line,block *b,const BlockInt offset) TEXT_SECTION;
	Boolean inserted_text(const BlockInt n_chars,const BlockInt n_bytes,const Int8 grow) TEXT_SECTION;
	//void removed_block() TEXT_SECTION;
	//void added_block() TEXT_SECTION;

	Boolean file_dirty() const  TEXT_SECTION;
	void clear_dirty_flag()  TEXT_SECTION;
	void set_dirty_flag()  TEXT_SECTION;
	Position find_end_line(const Int16 line) TEXT_SECTION;
	void check_newline_position(Position& p,const Int16 dir)  TEXT_SECTION;
	const Char * get_stripped_text(const Position start,const Position end, const BlockInt max_chars) TEXT_SECTION;
	void insert_block(const Int16 prev_line) TEXT_SECTION;

	void remove_block(const Int16 line) TEXT_SECTION;
	void remove_text_range(const Int16 line,const BlockInt  start_x,BlockInt  end_x) TEXT_SECTION;
	Position find_end_document()  TEXT_SECTION;
	Boolean has_done_insert() const TEXT_SECTION;
	void ready_for_change() TEXT_SECTION;

	void invalidate_cache() TEXT_SECTION;
	//	void check_cache(const Int16 start_line,const Int16 end_line) TEXT_SECTION;


	Boolean ensure_allocated(Int16 index) TEXT_SECTION;

	void clear_changes() TEXT_SECTION;
	SiTextChange * get_next_change() TEXT_SECTION;

	Boolean get_done_insert() const TEXT_SECTION;
	void set_view(SiTextView * view) TEXT_SECTION;
	const Char * get_initial_filename() TEXT_SECTION;
	void finished_initial_opening() TEXT_SECTION;
#ifdef TEST_OBJECT_UNIT
	Boolean perform_tests() TEXT_SECTION;
#endif
	void set_opening_file_mode() TEXT_SECTION;
	void clear_opening_file_mode() TEXT_SECTION;
	Int16 get_apparent_number_blocks() const TEXT_SECTION;
	void set_apparent_number_blocks(const Int16 num) TEXT_SECTION;
	Boolean ensure_tidied(const Int16 line) TEXT_SECTION;
	void tidy_up_lines(Int16 line) TEXT_SECTION;
	Int16 last_line_tidied;
	Boolean has_had_memory_error() const TEXT_SECTION;
	void set_memory_error(Boolean m) TEXT_SECTION;
private:

	Boolean line_ends_with_line_feed(const Int16 l) TEXT_SECTION;
	
	
	Boolean ends_in_line_feed(const Int16 l) TEXT_SECTION;
	void allocate_new_block_buffers(const Int16 num) TEXT_SECTION;
	block_buffer* get_block_buffer(const Int16 line,Int16 * start_index,Int16 &b_b_index) TEXT_SECTION;
	//internal state
	SiTextChange * text_change_list;
	MemHandle text_change_handle;
	UInt16 number_changes;
	UInt16 curr_change;
	Boolean dirty_flag;
	UInt32 max_char;
	UInt32 document_length;
	Int16 number_blocks;
	Int16 number_block_buffers;

	//data
	MemHandle block_buffer_array_handle;
	block_buffer* block_buffer_array;

	//cache
	block_buffer* prev_locked_block_buffer;
	Int16 prev_locked_start_index;
	//Int16 cached_get_line_index;
	//nt16 cached_line_block_buffer_index;
	//Int16 cached_line_start_index;
	//Int16 prev_locked_line;
	SiTextView * m_text_view;

	#ifdef USE_CHAR_CACHE
	Int16 cached_get_char_block_index;
	BlockInt cached_bound_offset;
	BlockInt cached_bound_byte_offset;
	#endif

	Boolean allow_change_add;
	Boolean done_insert;
	#ifdef USE_LINE_CACHE
	Int16 cached_get_line_index;
	Int16 cached_line_block_buffer_index;
	Int16 cached_line_start_index;
	#endif
	Boolean m_opening_file;
	Int16 apparent_number_blocks;
	Int32 line_width_estimate;
	Int32 n_lines_estimated;
	Boolean m_memory_error_occurred;
	Boolean m_background_tidy;
	
};

#endif
