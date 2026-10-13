#include <iostream>
using namespace std;

// ==================== Array-Based Circular Queue ====================
const int MAX_PATIENTS = 100;

class WaitingRoom {
private:
    int patientIds[MAX_PATIENTS];
    int frontIndex;
    int rearIndex;
    int count;
    int nextPatientId;

public:
    WaitingRoom() {
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
        nextPatientId = 1;
    }

    // Register a patient and assign the next available ID.
    void RegisterPatient() {
        if (count == MAX_PATIENTS) {
            cout << "Waiting room is full. Patient cannot be registered.\n";
            return;
        }

        rearIndex = (rearIndex + 1) % MAX_PATIENTS;
        patientIds[rearIndex] = nextPatientId;
        count++;

        cout << "Patient registered successfully. Assigned ID: "
             << nextPatientId << "\n";

        nextPatientId++;
    }

    // Serve and remove the patient who has waited the longest.
    void ServePatient() {
        if (CanDoctorGoHome()) {
            cout << "No patients are waiting to be served.\n";
            return;
        }

        int servedId = patientIds[frontIndex];
        frontIndex = (frontIndex + 1) % MAX_PATIENTS;
        count--;

        if (count == 0) {
            frontIndex = 0;
            rearIndex = -1;
        }

        cout << "Patient ID " << servedId << " has been called for service.\n";
    }

    // Remove every patient currently waiting.
    void CancelAll() {
        if (CanDoctorGoHome()) {
            cout << "There are no waiting patients to cancel.\n";
            return;
        }

        int cancelledCount = count;

        frontIndex = 0;
        rearIndex = -1;
        count = 0;

        cout << "All " << cancelledCount
             << " waiting patient appointment(s) have been cancelled.\n";
    }

    // Return true if the waiting room is empty.
    bool CanDoctorGoHome() const {
        return count == 0;
    }

    // Display waiting patient IDs in ascending sorted order.
    void ShowAllPatient() const {
        if (CanDoctorGoHome()) {
            cout << "No patients are waiting.\n";
            return;
        }

        // Copy the IDs from the circular queue into a temporary array.
        int sortedIds[MAX_PATIENTS];

        for (int i = 0; i < count; i++) {
            int queueIndex = (frontIndex + i) % MAX_PATIENTS;
            sortedIds[i] = patientIds[queueIndex];
        }

        // Sort the copied IDs using selection sort.
        for (int i = 0; i < count - 1; i++) {
            int smallestIndex = i;

            for (int j = i + 1; j < count; j++) {
                if (sortedIds[j] < sortedIds[smallestIndex]) {
                    smallestIndex = j;
                }
            }

            int temporary = sortedIds[i];
            sortedIds[i] = sortedIds[smallestIndex];
            sortedIds[smallestIndex] = temporary;
        }

        cout << "Waiting patient IDs in sorted order: ";

        for (int i = 0; i < count; i++) {
            cout << sortedIds[i];

            if (i < count - 1) {
                cout << ", ";
            }
        }

        cout << "\n";
    }
};

// ==================== Main Menu ====================
int main() {
    WaitingRoom room;
    int choice;

    do {
        cout << "\n============================================\n";
        cout << "       TASK 4 - Waiting Room Management\n";
        cout << "============================================\n";
        cout << "1. Register a patient\n";
        cout << "2. Serve the next patient\n";
        cout << "3. Cancel all waiting appointments\n";
        cout << "4. Check if the doctor can go home\n";
        cout << "5. Show all waiting patient IDs\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (choice == 1) {
            room.RegisterPatient();
        }
        else if (choice == 2) {
            room.ServePatient();
        }
        else if (choice == 3) {
            room.CancelAll();
        }
        else if (choice == 4) {
            if (room.CanDoctorGoHome()) {
                cout << "Yes. No patients are waiting; the doctor can go home.\n";
            } else {
                cout << "No. Patients are still waiting for service.\n";
            }
        }
        else if (choice == 5) {
            room.ShowAllPatient();
        }
        else if (choice == 6) {
            cout << "Exiting program. Goodbye!\n";
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}