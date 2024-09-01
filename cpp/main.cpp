#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string simpleHash(const string& input) {
    string hash = input;
    for (char& c : hash) {
        c ^= 0xAA; // XOR with a simple key
    }
    return hash;
}

void registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Hash the password before storing
    string hashedPassword = simpleHash(password);

    ofstream file;
    file.open("users.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << hashedPassword << endl;
        file.close();
        cout << "Registration successful!" << endl;
    } else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

bool loginUser() {
    string username, password, storedUser, storedPass;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Hash the password for comparison
    string hashedPassword = simpleHash(password);

    ifstream file("users.txt");
    if (file.is_open()) {
        while (file >> storedUser >> storedPass) {
            if (storedUser == username && storedPass == hashedPassword) {
                cout << "Login successful!" << endl;
                return true;
            }
        }
        file.close();
        cout << "Invalid username or password!" << endl;
        return false;
    } else {
        cout << "Error: Unable to open file for reading." << endl;
        return false;
    }
}

int main() {
    int choice;
    cout << "1. Register\n2. Login\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        registerUser();
    } else if (choice == 2) {
        loginUser();
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
