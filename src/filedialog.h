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
#include "file_interface.h"
#include "dirnode.h"
#define STANDARD 0
#define EXCLUDE_LEAF_NODE 1
#define INCLUDE_CARD 2
enum {SAVE_FILE,OPEN_FILE,MANAGE_FILE};
#define ENCRYPTED 1


void drawFileName(Int16 itemNum, RectangleType * bounds, Char ** itemsText) DIALOG_SECTION;
class SiFileDialog
{
public:
	static void initialise()  DIALOG_SECTION;
	static SiFile * ShowOpenFileDialog(const char* initial_dir,UInt16 vol) DIALOG_SECTION;
	static SiFile * ShowSaveFileDialog(const char * initial_filename,const char* initial_dir,const UInt32 size,UInt16 vol) DIALOG_SECTION;
	static SiFile* ShowFileManageDialog(Char * location,UInt16 vol) DIALOG_SECTION;
	static Boolean handle_list_select(const Int16 num) DIALOG_SECTION;
	static Boolean handle_button_press(const UInt16 button) DIALOG_SECTION;
	static void switch_to_dir(UInt16 num) DIALOG_SECTION;
	static void move_up_dir() DIALOG_SECTION;
	static Boolean list_selection_is_file(const UInt16 sel) DIALOG_SECTION;
	static Boolean get_update_dir_display()  DIALOG_SECTION;
	static void Beam(const UInt16 id) DIALOG_SECTION;
	static void exit() DIALOG_SECTION;
	static void initialise_dir_field() DIALOG_SECTION;
	static void set_open_field(SiDirNode* node) DIALOG_SECTION;
	#ifdef TEST_OBJECT_UNIT
	static void perform_tests() DIALOG_SECTION;
	#endif
	
	//static SiFile* popup_file_list(const Int16 x,const Int16 y) DIALOG_SECTION;
protected:
	static void check_decrypt_button(const Int16 num) DIALOG_SECTION;
	static void show_manage_buttons() DIALOG_SECTION;
	static Boolean check_selected_file() DIALOG_SECTION;
	static void tidy() DIALOG_SECTION;
	static void set_working_dir(SiFile * t_file) DIALOG_SECTION;
	static void make_current_path(Char * path) DIALOG_SECTION;
	static Char * get_next_name(const Char * location,Int16 & start_pos,const Int16 len);
	friend void drawFileName(Int16 itemNum, RectangleType * bounds, Char ** itemsText) DIALOG_SECTION;
	static SiDirNode * curr_node ;
	static void handle_new_dir() DIALOG_SECTION;
	static Char *show_save_form(const Char * initial_dir,UInt16 vol) DIALOG_SECTION;
	static UInt16 show_open_form(const Char * initial_dir,UInt16 vol) DIALOG_SECTION;

	static void initialise_list(const Char * initial_dir,UInt16 vol) DIALOG_SECTION;
	static SiDirNode * parse_path(const Char * path,UInt16 vol) DIALOG_SECTION;

	static void set_dir_field(SiDirNode* node) DIALOG_SECTION;
	static void populate_node(SiDirNode * node) DIALOG_SECTION;
	static void make_current_node(SiDirNode* node) DIALOG_SECTION;
	static void redraw_list() DIALOG_SECTION;
	static Boolean display_file_select(const fontID font,Char * filename) DIALOG_SECTION;

	static void draw_data_display(UInt16 num) DIALOG_SECTION;
	static SiDirNode* get_node(const Char * initial_dir,UInt16 vol)  DIALOG_SECTION;

	static void clear_data_display() DIALOG_SECTION;
	static Boolean valid_file_name(const char *name) DIALOG_SECTION;

	static void handle_decrypt_file() DIALOG_SECTION;
	static void handle_rename() DIALOG_SECTION;
	static void handle_delete() DIALOG_SECTION;
	static void show_buttons() DIALOG_SECTION;
	static void clear_selection() DIALOG_SECTION;
	static Boolean update_dir_display;
	static Int16 file_selected;
	static Char * curr_path;
	static UInt32 current_volume ;
	//		static SiFile * create_file_record(const char * location);
	static TimeFormatType TIME_STYLE ;
	static DateFormatType DATE_STYLE ;
	static Boolean VFS_SUPPORT ;
	static UInt16 dialog_mode;
	static UInt16 save_options;
	static Char * working_dir;
	static UInt16 working_vol;

	static const Char * m_initial_filename;
};
