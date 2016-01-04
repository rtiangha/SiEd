//
// C++ Interface: simacrorecorder
//
// Description:
//
//
// Author: Benjamin Roe <sied@benroe.com>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SIMACRORECORDER_H
#define SIMACRORECORDER_H
#include <PalmOS.h>
#include <PalmTypes.h>
#include "sections.h"
/**
@author Benjamin Roe
*/

class SiMacroRecorder
{
public:
	SiMacroRecorder() DIALOG_SECTION;
	Boolean give_event(EventPtr e) DIALOG_SECTION;
	~SiMacroRecorder() DIALOG_SECTION;
	void start_playback() DIALOG_SECTION;
	Boolean start_record() DIALOG_SECTION;
	void stop_record() DIALOG_SECTION;
	void draw_macro_name(const UInt16 num,RectangleType * pos);
	void delete_selected_macro() DIALOG_SECTION;
	Boolean check_valid() DIALOG_SECTION;
	void popup_macro_list() DIALOG_SECTION;
	Boolean recording;
	Boolean playing;
protected:
	void do_quick_macro(Char * the_char) DIALOG_SECTION;
	void draw_macro_active_rect() DIALOG_SECTION;
	void draw_macro_active_char(Char * text) DIALOG_SECTION;
	void erase_macro_active_rect() DIALOG_SECTION;
	void prepare_quick_macro() DIALOG_SECTION;
	Char * display_macro_select(Int16 & index,Int16 mode) DIALOG_SECTION;
	void close_macro_database() DIALOG_SECTION;
	Boolean open_macro_database() DIALOG_SECTION;
	Boolean add_macro_record(Char * name) DIALOG_SECTION;
	ListPtr initialise_list(FormPtr frm) DIALOG_SECTION;
	Boolean initialise_macro_record() DIALOG_SECTION;
	Boolean write_event_to_macro(EventPtr e) DIALOG_SECTION;
	Boolean handle_tap(EventPtr e) DIALOG_SECTION;

	Boolean play_macro(Int16 index) DIALOG_SECTION;
	void copy_event(EventPtr target,EventPtr source) DIALOG_SECTION;
	void initialise_macro_record(Char * name) DIALOG_SECTION;
	Boolean open_macro(Int16 index) DIALOG_SECTION;
	MemHandle macro_handle;
	Char * macro_name;

	UInt16 number_events;
	DmOpenRef open_ref;
	LocalID id;
	UInt16 curr_macro_index;
	UInt16 name_offset;
	UInt16 number_macros;
	Int16 dialog_mode;
	Boolean quick_macro_ready;
	Int16 list_draw_mode;

};

#endif
