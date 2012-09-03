#ifndef __main_window__
#define __main_window__

/**
@file
Subclass of MainWindow_frame, which is generated by wxFormBuilder.
*/

#include "main_window_base.h"
#include "pteros/pteros_visualizer.h"

/** Implementing MainWindow_frame */
class main_window : public MainWindow_frame
{
protected:
	// Handlers for MainWindow_frame events.
	void evt_system_add( wxCommandEvent& event );
	void evt_system_delete( wxCommandEvent& event );
	void evt_system_load( wxCommandEvent& event );

	void evt_perspective_toggle( wxCommandEvent& event );
	void evt_fit_to_window( wxCommandEvent& event );

public:
	/** Constructor */
	main_window( wxWindow* parent );
	// Pointer to visualizer object
	pteros::Visualizer_wx* vis;
};

#endif // __main_window__
