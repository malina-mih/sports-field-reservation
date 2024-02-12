#pragma once

class ReservationManager {
public:

    void AddReservation(const Reservation& reservation)
    {
        reservations_.push_back(reservation);
    }



    std::vector<Reservation> GetAllReservations() const
    {
        return reservations_;
    }



        void LoadReservationsFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            return;
        }

        reservations_.clear();

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string name, time, date, field, duration, phoneNumber;
            if (iss >> name >> time >> date >> field >> duration >> phoneNumber)
            {
                // Create a new Reservation object and add it to the vector
                wxDateTime wxDate;
                wxDate.ParseISODate(date);
                Reservation reservation(wxString::FromUTF8(name), wxString::FromUTF8(time), wxDate, wxString::FromUTF8(field), wxString::FromUTF8(duration), wxString::FromUTF8(phoneNumber));
                reservations_.push_back(reservation);
            }
        }

        file.close();
    }
    std::vector<Reservation>& GetAllReservations()
{
    return reservations_;
}


    void SaveReservationsToFile(const std::string& filename)
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            return;
        }

        for (const auto& reservation : reservations_)
        {
            file << reservation.GetName().ToStdString() << " "
                 << reservation.GetTime().ToStdString() << " "
                 << reservation.GetDate().FormatISODate().ToStdString() << " "
                 << reservation.GetField().ToStdString() << " "
                 << reservation.GetDuration().ToStdString() << " "
                 << reservation.GetPhoneNumber().ToStdString() << "\n";
        }

        file.close();
    }
private:
    std::vector<Reservation> reservations_;
};
