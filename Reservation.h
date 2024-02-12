#pragma once

class Reservation {
public:
     Reservation(const wxString& name, const wxString& time, const wxDateTime& date, const wxString& field, const wxString& duration, const wxString& phoneNumber)
        : name_(name), time_(time), date_(date), field_(field), duration_(duration), phoneNumber_(phoneNumber)
{
    // Calculate and set the end time based on the reservation time and duration
    wxString startTime = time_;
    wxString endTime;

    int startHour, startMinute;
    int durationHour, durationMinute;
    if (wxSscanf(time_.c_str(), "%d:%d", &startHour, &startMinute) == 2 &&
        wxSscanf(duration_.c_str(), "%d:%d", &durationHour, &durationMinute) == 2)
    {
        int endHour = startHour + durationHour;
        int endMinute = startMinute + durationMinute;

        if (endMinute >= 60)
        {
            endHour += 1;
            endMinute -= 60;
        }

        endTime = wxString::Format("%02d:%02d", endHour, endMinute);
    }

    end_ = endTime;
}


    wxString GetName() const { return name_; }
    wxString GetTime() const { return time_; }
    wxDateTime GetDate() const { return date_; }
    wxString GetField() const { return field_; }
    wxString GetReservationId() const { return reservationId_; }
    wxString GetDuration() const { return duration_; }
    wxString GetEndTime() const { return end_; }
    wxString GetPhoneNumber() const { return phoneNumber_; }
    wxString GetEnd() const { return end_; }




    void SetDuration(const wxString& duration) { duration_ = duration; }
    void SetReservationId(const wxString& id) { reservationId_ = id; }
    void SetTime(const wxString& time) { time_ = time; }
    void SetDate(const wxDateTime& date) { date_ = date; }
    void SetName(const wxString& name) {name_ = name; }
    void SetEnd(const wxString& endTime) {end_ = endTime; }


private:
    wxString name_;
    wxString time_;
    wxDateTime date_;
    wxString field_;
    wxString reservationId_;
    wxString duration_;
    wxString end_;
    wxString phoneNumber_;
};
