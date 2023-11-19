#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
using namespace std;

struct User {
    string userName;
    string email;
    string password;
};

struct HouseHelper {
    string name;
    string address;
    string contactNumber;
    string skills;
    HouseHelper* next;
    HouseHelper* prev;
};

class RegistrationSystem {
private:
    fstream file;
    unordered_map<string, User> users;
    HouseHelper* helpers;

public:
    RegistrationSystem() : helpers(nullptr) {}

    void displayMenu();
    void processUserChoice(char choice);
    void registerUser();
    void loginUser();
    void forgotPassword();

    void displayHelpers();
    void registerHelper();
    void searchByLocation(const string& location);
    void searchBySkill(const string& skill);
    void bookAppointment(HouseHelper* helper);

    ~RegistrationSystem() {
        // Clean up allocated memory for HouseHelper objects
        HouseHelper* current = helpers;
        while (current != nullptr) {
            HouseHelper* next = current->next;
            delete current;
            current = next;
        }
    }
};

void RegistrationSystem::displayMenu() {
    char choice;
    cout << "\n1- Login";
    cout << "\n2- Sign-Up";
    cout << "\n3- Forgot Password";
    cout << "\n4- Helper Registration";
    cout << "\n5- Exit";
    cout << "\nEnter Your Choice :: ";
    cin >> choice;

    processUserChoice(choice);
}

void RegistrationSystem::processUserChoice(char choice) {
    cin.ignore();  // Clear the newline character from the input buffer
    switch (choice) {
        case '1':
            loginUser();
            break;
        case '2':
            registerUser();
            break;
        case '3':
            forgotPassword();
            break;
        case '4':
            registerHelper();
            break;
        case '5':
            exit(0);
            break;
        default:
            cout << "Invalid Selection...!";
            break;
    }

    displayMenu();
}

void RegistrationSystem::registerUser() {
    User user;
    cout << "Enter Your User Name :: ";
    getline(cin, user.userName);
    cout << "Enter Your Email Address :: ";
    getline(cin, user.email);
    cout << "Enter Your Password :: ";
    getline(cin, user.password);

    users[user.userName] = user;

    file.open("loginData.txt", ios::out | ios::app);
    file << user.userName << "*" << user.email << "*" << user.password << endl;
    file.close();
}

void RegistrationSystem::loginUser() {
    string searchName, searchPass;

    cout << "----------LOGIN---------" << endl;
    cout << "Enter Your User Name :: " << endl;
    getline(cin, searchName);
    cout << "Enter Your Password :: " << endl;
    getline(cin, searchPass);

    auto it = users.find(searchName);
    if (it != users.end()) {
        const User& user = it->second;
        if (user.password == searchPass) {
            cout << "\nAccount Login Successful...!" << endl;
            cout << "Username :: " << user.userName << endl;
            cout << "Email :: " << user.email << endl;
        } else {
            cout << "Password is Incorrect...!" << endl;
        }
    } else {
        cout << "User not found...!" << endl;
    }
}

void RegistrationSystem::forgotPassword() {
    string searchName, searchEmail;

    cout << "Enter Your UserName :: ";
    getline(cin, searchName);
    cout << "Enter Your Email Address :: ";
    getline(cin, searchEmail);

    auto it = users.find(searchName);
    if (it != users.end()) {
        const User& user = it->second;
        if (user.email == searchEmail) {
            cout << "\nAccount Found...!" << endl;
            cout << "Your Password :: " << user.password << endl;
        } else {
            cout << "Email address does not match...!" << endl;
        }
    } else {
        cout << "User not found...!" << endl;
    }
}

void RegistrationSystem::displayHelpers() {
    HouseHelper* current = helpers;
    int i = 1;
    while (current != nullptr) {
        cout << "Helper " << i << ":\n";
        cout << "Name: " << current->name << endl;
        cout << "Address: " << current->address << endl;
        cout << "Contact Number: " << current->contactNumber << endl;
        cout << "Skills: " << current->skills << endl;
        cout << "Registration Successful!" << endl;
        current = current->next;
        i++;
    }
}

void RegistrationSystem::registerHelper() {
    char registerAnother = 'n';

    do {
        HouseHelper* helper = new HouseHelper;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, helper->name);
        cout << "Enter your address: ";
        getline(cin, helper->address);
        cout << "Enter your contact number: ";
        getline(cin, helper->contactNumber);
        cout << "Enter your skills: ";
        getline(cin, helper->skills);

        if (helpers == nullptr) {
            helpers = helper;
        } else {
            HouseHelper* current = helpers;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = helper;
            helper->prev = current;
        }

        cout << "Do you want to register another helper? (y/n): ";
        cin >> registerAnother;
        cin.ignore();  // Clear the newline character from the input buffer
    } while (registerAnother == 'y' || registerAnother == 'Y');
}

void RegistrationSystem::searchByLocation(const string& location) {
    cout << "Search results for location: " << location << endl;
    bool found = false;
    HouseHelper* current = helpers;
    while (current != nullptr) {
        if (current->address.find(location) != string::npos) {
            cout << "Name: " << current->name << endl;
            cout << "Address: " << current->address << endl;
            cout << "Contact Number: " << current->contactNumber << endl;
            cout << "Skills: " << current->skills << endl;
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        cout << "No helpers found in the location: " << location << endl;
    }
}

void RegistrationSystem::searchBySkill(const string& skill) {
    cout << "Search results for skill: " << skill << endl;
    bool found = false;
    HouseHelper* current = helpers;
    while (current != nullptr) {
        if (current->skills.find(skill) != string::npos) {
            cout << "Name: " << current->name << endl;
            cout << "Address: " << current->address << endl;
            cout << "Contact Number: " << current->contactNumber << endl;
            cout << "Skills: " << current->skills << endl;
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        cout << "No helpers found with the skill: " << skill << endl;
    }
}

void RegistrationSystem::bookAppointment(HouseHelper* helper) {
    cout << "Booking an appointment with the selected helper..." << endl;
    cout << "Helper Details:" << endl;
    cout << "Name: " << helper->name << endl;
    cout << "Address: " << helper->address << endl;
    cout << "Contact Number: " << helper->contactNumber << endl;
    cout << "Skills: " << helper->skills << endl;
    // Additional logic for booking appointment can be added here
}

int main() {
    RegistrationSystem registrationSystem;
    registrationSystem.displayMenu();

    return 0;
}