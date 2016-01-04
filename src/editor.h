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
#include "textview.h"
#include "texthandler.h"
#include "filehandler.h"
#include "file_interface.h"
#include <PalmOS.h>
#include <PalmTypes.h>
#include "sidocument.h"
#include "preferences.h"
#include "minibuffer.h"
#ifndef EDITOR_HH
#define EDITOR_HH
#define SIZE_TEST 100
#define NO_ITERATIONS 3000000
class SiKeyboard;
Boolean keyboardEventLoop(EventPtr event);
enum { VERTICAL,HORIZONTAL };

struct Position;
struct block;

class SiEditor
{
public:
	// SiEditor(const Int16 height, const Int16 top_y, const UInt16 index);
	SiEditor(const Int16 height, const Int16 top_y, const UInt16 index) EDIT_SECTION;
	~SiEditor() EDIT_SECTION;
	void resize(const Int16 height, const Int16 top_y) EDIT_SECTION;
	void set_ignore_events() EDIT_SECTION;
	void clear_ignore_events() EDIT_SECTION;

	//event handling
	Boolean handle_key(const WChar keycode, const UInt16 modifiers) EDIT_SECTION;
	void handle_scroll(const Int16 old_v, const Int16 new_v) EDIT_SECTION;
	void handle_menu_command(const UInt16 id)  EDIT_SECTION;
	void handle_commandbar_popup()  EDIT_SECTION;

	void give_focus() EDIT_SECTION;
	void lost_focus() EDIT_SECTION;

	const Char * get_initial_filename() EDIT_SECTION;
	//notifications
	void notify_block_deleted(const Int16 line) EDIT_SECTION;
	void redraw() EDIT_SECTION;
	void set_scrollbar(UInt16 id) EDIT_SECTION;
	//event handlers
	void handle_tap(Coord x, Coord y,Int16 n_taps) EDIT_SECTION;
	Position get_min_selected_position() const EDIT_SECTION;
	Position get_max_selected_position() const EDIT_SECTION;
	Char* get_filename() EDIT_SECTION;
	fontID get_font() const EDIT_SECTION;
	void initialise() EDIT_SECTION;
	//void redraw();
	void handle_cursor_movement(const UInt16 direction,const Int16 amount, const UInt16 mod) EDIT_SECTION;
	void delete_forward_cursor(const UInt16 mod) EDIT_SECTION;
	void delete_backward_cursor(const UInt16 mod) EDIT_SECTION;
	void redraw_chrome(Boolean force=true) EDIT_SECTION;
	//public state for speed
	Int16 HEIGHT;
	Int16 TOP_Y, BOTTOM_Y;
	Int16 COMMAND_LINE;

	void toggle_find_whole_word() EDIT_SECTION;
	void toggle_find_match_case() EDIT_SECTION;
	void toggle_find_from_top() EDIT_SECTION;
	Boolean point_in_drag_area(const Int16 x,const Int16 y) EDIT_SECTION;
	void initialise_replace_fields() EDIT_SECTION;
	Boolean finished_processing() const EDIT_SECTION;
	void do_quick_slosh() EDIT_SECTION;

	#ifdef TEST_OBJECT_UNIT
	Boolean perform_tests() EDIT_SECTION;
	void test_undo() EDIT_SECTION;
	void test_replace() EDIT_SECTION;
	void test_large_insert() EDIT_SECTION;
	void test_char_insert() EDIT_SECTION;
	void test_word_wrap() EDIT_SECTION;
	void insert_test_text() EDIT_SECTION;
	void test_reopen() EDIT_SECTION;
	void test_find() EDIT_SECTION;
	void test_clipboard() EDIT_SECTION;
	void test_selection() EDIT_SECTION;
	void test_redraw() EDIT_SECTION;
	void test_controls() EDIT_SECTION;
	void test_file_save() EDIT_SECTION;
	#endif

	#ifdef BENCH_OBJECTS
	Boolean perform_benchmark()  EDIT_SECTION;
	#endif
	UInt8 m_index;
	void erase_not_found() EDIT_SECTION;
	void resize_for_dialog(const Int16 height) EDIT_SECTION;

	void return_to_original_size() EDIT_SECTION;
	void finished_replace() EDIT_SECTION;
	Boolean is_displaying_dialog() const EDIT_SECTION;
	void reset_from_top_find() EDIT_SECTION;
	void read_preferences(Char * file_to_open) EDIT_SECTION;
	void make_cursor_visible() EDIT_SECTION;

	//editor actions interface (callable from some mythical macro language one day)
	void clear_selection() EDIT_SECTION ;
	Boolean delete_selection() EDIT_SECTION ;
	void undo() EDIT_SECTION;
	void redo() EDIT_SECTION;
	void paste_clipboard() EDIT_SECTION ;
	void move_cursor_to(Position pos) EDIT_SECTION ;
	void save_current_file() EDIT_SECTION ;
	void change_font(const fontID font) EDIT_SECTION;
	void start_waiting() EDIT_SECTION;
	void stop_waiting() EDIT_SECTION;
	Boolean replace_text(Char * rep_text,Char * with_text,const Boolean show_end) EDIT_SECTION;
	Boolean find_term(char *term) EDIT_SECTION;
	void replace_all(Char * rep_text,Char * with_text) EDIT_SECTION;
	void insert_chars(const Char * data, const BlockInt n_chars,const BlockInt n_bytes) EDIT_SECTION;
	void delete_chars(const Position start,const Position end) EDIT_SECTION;
	void set_selection(const Position start,const Position end) EDIT_SECTION;
	Boolean get_read_only() EDIT_SECTION;
private:

