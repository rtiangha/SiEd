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
#include <UI/Form.h>
#ifndef TEXTVIEW_HH
#define TEXTVIEW_HH
#define PERCENTAGE_LIST_LENGTH 5
#include "types.h"
#include "sections.h"
#include "sidocument.h"
class SiTextHandler;
class SiEditor;

class SiTextView
{
public:
	//SiTextView(SiEditor * editor, SiTextHandler * texthandle) ;
	SiTextView(SiEditor * editor, SiDocument * doc) ;
	~SiTextView() ;
	void initialise_display() FILE_SECTION;
	void set_scrollbar(ScrollBarType * sb,UInt16 index);
	void start_waiting();
	void stop_waiting();
	//notifications
	void notify_cursor_moved(const Position cursor_pos, Boolean erase) UTIL_SECTION;
	void notify_block_deleted(const Int16 line) UTIL_SECTION;
	void notify_block_inserted(const Int16 line) UTIL_SECTION;
	void notify_text_deleted(const Int16 line,const BlockInt start_x)UTIL_SECTION;
	void notify_text_changed(Position start,Position end) UTIL_SECTION;
	Boolean notify_scrolled(Int16 a, Boolean scroll,Boolean quick=true) UTIL_SECTION;
	void notify_size_changed() UTIL_SECTION;
	void notify_saved() UTIL_SECTION;
	void notify_lost_focus() UTIL_SECTION;
	void notify_got_focus() ;
	void notify_font_changed() UTIL_SECTION ;
	void notify_selection_cleared();
	
	//void notify_selection_cleared(Position min_pos,Position max_pos) FILE_SECTION;

	//document data get functions

	void set_filename_dirty();
	Position find_position(const Int16 x,const Int16 y) ;
	DrawPosition find_draw_position(Position p) ;

	Position find_vertical_cursor_position(Int16 line) ;

	Int16 get_top_line() ;

	//screen drawing controls
	void enable_screen_updates() ;
	void disable_screen_updates() ;
	void clear_screen() UTIL_SECTION;
	void redraw_selection(Position prev_p,Position p);
	void redraw_display(const Boolean redraw_scroll=false);
	void redraw_text();
	void redraw_chrome(Boolean force=true);
	void ensure_visible(BlockInt line);

	void erase_cursor() ;
	void redraw_cursor() ;
	Boolean point_in_save_star(Coord x,Coord y);
	Boolean point_in_file_name(Coord x,Coord y);
	Int16 point_in_line_number(Coord x,Coord y);
	void make_top_line(BlockInt line,Boolean always);
	Position get_last_redraw_position();
	Boolean point_in_drag_area(const Int16 x,const Int16 y);
	Int16 get_status_y();
	void draw_status_line_number();
	void clear_self() UTIL_SECTION;
	void draw_status_read_only();
private:

	void draw_waiting();
	void done_waiting();
	void update_scrollbar(const Int16 line) ;
	void update_scrollbar();
	void clear_after_line(const BlockInt line,Boolean tidy_end);
	void redraw_between(Position &min_pos,Position &max_pos) ;
	Boolean is_onscreen(const Int16 line) const;
	//internal drawing functions
	//void draw_between(Position start,Position end) ;
	void draw_block(DrawPosition draw_pos,const Position text_pos,BlockInt  max) ;

	void fill_tab(const Int16 x, const Int16 curr_line,
				  const Int16 right_edge) ;
	void clear_tab_space(const Int16 x, const Int16 curr_line,
						 const Int16 right_edge) ;
	void tidy_end_line(Int16 line);
	void scroll_up(const Int16 lines) UTIL_SECTION ;
	void scroll_down(const Int16 lines) UTIL_SECTION ;
	void clear_line(DrawPosition start) UTIL_SECTION;
	void clear_line(Int16 line) UTIL_SECTION;
	void clear_line(DrawPosition start, const Int16 right) UTIL_SECTION;
	void draw_sel_block(const DrawPosition p,const Int16 thick) UTIL_SECTION ;
	void quick_scroll_display(Int16 n_lines) UTIL_SECTION;
	void get_resources() UTIL_SECTION;
	void redraw_text_view();
	void tidy_start_line(Int16 line);
	Int16 get_y(Int16 text_line);
	Int16 draw_EOL(DrawPosition p,const Boolean invert);
	void DrawSelectedChars(const Char * chars,Int16 len,Coord x,Coord y);
	//cursor drawing
	void get_cursor_window();
	void draw_status_asterisk();
	void draw_status_lines();
	void draw_status_filename();

	void draw_status_controls();
	void draw_cursor(DrawPosition p) ;
	void draw_status_dis(Boolean force) ;
	void exit_display() FILE_SECTION;
	void clear_sel_block(const DrawPosition p,const Int16 thick);
	Boolean change_onscreen(SiTextChange * change);
	Boolean focused;
	void initialise(SiEditor * editor, SiDocument * doc) ;

	void clear_last_lines();

	//internal screen state
	MemHandle text_buff;
	Int16 prev_dis_width;
	RectangleType rp;
	RectangleType cont_r;
	RectangleType clear_rect;
	Int16 line_height;
	Int32 top_line;
	Int16 last_offset;
	DrawPosition cursor_location;
	Boolean filename_dirty;
	Int16 status_cursor_line;
	Int16 status_last_line;
	WinHandle cursor_backing_store;
	//WinHandle scroll_backing_store;
	Position prev_frame_selected_position;
	Int16 prev_document_number_blocks;
	SiDocument * m_document;
	SiEditor *m_editor;
	UInt16 m_scroll_index;
	ScrollBarType *m_scrollbar;
	Int16 last_line;
	Boolean cursor_drawn;
	Boolean dirty_state;
	UInt32 min_index;
	UInt32 max_index;
	RectangleType star_pos;
	Boolean update_screen_enabled;
	Boolean scrollbar_visible;
	MemHandle return_rsc;
	MemHandle small_return_rsc;
	RectangleType screen_size;
	RectangleType old_screen_size;
	Boolean m_tidy_after;
	Int16 m_waiting_count;	
	
};

#endif
