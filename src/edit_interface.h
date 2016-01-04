#ifndef SIEDITINT_HPP
#define SIEDITINT_HPP
#include "editor.h"
#include "preferences.h"
#include "simacrorecorder.h"

class SiEditInterface
{
public:
	SiEditInterface(Char * file_to_open);
	~SiEditInterface();
	Boolean handle_event(EventPtr e);
	Boolean intercept_event(EventPtr e);
	void emit_redraw_signal(SiEditor * edit);
	Boolean split_screen();
	Boolean unsplit_screen();
	void change_font();
#ifdef PERFORM_TEST
	SiEditor *the_editor_active;
#endif
	Int32 get_event_delay();
	void do_quick_slosh();
#ifdef TEST_OBJECT_UNIT
	Boolean perform_tests() EDIT_SECTION;       
#endif
private:
	void change_active_editor(SiEditor * edit);
	Boolean is_macro_tap(const Int16 x,const Int16 y);
	Boolean view_menu_handle(const UInt16 id);
	SiEditor * get_editor_in_bounds(const Int16 y);
	SiEditor *the_editor_top;
	SiEditor *the_editor_bottom;
#ifndef PERFORM_TEST
	SiEditor *the_editor_active;
#endif
	//Boolean check_resize_drag_start(const Int16 x,const Int16 y);
	//Boolean do_drag_resize(const Int16 x,const Int16 y);
	SiMacroRecorder * macro_recorder;
	//Boolean drag_resizing;
	//Int16 drag_resizing_y;

};

#endif