	void set_viewport() EDIT_SECTION;
	void show_replace_controls() EDIT_SECTION;
	void hide_replace_controls() EDIT_SECTION;

	void do_scroll(const Int16 amount,const Boolean scroll,const Boolean quick=true) EDIT_SECTION;
	void scroll_page(const Int16 dir,const UInt16 modifiers) EDIT_SECTION;
	Boolean handle_inc_search_key(WChar the_char) EDIT_SECTION;
	void do_incremental_search() EDIT_SECTION;
	void stop_inc_search() EDIT_SECTION;
	void set_field_term(FieldType* text_field,MemHandle handle,Boolean set_selection);
	//	void copy_field_term(FieldType * text_field,MemHandle &handle);
	void check_scroll_position() EDIT_SECTION;
	void do_open_file() EDIT_SECTION;
	void do_save_file_as() EDIT_SECTION;
	Boolean save_doc_file(Char * name) EDIT_SECTION;
	Boolean open_doc_file(Char * name) EDIT_SECTION;
	void do_file_manage() EDIT_SECTION;
	void save_preferences() EDIT_SECTION;
	void do_new_file() EDIT_SECTION;
	void delete_line(const Int16 line) EDIT_SECTION;
	void select_word(Coord x,Coord y) EDIT_SECTION ;
	Boolean ui_tap(Coord x,Coord y) EDIT_SECTION ;

	void update_word_count() EDIT_SECTION ;
	void draw_stats_data() EDIT_SECTION ;
	void revert_curr_file() EDIT_SECTION ;
	Boolean point_in_line_number(Coord x,Coord y) EDIT_SECTION ;
	void select_current_word() EDIT_SECTION ;
	Boolean ensure_tidied(const Int16 line) EDIT_SECTION ;
	//search and replace
	Boolean do_replace_replace_next(Boolean show_end) EDIT_SECTION ;
	void do_replace_find_next() EDIT_SECTION;
	void do_replace_replace_all() EDIT_SECTION;

	friend Boolean replaceEventLoop(EventPtr event) EDIT_SECTION;
	friend Boolean stats_dialog_loop(EventPtr event) EDIT_SECTION;
	//editor state data get functions
	void set_open_file() EDIT_SECTION ;
	//Position get_start_selected_position() const;
	//Position get_end_selected_position() const;
	Char * get_prev_search_term() EDIT_SECTION ;
	Position get_c_pos() const EDIT_SECTION;

	Boolean check_whole_word_match(Position, Position) EDIT_SECTION ;
	Boolean over_threshold(const Int16 x,const Int16 y) EDIT_SECTION ;
	void make_visible_selection(Position start_pos, Position end_pos) EDIT_SECTION;
	void popup_menu() EDIT_SECTION;
	void reopen() EDIT_SECTION;


	void display_stats_dialog() EDIT_SECTION;
	void update_cursor_pos(const Position& p,const Boolean erase) EDIT_SECTION;

	// cursor insertion/deletion functions
	void insert_ch_cursor(const WChar c) EDIT_SECTION;





	void notify_selection_changed() EDIT_SECTION ;
	void set_sizes(const fontID font_id) EDIT_SECTION;

	// selection/clipboard
	
	Boolean copy_selection_to_clipboard() EDIT_SECTION ;

	void set_end_selected_position(Position p,Boolean check_newline=true) EDIT_SECTION ;
	void set_start_selected_position(Position P) EDIT_SECTION ;
	void close_file(Boolean ask=false) EDIT_SECTION ;
	//dialogs
	//void do_find_dialog() EDIT_SECTION ;
	void do_replace_dialog() EDIT_SECTION ;
	void show_not_found() EDIT_SECTION ;
	void toggle_read_only_mode() EDIT_SECTION;
	void check_gsi_status() EDIT_SECTION;
	#ifdef NEW_LINE_OPTIONS
	Boolean do_new_line_insert(const WChar c) EDIT_SECTION;
	#endif
	Boolean valid_tap(const Int16 x, const Int16 y) EDIT_SECTION;
	#ifdef REPORT_MEM_USAGE
	void show_mem_usage() EDIT_SECTION ;
	#endif
	void do_typing() EDIT_SECTION;
	#ifdef COLLECT_STATISTICS
	
	void detailed_benchmarks() EDIT_SECTION;
	#endif


	//internal state data
	Position cursor_pos;
	Int16 preferred_cursor_x;

	Position start_selected_position;
	Position end_selected_position;

	Boolean ignore_events;
	SiTextView *m_text_view;
	SiFileHandler *m_file_handler;
	SiTextHandler *m_text_handler;
	//	MemHandle prev_search_term;
	//	MemHandle prev_replace_term;
	// find options
	Boolean find_option_match_case;
	Boolean find_option_whole_word;
	Boolean find_option_from_top;
	Boolean first_find;
	Boolean exiting;
	UInt8 selection_mode;
	SiKeyboard * m_keyboard;


	FieldPtr Altfield;
	FormPtr mfrm;
	fontID m_font_id;
	Int16 prev_height;

	SiDocument * m_document;
	Boolean m_incremental_search;

	SiMiniBuffer * m_mini_buffer;
	Boolean m_not_found;
	IndexedColorType m_not_found_colour;
	Int16 m_initial_height;
	Int16 m_initial_top;
	
	Boolean m_displaying_dialog;	
	Boolean m_has_found_term;
	Boolean m_read_only;
};

#endif
