#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Movie class with hall seats
class Movie {
public:
    string movieName;
    string time;
    string hall;
    int rows;
    int cols;
    int price;
    vector<vector<bool>> seats; // true = booked

    Movie(string name, string t, string h, int r, int c, int p) {
        movieName = name;
        time = t;
        hall = h;
        rows = r;
        cols = c;
        price = p;
        seats = vector<vector<bool>>(rows, vector<bool>(cols, false));
    }

    void displayMovie() {
        cout << "Movie: " << movieName << endl;
        cout << "Time: " << time << ", Hall: " << hall << endl;
        cout << "Price: " << price << " per ticket" << endl;
        cout << "Seat Layout:\n";
        displayHall();
        cout << "----------------------------------------" << endl;
    }

    void displayHall() {
        for (int i = 0; i < rows; i++) {
            char rowChar = 'A' + i;
            for (int j = 0; j < cols; j++) {
                if (seats[i][j]) {
                    cout << " X ";
                } else {
                    cout << " " << rowChar << (j + 1) << " ";
                }
            }
            cout << endl;
        }
    }

    bool isSeatAvailable(string seatCode) {
        if (seatCode.length() < 2) return false;
        char rowChar = seatCode[0];
        int row = rowChar - 'A';
        int col = stoi(seatCode.substr(1)) - 1;

        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return !seats[row][col];
        }
        return false;
    }

    bool bookSeat(string seatCode) {
        char rowChar = seatCode[0];
        int row = rowChar - 'A';
        int col = stoi(seatCode.substr(1)) - 1;

        if (row >= 0 && row < rows && col >= 0 && col < cols && !seats[row][col]) {
            seats[row][col] = true;
            return true;
        }
        return false;
    }

    void cancelSeat(string seatCode) {
        char rowChar = seatCode[0];
        int row = rowChar - 'A';
        int col = stoi(seatCode.substr(1)) - 1;

        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            seats[row][col] = false;
        }
    }
};

// Booking class
class Booking {
public:
    string customerName;
    string movieName;
    string seatCode;
    int amount;

    Booking(string name, string mName, string seat, int amt) {
        customerName = name;
        movieName = mName;
        seatCode = seat;
        amount = amt;
    }

    void displayBooking() {
        cout << "Customer: " << customerName
             << ", Movie: " << movieName
             << ", Seat: " << seatCode
             << ", Amount: " << amount << endl;
    }
};

vector<Movie> movies;
vector<Booking> bookings;

// Add new movie
void addMovie() {
    string name, time, hall;
    int rows, cols, price;
    cout << "Enter movie name: ";
    cin >> ws;
    getline(cin, name);
    cout << "Time: ";
    getline(cin, time);
    cout << "Hall name: ";
    getline(cin, hall);
    cout << "Number of rows in hall: ";
    cin >> rows;
    cout << "Number of seats per row: ";
    cin >> cols;
    cout << "Price per ticket: ";
    cin >> price;

    Movie newMovie(name, time, hall, rows, cols, price);
    movies.push_back(newMovie);
    cout << "Movie added successfully!\n";
}

// View all movies
void viewMovies() {
    if (movies.empty()) {
        cout << "No movies available.\n";
        return;
    }
    for (auto &m : movies) {
        m.displayMovie();
    }
}

// Book ticket (updated to retry if seat is booked)
void bookTicket() {
    string movieName;
    cout << "Enter movie name to book ticket: ";
    cin >> ws;
    getline(cin, movieName);
    bool found = false;

    for (auto &m : movies) {
        if (m.movieName == movieName) {
            found = true;
            m.displayHall();

            bool booked = false;
            do {
                string seatCode;
                cout << "Enter seat code to book (e.g. A1): ";
                cin >> seatCode;

                if (m.isSeatAvailable(seatCode)) {
                    if (m.bookSeat(seatCode)) {
                        string custName;
                        cout << "Enter your name: ";
                        cin >> ws;
                        getline(cin, custName);
                        int amount = m.price;
                        Booking b(custName, movieName, seatCode, amount);
                        bookings.push_back(b);
                        cout << "Booking successful! Amount: " << amount << endl;
                        booked = true;
                    } else {
                        cout << "Seat booking failed.\n";
                    }
                } else {
                    cout << "Seat not available.\n";
                    cout << "Do you want to try another seat? (Y/N): ";
                    char ch;
                    cin >> ch;
                    if (ch == 'N' || ch == 'n') {
                        booked = true; // exit loop
                    }
                    // else booked remains false → loop again
                }
            } while (!booked);
            break;
        }
    }
    if (!found) {
        cout << "Movie not found.\n";
    }
}

// Cancel booking
void cancelBooking() {
    string custName, movieName, seatCode;
    cout << "Enter your name: ";
    cin >> ws;
    getline(cin, custName);
    cout << "Enter movie name: ";
    getline(cin, movieName);
    cout << "Enter seat code to cancel (e.g. A1): ";
    getline(cin, seatCode);

    bool found = false;

    for (auto it = bookings.begin(); it != bookings.end(); ++it) {
        if (it->customerName == custName && it->movieName == movieName && it->seatCode == seatCode) {
            // Cancel seat in movie
            for (auto &m : movies) {
                if (m.movieName == movieName) {
                    m.cancelSeat(seatCode);
                    break;
                }
            }
            bookings.erase(it);
            cout << "Booking cancelled successfully.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Booking not found.\n";
    }
}

// Show all bookings
void showBookings() {
    if (bookings.empty()) {
        cout << "No bookings yet.\n";
        return;
    }
    for (auto &b : bookings) {
        b.displayBooking();
    }
}

int main() {
    int choice;
    do {
        cout << "\n=== Movie Ticket Management System ===\n";
        cout << "1. Add Movie\n";
        cout << "2. View Movies\n";
        cout << "3. Book Ticket\n";
        cout << "4. Cancel Booking\n";
        cout << "5. Show All Bookings\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addMovie(); break;
            case 2: viewMovies(); break;
            case 3: bookTicket(); break;
            case 4: cancelBooking(); break;
            case 5: showBookings(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
