#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/grid.h>

class Mainhub : public wxFrame {
public:
	Mainhub(const wxString& title);

	void createServer(wxCommandEvent& event);
	void onQuit(wxCommandEvent& event);
};

class ServerGrid : public wxGrid {
public:
	ServerGrid(wxNotebook* parent);
};