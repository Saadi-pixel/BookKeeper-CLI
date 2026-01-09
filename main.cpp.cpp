#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio> // Required for remove() and rename()

using namespace std;

// Standard structure for a book to keep the code clean
void addBooks() {
    ofstream file("library.txt", ios::app);
    int id, edition, year;
    string name, author, isbn;

    cout << "Enter book id: "; cin >> id;
    cin.ignore();
    cout << "Enter the Title: "; getline(cin, name);
    cout << "Enter the Author: "; getline(cin, author);
    cout << "Enter the ISBN: "; getline(cin, isbn);
    cout << "Enter Edition: "; cin >> edition;
    cout << "Enter Year: "; cin >> year;
    cin.ignore();

    // We add a '|' at the very end to help the computer read the status clearly
    file << id << "|" << name << "|" << author << "|" << isbn << "|" << edition << "|" << year << "|Available|" << endl;
    file.close();
    cout << "Book added successfully!" << endl;
}

void displayBooks() {
    ifstream file("library.txt");
    if (!file) { cout << "Library is empty." << endl; return; }
   // bool hasData=false;

    string line;
    bool hasData=false;

    while (getline(file, line)) {
    if (line.empty() || line == "\r") continue;
        stringstream ss(line);
        string id, name, author, isbn, edition, year, status;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, author, '|');
        getline(ss, isbn, '|');
        getline(ss, edition, '|');
        getline(ss, year, '|');
        getline(ss, status, '|');
        hasData=true;

        if(id != "") { // Prevents printing empty lines
            cout << "------------------------------------" << endl;
            cout <<" \n ID: "<<id;
            cout<<"\n Book Title: "<<name;
            cout<<"\n Author Name: "<<author;
            cout<<"\n ISBN: "<<isbn;
            cout<<"\n Edition: "<<edition;
            cout<<"\n Publishing Year: "<<year;
            cout<<"\n Status: "<<status;
            cout<<"-----------------------------------------"<<endl;
        }}
      //  else 
      //  cout<<"no book available";
      if(!hasData)
      cout<<"no books in library"<<endl;
    
    file.close();
}

void issueBook() {
    ifstream file("library.txt");
    ofstream temp("temp.txt");
    string searchId, line;
    bool found = false;

    cout << "Enter ID to issue: "; cin >> searchId;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, author, isbn, ed, yr, status;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, author, '|');
        getline(ss, isbn, '|');
        getline(ss, ed, '|');
        getline(ss, yr, '|');
        getline(ss, status, '|');

        if (id == searchId && status == "Available") {
            temp << id << "|" << name << "|" << author << "|" << isbn << "|" << ed << "|" << yr << "|Issued|" << endl;
            found = true;
        } else {
            temp << line << endl; // Keep the line exactly as it was
        }
    }

    file.close(); // IMPORTANT: Close before removing
    temp.close(); // IMPORTANT: Close before renaming

    if (found) {
        remove("library.txt");
        rename("temp.txt", "library.txt");
        cout << "Book issued successfully!" << endl;
    } else {
        remove("temp.txt"); // Delete the temp file since we didn't change anything
        cout << "Error: Book not found or already issued." << endl;
    }
}

void deleteBooks() {
    ifstream file("library.txt");
    ofstream temp("temp.txt");
    string deleteId, line;
    bool found = false;

    cout << "Enter ID to delete: "; cin >> deleteId;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id;
        getline(ss, id, '|');

        if (id == deleteId) {
            found = true; // Just skip writing this line to the temp file
        } else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    if (found) {
        remove("library.txt");
        rename("temp.txt", "library.txt");
        cout << "Book deleted successfully!" << endl;
    } else {
        remove("temp.txt");
        cout << "Book ID not found." << endl;
    }
}

// Check Availability function
void checkAvailability() {
    ifstream file("library.txt");
    string searchId, line;
    cout << "Enter ID to check: "; cin >> searchId;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, author, isbn, ed, yr, status;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, author, '|');
        getline(ss, isbn, '|');
        getline(ss, ed, '|');
        getline(ss, yr, '|');
        getline(ss, status, '|');

        if (id == searchId) {
            cout << "Book: " << name << " is currently [" << status << "]" << endl;
            file.close();
            return;
        }
    }
    cout << "Book not found." << endl;
    file.close();
}

int main() {
    int choice;
    do {
        cout << "\n1. Add Books :";
		cout<<"\n2. Display Books :";
		cout<<"\n3. Check Availability : ";
		cout<<"\n4. Issue Books :";
		cout<<"\n5. Delete Books :";
		cout<<"\n6. Exit Menue : "<<endl;
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1: addBooks(); break;
            case 2: displayBooks(); break;
            case 3: checkAvailability(); break;
            case 4: issueBook(); break;
            case 5: deleteBooks(); break;
        }
    } while (choice != 6);
    return 0;
}
