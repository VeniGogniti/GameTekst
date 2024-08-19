//
// Created by stefx on 9/8/24.
//

#ifndef GAMETEKST_RESERVATION_HPP
#define GAMETEKST_RESERVATION_HPP

#include <string>
#include "wx/wx.h"
#include "wx/listctrl.h"

//Test file for now
class Reservation {
private:
    wxPanel* prv_panel;
    std::string prv_surname;
    std::string prv_name;
    std::string prv_phone;
    std::string prv_room;
    std::string prv_sport;
    std::string prv_data;
    std::string prv_time;
    bool arrivalConfirmation = false;
    bool eraseReservation = false;

public:
    Reservation(wxPanel* panel, std::string& surname, std::string& name, std::string& phone);

    void makeReservation();
};


#endif //GAMETEKST_RESERVATION_HPP
