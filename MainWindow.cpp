//
// Created by stefx on 8/21/24.
//

#include "MainWindow.hpp"
#include "wx/splitter.h"


bool MyApp::OnInit() {
    auto *frame = new MyFrame(wxT("HalSpo"));
    frame->Show(true);
    return true;
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)

END_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title)
         : wxFrame(nullptr, wxID_ANY, title, wxPoint(wxDefaultPosition), wxSize(1280, 820)) {

    panel = new wxPanel(this, wxID_ANY);
    mainSizer = new wxBoxSizer(wxHORIZONTAL);

    CreateLeftPanel();
    CreateRightPanel();

    panel->SetSizer(mainSizer);
}

void MyFrame::CreateLeftPanel() {
    wxArrayString chooseObject;
    chooseObject.Add(wxT("1/3 Hali"));
    chooseObject.Add(wxT("2/3 Hali"));
    chooseObject.Add(wxT("Cała Hala"));
    chooseObject.Add(wxT("Salka ćwiczeń"));
    chooseObject.Add(wxT("Siłownia"));
    chooseObject.Add(wxT("Konferencyjny"));

    auto* leftSizer = new wxBoxSizer(wxVERTICAL);
    auto* leftBoxBtn = new wxBoxSizer(wxHORIZONTAL);

    //Static Box for left panel
    auto* leftBox = new wxStaticBox(panel, wxID_ANY, wxT("Panel rezerwacji"), wxDefaultPosition, wxSize(250, 720), wxALIGN_CENTRE);

    //Again BoxSizer for fill left
    auto* fillLeftPanel = new wxStaticBoxSizer(leftBox, wxVERTICAL);

    //Pola związane z Nazwiskiem
    auto* registerInfoTxt = new wxStaticText(panel, wxID_ANY, wxT("Dane rezerwującego"));
    auto* nameTxt = new wxStaticText(panel, wxID_ANY, wxT("Nazwisko:"), wxDefaultPosition, wxSize(100, 30));
    getSurname = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 30));

    //Pola związane z Imieniem
    auto* surnameTxt = new wxStaticText(panel, wxID_ANY, wxT("Imię:"), wxDefaultPosition, wxSize(100, 30));
    getName = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 30));

    //Pola związane z telefonem
    auto* telTxt = new wxStaticText(panel, wxID_ANY, wxT("Telefon:"), wxDefaultPosition, wxSize(100, 30));
    getPhone = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 30));

    //Pola związane z wyborem pomieszczenia rezerwacji
    auto* whatIsReservedTxt = new wxStaticText(panel, wxID_ANY, wxT("Obiekt:"));
    getRoom = new wxComboBox(panel, ID_SELECTROOM, wxT("Wybierz"), wxDefaultPosition, wxSize(200, 30), chooseObject);

    //Pola związane z wyborem sportu
    auto* sportKindTxt = new wxStaticText(panel, wxID_ANY, wxT("Rodzaj sportu:"));
    getSport = new wxComboBox(panel, ID_SELECTSPORT, wxT("Pole nieaktywne"), wxDefaultPosition, wxSize(200, 30), chooseExercise);

    auto* dateTxt = new wxStaticText(panel, wxID_ANY, wxT("Data:"));
    calendar = new wxCalendarCtrl(panel, wxID_ANY, wxDateTime::Now(), wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS);

    auto* timeFrom = new wxStaticText(panel, wxID_ANY, wxT("Od:"));
    timePick = new wxTimePickerCtrl(panel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize(150, 30));

    auto* timeTo = new wxStaticText(panel, wxID_ANY, wxT("Do:"));
    timePick2 = new wxTimePickerCtrl(panel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize(150, 30));

    auto* saveBtn = new wxButton(panel, wxID_ANY, wxT("Zapisz"));
    auto* clearBtn = new wxButton(panel, wxID_ANY, wxT("Wyczyść"));

    //Pola obsługi Imienia i Nazwiska
    fillLeftPanel->Add(registerInfoTxt, 1, wxALL, 5);
    fillLeftPanel->Add(nameTxt, 1, wxALL, 1);
    fillLeftPanel->Add(getSurname, 1, wxALL, 5);
    getSurname->Bind(wxEVT_TEXT, &MyFrame::OnNameTyping, this);

    fillLeftPanel->Add(surnameTxt, 1, wxALL, 1);
    fillLeftPanel->Add(getName, 1, wxALL, 5);
    getName->Bind(wxEVT_TEXT, &MyFrame::OnNameTyping, this);

    //Pole obsługi nr. tel.
    fillLeftPanel->Add(telTxt, 1, wxALL, 1);
    fillLeftPanel->Add(getPhone, 1, wxALL, 5);
    getPhone->Bind(wxEVT_TEXT, &MyFrame::OnNumberTyping, this);

    //Pole obsługi pomieszczeń
    fillLeftPanel->Add(whatIsReservedTxt, 1, wxALL, 1);
    fillLeftPanel->Add(getRoom, 1, wxALL, 5);

    //Funkcja odświeża listę rodzaju sportu wybranych względem pomieszczenia
    getRoom->Bind(wxEVT_COMBOBOX, &MyFrame::selectRoomDropBox ,this);

    //Pole obsługi rodzaju sportu
    fillLeftPanel->Add(sportKindTxt, 1, wxALL, 1);
    fillLeftPanel->Add(getSport, 1, wxALL, 5);

    //Pole obsługi daty
    fillLeftPanel->Add(dateTxt, 1, wxALL, 1);
    fillLeftPanel->Add(calendar, 1, wxALL, 1);

    //Pole obsługi godziny
    fillLeftPanel->Add(timeFrom, 1, wxALL, 1);
    fillLeftPanel->Add(timePick, 1, wxALL, 1);
    fillLeftPanel->Add(timeTo, 1, wxALL, 1);
    fillLeftPanel->Add(timePick2, 1, wxALL, 1);

    fillLeftPanel->Add(leftBoxBtn, 1, wxALL, 5);

    //Przyciski SAVE oraz CLEAR
    leftBoxBtn->Add(saveBtn, 1, wxALL, 5);

    saveBtn->Bind(wxEVT_BUTTON, &MyFrame::OnSaveButtonClick, this);

    leftBoxBtn->Add(clearBtn, 1, wxALL, 5);
    clearBtn->Bind(wxEVT_BUTTON, &MyFrame::OnClearButtonClick, this);

    leftSizer->Add(fillLeftPanel, 1, wxALL, 5);
    mainSizer->Add(leftSizer, 1, wxALL, 5);
}

