# Sports Field Reservation System

## Overview

The Sports Field Reservation System is a C++ application built using the wxWidgets library. It provides a user-friendly interface for managing sports reservations, allowing users to add, edit, and delete reservations for various sports fields.

## Features

- **Add Reservation:** Users can add new reservations, providing details such as name, phone number, date, time, sports field, and duration.

- **Edit Reservation:** Modify existing reservations, including date, time, and user details.

- **Delete Reservation:** Remove reservations that are no longer needed.

- **View Reservations:**
  - Display all reservations.
  - Filter reservations by sports field.
  - Filter reservations by date.


## File Structure

- **main.cpp:** Contains the main application logic, including the user interface and interaction with reservation data.

- **Reservation.h** Contains declarations for member functions to get and set reservation details such as name, time, date, field, duration, etc.
- **ReservationManager.h** Contains declarations for functions to add, retrieve, and manipulate reservations and includes methods to load reservations from a file, save reservations to a file, and get all reservations.
- **MainFrame.h:** Contains declarations for functions related to the user interface and interaction with reservations.
  




## Data Storage

- Reservations are stored in a text file (`reservations.txt`). The application reads from and writes to this file to persist reservation data.

