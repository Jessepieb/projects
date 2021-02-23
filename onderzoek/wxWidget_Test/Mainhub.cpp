#include "Mainhub.h"

const int ID_CREATE_SERVER = 101;
const int ID_CREATE_CLIENT = 102;

Mainhub::Mainhub(const wxString& title) :
	wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400)) {

	wxImage::AddHandler(new wxPNGHandler);

	wxBitmap create(wxT("create.png"), wxBITMAP_TYPE_PNG);

	wxToolBar* toolbar = CreateToolBar();
	toolbar->AddTool(wxID_EXIT, wxT("exit app"),create,wxT("Create new server"));
	toolbar->SetToolBitmapSize(wxSize(24, 24));
	toolbar->Realize();

	wxNotebook* nb = new wxNotebook(this, -1, wxPoint(-1, -1), wxSize(-1, -1), wxNB_BOTTOM);

	wxMenuBar* menubar = new wxMenuBar;

	//wxMenu* file = new wxMenu;
	wxMenu* file = new wxMenu;
	wxMenu* about = new wxMenu;


	file->Append(ID_CREATE_SERVER, wxT("Create Server"), wxT("Create a new server"));
	file->Append(ID_CREATE_CLIENT, wxT("Create Client"), wxT("Create a new client"));

	file->AppendSeparator();
	file->Append(wxID_EXIT, wxT("Quit"), wxT(""));


	about->Append(wxID_ABOUT, wxT("About"));

	menubar->Append(file, wxT("&File"));
	menubar->Append(about, wxT("&About"));
	

	SetMenuBar(menubar);

	ServerGrid* grid1 = new ServerGrid(nb);
	ServerGrid* grid2 = new ServerGrid(nb);

	nb->AddPage(grid1, wxT("TCP-Servers"));
	nb->AddPage(grid2, wxT("UDP-Servers"));

	CreateStatusBar();
	Center();


	Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Mainhub::createServer));
	Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Mainhub::onQuit));
	Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Mainhub::onQuit));
};

void Mainhub::createServer(wxCommandEvent& event) {

}

void Mainhub::onQuit(wxCommandEvent& event) {
	Close(true);
};

ServerGrid::ServerGrid(wxNotebook* parent): wxGrid(parent,wxID_ANY) {
	CreateGrid(10, 10);
	SetRowLabelSize(50);
	SetColLabelSize(25);

	SetRowLabelAlignment(wxALIGN_RIGHT, wxALIGN_CENTRE);
	SetLabelFont(wxFont(9, wxFONTFAMILY_DEFAULT,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	for (int i = 0; i < 10; i++)
	{
		this->SetRowSize(i, 25);
	}
};