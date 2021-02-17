#include <wx/stattext.h>
#include "Communicate.h"

ServerViewPanel::ServerViewPanel(wxPanel* parent) : 
	wxPanel(parent,wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN) {
	
	m_text = new wxStaticText(this, -1, wxT(""));

};

ServerToolPanel::ServerToolPanel(wxPanel* parent) :
	wxPanel(parent, -1, wxDefaultPosition, wxDefaultSize,wxBORDER_DEFAULT) {
	m_parent = parent;
	m_start = new wxButton(this, ID_START, wxT("Start"), wxPoint(10,0));
	m_stop = new wxButton(this, ID_STOP, wxT("Stop"), wxPoint(10,30));

	Connect(ID_START, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ServerToolPanel::onStart));
	Connect(ID_STOP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ServerToolPanel::onStop));
};

void ServerToolPanel::onStart(wxCommandEvent& event) {
	Communicate* comm = (Communicate*)m_parent->GetParent();
	//comm->m_sviewPanel->m_text->SetLabel(wxString::Format(wxT("Starting server...")));
}

void ServerToolPanel::onStop(wxCommandEvent& event) {
	Communicate* comm = (Communicate*)m_parent->GetParent();
	//comm->m_sviewPanel->m_text->SetLabel(wxString::Format(wxT("Stopping server...")));
}