void MyFrame::CreateRightPanel() {
    auto* rightSizer = new wxBoxSizer(wxVERTICAL);

    auto* rightBox = new wxStaticBox(panel, wxID_ANY, wxT("Aktualne rezerwacje"), wxDefaultPosition, wxSize(1030, 820), wxALIGN_CENTRE);
    auto* fillRightPanel = new wxStaticBoxSizer(rightBox, wxVERTICAL);
    auto* rightListBox = new wxBoxSizer(wxHORIZONTAL);
    auto* rightCheckBox = new wxCheckBox(panel, wxID_ANY, wxT("Sortowanie względem daty"),wxPoint(20, 20));

    listOfRegistredPeople = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(1030, 720), wxLC_REPORT | wxBORDER_SUNKEN);
    listOfRegistredPeople->InsertColumn(0, wxT("Lp."), wxLIST_FORMAT_LEFT, 50);
    listOfRegistredPeople->InsertColumn(1, wxT("Nazwisko"), wxLIST_FORMAT_LEFT, 120);
    listOfRegistredPeople->InsertColumn(2, wxT("Imię"), wxLIST_FORMAT_LEFT, 90);
    listOfRegistredPeople->InsertColumn(3, wxT("Telefon"), wxLIST_FORMAT_LEFT, 110);
    listOfRegistredPeople->InsertColumn(4, wxT("Pomieszczenie"), wxLIST_FORMAT_LEFT, 120);
    listOfRegistredPeople->InsertColumn(5, wxT("Sport"), wxLIST_FORMAT_LEFT, 100);
    listOfRegistredPeople->InsertColumn(6, wxT("Data"), wxLIST_FORMAT_LEFT, 100);
    listOfRegistredPeople->InsertColumn(7, wxT("Od"), wxLIST_FORMAT_LEFT, 90);
    listOfRegistredPeople->InsertColumn(8, wxT("Do"), wxLIST_FORMAT_LEFT, 90);
    listOfRegistredPeople->InsertColumn(9, wxT("Usuń"), wxLIST_FORMAT_LEFT, 50);

    refreshData(listOfRegistredPeople);
    recordsCheckAndSort(dataVectorList);
    fillVector();

    //Prawy panel lista rezerwacji
    fillRightPanel->Add(rightCheckBox, 1, wxALIGN_CENTRE, 10);
    rightCheckBox->SetValue(true);
    fillRightPanel->Add(rightListBox, 1, wxALL, 10);

    rightListBox->Add(listOfRegistredPeople, 1, wxALL, 1);

    rightSizer->Add(fillRightPanel, 1, wxALL, 5);
    mainSizer->Add(rightSizer, 2, wxALL, 5);
}

