
#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/wx.h>

#pragma once

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title);

private:
    void CreateControls();
    void BindEventHandler();

    void OnAddBtnClicked(wxCommandEvent &evt);
    void OnInputEnter(wxCommandEvent &evt);
    void OnListKeyDown(wxKeyEvent &evt);

    void MoveSelectedTask(int offset);
    void SwapTask(int i, int j);

    void OnClearBtnClicked(wxCommandEvent &evt);

    void OnWindowClosed(wxCloseEvent &evt);

    void AddSavedTasks();

    void AddTaskFromInput();
    void DeleteSelectedTask();

    wxPanel *panel;
    wxStaticText *headlinetext;
    wxTextCtrl *inputText;
    wxButton *addbutton;
    wxCheckListBox *checkListBox;
    wxButton *clearButton;

    ;
};

#endif
