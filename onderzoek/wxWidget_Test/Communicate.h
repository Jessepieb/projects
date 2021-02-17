#pragma once
#include "Panels.h"
#include <wx/wxprec.h>

class Communicate : public wxFrame {
public:
	Communicate(const wxString& title);

	ServerViewPanel* m_sviewPanel;
	ServerToolPanel* m_sToolPanel;
	wxPanel* m_parent;
};