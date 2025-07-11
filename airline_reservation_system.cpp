#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class to store Flight details
class Flight {
public:
    string flightNo;
    string flightName;
    string source;
    string destination;
    string date;
    string time;
    int totalSeats;
    int bookedSeats;

    Flight(string fNo, string fName, string src, string dest, string dt, string tm, int seats) {
        flightNo = fNo;
        flightName = fName;
        source = src;
        destination = dest;
        date = dt;
        time = tm;
        totalSeats = seats;
        bookedSeats = 0;
    }

    void displayDetails() {
        cout << "Flight No: " << flightNo << endl;
        cout << "Flight Name: " << flightName << endl;
        cout << "From: " << source << " To: " << destination << endl;
        cout << "Date: " << date << " Time: " << time << endl;
        cout << "Total Seats: " << totalSeats << " | Booked Seats: " << bookedSeats << endl;
        cout << "Available Seats: " << (totalSeats - bookedSeats) << endl;
    }
};

// Class to store Passenger details
class Passenger {
public:
    string name;
    int age;
    string id;
    string contact;
    string bookedFlightNo;

    Passenger(string n, int a, string i, string c, string fNo) {
        name = n;
        age = a;
        id = i;
        contact = c;
        bookedFlightNo = fNo;
    }

    void displayPassenger() {
        cout << "Name: " << name << ", Age: " << age
             << ", ID: " << id << ", Contact: " << contact
             << ", Flight No: " << bookedFlightNo << endl;
    }
};

vector<Flight> flights;
vector<Passenger> passengers;

// Add new flight
void addFlight() {
    string fNo, fName, src, dest, dt, tm;
    int seats;
    cout << "Enter Flight No: "; cin >> fNo;
    cout << "Enter Flight Name: "; cin >> fName;
    cout << "Source: "; cin >> src;
    cout << "Destination: "; cin >> dest;
    cout << "Date (DD/MM/YYYY): "; cin >> dt;
    cout << "Time (HH:MM): "; cin >> tm;
    cout << "Total Seats: "; cin >> seats;

    Flight newFlight(fNo, fName, src, dest, dt, tm, seats);
    flights.push_back(newFlight);
    cout << "Flight added successfully!\n";
}

// View all flights
void viewFlights() {
    if (flights.empty()) {
        cout << "No flights available.\n";
        return;
    }
    for (auto &f : flights) {
        f.displayDetails();
        cout << "-------------------------\n";
    }
}

// Delete a flight
void deleteFlight() {
    string fNo;
    cout << "Enter Flight No to delete: ";
    cin >> fNo;
    bool found = false;

    for (auto it = flights.begin(); it != flights.end(); ++it) {
        if (it->flightNo == fNo) {
            flights.erase(it);
            found = true;
            break;
        }
    }

    if (found) {
        // Remove passengers booked on this flight
        for (auto it = passengers.begin(); it != passengers.end();) {
            if (it->bookedFlightNo == fNo) {
                it = passengers.erase(it);
            } else {
                ++it;
            }
        }
        cout << "Flight and related bookings deleted successfully!\n";
    } else {
        cout << "Flight not found.\n";
    }
}

// Book a seat
void bookFlight() {
    string fNo;
    cout << "Enter Flight No to book: ";
    cin >> fNo;
    bool found = false;

    for (auto &f : flights) {
        if (f.flightNo == fNo) {
            found = true;
            if (f.bookedSeats < f.totalSeats) {
                string name, id, contact;
                int age;
                cout << "Enter Passenger Name: "; cin >> name;
                cout << "Age: "; cin >> age;
                cout << "ID/Passport: "; cin >> id;
                cout << "Contact: "; cin >> contact;

                Passenger p(name, age, id, contact, fNo);
                passengers.push_back(p);
                f.bookedSeats++;
                cout << "Booking successful!\n";
            } else {
                cout << "No seats available.\n";
            }
            break;
        }
    }
    if (!found) {
        cout << "Flight not found.\n";
    }
}

// View passengers in a flight
void viewPassengersInFlight() {
    string fNo;
    cout << "Enter Flight No: ";
    cin >> fNo;
    bool found = false;

    for (auto &p : passengers) {
        if (p.bookedFlightNo == fNo) {
            p.displayPassenger();
            found = true;
        }
    }
    if (!found) {
        cout << "No passengers found for this flight.\n";
    }
}

// Cancel booking for a passenger
void cancelBooking() {
    string id;
    cout << "Enter Passenger ID to cancel booking: ";
    cin >> id;
    bool found = false;

    for (auto it = passengers.begin(); it != passengers.end(); ++it) {
        if (it->id == id) {
            // Decrease bookedSeats in flight
            string fNo = it->bookedFlightNo;
            for (auto &f : flights) {
                if (f.flightNo == fNo) {
                    f.bookedSeats--;
                    break;
                }
            }
            passengers.erase(it);
            cout << "Booking cancelled successfully!\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Passenger not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n===== Airline Reservation System =====\n";
        cout << "1. Add Flight\n";
        cout << "2. View Flights\n";
        cout << "3. Book Flight\n";
        cout << "4. View Passengers in a Flight\n";
        cout << "5. Delete Flight\n";
        cout << "6. Cancel Booking\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addFlight(); break;
            case 2: viewFlights(); break;
            case 3: bookFlight(); break;
            case 4: viewPassengersInFlight(); break;
            case 5: deleteFlight(); break;
            case 6: cancelBooking(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}
