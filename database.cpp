#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

struct Student
{
    string uid;
    string name;
    int classesAttended;
    int totalClasses;
};

vector<Student> database;
string fileName = "database.txt";

//  Load Data
void loadData()
{
    ifstream file(fileName);
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        Student s;
        if (ss >> s.uid >> s.name >> s.classesAttended >> s.totalClasses)
        {
            database.push_back(s);
        }
    }
    file.close();
}

// Save Data
void saveData()
{
    ofstream file(fileName);
    for (Student s : database)
    {
        file << s.uid << " " << s.name << " " << s.classesAttended << " " << s.totalClasses << "\n";
    }
    file.close();
}

// Add Record underscore
void addRecord()
{
    Student s;
    cout << "\nEnter UID: ";
    cin >> s.uid;

    cout << "Enter Full Name: ";
    cin >> ws;            //  Clears leftover enter-keys from the UID input
    getline(cin, s.name); // Allows you to type spaces!

    //  Secretly turn spaces into underscores for safe saving
    for (int i = 0; i < s.name.length(); i++)
    {
        if (s.name[i] == ' ')
        {
            s.name[i] = '_';
        }
    }

    cout << "Enter Classes Attended: ";
    cin >> s.classesAttended;
    cout << "Enter Total Classes: ";
    cin >> s.totalClasses;

    database.push_back(s);
    saveData();
    cout << "[SYSTEM] Student Added Successfully!\n";
}

// 4. View Records (With the Underscore-to-Space)
void viewRecords()
{
    cout << "\n------------------------------------------------------\n";
    cout << left << setw(15) << "UID"
         << left << setw(20) << "NAME"
         << left << setw(15) << "ATTENDANCE" << "\n";
    cout << "------------------------------------------------------\n";

    for (Student s : database)
    {
        // Turn underscores back to spaces for a clean display
        string displayName = s.name;
        for (int i = 0; i < displayName.length(); i++)
        {
            if (displayName[i] == '_')
            {
                displayName[i] = ' ';
            }
        }

        int percentage = 0;
        if (s.totalClasses > 0)
        {
            percentage = (s.classesAttended * 100) / s.totalClasses;
        }

        cout << left << setw(15) << s.uid
             << left << setw(20) << displayName
             << left << setw(15) << to_string(percentage) + "%" << "\n";
    }
    cout << "------------------------------------------------------\n";
}

// 5. Main Menu
int main()
{
    loadData();

    int choice = 0;
    while (choice != 3)
    {
        cout << "\n=======================================\n";
        cout << " STUDENT REGISTRATION & ATTENDANCE DB\n";
        cout << "=======================================\n";
        cout << " 1. Add New Student Record\n";
        cout << " 2. View All Student Records\n";
        cout << " 3. Exit System\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            addRecord();
        }
        else if (choice == 2)
        {
            viewRecords();
        }
        else if (choice == 3)
        {
            cout << "Exiting system...\n";
        }
        else
        {
            cout << "[ERROR] Invalid choice. Try again.\n";
        }
    }

    return 0;
}