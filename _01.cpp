#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Student {
public:
    int id;
    string name;
    float marks;
    char grade;

    Student(int i, string n, float m) {
        id = i;
        name = n;
        marks = m;
        grade = calculateGrade();
    }

    char calculateGrade() {
        if (marks >= 90) return 'A';
        else if (marks >= 75) return 'B';
        else if (marks >= 50) return 'C';
        else return 'F';
    }
};

class StudentManager {
private:
    vector<Student> students;

public:
    void addStudent() {
        int id;
        string name;
        float marks;

        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Marks: ";
        cin >> marks;

        students.push_back(Student(id, name, marks));
        cout << "Student added!\n";
    }

    void displayStudents() {
        if (students.empty()) {
            cout << "No data available!\n";
            return;
        }

        for (auto &s : students) {
            cout << "\nID: " << s.id
                 << "\nName: " << s.name
                 << "\nMarks: " << s.marks
                 << "\nGrade: " << s.grade << "\n";
        }
    }

    void sortByMarks() {
        sort(students.begin(), students.end(), [](Student a, Student b) {
            return a.marks > b.marks;
        });
        cout << "Sorted by marks!\n";
    }

    void sortByID() {
        sort(students.begin(), students.end(), [](Student a, Student b) {
            return a.id < b.id;
        });
    }

    void searchStudent() {
        sortByID(); // required for binary search

        int key;
        cout << "Enter ID to search: ";
        cin >> key;

        int left = 0, right = students.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;

            if (students[mid].id == key) {
                cout << "\nFound:\n";
                cout << "Name: " << students[mid].name
                     << ", Marks: " << students[mid].marks
                     << ", Grade: " << students[mid].grade << endl;
                return;
            }
            else if (students[mid].id < key)
                left = mid + 1;
            else
                right = mid - 1;
        }
        cout << "Student not found!\n";
    }

    void saveToFile() {
        ofstream file("students.txt");
        for (auto &s : students) {
            file << s.id << " " << s.name << " " << s.marks << endl;
        }
        file.close();
        cout << "Data saved!\n";
    }

    void loadFromFile() {
        ifstream file("students.txt");
        if (!file) return;

        students.clear();
        int id;
        string name;
        float marks;

        while (file >> id >> name >> marks) {
            students.push_back(Student(id, name, marks));
        }
        file.close();
    }

    void averageMarks() {
        if (students.empty()) return;

        float sum = 0;
        for (auto &s : students)
            sum += s.marks;

        cout << "Average Marks: " << sum / students.size() << endl;
    }
};

int main() {
    StudentManager sm;
    sm.loadFromFile();

    int choice;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student (Binary Search)\n";
        cout << "4. Sort by Marks\n";
        cout << "5. Average Marks\n";
        cout << "6. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: sm.addStudent(); break;
            case 2: sm.displayStudents(); break;
            case 3: sm.searchStudent(); break;
            case 4: sm.sortByMarks(); break;
            case 5: sm.averageMarks(); break;
            case 6: sm.saveToFile(); break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}