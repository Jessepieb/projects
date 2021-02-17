#include "main.h"
#include "Mainhub.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {

	Mainhub* mainh = new Mainhub("Main");
	mainh->Show(true);

	return true;
};