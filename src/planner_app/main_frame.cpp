#include <iostream>

#include "main_frame.h"
#include "add_new_event_dialog.h"


using std::cout;
using std::endl;

MainFrame::MainFrame(const wxString& title,
                 const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    initMenu();

    wxSizer* mainFrameSizer = new wxBoxSizer(wxHORIZONTAL);



    
    wxSizer* monSizer = new wxBoxSizer(wxVERTICAL);
    wxPanel* monPanel = new wxPanel(this, wxID_ANY);
    
    for (int i = 0; i < 10; i++) {
        createNewEventPanel(monSizer, monPanel);
    }

    monPanel->SetSizer(monSizer);

    mainFrameSizer->Add(monPanel);

    


    CreateStatusBar();
    SetStatusText("Welcome to Plan My Week!");
}


void MainFrame::initMenu() {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(Id_CreateNewEvent, "Add New Event...\tCtrl-H",
                     "Add a new event to the planner");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, "Exit...\tCtrl-X",
                     "Exit the application");

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    this->Bind(wxEVT_MENU, &MainFrame::onCreateNewEvent, this, Id_CreateNewEvent);
    this->Bind(wxEVT_MENU, &MainFrame::onAbout, this, wxID_ABOUT);
    this->Bind(wxEVT_MENU, &MainFrame::onExit, this, wxID_EXIT);
    SetMenuBar(menuBar);
}



void MainFrame::onAbout(wxCommandEvent& event)
{
    wxMessageBox(
        "This planner application generates a weekly schedule for you based on the events you provided",
        "About Plan My Week",
        wxOK | wxICON_INFORMATION
    );
}

void MainFrame::onExit(wxCommandEvent& event)
{
    cout << "OnExit: Exiting Hello World app!" << endl;
    Close(true);
}

void MainFrame::onCreateNewEvent(wxCommandEvent& event)
{
    AddNewEventDialog* dialog = new AddNewEventDialog(this, wxID_ANY, "Add A New Event");
    if (dialog->ShowModal() == wxID_OK) {
        wxMessageBox(
            wxString::Format(
                "Event name: %s\nEvent description: %s\n",
                dialog->name,
                dialog->description
            )
        );
    }

    dialog->Destroy();
}

void MainFrame::createNewEventPanel(wxSizer* parentSizer, wxPanel* parentPanel) {
    wxPanel* eventPanel = new wxPanel(parentPanel, wxID_ANY);
    wxSizer* eventSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* eventLabel = new wxStaticText(eventPanel, wxID_ANY, "Test Event");

    eventSizer->Add(eventLabel);
    eventPanel->SetSizer(eventSizer);

    parentSizer->Add(eventPanel);
}