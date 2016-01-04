#include "edit_interface.h"
#include "utility.h"
#include "preferences.h"
#include "error.h"
#include "form_pos.h"
#include "test.h"

SiEditInterface::SiEditInterface(Char * file_to_open)
{
#ifdef TEST_OBJECTS_LOG
	log_entry("SiEditInterface::SiEditInterface()");
	log_entry_number("MemHandle size=",sizeof(MemHandle));
#endif	

	the_editor_top=the_editor_active=the_editor_bottom=NULL;
	
	SiUtility::initialise_calls();
	macro_recorder=new SiMacroRecorder();

	#ifdef BENCH_OBJECTS
	perform_benchmarks();
	#endif

	if(SiPreferencesDatabase::get_split_screen()&&NULL==file_to_open)
	  split_screen();
	else
	  {
	    the_editor_active=the_editor_top=new SiEditor(SiUtility::SCREEN_HEIGHT,0,0);
	    the_editor_active->read_preferences(file_to_open);
	  }

	if(SiPreferencesDatabase::get_focused_editor()==0)
	  {
	    change_active_editor(the_editor_top);	   
	  }
	else
	  {
	    change_active_editor(the_editor_bottom);
	  }

	SiPreferencesDatabase::tidy();

	#ifdef TEST_OBJECT_UNIT
	unsplit_screen();
	the_editor_top->initialise();
	
	perform_tests();
	
	perform_object_tests();
	#endif
}

SiEditInterface::~SiEditInterface()
{
#ifdef TEST_OBJECTS_LOG
	log_entry("SiEditInterface::~SiEditInterface()");
#endif

	if(the_editor_top!=NULL)
	{
		delete the_editor_top;
		the_editor_top=NULL;
	}
	if(the_editor_bottom!=NULL)
	{
		delete the_editor_bottom;
		the_editor_bottom=NULL;
	}

#ifdef MACRO
	if(macro_recorder!=NULL)
	{
		delete macro_recorder;
		macro_recorder=NULL;
	}
#endif
}

SiEditor * SiEditInterface::get_editor_in_bounds(const Int16 y)
{
#ifdef TEST_OBJECTS_LOG
	log_entry("SiEditInterface::get_editor_in_bounds()");
#endif

	SiEditor *ret;
	if (the_editor_top == NULL)
		ret = the_editor_bottom;
	else if (the_editor_bottom == NULL)
		ret = the_editor_top;
	else if (y > the_editor_top->TOP_Y && y < the_editor_bottom->TOP_Y)
		ret = the_editor_top;
	else
		ret = the_editor_bottom;
	
	if (ret != the_editor_active)
	{
		the_editor_active->lost_focus();
		SiPreferencesDatabase::set_focused_editor(ret->m_index);
		ret->give_focus();
	}
	return ret;
}
Int32 SiEditInterface::get_event_delay()
{

	if(the_editor_top!=NULL)
		if(!the_editor_top->finished_processing())
		  {
		    return PROCESSING_INTERVAL;
		  }
	if(the_editor_bottom!=NULL)
		if(!the_editor_bottom->finished_processing())
		  return PROCESSING_INTERVAL;
			
	return evtWaitForever;
}
void SiEditInterface::do_quick_slosh()
{
	if(the_editor_top!=NULL)
		if(!the_editor_top->finished_processing())
			the_editor_top->do_quick_slosh();
	if(the_editor_bottom!=NULL)
		if(!the_editor_bottom->finished_processing())
			the_editor_bottom->do_quick_slosh();
}

void SiEditInterface::change_active_editor(SiEditor * edit)
{
  if(the_editor_active!=NULL)
    the_editor_active->lost_focus();
  the_editor_active=edit;
  the_editor_active->give_focus();
  SiPreferencesDatabase::set_focused_editor(edit->m_index);
}

