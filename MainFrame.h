#pragma once

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(900, 900)), // Increased size of the main frame
          reservationManager_()
    {
        // Set background color
        SetBackgroundColour(wxColour(226, 230, 231));  // Light gray color

        // Create the main panel
        wxPanel* panel = new wxPanel(this);

        // Create the buttons
        wxButton* btnAddReservation = new wxButton(panel, wxID_ANY, "Add Reservation");
        wxButton* btnEditReservation = new wxButton(panel, wxID_ANY, "Edit Reservation");
        wxButton* btnDeleteReservation = new wxButton(panel, wxID_ANY, "Delete Reservation");
        wxButton* btnShowReservationsByField = new wxButton(panel, wxID_ANY, "Show Reservations by Field");
        wxButton* btnShowReservationsByDate = new wxButton(panel, wxID_ANY, "Show Reservations by Date");
        wxButton* btnShowAllReservations = new wxButton(panel, wxID_ANY, "Show All Reservations");

        // Set button colors
        btnAddReservation->SetBackgroundColour(wxColour(62, 150, 48));      // Green color
        btnEditReservation->SetBackgroundColour(wxColour(217, 187, 56));     // Yellow color
        btnDeleteReservation->SetBackgroundColour(wxColour(171, 41, 41));     // Red color

        // Set button font
        wxFont buttonFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);  // Increased font size
        btnAddReservation->SetFont(buttonFont);
        btnEditReservation->SetFont(buttonFont);
        btnDeleteReservation->SetFont(buttonFont);
        btnShowReservationsByField->SetFont(buttonFont);
        btnShowReservationsByDate->SetFont(buttonFont);
        btnShowAllReservations->SetFont(buttonFont);

        // Create the main sizer
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        // Add buttons to the main sizer
        mainSizer->Add(btnAddReservation, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 15);  // Increased button spacing
        mainSizer->Add(btnEditReservation, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 15);
        mainSizer->Add(btnDeleteReservation, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 15);
        mainSizer->Add(btnShowReservationsByField, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 15);
        mainSizer->Add(btnShowReservationsByDate, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 15);
        mainSizer->Add(btnShowAllReservations, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 15);

        // Set sizer for the panel
        panel->SetSizer(mainSizer);

        // Bind button events
        btnAddReservation->Bind(wxEVT_BUTTON, &MainFrame::OnAddReservation, this);
        btnEditReservation->Bind(wxEVT_BUTTON, &MainFrame::OnEditReservation, this);
        btnDeleteReservation->Bind(wxEVT_BUTTON, &MainFrame::OnDeleteReservation, this);
        btnShowReservationsByField->Bind(wxEVT_BUTTON, &MainFrame::OnShowReservationsByField, this);
        btnShowReservationsByDate->Bind(wxEVT_BUTTON, &MainFrame::OnShowReservationsByDate, this);
        btnShowAllReservations->Bind(wxEVT_BUTTON, &MainFrame::OnShowAllReservations, this);



        reservationManager_.LoadReservationsFromFile("reservations.txt");
    }

    ~MainFrame()
    {
        reservationManager_.SaveReservationsToFile("reservations.txt");
    }


