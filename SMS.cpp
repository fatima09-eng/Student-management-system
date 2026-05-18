#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string course;
    float cgpa;
    string email;
    string phone;
};

vector<Student> students;
const string FILE_NAME = "students.dat";

// Function declarations
void loadData();
void saveData();
void addStudent();
void displayAll();
void searchStudent();
void updateStudent();
void deleteStudent();
void showMenu();

int main() {
    loadData();
    int choice;
    
    while (true) {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear buffer
        
        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: saveData(); cout << "Data saved. Exiting...\n"; return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
        cout << "\nPress Enter to continue...";
        cin.get();
    }
}

void showMenu() {
    system("cls"); // use system("clear") if on Linux/Mac
    cout << "====================================\n";
    cout << "   STUDENT MANAGEMENT SYSTEM\n";
    cout << "====================================\n";
    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student by Roll No\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Save & Exit\n";
    cout << "====================================\n";
}

void loadData() {
    ifstream fin(FILE_NAME);
    Student s;
    students.clear();
    while (fin >> s.rollNo) {
        fin.ignore();
        getline(fin, s.name);
        getline(fin, s.course);
        fin >> s.cgpa;
        fin.ignore();
        getline(fin, s.email);
        getline(fin, s.phone);
        students.push_back(s);
    }
    fin.close();
}

void saveData() {
    ofstream fout(FILE_NAME);
    for (auto &s : students) {
        fout << s.rollNo << "\n" 
             << s.name << "\n" 
             << s.course << "\n" 
             << s.cgpa << "\n" 
             << s.email << "\n" 
             << s.phone << "\n";
    }
    fout.close();
}

void addStudent() {
    Student s;
    cout << "\n--- Add New Student ---\n";
    cout << "Enter Roll No: ";
    cin >> s.rollNo;
    cin.ignore();
    
    // Check duplicate roll no
    for (auto &st : students) {
        if (st.rollNo == s.rollNo) {
            cout << "Roll No already exists!\n";
            return;
        }
    }
    
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Course: ";
    getline(cin, s.course);
    cout << "Enter CGPA: ";
    cin >> s.cgpa;
    cin.ignore();
    cout << "Enter Email: ";
    getline(cin, s.email);
    cout << "Enter Phone: ";
    getline(cin, s.phone);
    
    students.push_back(s);
    saveData();
    cout << "Student added successfully!\n";
}

void displayAll() {
    cout << "\n--- All Students ---\n";
    if (students.empty()) {
        cout << "No students found.\n";
        return;
    }
    
    cout << left << setw(8) << "Roll" 
         << setw(20) << "Name" 
         << setw(15) << "Course" 
         << setw(8) << "CGPA" 
         << setw(25) << "Email" 
         << setw(15) << "Phone" << "\n";
    cout << string(91, '-') << "\n";
    
    for (auto &s : students) {
        cout << left << setw(8) << s.rollNo 
             << setw(20) << s.name 
             << setw(15) << s.course 
             << setw(8) << fixed << setprecision(2) << s.cgpa
             << setw(25) << s.email 
             << setw(15) << s.phone << "\n";
    }
}

void searchStudent() {
    int roll;
    cout << "\nEnter Roll No to search: ";
    cin >> roll;
    
    for (auto &s : students) {
        if (s.rollNo == roll) {
            cout << "\nStudent Found:\n";
            cout << "Roll No: " << s.rollNo << "\n";
            cout << "Name: " << s.name << "\n";
            cout << "Course: " << s.course << "\n";
            cout << "CGPA: " << s.cgpa << "\n";
            cout << "Email: " << s.email << "\n";
            cout << "Phone: " << s.phone << "\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

void updateStudent() {
    int roll;
    cout << "\nEnter Roll No to update: ";
    cin >> roll;
    cin.ignore();
    
    for (auto &s : students) {
        if (s.rollNo == roll) {
            cout << "Enter new Name: ";
            getline(cin, s.name);
            cout << "Enter new Course: ";
            getline(cin, s.course);
            cout << "Enter new CGPA: ";
            cin >> s.cgpa;
            cin.ignore();
            cout << "Enter new Email: ";
            getline(cin, s.email);
            cout << "Enter new Phone: ";
            getline(cin, s.phone);
            
            saveData();
            cout << "Student updated successfully!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

void deleteStudent() {
    int roll;
    cout << "\nEnter Roll No to delete: ";
    cin >> roll;
    
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->rollNo == roll) {
            students.erase(it);
            saveData();
            cout << "Student deleted successfully!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}