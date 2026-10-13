#include <iostream>
#include <iomanip>
using namespace std;

// Each item in the queue is one print request.
struct PrintRequest {
    int id = 0;
    int arrivalTime = 0;
    int processingTime = 0;
};

// ==================== Dynamic Circular Queue ====================
class CircularQueue {
private:
    PrintRequest* data;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;
    const int minimumCapacity = 3;

public:
    CircularQueue() {
        capacity = minimumCapacity;
        data = new PrintRequest[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ~CircularQueue() {
        delete[] data;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    int size() {
        return count;
    }

    int getCapacity() {
        return capacity;
    }

    // Change the array capacity while keeping requests in FIFO order.
    void resize(int newCapacity) {
        if (newCapacity < minimumCapacity) {
            newCapacity = minimumCapacity;
        }

        if (newCapacity < count) {
            newCapacity = count;
        }

        if (newCapacity == capacity) {
            return;
        }

        PrintRequest* newData = new PrintRequest[newCapacity];

        // Copy requests from front to rear in their queue order.
        for (int i = 0; i < count; i++) {
            newData[i] = data[(frontIndex + i) % capacity];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = count - 1;

        cout << "Queue resized to capacity " << capacity
             << ". Requests kept in the same order.\n";
    }

    void displayQueue() {
        cout << "Queue state (front to rear): ";

        if (isEmpty()) {
            cout << "[empty]";
        } else {
            for (int i = 0; i < count; i++) {
                int index = (frontIndex + i) % capacity;
                cout << "[ID " << data[index].id
                     << ", arrival " << data[index].arrivalTime
                     << ", processing " << data[index].processingTime
                     << "]";
                if (i < count - 1) {
                    cout << " -> ";
                }
            }
        }

        cout << "\nQueue size: " << count
             << " | Capacity: " << capacity << "\n";
    }

    void enqueue(PrintRequest request) {
        // Grow the queue if it is full.
        if (isFull()) {
            resize(capacity * 2);
        }

        rearIndex = (rearIndex + 1) % capacity;
        data[rearIndex] = request;
        count++;

        cout << "Enqueued request ID " << request.id << ".\n";
        displayQueue();
    }

    // Returns the next request. Call only when the queue is not empty.
    PrintRequest dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. There is no request to dequeue.\n";
            return PrintRequest{};
        }

        PrintRequest request = data[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;

        if (count == 0) {
            frontIndex = 0;
            rearIndex = -1;
        }

        // Shrink the queue when it is one-quarter full or less.
        if (capacity > minimumCapacity && count <= capacity / 4) {
            resize(capacity / 2);
        }

        cout << "Dequeued request ID " << request.id << ".\n";
        displayQueue();
        return request;
    }

    // Returns the next request without removing it.
    PrintRequest front() {
        if (isEmpty()) {
            cout << "Queue is empty. There is no front request.\n";
            return PrintRequest{};
        }

        return data[frontIndex];
    }
};

// ==================== Print Server Simulation ====================
int main() {
    CircularQueue requests;

    int choice;
    int serverAvailableTime = 0;
    long long totalWaitingTime = 0;
    int processedCount = 0;

    do {
        cout << "\n============================================\n";
        cout << "      TASK 3 - Print Server Request System\n";
        cout << "============================================\n";
        cout << "1. Enqueue a print request\n";
        cout << "2. Process the next request (dequeue)\n";
        cout << "3. View the front request\n";
        cout << "4. View queue status\n";
        cout << "5. Show average waiting time\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (choice == 1) {
            PrintRequest request;

            cout << "Enter request ID: ";
            cin >> request.id;

            cout << "Enter arrival time (non-negative integer): ";
            cin >> request.arrivalTime;

            cout << "Enter processing time (positive integer): ";
            cin >> request.processingTime;

            if (request.arrivalTime < 0 || request.processingTime <= 0) {
                cout << "Invalid request. Arrival time must be non-negative "
                     << "and processing time must be positive.\n";
            } else {
                requests.enqueue(request);
            }
        }
        else if (choice == 2) {
            if (requests.isEmpty()) {
                cout << "No requests are waiting to be processed.\n";
            } else {
                PrintRequest request = requests.dequeue();

                // The server starts when both the request has arrived
                // and the server is available.
                int startTime = serverAvailableTime;
                if (request.arrivalTime > startTime) {
                    startTime = request.arrivalTime;
                }

                int waitingTime = startTime - request.arrivalTime;
                serverAvailableTime = startTime + request.processingTime;

                totalWaitingTime += waitingTime;
                processedCount++;

                cout << "Processing request ID " << request.id << ":\n";
                cout << "  Start time: " << startTime << "\n";
                cout << "  Waiting time: " << waitingTime << "\n";
                cout << "  Finish time: " << serverAvailableTime << "\n";
            }
        }
        else if (choice == 3) {
            if (requests.isEmpty()) {
                cout << "Queue is empty.\n";
            } else {
                PrintRequest request = requests.front();
                cout << "Front request: ID " << request.id
                     << ", arrival time " << request.arrivalTime
                     << ", processing time " << request.processingTime
                     << "\n";
            }
        }
        else if (choice == 4) {
            requests.displayQueue();
            cout << "isEmpty: " << (requests.isEmpty() ? "true" : "false")
                 << " | isFull: " << (requests.isFull() ? "true" : "false")
                 << "\n";
        }
        else if (choice == 5) {
            if (processedCount == 0) {
                cout << "No requests have been processed yet.\n";
            } else {
                double averageWaitingTime =
                    static_cast<double>(totalWaitingTime) / processedCount;

                cout << fixed << setprecision(2);
                cout << "Average waiting time: "
                     << averageWaitingTime << " time units\n";
            }
        }
        else if (choice == 6) {
            cout << "Exiting program.\n";
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);

    if (processedCount > 0) {
        double averageWaitingTime =
            static_cast<double>(totalWaitingTime) / processedCount;

        cout << fixed << setprecision(2);
        cout << "Final average waiting time: "
             << averageWaitingTime << " time units\n";
    } else {
        cout << "No requests were processed, so there is no average waiting time.\n";
    }

    return 0;
}