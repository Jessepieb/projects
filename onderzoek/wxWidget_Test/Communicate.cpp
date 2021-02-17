#include "Communicate.h"

Communicate::Communicate(const wxString& title): wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(290,150))
{
	m_parent = new wxPanel(this, wxID_ANY);

	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

	m_sviewPanel = new ServerViewPanel(m_parent);
	m_sToolPanel = new ServerToolPanel(m_parent);

	hbox->Add(m_sviewPanel, 1, wxEXPAND | wxALL, 5);
	hbox->Add(m_sToolPanel, 1, wxEXPAND | wxALL, 5);

	m_parent->SetSizer(hbox);

	this->Center();
}