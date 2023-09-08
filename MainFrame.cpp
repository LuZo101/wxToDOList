
#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include "Task.h"

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    CreateControls();
    AddSavedTasks();
    BindEventHandler();
}
void MainFrame::CreateControls()
{
    wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
    wxFont mainFont(wxFontInfo(wxSize(0, 24)));

    panel = new wxPanel(this);
    panel->SetFont(mainFont);
    headlinetext = new wxStaticText(panel, wxID_ANY, "ToDo List", wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
    headlinetext->SetFont(headlineFont);

    inputText = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 80), wxSize(495, 35), wxTE_PROCESS_ENTER);
    addbutton = new wxButton(panel, wxID_ANY, "Add Task", wxPoint(600, 80), wxSize(100, 35));
    checkListBox = new wxCheckListBox(panel, wxID_ANY, wxPoint(100, 120), wxSize(600, 400));
    clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(100, 525), wxSize(100, 35));
}
void MainFrame::BindEventHandler()
{
    addbutton->Bind(wxEVT_BUTTON, &MainFrame::OnAddBtnClicked, this);
    inputText->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnter, this);
    checkListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this);
    clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearBtnClicked, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnCloseWindow, this);
}
void MainFrame::AddTaskFromInput()
{
    wxString description = inputText->GetValue();
    if (!description.IsEmpty())
    { // append on checklist
        checkListBox->Insert(description, checkListBox->GetCount());
        // Clear the input field
        inputText->Clear();
    }
    // set focus after clear to write the next task
    inputText->SetFocus();
}
void MainFrame::OnAddBtnClicked(wxCommandEvent &evt)
{
    AddTaskFromInput();
}

void MainFrame::OnInputEnter(wxCommandEvent &evt)
{
    AddTaskFromInput();
}

void MainFrame::DeleteSelectedTask()
{
    int selectedIndex = checkListBox->GetSelection();

    if (selectedIndex == wxNOT_FOUND)
    {
        return;
    }

    checkListBox->Delete(selectedIndex);
}
void MainFrame::OnListKeyDown(wxKeyEvent &evt)
{
    switch (evt.GetKeyCode())
    {
    case WXK_DELETE:
        DeleteSelectedTask();
        break;

    case WXK_UP:
        MoveSelectedTask(-1); // offset -1
        break;
    case WXK_DOWN:
        MoveSelectedTask(1); // offset +1
        break;
    }
}
void MainFrame::MoveSelectedTask(int offset)
{
    int selectedIndex = checkListBox->GetSelection();

    if (selectedIndex == wxNOT_FOUND)
    {
        return;
    }
    int newIndex = selectedIndex + offset;
    if (newIndex >= 0 && newIndex < checkListBox->GetCount())
    {
        SwapTask(selectedIndex, newIndex);
        checkListBox->SetSelection(newIndex, true);
    }
}
void MainFrame::SwapTask(int i, int j)
{
    Task taskI{checkListBox->GetString(i).ToStdString(), checkListBox->IsChecked(i)};
    Task taskJ{checkListBox->GetString(j).ToStdString(), checkListBox->IsChecked(j)};

    checkListBox->SetString(i, taskJ.description_);
    checkListBox->Check(i, taskJ.done);

    checkListBox->SetString(j, taskI.description_);
    checkListBox->Check(j, taskI.done);
}

void MainFrame::OnClearBtnClicked(wxCommandEvent &evt)
{
    if (checkListBox->IsEmpty())
    {
        return;
    }
    wxMessageDialog dialog(this, "Are you sure want clear", "Clear", wxYES_NO | wxCANCEL);
    int result = dialog.ShowModal();
    if (result == wxID_YES)
    {
        checkListBox->Clear();
    }
}

void MainFrame::OnWindowClosed(wxCloseEvent &evt)
{
    std::vector<Task> tasks;
    for (int i = 0; i < checkListBox->GetCount(); i++)
    {
        Task task;
        task.description_ = checkListBox->GetString(i);
        task.done = checkListBox->IsChecked(i);
        tasks.push_back(task);
    }
    SaveTasksToFile(tasks, "tasks.txt");
    evt.Skip();
}
void MainFrame::AddSavedTasks()
{
    std::vector<Task> tasks = loadTasksFromFile("tasks.txt");
    for (const Task &task : tasks)
    {
        int index = checkListBox->GetCount();
        checkListBox->Insert(task.description_, index);
        checkListBox->Check(index, task.done);
    }
}