Boolean SiEditInterface::split_screen()
{
#ifdef TEST_OBJECTS_LOG
	log_entry("SiEditInterface::split_screen()");
#endif

	Boolean start_up=false;
	if(the_editor_top==NULL)
	{
		the_editor_top=new SiEditor(SiUtility::ACTIVE_SCREEN_HEIGHT/2,0,0);
		the_editor_top->set_scrollbar(ScrollBarTop);
		//		the_editor_top->give_focus();
		the_editor_active=the_editor_top;
		start_up=true;
	}

	if (the_editor_bottom == NULL)
	{
		the_editor_top->set_ignore_events();
		the_editor_top->resize(SiUtility::ACTIVE_SCREEN_HEIGHT/2-1, 0);

		the_editor_bottom =
			new SiEditor(SiUtility::ACTIVE_SCREEN_HEIGHT/2,
						 SiUtility::ACTIVE_SCREEN_HEIGHT/2, 1);
		
		//set the scrollbar on the new editor only if it hasn't already done it
		//which happens if it has popped up a keyboard or something
		if(the_editor_bottom->TOP_Y!=0)
		  the_editor_bottom->set_scrollbar(ScrollBarBottom);
		if(!start_up)
		  {
		    change_active_editor(the_editor_bottom);
		    the_editor_bottom->read_preferences(NULL);
		  }
		else
		  {
		    the_editor_top->read_preferences(NULL);
		    the_editor_bottom->read_preferences(NULL);
		    the_editor_bottom->lost_focus();
		  }
		the_editor_top->clear_ignore_events();
		SiPreferencesDatabase::set_split_screen(true);
		return true;
	}
	else
		return false;
}

Boolean SiEditInterface::unsplit_screen()
{
#ifdef TEST_OBJECTS_LOG
	log_entry("SiEditInterface::unsplit_screen()");
#endif

	if (the_editor_bottom != NULL)
	{
		the_editor_bottom->set_ignore_events();
		the_editor_top->set_ignore_events();
		SiEditor * temp_ed=the_editor_bottom;
		if(the_editor_active==the_editor_bottom)
		  the_editor_active=NULL;
		the_editor_bottom=NULL;
		delete temp_ed;

		change_active_editor(the_editor_top);
		the_editor_top->resize(SiUtility::ACTIVE_SCREEN_HEIGHT, 0);

		the_editor_top->clear_ignore_events();

		emit_redraw_signal(NULL);

		SiPreferencesDatabase::set_split_screen(false);

		return true;
	}
	else
		return false;
}

Boolean SiEditInterface::view_menu_handle(const UInt16 id)
{

	Boolean handled = false;

	switch (id)
	{
	case ViewMenuSplit:
		handled = split_screen();
		break;
	case ViewMenuUnsplit:
		handled=unsplit_screen();
	}
	return handled;
}

Boolean SiEditInterface::handle_event(EventPtr event)
{
  #ifdef TEST_OBJECTS
  //  log_entry("Event");
  #endif

	FormPtr form=NULL;
	Boolean handled = false;
#ifdef MACRO
	if(macro_recorder->give_event(event))
		return true;
#endif

	switch (event->eType)
	{
	case winExitEvent:
		form=FrmGetFormPtr(ResformID_text);
		if (event->data.winExit.exitWindow == (WinHandle) form)
		{
			if (the_editor_top != NULL)
				the_editor_top->set_ignore_events();
			if (the_editor_bottom != NULL)
				the_editor_bottom->set_ignore_events();
		}
		break;
	case winEnterEvent:
		form=FrmGetFormPtr(ResformID_text);
		if (event->data.winEnter.enterWindow == (WinHandle) form)
		{
			if (the_editor_top != NULL)
				the_editor_top->clear_ignore_events();
			if (the_editor_bottom != NULL)
				the_editor_bottom->clear_ignore_events();
		}
		break;
	case menuEvent:
		if (!view_menu_handle(event->data.menu.itemID))
			the_editor_active->handle_menu_command(event->data.menu.itemID);
		handled = true;
		break;
	case menuCmdBarOpenEvent:
		the_editor_active->handle_commandbar_popup();
		event->data.menuCmdBarOpen.preventFieldButtons = true;

		break;
	case penDownEvent:
		if(!is_macro_tap(event->screenX,event->screenY))
		{
			the_editor_active = get_editor_in_bounds(event->screenY);
			if (event->screenY <= SiUtility::SCREEN_HEIGHT&&event->screenX<=SiUtility::ACTIVE_SCREEN_WIDTH)
			  {
			    the_editor_active->handle_tap(event->screenX,event->screenY,event->tapCount);
			    handled=true;
			  }
		}

		break;
		
	case keyDownEvent:
		handled =the_editor_active->handle_key(event->data.keyDown.chr,event->data.keyDown.modifiers);
		break;
	case sclRepeatEvent:
		switch (event->data.sclRepeat.scrollBarID)
		{
		case ScrollBarMain:
		case ScrollBarTop:
			the_editor_top->handle_scroll(event->data.sclRepeat.value,event->data.sclRepeat.newValue);
			break;
		case ScrollBarBottom:
			the_editor_bottom->handle_scroll(event->data.sclRepeat.value,event->data.sclRepeat.newValue);
			break;
		}
		break;
	case ctlSelectEvent:
		if(event->data.ctlSelect.controlID==PopupTriggerButton)
		{
			macro_recorder->popup_macro_list();
			handled=true;
		}
		break;
	case nilEvent:
		do_quick_slosh();
		handled=true;
		break;
	case frmUpdateEvent:
	  if(ResformID_text==event->data.frmUpdate.formID)
	    emit_redraw_signal(NULL);
	  break;
	default:
		break;
	}


	return handled;
}
/*
Boolean SiEditInterface::check_resize_drag_start(const Int16 x,const Int16 y)
{
	if(the_editor_top!=NULL&&the_editor_bottom!=NULL&&!drag_resizing)
	{
		if(the_editor_top->point_in_drag_area(x,y))
		{
			drag_resizing=true;
			drag_resizing_y=y;
		}
	}
	return drag_resizing;
}
 
Boolean SiEditInterface::do_drag_resize(const Int16 x,const Int16 y)
{
	Int16 y_offset=the_editor_top->get_status_y()-drag_resizing_y;
	if(abs(y-drag_resizing_y)<FntLineHeight())
		return true;
	drag_resizing_y=y;
	the_editor_top->resize(drag_resizing_y-y_offset,0);
	if(the_editor_bottom!=NULL)
		the_editor_bottom->resize(SiUtility::SCREEN_HEIGHT-(drag_resizing_y-y_offset),drag_resizing_y-y_offset);
	emit_redraw_signal(NULL);
	return true;
}
*/
void SiEditInterface::emit_redraw_signal(SiEditor* source)
{
	if(the_editor_top!=NULL&&the_editor_top!=source)
		the_editor_top->redraw();
	if(the_editor_bottom!=NULL&&the_editor_bottom!=source)
		the_editor_bottom->redraw();
}

