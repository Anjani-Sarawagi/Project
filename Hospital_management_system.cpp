#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class representing a patient
class Patient {
public:
    string name;
    string gender;
    int age;
    int ID;
};

// Class representing a doctor
class Doctor {
public:
    string name;
    string gender;
    int age;
    int experience;
    int ID;
};

// Class representing an appointment
class Appointment {
public:
    int Patient_ID;
    int Doctor_ID;
    string Date;
    string Time;
};

// Function to add a patient to the database
void addPatient(vector<Patient>& Pt) {
    Patient new_patient;
    cout << "Enter patient details:\n";
    cin.ignore(); // To handle leftover newline in buffer
    cout << "Name: ";
    getline(cin, new_patient.name);
    cout << "ID: ";
    cin >> new_patient.ID;
    cout << "Age: ";
    cin >> new_patient.age;
    cout << "Gender: ";
    cin >> new_patient.gender;

    Pt.push_back(new_patient); // Add patient to the vector
    cout << "Patient " << new_patient.name << " (ID: " << new_patient.ID << ") has been successfully added.\n";
}

// Function to add a doctor to the database
void addDoctor(vector<Doctor>& Dr) {
    Doctor new_doctor;
    cout << "Enter doctor details:\n";
    cin.ignore();
    cout << "Name: ";
    getline(cin, new_doctor.name);
    cout << "ID: ";
    cin >> new_doctor.ID;
    cout << "Experience (years): ";
    cin >> new_doctor.experience;
    cout << "Gender: ";
    cin >> new_doctor.gender;
    cout << "Age: ";
    cin >> new_doctor.age;

    Dr.push_back(new_doctor); // Add doctor to the vector
    cout << "Doctor " << new_doctor.name << " (ID: " << new_doctor.ID << ") has been successfully added.\n";
}

// Function to schedule an appointment after verifying doctor and patient exist
void addAppointment(vector<Appointment>& App, const vector<Patient>& Pt, const vector<Doctor>& Dr) {
    Appointment new_appointment;
    cout << "Enter appointment details:\n";
    cout << "Patient ID: ";
    cin >> new_appointment.Patient_ID;
    cout << "Doctor ID: ";
    cin >> new_appointment.Doctor_ID;

    // Verify patient and doctor exist
    bool patientExists = false, doctorExists = false;
    for (const auto& p : Pt)
        if (p.ID == new_appointment.Patient_ID) patientExists = true;
    for (const auto& d : Dr)
        if (d.ID == new_appointment.Doctor_ID) doctorExists = true;

    if (!patientExists || !doctorExists) {
        cout << "Invalid Patient ID or Doctor ID. Cannot schedule appointment.\n";
        return;
    }

    cout << "Date (DD/MM/YYYY): ";
    cin >> new_appointment.Date;
    cout << "Time (HH:MM): ";
    cin >> new_appointment.Time;

    App.push_back(new_appointment); // Add appointment to the vector
    cout << "Appointment scheduled successfully.\n";
}

// Function to remove a patient using their ID
void removePatient(vector<Patient>& Pt) {
    int ID;
    cout << "Enter Patient ID to remove: ";
    cin >> ID;

    for (auto it = Pt.begin(); it != Pt.end(); ++it) {
        if (it->ID == ID) {
            cout << "Removing Patient: " << it->name << " (ID: " << it->ID << ")\n";
            Pt.erase(it); // Remove patient
            return;
        }
    }
    cout << "Patient ID not found.\n";
}

// Function to remove a doctor using their ID
void removeDoctor(vector<Doctor>& Dr) {
    int ID;
    cout << "Enter Doctor ID to remove: ";
    cin >> ID;

    for (auto it = Dr.begin(); it != Dr.end(); ++it) {
        if (it->ID == ID) {
            cout << "Removing Doctor: " << it->name << " (ID: " << it->ID << ")\n";
            Dr.erase(it); // Remove doctor
            return;
        }
    }
    cout << "Doctor ID not found.\n";
}

// Function to remove an appointment using patient and doctor IDs
void removeAppointment(vector<Appointment>& App) {
    int Patient_ID, Doctor_ID;
    cout << "Enter Patient ID: ";
    cin >> Patient_ID;
    cout << "Enter Doctor ID: ";
    cin >> Doctor_ID;

    for (auto it = App.begin(); it != App.end(); ++it) {
        if (it->Patient_ID == Patient_ID && it->Doctor_ID == Doctor_ID) {
            App.erase(it); // Remove appointment
            cout << "Appointment removed successfully.\n";
            return;
        }
    }
    cout << "No matching appointment found.\n";
}

// Function to display the list of all patients
void viewPatients(const vector<Patient>& Pt) {
    if (Pt.empty()) {
        cout << "No patients available.\n";
        return;
    }
    for (size_t i = 0; i < Pt.size(); ++i) {
        cout << "(" << i + 1 << ")\n";
        cout << "Name: " << Pt[i].name << "\nID: " << Pt[i].ID
             << "\nAge: " << Pt[i].age << "\nGender: " << Pt[i].gender << "\n\n";
    }
}

// Function to display the list of all doctors
void viewDoctors(const vector<Doctor>& Dr) {
    if (Dr.empty()) {
        cout << "No doctors available.\n";
        return;
    }
    for (size_t i = 0; i < Dr.size(); ++i) {
        cout << "(" << i + 1 << ")\n";
        cout << "Name: " << Dr[i].name << "\nID: " << Dr[i].ID
             << "\nExperience: " << Dr[i].experience << " years"
             << "\nAge: " << Dr[i].age << "\nGender: " << Dr[i].gender << "\n\n";
    }
}

// Function to display the list of all appointments
void viewAppointments(const vector<Appointment>& App) {
    if (App.empty()) {
        cout << "No appointments available.\n";
        return;
    }
    for (size_t i = 0; i < App.size(); ++i) {
        cout << "(" << i + 1 << ")\n";
        cout << "Patient ID: " << App[i].Patient_ID
             << "\nDoctor ID: " << App[i].Doctor_ID
             << "\nDate: " << App[i].Date
             << "\nTime: " << App[i].Time << "\n\n";
    }
}

int main() {
    vector<Patient> Pt;
    vector<Doctor> Dr;
    vector<Appointment> App;

    // Display the menu
    cout << "WELCOME TO DR. MOHAR SINGH SURGICAL HOSPITAL, SIRSA (HARYANA)"<<endl;
    cout << "----- MENU -----"<<endl;
    cout << "1. Add Patient"<<endl;
    cout << "2. Add Doctor"<<endl;
    cout << "3. Schedule Appointment"<<endl;
    cout << "4. Remove Patient"<<endl;
    cout << "5. Remove Doctor"<<endl;
    cout << "6. Remove Appointment"<<endl;
    cout << "7. View Patients"<<endl;
    cout << "8. View Doctors"<<endl;
    cout << "9. View Appointments"<<endl;
    cout << "10. Exit"<<endl;

    int choice;
    // Infinite loop to keep menu running
    while (true) {
        cout << endl << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: addPatient(Pt); break;
            case 2: addDoctor(Dr); break;
            case 3: addAppointment(App, Pt, Dr); break;
            case 4: removePatient(Pt); break;
            case 5: removeDoctor(Dr); break;
            case 6: removeAppointment(App); break;
            case 7: viewPatients(Pt); break;
            case 8: viewDoctors(Dr); break;
            case 9: viewAppointments(App); break;
            case 10: cout << "Exiting the system. Goodbye!\n"; return 0;
            default: cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}