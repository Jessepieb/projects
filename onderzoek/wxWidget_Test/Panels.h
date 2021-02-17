#pragma once
#include <wx/wx.h>
#include <wx/panel.h>

class ServerViewPanel : public wxPanel {
public:

	ServerViewPanel(wxPanel* parent);

	void onSetText(wxCommandEvent& event);

	wxStaticText* m_text;
};

class ServerToolPanel : public wxPanel {
public:
	ServerToolPanel(wxPanel* parent);

	void onStart(wxCommandEvent& event);
	void onStop(wxCommandEvent& event);

	wxButton* m_start;
	wxButton* m_stop;
	wxPanel* m_parent;
};

const int ID_START = 101;
const int ID_STOP = 102;