#ifdef V_KEYBOARD
Boolean SiEditInterface::intercept_event(EventPtr e)
{
#ifdef TEST_OBJECTS_LOG
	log_entry("intercepting");
#endif

	if(macro_recorder==NULL)
		return false;
	if(e->eType==keyDownEvent)
	{
		if(the_editor_active!=NULL)
		{
			if(!macro_recorder->recording)
				if(e->data.keyDown.chr==vchrKeyboardAlpha||e->data.keyDown.chr==vchrKeyboardNumeric)
					return the_editor_active->handle_key(e->data.keyDown.chr,e->data.keyDown.modifiers);
		}
	}

	return false;
}
#endif

void SiEditInterface::change_font()
{
	if(the_editor_top!=NULL)
		the_editor_top->change_font(SiPreferencesDatabase::get_font());
	if(the_editor_bottom!=NULL)
		the_editor_bottom->change_font(SiPreferencesDatabase::get_font());
}

Boolean SiEditInterface::is_macro_tap(const Int16 x,const Int16 y)
{
	if(x>=72&&x<=95)
		if(y>=149&&y<=158)
			return true;

	return false;
}

#ifdef TEST_OBJECT_UNIT
Boolean SiEditInterface::perform_tests()
{
  for(Int16 i=0;i<15;++i)
    {
      
      split_screen();
      ErrFatalDisplayIf(the_editor_top==NULL||the_editor_bottom==NULL,"Edit interface not splitting");
      ErrFatalDisplayIf(the_editor_top->HEIGHT!=SiUtility::ACTIVE_SCREEN_HEIGHT/2-1||the_editor_top->TOP_Y!=0,"Incorrect position on split screen: top editor");
      ErrFatalDisplayIf(the_editor_bottom->HEIGHT!=SiUtility::ACTIVE_SCREEN_HEIGHT/2||the_editor_bottom->TOP_Y!=SiUtility::ACTIVE_SCREEN_HEIGHT/2,"Incorrect position on split screen: bottom editor");
      unsplit_screen();
      ErrFatalDisplayIf(the_editor_bottom!=NULL,"Edit Interface not unsplitting");
      ErrFatalDisplayIf(the_editor_top==NULL,"Incorrect editor being deleted on unsplit");
      ErrFatalDisplayIf(the_editor_top->HEIGHT!=SiUtility::ACTIVE_SCREEN_HEIGHT,"Incorrect height on unsplit");
      
      ErrFatalDisplayIf(the_editor_top->TOP_Y!=0,"Incorrect TOP_Y on unsplit");
    }
  #ifdef TEST_OBJECTS
  log_entry("SiEditInterface tests complete");
  #endif
  return true;
      
}

#endif
