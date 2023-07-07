#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <regex>
#include <sstream>
#include <dos.h>

#include "User.h"
#include "ConsoleSize.h"
#include "Title.h"
#include "ConsoleColor.h"
#include "Admin.h"
#include "MenuAndTime.h"
#include "Global.h"
#include "Movies.h"

bool isValidPhoneNumber(const std::string& phoneNumber) {
    // Regular expression pattern for a valid phone number
    std::regex pattern("^\\d{8}$");

    // Check if the phone number matches the pattern
    return std::regex_match(phoneNumber, pattern);
}

bool isValidEmail(const std::string& email)
{
    const std::regex pattern1("(\\w+)(\\.|)?(\\w*)@gmail(\\.com)+");
    const std::regex pattern2("(\\w+)(\\.|)?(\\w*)@yahoo(\\.com)+");
    const std::regex pattern3("(\\w+)(\\.|)?(\\w*)@khec(\\.np)+");
    return regex_match(email, pattern1) || regex_match(email, pattern2) || regex_match(email, pattern3);
}


void User::getUserInfo() {
    std::ofstream user(USER_FILE, std::ios::app);
    if (!user) {
        std::cout << "File could not open";
    }
    else {

        char c;
        gotoxy(centerX - 50, centerY - 5);
        std::cout << "Username: ";
        std::cin >> username;

        gotoxy(centerX + 50, centerY - 4);
        std::cout << "Uppercase" << std::endl;
        gotoxy(centerX + 50, centerY - 3);
        std::cout << "Lowercase" << std::endl;
        gotoxy(centerX + 50, centerY - 2);
        std::cout << "Digit" << std::endl;
        gotoxy(centerX + 50, centerY - 1);
        std::cout << "Special" << std::endl;
        gotoxy(centerX + 50, centerY - 0);
        std::cout << "Character count: " << std::endl;

        gotoxy(centerX - 50, centerY - 4); 
        std::cout << "Password: ";

        int tick = 1;

        bool hasUpperCase = false;
        bool hasLowerCase = false;
        bool hasDigit = false;
        bool hasSpecialChar = false;
        bool isPasswordValid = false;

        while (!isPasswordValid) {
            password = ""; // Clear the password on each iteration
            gotoxy(centerX - 40, centerY - 3);
            std::cout << "Press '~' to show password\n";

            while (true) {
                tick++;
                gotoxy(centerX - 40 + password.length(), centerY - 4);
                c = _getch();
                if (c == '\r') {
                    // Enter key pressed, exit the loop
                    break;
                }
                else if (c == '\b') {
                    // Backspace key pressed, erase the last character
                    if (!password.empty()) {
                        password.pop_back();

                        // Move the cursor back one position
                        gotoxy(centerX + password.length() - 40, centerY - 4);

                        // Print a space to erase the character
                        std::cout << ' ';
                    }//password empty closing
                    gotoxy(centerX + password.length() - 41, centerY - 4); //move the cursor back after each backspace
                }//backspace closing

                else {
                    //tilde sign gives password
                    if (c != '~') password += c;
                    //to show the password in desired location
                    gotoxy(centerX + password.length() - 41, centerY - 4);
                    resetHighlight();
                    if (c != '~') {
                        gotoxy(centerX - 40, centerY - 4);
                        for (int i = 0; i < password.length(); i++) std::cout << "*";
                    }
                    else {
                        gotoxy(centerX - 40, centerY - 4);
                        std::cout << password;
                    }
                    gotoxy(centerX + password.length() - 40, centerY - 4);
                }

                resetHighlight();
                hasUpperCase = false;
                hasLowerCase = false;
                hasDigit = false;
                hasSpecialChar = false;

                for (char c : password) {
                    if (std::isupper(c)) hasUpperCase = true;
                    else if (std::islower(c)) hasLowerCase = true;
                    else if (std::isdigit(c)) hasDigit = true;
                    else hasSpecialChar = true;
                }

                hasUpperCase ? highlightGreen() : highlightRed();
                gotoxy(centerX + 50, centerY - 4);
                std::cout << "Uppercase" << std::endl;

                hasLowerCase ? highlightGreen() : highlightRed();
                gotoxy(centerX + 50, centerY - 3);
                std::cout << "Lowercase" << std::endl;

                hasDigit ? highlightGreen() : highlightRed();
                gotoxy(centerX + 50, centerY - 2);
                std::cout << "Digit" << std::endl;

                hasSpecialChar ? highlightGreen() : highlightRed();
                gotoxy(centerX + 50, centerY - 1);
                std::cout << "Special" << std::endl;

                //character count and password count
                (password.length() >= 8) ? highlightGreen() : highlightRed();
                gotoxy(centerX + 50, centerY - 0);
                std::cout << "Character Count: " << password.length() << " " << std::endl;

                //for debugging
               /* if (debug) {
                    gotoxy(centerX + 50, centerY + tick);
                    std::cout << password;
                }
                */
            }
            resetHighlight();
            if (password.length() >= 8 && hasUpperCase && hasLowerCase && hasDigit && hasSpecialChar) {
                gotoxy(centerX + 20, centerY - 4);
                highlightGreen();
                std::cout << "Strong Enough\n";
                resetHighlight();
                isPasswordValid = true;
                gotoxy(centerX - 40, centerY - 3);
                std::cout << "                           ";//overwriting show password by ~
            }
            else {
                gotoxy(centerX - 40, centerY - 4);
                for (int i = 1; i <= password.length(); i++) {
                    std::cout << " ";
                }
                password = "";
                gotoxy(centerX + 20, centerY - 4);
                highlightRed();
                std::cout << "!Enough\n";
                resetHighlight();
            }
        }
      
        
        gotoxy(centerX + 50, centerY - 4);
        std::cout << "         " << std::endl;
        gotoxy(centerX + 50, centerY - 3);
        std::cout << "         " << std::endl;
        gotoxy(centerX + 50, centerY - 2);
        std::cout << "      " << std::endl;
        gotoxy(centerX + 50, centerY - 1);
        std::cout << "        " << std::endl;
        gotoxy(centerX + 50, centerY - 0);
        std::cout << "                       " << std::endl;

        while (true) {
            gotoxy(centerX - 50, centerY - 3);
            std::cout << "Phone Number: +977-98";
            std::string phoneNumberSuffix;
            std::cin >> phoneNumberSuffix;
            phonenumber = "+977_98" + phoneNumberSuffix;

            (phoneNumberSuffix.length() >= 8) ? highlightGreen() : highlightRed();
                gotoxy(centerX + 50, centerY - 1);
                std::cout << "Character Count: " << phoneNumberSuffix.length() << " " << std::endl;
                resetHighlight();
            // Validate the phone number suffix
            if (!isValidPhoneNumber(phoneNumberSuffix)) {
                // Overwrite the number with blank space
                gotoxy(centerX - 50, centerY - 3);
                for (int i = 0; i < phoneNumberSuffix.length(); i++) {
                    std::cout << " ";
                }
                gotoxy(centerX + 20, centerY - 3);
                std::cout << "!Valid Number\n";
                phoneNumberSuffix = "";
                continue;
            }

            else {
                gotoxy(centerX + 20, centerY - 3);
                std::cout << "Valid Number\n";
                break;
            }
        }

        while (true) {
            gotoxy(centerX - 50, centerY - 2);
            std::cout << "Email: ";
            std::cin >> email;
            if (!isValidEmail(email)){
                gotoxy(centerX + 20, centerY - 2);
                std::cout << "!Valid Email\n";
                continue;
            }
            else {
                gotoxy(centerX + 20, centerY - 2);
                std::cout << "Valid Email\n";
                break;
            }
        }
        system("cls");
        Title("Your account has been created successfully", centerY + 2);
        Sleep(500);
        // Write the user data to the file
        std::ostringstream UserData;
        user << username << "," << password << "," << phonenumber << "," << email << std::endl;
        user << UserData.str();
        user.close();
        if (user.fail()) {
            std::cout << "Error occurred while writing user data to the file." << std::endl;
            return;
        }
        
        
    }

}

