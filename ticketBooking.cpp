#include <iostream>
#include <string>
using namespace std;

const int MAX_TICKETS = 100;

// Ticket class
class Ticket {
public:
    string name, destination, date;
    int number;
    float price;

    float getPrice(string dest) {
        if (dest == "Delhi") return 500;
        else if (dest == "Mumbai") return 800;
        else if (dest == "Chennai") return 700;
        else if (dest == "Kolkata") return 600;
        else return 450;
    }

    void input(int num) {
        number = num;
        cin.ignore();
        cout << "\nEnter Name: ";
        getline(cin, name);
        cout << "Enter Destination: ";
        getline(cin, destination);
        cout << "Enter Date (dd/mm/yyyy): ";
        getline(cin, date);

        price = getPrice(destination);
    }

    void show() {
        cout << "Ticket No: " << number
             << " | Name: " << name
             << " | To: " << destination
             << " | Date: " << date
             << " | ₹" << price << endl;
    }
};

// Booking system using array (queue-like)
class BookingSystem {
    Ticket tickets[MAX_TICKETS];
    int front, rear, ticketNo;

public:
    BookingSystem() {
        front = -1;
        rear = -1;
        ticketNo = 1;
    }

    bool full() {
        return rear == MAX_TICKETS - 1;
    }

    bool empty() {
        return front == -1 || front > rear;
    }

    void book() {
        if (full()) {
            cout << "\n❌ No more tickets can be booked!\n";
            return;
        }

        Ticket t;
        t.input(ticketNo++);
        if (empty()) {
            front = rear = 0;
        } else {
            rear++;
        }

        tickets[rear] = t;
        cout << "✅ Ticket booked!\n";
    }

    void cancel() {
        if (empty()) {
            cout << "\n❌ No tickets to cancel.\n";
            return;
        }

        cout << "\nCancelled Ticket:\n";
        tickets[front].show();
        front++;
        if (front > rear) front = rear = -1;
    }

    void display() {
        if (empty()) {
            cout << "\n📭 No tickets booked yet.\n";
            return;
        }

        cout << "\n📄 List of Booked Tickets:\n";
        for (int i = front; i <= rear; i++) {
            tickets[i].show();
        }
    }
};

int main() {
    BookingSystem system;
    int ch;

    do {
        cout << "\n===========================\n";
        cout << "     🎫 Ticket Menu\n";
        cout << "===========================\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. Show All Tickets\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch) {
            case 1: system.book(); break;
            case 2: system.cancel(); break;
            case 3: system.display(); break;
            case 4: cout << "\n👍 Exit done. Thank you!\n"; break;
            default: cout << "⚠️ Invalid option!\n";
        }

    } while (ch != 4);

    return 0;
}