//
// Created by stefx on 8/21/24.
//

#ifndef GAMETEKST_MAINWINDOW_HPP
#define GAMETEKST_MAINWINDOW_HPP

#include "wx/wx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>

#include "Reservation.hpp"
#include "wx/calctrl.h"
#include "wx/listctrl.h"
#include "wx/timectrl.h"
#include "wx/datetime.h"

enum {
    ID_SELECTROOM = 1989,
    ID_SELECTSPORT,
    ID_COMBOBOX0
};

struct Records {
    std::string rImie;
    std::string rNaziwsko;
    std::string rPhone;
    std::string rRoom;
    std::string rSport;
    std::string rDate;
    std::string rTimeFrom;
    std::string rTimeTo;
    bool rRemove = false;
};

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

DECLARE_APP(MyApp)

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnNameTyping(wxCommandEvent& event);
    void CreateLeftPanel();
    void CreateRightPanel();

    void LoadDataBase(wxListCtrl* loadListOfRegistredPeople, std::string& surname, std::string& name, std::string& phone, std::string& room, std::string& sport,
                      int num, std::string& date, std::string& time, std::string& timeTo);
    void fillVector();

    void refreshData(wxListCtrl* refreshListOfRegistredPeople);

    void selectRoomDropBox(wxCommandEvent& event);
    void OnNumberTyping(wxCommandEvent& event);

    void recordsCheckAndSort(std::vector<Records>& dataVector);

    void OnSaveButtonClick(wxCommandEvent& event);
    void OnClearButtonClick(wxCommandEvent& event);

    std::string vName, vSurname, vPhone, vRoom, vSport, vDate, vTimeFrom, vTimeTo;

    wxTextCtrl* getName;
    wxTextCtrl* getSurname;
    wxTextCtrl* getPhone;
    wxComboBox* getRoom;
    wxComboBox* getSport;
    wxArrayString chooseExercise;

    std::vector<Records> dataVectorList;
    wxTextCtrl* textCtrl;
    wxPanel* panel;
    wxBoxSizer* mainSizer;
    wxListCtrl* listOfRegistredPeople;
    wxCalendarCtrl* calendar;
    wxTimePickerCtrl* timePick;
    wxTimePickerCtrl* timePick2;

    DECLARE_EVENT_TABLE()
};

#endif //GAMETEKST_MAINWINDOW_HPP