/*void getUserId() {
    int id=-1;
    std::ifstream user(USER_FILE, std::ios::in);
    if (!user) {
        std::cout << "file could not oopen";
    }
    else {
        bool found = false;
        int currentId;
        while (user >> currentId) {
            if (currentId == id) {
                found = true;
                break;
            }

        }
        if (found) {
            id++;
            std::cout << "id" << id;
        }
    }
 }*/


void User::CustomerDetails() {
    //customer details
}


void User::customerPortal() {
    char choice;
    Movies mov;
    User user;
    do {
        system("cls");
        presentTime();
        Title("Movie-Ticket Booking System", centerY - 12);
        gotoxy(centerX - 50, centerY - 8);
        std::cout << "Welcome " << username << std::endl;

        gotoxy(centerX - 50, centerY - 4);
        std::cout << "1. Available Movies\n";
        gotoxy(centerX - 50, centerY - 3);
        std::cout << "2. Your Details\n";
        gotoxy(centerX - 50, centerY - 2);
        std::cout << "3. Logout\n";

        choice = menuInput(centerY - 4, centerX - 50 - 1, 3);

        switch (choice) {
        case 1:
            mov.showMovies();
            break;
        case 2:
            user.CustomerDetails();
            break;
        }

        _getch();
    } while (choice != '3');
}