void OnAddReservation(wxCommandEvent& event)
{
    wxString name;
    wxDateTime date;
    int selectedTimeIndex;
    wxString field;
    int selectedDurationIndex;
    wxString duration;
    wxString phoneNumber;

    while (true)
    {
        name = wxGetTextFromUser("Enter your name:", "Add Reservation");
        if (!IsValidName(name))
        {
            wxMessageBox("Invalid name! Name should only contain letters and spaces.", "Add Reservation Error", wxOK | wxICON_ERROR);
            continue;
        }
        break;
    }

    while (true)
    {
        phoneNumber = wxGetTextFromUser("Enter your phone number:", "Add Reservation");
        if (!IsValidPhoneNumber(phoneNumber))
        {
            wxMessageBox("Invalid phone number! Please enter a valid phone number.", "Add Reservation Error", wxOK | wxICON_ERROR);
            continue;
        }
        break;
    }

    wxDialog dateDialog(this, wxID_ANY, "Pick a Date");

    wxDatePickerCtrl* datePickerCtrl = new wxDatePickerCtrl(&dateDialog, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(datePickerCtrl, 0, wxALL, 10);
    sizer->Add(dateDialog.CreateStdDialogButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, 10);

    dateDialog.SetSizerAndFit(sizer);

    if (dateDialog.ShowModal() == wxID_OK)
    {
        date = datePickerCtrl->GetValue();

        std::vector<wxString> timeOptions;
        for (int hour = 8; hour < 20; ++hour)
        {
            for (int minute = 0; minute < 60; minute += 30)
            {
                wxString timeOption = wxString::Format("%02d:%02d", hour, minute);
                timeOptions.push_back(timeOption);
            }
        }

        wxArrayString timeOptionsArray;
        for (const auto& option : timeOptions)
        {
            timeOptionsArray.Add(option);
        }

        wxSingleChoiceDialog timeDialog(this, "Select the reservation time:", "Add Reservation", timeOptionsArray);
        if (timeDialog.ShowModal() == wxID_OK)
        {
            selectedTimeIndex = timeDialog.GetSelection();
            if (selectedTimeIndex != wxNOT_FOUND)
            {
                wxString selectedTime = timeOptions[selectedTimeIndex];

                std::vector<wxString> durationOptions = {
                        "30 minutes",
                        "1 hour",
                        "1.5 hours",
                        "2 hours",
                        "Custom duration"
                    };

                wxArrayString durationOptionsArray;
                for (const auto& option : durationOptions)
                {
                    durationOptionsArray.Add(option);
                }

                wxSingleChoiceDialog durationDialog(this, "Select the reservation duration:", "Add Reservation", durationOptionsArray);
                if (durationDialog.ShowModal() == wxID_OK)
                {
                    selectedDurationIndex = durationDialog.GetSelection();
                    if (selectedDurationIndex != wxNOT_FOUND)
                    {
                        wxString selectedDuration = durationOptions[selectedDurationIndex];

                        if (selectedDuration == "Custom duration")
                        {
                            wxString customDurationText = wxGetTextFromUser("Enter the custom duration (in minutes):", "Add Reservation");
                            long customDurationValue;

                            if (customDurationText.ToLong(&customDurationValue))
                            {
                                int hour = customDurationValue / 60;
                                int minute = customDurationValue % 60;
                                duration = wxString::Format("%02d:%02d", hour, minute);
                            }
                            else
                            {
                                wxMessageBox("Invalid custom duration! Please enter a valid integer value.", "Add Reservation Error", wxOK | wxICON_ERROR);
                                return;
                            }
                        }
                        else if (selectedDuration == "30 minutes")
                        {
                            int hour = 0;
                            int minute = 30;
                            duration = wxString::Format("%02d:%02d", hour, minute);
                        }
                        else if (selectedDuration == "1 hour")
                        {
                            int hour = 1;
                            int minute = 0;
                            duration = wxString::Format("%02d:%02d", hour, minute);
                        }
                        else if (selectedDuration == "1.5 hours")
                        {
                            int hour = 1;
                            int minute = 30;
                            duration = wxString::Format("%02d:%02d", hour, minute);
                        }
                        else if (selectedDuration == "2 hours")
                        {
                            int hour = 2;
                            int minute = 0;
                            duration = wxString::Format("%02d:%02d", hour, minute);
                        }

                        std::vector<wxString> fieldOptions = {
                            "Football1",
                            "Football2",
                            "Football3",
                            "Football4",
                            "Tennis1",
                            "Tennis2",
                            "Padbol",
                            "Volleyball"
                        };

                        wxArrayString fieldOptionsArray;
                        for (const auto& option : fieldOptions)
                        {
                            fieldOptionsArray.Add(option);
                        }

                        wxSingleChoiceDialog fieldDialog(this, "Select the sports field:", "Add Reservation", fieldOptionsArray);
                        if (fieldDialog.ShowModal() == wxID_OK)
                        {
                            wxString selectedField = fieldOptions[fieldDialog.GetSelection()];

                            Reservation reservation(name, selectedTime, date, selectedField, duration, phoneNumber);
                            reservation.SetDuration(duration);

                            wxString endTime = reservation.GetEndTime();
                            int endHour, endMinute;
                            if (wxSscanf(endTime.c_str(), "%d:%d", &endHour, &endMinute) == 2)
                            {
                                if (endHour >= 22)
                                {
                                    wxMessageBox("End time cannot exceed 22:00.", "Add Reservation Error", wxOK | wxICON_ERROR);
                                    return;
                                }
                            }

                            reservationManager_.AddReservation(reservation);
                            wxMessageBox("Reservation added successfully!", "Add Reservation", wxOK | wxICON_INFORMATION);
                        }
                    }
                }
            }
        }
    }
}




void OnShowAllReservations(wxCommandEvent& event)
{
    std::vector<Reservation> reservations = reservationManager_.GetAllReservations();

    // Sort reservations by date and time
    std::sort(reservations.begin(), reservations.end(), [](const Reservation& a, const Reservation& b) {
        if (a.GetDate() != b.GetDate())
            return a.GetDate() < b.GetDate();
        return a.GetTime() < b.GetTime();
    });

    wxString reservationsData;
    for (const auto& reservation : reservations)
    {
        reservationsData += "Name: " + reservation.GetName() + "\n";
        reservationsData += "Phone Number: " + reservation.GetPhoneNumber() + "\n";
        reservationsData += "Field: " + reservation.GetField() + "\n";
        reservationsData += "Date: " + reservation.GetDate().FormatISODate() + "\n";
        reservationsData += "Time: " + reservation.GetTime() + " - " + reservation.GetEndTime() + "\n";
        reservationsData += "------------------------\n";
    }

    wxMessageBox(reservationsData, "All Reservations", wxOK | wxICON_INFORMATION);
}

void ShowReservationsByField(const wxString& fieldName)
{
    std::vector<Reservation> reservations = reservationManager_.GetAllReservations();

    // Sort reservations by date and time
    std::sort(reservations.begin(), reservations.end(), [](const Reservation& a, const Reservation& b) {
        if (a.GetDate() == b.GetDate())
        {
            return a.GetTime() < b.GetTime();
        }
        return a.GetDate() < b.GetDate();
    });

    wxString reservationsData;
    for (const auto& reservation : reservations)
    {
        if (reservation.GetField() == fieldName)
        {
            reservationsData += "Name: " + reservation.GetName() + "\n";
            reservationsData += "Phone Number: " + reservation.GetPhoneNumber() + "\n";
            reservationsData += "Field: " + reservation.GetField() + "\n";
            reservationsData += "Date: " + reservation.GetDate().FormatISODate() + "\n";
            reservationsData += "Time: " + reservation.GetTime() + " - " + reservation.GetEndTime() + "\n";
            reservationsData += "------------------------\n";
        }
    }

    if (!reservationsData.IsEmpty())
    {
        wxMessageBox(reservationsData, "Reservations for " + fieldName, wxOK | wxICON_INFORMATION);
    }
    else
    {
        wxMessageBox("No reservations found for " + fieldName, "Reservations", wxOK | wxICON_INFORMATION);
    }
}


void OnShowReservationsByField(wxCommandEvent& event){
    std::vector<wxString> fieldOptions = {
        "Football1",
        "Football2",
        "Football3",
        "Football4",
        "Tennis1",
        "Tennis2",
        "Padbol",
        "Volleyball"
    };

    wxArrayString fieldOptionsArray;
    for (const auto& option : fieldOptions)
    {
        fieldOptionsArray.Add(option);
    }

    wxSingleChoiceDialog fieldDialog(this, "Select a field name:", "Show Reservations by Field", fieldOptionsArray);
    if (fieldDialog.ShowModal() == wxID_OK)
    {
        wxString selectedField = fieldOptions[fieldDialog.GetSelection()];

        ShowReservationsByField(selectedField);
    }

}


void OnShowReservationsByDate(wxCommandEvent& event)
{
    wxDialog dateDialog(this, wxID_ANY, "Pick a Date");

    wxDatePickerCtrl* datePickerCtrl = new wxDatePickerCtrl(&dateDialog, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(datePickerCtrl, 0, wxALL, 10);
    sizer->Add(dateDialog.CreateStdDialogButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, 10);

    dateDialog.SetSizerAndFit(sizer);

    if (dateDialog.ShowModal() == wxID_OK)
    {
        wxDateTime selectedDate = datePickerCtrl->GetValue();

        std::vector<Reservation> reservations;

        // Filter reservations based on the selected date
        for (const auto& reservation : reservationManager_.GetAllReservations())
        {
            if (reservation.GetDate().IsSameDate(selectedDate))
            {
                reservations.push_back(reservation);
            }
        }

        // Sort reservations by field name and time
        std::sort(reservations.begin(), reservations.end(), [](const Reservation& a, const Reservation& b) {
            if (a.GetField() != b.GetField())
                return a.GetField() < b.GetField();
            return a.GetTime() < b.GetTime();
        });

        wxString reservationsData;
        wxString currentField;

        for (const auto& reservation : reservations)
        {
            if (reservation.GetField() != currentField)
            {
                currentField = reservation.GetField();
                reservationsData += "Field: " + currentField + "\n";
                reservationsData += "------------------------\n";
            }

            reservationsData += "Name: " + reservation.GetName() + "\n";
            reservationsData += "Phone Number: " + reservation.GetPhoneNumber() + "\n";
            reservationsData += "Date: " + reservation.GetDate().FormatISODate() + "\n";
            reservationsData += "Time: " + reservation.GetTime() + " - " + reservation.GetEndTime() + "\n";
            reservationsData += "------------------------\n";
        }

        if (reservationsData.IsEmpty())
        {
            reservationsData = "No reservations found for the selected date.";
        }

        wxMessageBox(reservationsData, "Reservations for " + selectedDate.FormatISODate(), wxOK | wxICON_INFORMATION);
    }
}





void CalculateEndTime(Reservation& reservation)
{
    wxString endTime;
    wxString startTime = reservation.GetTime();
    wxString duration_ = reservation.GetDuration();
    int startHour, startMinute;
    int durationHour, durationMinute;
    if (wxSscanf(startTime.c_str(), "%d:%d", &startHour, &startMinute) == 2 &&
        wxSscanf(duration_.c_str(), "%d:%d", &durationHour, &durationMinute) == 2)
    {
        int endHour = startHour + durationHour;
        int endMinute = startMinute + durationMinute;

        if (endMinute >= 60)
        {
            endHour += 1;
            endMinute -= 60;
        }

        // Check if the end time is after 22:00
        if (endHour > 22 || (endHour == 22 && endMinute > 0))
        {
            wxMessageBox("Invalid reservation! The reservation end time should not exceed 22:00.", "Add Reservation Error", wxOK | wxICON_ERROR);
            return;
        }

        endTime = wxString::Format("%02d:%02d", endHour, endMinute);
    }
    reservation.SetEnd(endTime);
}




void OnEditReservation(wxCommandEvent& event)
{
    std::vector<Reservation>& reservations = reservationManager_.GetAllReservations();

    if (reservations.empty())
    {
        wxMessageBox("There are no reservations to edit.", "Edit Reservation", wxOK | wxICON_INFORMATION);
        return;
    }

    std::vector<wxString> choices;
    for (const auto& reservation : reservations)
    {
        wxString choice = reservation.GetName() + " - " + reservation.GetTime() + " - " + reservation.GetDate().FormatISODate();
        choices.push_back(choice);
    }

    wxArrayString choicesArray;
    for (const auto& choice : choices)
    {
        choicesArray.Add(choice);
    }

    wxSingleChoiceDialog dialog(this, "Select a reservation to edit:", "Edit Reservation", choicesArray);
    if (dialog.ShowModal() == wxID_OK)
    {
        int selectedIndex = dialog.GetSelection();
        if (selectedIndex != wxNOT_FOUND)
        {
            Reservation& reservation = reservations[selectedIndex];

            wxDialog editDialog(this, wxID_ANY, "Edit Reservation");

            wxDatePickerCtrl* datePickerCtrl = new wxDatePickerCtrl(&editDialog, wxID_ANY, reservation.GetDate(), wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);
            wxTextCtrl* timeTextCtrl = new wxTextCtrl(&editDialog, wxID_ANY, reservation.GetTime(), wxDefaultPosition, wxDefaultSize);
            wxTextCtrl* nameTextCtrl = new wxTextCtrl(&editDialog, wxID_ANY, reservation.GetName(), wxDefaultPosition, wxDefaultSize);

            wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
            sizer->Add(datePickerCtrl, 0, wxALL, 10);
            sizer->Add(timeTextCtrl, 0, wxALL, 10);
            sizer->Add(nameTextCtrl, 0, wxALL, 10);
            sizer->Add(editDialog.CreateStdDialogButtonSizer(wxOK), 0, wxALL | wxALIGN_RIGHT, 10);

            editDialog.SetSizerAndFit(sizer);

            if (editDialog.ShowModal() == wxID_OK)
            {
                wxDateTime newDate = datePickerCtrl->GetValue();
                wxString newTime = timeTextCtrl->GetValue();
                wxString newName = nameTextCtrl->GetValue();

                // Validate the name
                if (!IsValidName(newName))
                {
                    wxMessageBox("Invalid name! Name should only contain letters and spaces.", "Edit Reservation Error", wxOK | wxICON_ERROR);
                    return;
                }

                // Validate the time
                if (!IsValidTime(newTime))
                {
                    wxMessageBox("Invalid time! Please enter a valid time in HH:MM format.", "Edit Reservation Error", wxOK | wxICON_ERROR);
                    return;
                }

                // Create a temporary reservation with the edited values
                Reservation editedReservation(newName, newTime, newDate, reservation.GetField(), reservation.GetDuration(), reservation.GetPhoneNumber());
                CalculateEndTime(editedReservation);

                // Check if the end time of the edited reservation exceeds 22:00
                int endHour, endMinute;
                wxString endTime = editedReservation.GetEnd();
                if (wxSscanf(endTime.c_str(), "%d:%d", &endHour, &endMinute) == 2)
                {
                    if (endHour > 22 || (endHour == 22 && endMinute > 0))
                    {
                        wxMessageBox("Invalid reservation! The edited end time should not exceed 22:00.", "Edit Reservation Error", wxOK | wxICON_ERROR);
                        return;
                    }
                }

                // Update the original reservation only if the end time is within bounds
                reservation.SetDate(newDate);
                reservation.SetTime(newTime);
                reservation.SetName(newName);
                CalculateEndTime(reservation);

                // Rewrite the file with the modified reservations
                reservationManager_.SaveReservationsToFile("reservations.txt");

                wxMessageBox("Reservation updated successfully!", "Edit Reservation", wxOK | wxICON_INFORMATION);

                // Refresh the displayed reservations
                OnShowAllReservations(event);
            }
        }
    }
}


void OnDeleteReservation(wxCommandEvent& event)
{
    std::vector<Reservation>& reservations = reservationManager_.GetAllReservations();

    if (reservations.empty())
    {
        wxMessageBox("There are no reservations to delete.", "Delete Reservation", wxOK | wxICON_INFORMATION);
        return;
    }

    std::vector<wxString> choices;
    for (const auto& reservation : reservations)
    {
        wxString choice = reservation.GetName() + " - " + reservation.GetTime() + " - " + reservation.GetDate().FormatISODate();
        choices.push_back(choice);
    }

    wxArrayString choicesArray;
    for (const auto& choice : choices)
    {
        choicesArray.Add(choice);
    }

    wxSingleChoiceDialog dialog(this, "Select a reservation to delete:", "Delete Reservation", choicesArray);
    if (dialog.ShowModal() == wxID_OK)
    {
        int selectedIndex = dialog.GetSelection();
        if (selectedIndex != wxNOT_FOUND)
        {
            Reservation& reservation = reservations[selectedIndex];

            int result = wxMessageBox("Are you sure you want to delete this reservation?", "Confirm Deletion", wxYES_NO | wxICON_QUESTION);
            if (result == wxYES)
            {
                // Remove the reservation from the vector
                reservations.erase(reservations.begin() + selectedIndex);

                // Rewrite the file with the modified reservations
                reservationManager_.SaveReservationsToFile("reservations.txt");

                wxMessageBox("Reservation deleted successfully!", "Delete Reservation", wxOK | wxICON_INFORMATION);

                // Refresh the displayed reservations
                OnShowAllReservations(event);
            }
        }
    }
}



private:
    bool IsValidName(const wxString& name)
    {
        for (const auto& ch : name)
        {
            if (!wxIsalpha(ch) && !wxIsspace(ch))
                return false;
        }
        return true;
    }
    bool IsValidPhoneNumber(const wxString& phoneNumber)
{
    wxString digitsOnly = phoneNumber;
    // Check if the resulting string has exactly 10 digits
    return digitsOnly.length() == 10;
}

    bool IsValidTime(const wxString& time)
    {
        int hour = 0;
        int minute = 0;
        if (wxSscanf(time, "%d:%d", &hour, &minute) != 2)
            return false;

        if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
            return false;

        return true;
    }
    ReservationManager reservationManager_;
};