void MyFrame::refreshData(wxListCtrl* refreshListOfRegistredPeople) {
    refreshListOfRegistredPeople->DeleteAllItems();

    std::ifstream loadData ("data");

    std::string line;
    int num = 0;
    //std::string surname, name, phone, room, sport, date, timeFrom, timeTo;
    while (std::getline(loadData, line)) {
        std::istringstream dane(line);
        std::getline(dane, vSurname, ',');
        std::getline(dane, vName, ',');
        std::getline(dane, vPhone, ',');
        std::getline(dane, vRoom, ',');
        std::getline(dane, vSport, ',');
        std::getline(dane, vDate, ',');
        std::getline(dane, vTimeFrom, ',');
        std::getline(dane, vTimeTo, ',');

        dataVectorList.push_back({vSurname, vName, vPhone, vRoom, vSport, vDate, vTimeFrom, vTimeTo, true});
        LoadDataBase(refreshListOfRegistredPeople, vSurname, vName, vPhone, vRoom, vSport, num, vDate, vTimeFrom, vTimeTo);
        ++num;
    }
}

void MyFrame::fillVector() {
    for (auto& it : dataVectorList) {
        std::cout << "Nowe dane: " << it.rNaziwsko << " " << it.rImie << " ";
    }
}

//TODO Zrobić wczytywanie i sortowanie. Zasanawiam się nad wywaleniem LoadDataBase z pętli while i przeniesieniem go do CreateRightPanel by wykonywała się tylko 1x a w niej był
//TODO wektork tóry będzie wczytywał dane i od razu wyświetlał je posortowane.

void MyFrame::LoadDataBase(wxListCtrl* loadListOfRegistredPeople, std::string& surname, std::string& name, std::string& phone, std::string& room, std::string& sport,
                           int number, std::string& date, std::string& timeFrom, std::string& timeTo) {

    wxString wSurname (surname.c_str(), wxConvUTF8);
    wxString wName (name.c_str(), wxConvUTF8);
    wxString wRoom (room.c_str(), wxConvUTF8);
    wxString wSport (sport.c_str(), wxConvUTF8);
    std::string lp = std::to_string(number + 1);
    wxString wDate (date.c_str(), wxConvUTF8);
    wxString wTimeFrom (timeFrom.c_str(), wxConvUTF8);
    wxString wTimeTo (timeTo.c_str(), wxConvUTF8);

    long itemIndex = loadListOfRegistredPeople->InsertItem(number, lp);
    loadListOfRegistredPeople->SetItem(itemIndex, 1, wSurname);
    loadListOfRegistredPeople->SetItem(itemIndex, 2, wName);
    loadListOfRegistredPeople->SetItem(itemIndex, 3, phone);
    loadListOfRegistredPeople->SetItem(itemIndex, 4, wRoom);
    loadListOfRegistredPeople->SetItem(itemIndex, 5, wSport);
    loadListOfRegistredPeople->SetItem(itemIndex, 6, wDate);
    loadListOfRegistredPeople->SetItem(itemIndex, 7, wTimeFrom);
    loadListOfRegistredPeople->SetItem(itemIndex, 8, wTimeTo);
}

void MyFrame::OnNumberTyping(wxCommandEvent& event) {
    auto* textCtrl1 = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
    if (textCtrl1) {
        std::string numberPhone = textCtrl1->GetValue().ToStdString();

        // Usunięcie wszystkich '-' z wprowadzonego numeru
        numberPhone.erase(std::remove_if(numberPhone.begin(), numberPhone.end(),  [](char c){return !std::isdigit(c); }), numberPhone.end());

        if (numberPhone.length() > 9) {
            numberPhone = numberPhone.substr(0, 9);
        }

        // Dodanie '-' po każdej trzeciej cyfrze
        for (size_t i = 3; i < numberPhone.length(); i += 4) {
            numberPhone.insert(i, "-");
        }

        // Wyłączenie obsługi zdarzeń na czas modyfikacji, aby uniknąć zapętlenia
        textCtrl1->Unbind(wxEVT_TEXT, &MyFrame::OnNumberTyping, this);
        textCtrl1->SetValue(numberPhone);
        textCtrl1->SetInsertionPointEnd();  // Ustawienie kursora na końcu tekstu
        textCtrl1->Bind(wxEVT_TEXT, &MyFrame::OnNumberTyping, this);
    }
}

void MyFrame::OnNameTyping(wxCommandEvent& event) {
    auto* nameTxtCtrl = dynamic_cast<wxTextCtrl*> (event.GetEventObject());

    if (nameTxtCtrl) {
        std::wstring nameStr = nameTxtCtrl->GetValue().ToStdWstring();
        nameStr.erase(std::remove_if(nameStr.begin(), nameStr.end(), [](char c){return std::isdigit(c);}), nameStr.end());

        nameTxtCtrl->Unbind(wxEVT_TEXT, &MyFrame::OnNameTyping, this);
        nameTxtCtrl->SetValue(nameStr);
        nameTxtCtrl->SetInsertionPointEnd();
        nameTxtCtrl->Bind(wxEVT_TEXT, &MyFrame::OnNameTyping, this);
    }
}