void User::Login() {
    gotoxy(centerX - 50, centerY - 5);
    std::cout << "Username: ";
    std::getline(std::cin, username);
    gotoxy(centerX - 50, centerY - 4);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    std::ifstream user(USER_FILE, std::ios::out);
    std::ifstream admin(ADMIN_FILE, std::ios::out);

    if (!user || !admin) {
        std::cout << "File could not open";
        return;
    }

    bool isAdmin = false;
    bool isCustomer = false;
    bool found = false;

    // Check if the user is an admin
    std::string adminLine;
    while (getline(admin, adminLine)) {
        size_t pos = adminLine.find(",");
        std::string adminUsername = adminLine.substr(0, pos);
        std::string adminPassword = adminLine.substr(pos + 1);
        if (adminUsername == username && adminPassword == password) {
            isAdmin = true;
            isCustomer = true;
            found = true;
            break;
        }
    }
    admin.close();

    if (!found) {
        // Check if the user is a customer
        std::string line;
        while (getline(user, line)) {
            size_t pos = line.find(",");
            storedUsername = line.substr(0, pos);
            storedPassword = line.substr(pos + 1);
            pos = storedPassword.find(",");
            storedPassword = storedPassword.substr(0, pos);

            if (storedUsername == username && storedPassword == password) {
                found = true;
                break;
            }
        }
        user.close();
    }

    if (found) {
        if (isAdmin) {
            char choice;
            //do {
                Admin admin;
                system("cls");  presentTime();
                Title("Movie-Ticket Booking System", centerY - 12);
                gotoxy(centerX - 50, centerY - 8);
                std::cout << "Welcome " << username << std::endl;

                    
                gotoxy(centerX - 50, centerY - 4);
                std::cout << "1. List of Movies for Modification\n";
                gotoxy(centerX - 50, centerY - 3);
                std::cout << "2. Customer Details";
                gotoxy(centerX - 50, centerY - 2);
                std::cout << "3. Logout\n";

                choice = menuInput(centerY - 4, centerX - 50-1, 3);
                //choice = _getch();
                    switch (choice) {
                    case 1:
                        admin.ListOfMovies();
                        break;

                    case 2:
                        admin.CustomerDetails();
                    // _getch();
                        break;
                    }
                    _getch();
            // }while (choice != '3');
        }
        else {
            customerPortal();
        }
    }
    else {
        std::cout << "Invalid username or password. Please try again." << std::endl;
        _getch();
    }
}

