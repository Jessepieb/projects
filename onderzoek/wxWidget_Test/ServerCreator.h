#pragma once
#include <wx/wx.h>
#include <wx/panel.h>

class ServerCreator : public wxDialog {
public:
	ServerCreator(const wxString& title);

	wxButton create_button;
	wxButton cancel_button;



	wxFrame* parent;
};