void MyFrame::selectRoomDropBox(wxCommandEvent &event) {
    auto select = event.GetSelection();

    select = event.GetSelection();
    if(select == wxNOT_FOUND) {
        wxMessageBox("Nie znaleziono wyboru!", "Błąd", wxOK | wxICON_ERROR);
        return;
    }

    int comboBoxId = event.GetId();
    if (comboBoxId == ID_SELECTROOM) {
        if (event.GetString() == L"Cała Hala" || event.GetString() == L"1/3 Hali" || event.GetString() == L"2/3 Hali") {
            chooseExercise.clear();
            chooseExercise.Add(wxT("Siatkówka"));
            chooseExercise.Add(wxT("Koszykówka"));
            chooseExercise.Add(wxT("Piłka nożna"));
            chooseExercise.Add(wxT("Ping-pong"));
        } else if (event.GetString() == L"Konferencyjny") {
            chooseExercise.Clear();
            chooseExercise.Add(wxT("Urodziny"));
            chooseExercise.Add(wxT("Inne"));
        } else {
            chooseExercise.Clear();
        }

        getSport->Clear();
        getSport->Append(chooseExercise);
        getSport->Refresh();
    }
}

void MyFrame::recordsCheckAndSort(std::vector<Records>& dataVector) {
    std::sort(dataVector.begin(), dataVector.end(), [](Records& a, Records& b){return a.rDate < b.rDate;});

    for (auto& it : dataVector) {
        std::cout << it.rDate << " " << it.rImie << std::endl;
    }

    std::cout << dataVector.size() << std::endl;
}

void MyFrame::OnSaveButtonClick(wxCommandEvent& event) {
    std::ofstream dataFile ("data", std::ofstream::out | std::ofstream::app);

    if (!getSurname->IsEmpty() && getRoom->GetSelection() != wxNOT_FOUND) {
        if (dataFile.is_open()) {
            dataFile << getSurname->GetValue() << ",";
            dataFile << getName->GetValue() << ",";
            dataFile << getPhone->GetValue() << ",";
            dataFile << getRoom->GetString(getRoom->GetSelection()) << ",";
            if (getSport->GetSelection() != wxNOT_FOUND) {
                dataFile << getSport->GetString(getSport->GetSelection()) << ",";
            } else {
                dataFile << "-" << ",";
            }

            wxDateTime date = calendar->GetDate();
            wxString dateString = date.FormatISODate();
            dataFile << dateString << ",";

            wxDateTime timeFrom = timePick->GetValue();
            timeFrom.SetSecond(0);
            wxString timeStringFrom = timeFrom.FormatTime();
            dataFile << timeStringFrom << ",";

            wxDateTime timeTo = timePick2->GetValue();
            timeTo.SetSecond(0);
            wxString timeStringTo = timeTo.FormatTime();

            if (getRoom->GetStringSelection() == L"Cała Hala" || getRoom->GetStringSelection() == L"1/3 Hali" || getRoom->GetStringSelection() == L"2/3 Hali") {
                if (timeFrom >= timeTo) {
                    dataFile << timeStringFrom << std::endl;
                }
                else {
                    dataFile << timeStringTo << std::endl;
                }
            } else {
                dataFile << "-" << std::endl;
            }

            wxMessageBox(wxT("Zapisano"), "Informacja", wxOK | wxICON_INFORMATION, this);
            refreshData(listOfRegistredPeople);
        }
    } else {
        wxMessageBox(wxT("Błąd: Brakuje nazwiska lub nie wybrano obiekt"), "UWAGA", wxOK | wxICON_INFORMATION, this);
    }
}

void MyFrame::OnClearButtonClick(wxCommandEvent &event) {
    getName->Clear();
    getSurname->Clear();
    getPhone->Clear();
    getSport->Clear();

    getName->Refresh();
    getSurname->Refresh();
    getPhone->Refresh();

    getRoom->SetValue(wxT("Wybierz"));
    getRoom->Refresh();

    getSport->Clear();
    getSport->SetValue(wxT("Pole nieaktywne"));
    getSport->Refresh();

    calendar->SetDate(wxGetCurrentTime());
    calendar->Refresh();

    wxDateTime now = wxDateTime::Now();
    timePick->SetTime(now.GetHour(), now.GetMinute(), now.GetSecond());
    timePick->Refresh();

    timePick2->SetTime(now.GetHour(), now.GetMinute(), now.GetSecond());
    timePick2->Refresh();
}

