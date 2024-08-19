//
// Created by stefx on 9/8/24.
//

#include "Reservation.hpp"

//Only test file for now
Reservation::Reservation(wxPanel* panel1, std::string &surname, std::string& name, std::string& phone) : prv_panel(panel1), prv_surname(surname), prv_name(name), prv_phone(phone) {
    auto* rightBox = new wxStaticBox(panel1, wxID_ANY, wxT("Aktualne rezerwacje"), wxDefaultPosition, wxSize(1030, 720), wxALIGN_CENTRE);

    auto* fillRightPanel = new wxStaticBoxSizer(rightBox, wxVERTICAL);
    auto* rightListBox = new wxBoxSizer(wxHORIZONTAL);

    auto *listOfRegistredPeople = new wxListCtrl(panel1, wxID_ANY, wxDefaultPosition, wxSize(1030, 720),
                                                 wxLC_REPORT | wxBORDER_SUNKEN);
    listOfRegistredPeople->InsertColumn(0, wxT("Lp."), wxLIST_FORMAT_LEFT, 50);
    listOfRegistredPeople->InsertColumn(1, wxT("Nazwisko"), wxLIST_FORMAT_LEFT, 150);
    listOfRegistredPeople->InsertColumn(2, wxT("Imię"), wxLIST_FORMAT_LEFT, 100);
    listOfRegistredPeople->InsertColumn(3, wxT("Telefon"), wxLIST_FORMAT_LEFT, 120);
    listOfRegistredPeople->InsertColumn(4, wxT("Pomieszczenie"), wxLIST_FORMAT_LEFT, 150);
    listOfRegistredPeople->InsertColumn(5, wxT("Sport"), wxLIST_FORMAT_LEFT, 150);
    listOfRegistredPeople->InsertColumn(6, wxT("Data"), wxLIST_FORMAT_LEFT, 100);
    listOfRegistredPeople->InsertColumn(7, wxT("Godzina"), wxLIST_FORMAT_LEFT, 100);

    makeReservation();

    rightListBox->Add(listOfRegistredPeople, 1, wxALL, 1);
}

void Reservation::makeReservation () {

}