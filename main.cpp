#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <vector>
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>

#include "Reservation.h"
#include "ReservationManager.h"
#include "MainFrame.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit()
    {
        MainFrame* frame = new MainFrame("Galaxy Reservations");
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
