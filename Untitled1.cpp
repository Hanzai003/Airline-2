#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Function prototypes
void show_options();
void client();
void administrator();
void reserve_flight();
void cancel_reserved_flight();
void display_flights();
void modify_flights();
void add_flight();  

int main() {
    system("color B0");
    int choice;

    do {
        show_options();
        cout << "Enter your choice (enter 0 to exit): ";
        cin >> choice;

        switch (choice) {
            case 1:
                client();
                break;
            case 2:
                administrator();
                break;
            case 0:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 0);

    return 0;
}

void show_options() {
    cout << "Welcome to the Airline Reservation System!" << endl;
    cout << "1. Client" << endl;
    cout << "2. Administrator" << endl;
}

void client() {
    string password;

    while (true) {
        cout << "Enter the password (enter 0 to go back to the main menu): ";
        cin >> password;

        if (password == "234") {
            int choice;
            cout << "Welcome, client! Here are your options:" << endl;
            cout << "1. Reserve a flight" << endl;
            cout << "2. Cancel a reserved flight" << endl;
            cout << "3. Display all flights" << endl;
            cout << "Enter your choice (enter 0 to go back to the main menu): ";
            cin >> choice;

            switch (choice) {
                case 1:
                    reserve_flight();
                    break;
                case 2:
                    cancel_reserved_flight();
                    break;
                case 3:
                    display_flights();
                    break;
                case 0:
                    cout << "Going back to the main menu." << endl;
                    return;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }
        } else if (password == "0") {
            cout << "Going back to the main menu." << endl;
            return;
        } else {
            cout << "Incorrect password. Try again." << endl;
        }
    }
}

void administrator() {
    string password;

    while (true) {
        cout << "Enter the password (enter 0 to go back to the main menu): ";
        cin >> password;

        if (password == "1234") {
            int choice;
            cout << "Welcome, administrator! Here are your options:" << endl;
            cout << "1. Modify flights" << endl;
            cout << "2. Add a flight" << endl;
            cout << "3. Display all flights" << endl;
            cout << "Enter your choice (enter 0 to go back to the main menu): ";
            cin >> choice;

            switch (choice) {
                case 1:
                    modify_flights();
                    break;
                case 2:
                    add_flight();
                    break;
                case 3:
                    display_flights();
                    break;
                case 0:
                    cout << "Going back to the main menu." << endl;
                    return;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }
        } else if (password == "0") {
            cout << "Going back to the main menu." << endl;
            return;
        } else {
            cout << "Incorrect password. Try again." << endl;
        }
    }
}

void reserve_flight() {
    string id, origin, destination, date, time;
    int available_seats;
    ifstream fin("flights.txt");
    ofstream fout("temp.txt");

    cout << "Enter the flight ID: ";
    cin >> id;

    bool found = false;
    while (fin >> id >> origin >> destination >> date >> time >> available_seats) {
        if (id == id) {
            found = true;
            if (available_seats == 0) {
                cout << "Sorry, the flight is fully booked." << endl;
                break;
            } else {
                available_seats--;
                fout << id << " " << origin << " " << destination << " " << date << " " << time << " " << available_seats << endl;
                cout << "Flight successfully reserved. " << available_seats << " seat(s) remaining." << endl;
            }
        } else {
            fout << id << " " << origin << " " << destination << " " << date << " " << time << " " << available_seats << endl;
        }
    }

    if (!found) {
        cout << "Sorry, no flight found with that ID." << endl;
    }

    fin.close();
    fout.close();

    if (rename("temp.txt", "flights.txt") != 0) {
        cout << "Error renaming file." << endl;
    }
}

void cancel_reserved_flight() {
    string id, origin, destination, date, time;
    int available_seats;
    ifstream fin("flights.txt");
    ofstream fout("temp.txt");

    cout << "Enter the flight ID: ";
    cin >> id;

    bool found = false;
    while (fin >> id >> origin >> destination >> date >> time >> available_seats) {
        if (id == id) {
            found = true;
            available_seats++;
            fout << id << " " << origin << " " << destination << " " << date << " " << time << " " << available_seats << endl;
            cout << "Reserved flight successfully cancelled. " << available_seats << " seat(s) available." << endl;
        } else {
            fout << id << " " << origin << " " << destination << " " << date << " " << time << " " << available_seats << endl;
        }
    }

    if (!found) {
        cout << "Sorry, no flight found with that ID." << endl;
    }

    fin.close();
    fout.close();

    if (rename("temp.txt", "flights.txt") != 0) {
        cout << "Error renaming file." << endl;
    }
}

void display_flights() {
    string id, origin, destination, date, time;
    int available_seats;
    ifstream fin("flights.txt");

    cout << setw(6) << left << "ID"
         << setw(13) << left << "Origin"
         << setw(13) << left << "Destination"
         << setw(10) << left << "Date"
         << setw(8) << left << "Time"
         << setw(15) << left << "Available Seats" << endl;

    while (fin >> id >> origin >> destination >> date >> time >> available_seats) {
        cout << setw(6) << left << id
             << setw(13) << left << origin
             << setw(13) << left << destination
             << setw(10) << left << date
             << setw(8) << left << time
             << setw(15) << left << available_seats << endl;
    }

    fin.close();
}

void modify_flights() {
    string id, newOrigin, newDestination, newDate, newTime;
    int newAvailableSeats;

    cout << "Existing Flight IDs: ";
    display_flights();

    cout << "Enter the flight ID to modify: ";
    cin >> id;

    ifstream fin("flights.txt");
    ofstream fout("temp.txt");

    bool found = false;
    while (fin >> id >> newOrigin >> newDestination >> newDate >> newTime >> newAvailableSeats) {
        if (id == id) {
            found = true;
            cout << "Enter new origin: ";
            cin >> newOrigin;
            cout << "Enter new destination: ";
            cin >> newDestination;
            cout << "Enter new date: ";
            cin >> newDate;
            cout << "Enter new time: ";
            cin >> newTime;
            cout << "Enter new available seats: ";
            cin >> newAvailableSeats;

            fout << id << " " << newOrigin << " " << newDestination << " " << newDate << " " << newTime << " " << newAvailableSeats << endl;
            cout << "Flight information successfully modified." << endl;
        } else {
            fout << id << " " << newOrigin << " " << newDestination << " " << newDate << " " << newTime << " " << newAvailableSeats << endl;
        }
    }

    if (!found) {
        cout << "Sorry, no flight found with that ID." << endl;
    }

    fin.close();
    fout.close();

    if (rename("temp.txt", "flights.txt") != 0) {
        cout << "Error renaming file." << endl;
    }
}

void add_flight() {
    string id, origin, destination, date, time;
    int available_seats;

    cout << "Enter the flight ID: ";
    cin >> id;

    ifstream checkExisting("flights.txt");
    string checkID;
    bool idExists = false;

    while (checkExisting >> checkID >> origin >> destination >> date >> time >> available_seats) {
        if (checkID == id) {
            idExists = true;
            break;
        }
    }

    checkExisting.close();

    if (idExists) {
        cout << "Flight with ID " << id << " already exists. Choose a different ID." << endl;
    } else {
        ofstream fout("flights.txt", ios::out | ios::app);

        cout << "Enter origin: ";
        cin >> origin;
        cout << "Enter destination: ";
        cin >> destination;
        cout << "Enter date: ";
        cin >> date;
        cout << "Enter time: ";
        cin >> time;
        cout << "Enter available seats: ";
        cin >> available_seats;

        fout << id << " " << origin << " " << destination << " " << date << " " << time << " " << available_seats << endl;
        cout << "Flight successfully added." << endl;

        fout.close();
    }
}

