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
#include "qrcode.hpp"
#include "Global.h"
#include "Movies.h"



bool usernameIsAlreadyTaken(std::string username) {
    std::ifstream user(USER_FILE, std::ios::in);
    if (!user ) {
        std::cout << "File could not open";
        return false;
    }

    std::string userLine, temp;
    while (std::getline(user, userLine)) {
        std::stringstream iss(userLine);
        std::getline(iss, temp, ',');//username scanned
        if (username == temp) {
            user.close();
            return true;
        }
    }
    user.close();
    return false;
}
bool isValidPhoneNumber(const std::string& phoneNumber) {
    // Regular expression pattern for a valid phone number
    std::regex pattern("^\\d{8}$");

    // Check if the phone number matches the pattern
    return std::regex_match(phoneNumber, pattern);
}

bool isValidEmail(const std::string& email) {
    const std::regex pattern1("(\\w+)(\\.|)?(\\w*)@gmail(\\.com)+");
    const std::regex pattern2("(\\w+)(\\.|)?(\\w*)@yahoo(\\.com)+");
    const std::regex pattern3("(\\w+)(\\.|)?(\\w*)@khec(\\.np)+");
    const std::regex pattern4("(\\w+)(\\.|)?(\\w*)@hotmail(\\.com)+");
    return regex_match(email, pattern1) || regex_match(email, pattern2) || regex_match(email, pattern3) || regex_match(email, pattern4);
}


void User::getUserInfo() {
    system("cls");  presentTime();
    Title("Movie-Ticket Booking System", centerY - 12);
    Title("CREATE ACCOUNT", centerY - 8);
    std::ofstream user(USER_FILE, std::ios::app );
    std::ifstream user1(USER_FILE, std::ios::app);
    if (!user) {
        std::cout << "File could not open";
    }
    else {
        char c;
        
        while (true) {
            system("cls");  presentTime();
            gotoxy(centerX - 50, centerY - 5);
            std::cout << "Username: ";
            std::cin >> username;
            gotoxy(centerX - 50 + username.length()+10, centerY - 5);
            if (usernameIsAlreadyTaken(username)) {
                std::cout << "  The username is already taken. retry!";
                _getch();
            }
            else break;
        }

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
        bool showPassword = false;

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
                    resetHighlight();
                    if (c == '~') {
                        if (showPassword) showPassword = false;
                        else showPassword = true;
                    }
                    else{
                        password += c;
                    }
                    if (showPassword) {
                        gotoxy(centerX - 40, centerY - 4);
                        std::cout << password;
                    }
                    else {
                        gotoxy(centerX - 40, centerY - 4);
                        for (int i = 0; i < password.length(); i++) std::cout << "*";
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
                gotoxy(centerX - 40, centerY - 4);
                for (int i = 0; i < password.length(); i++) std::cout << "*";
            }
            else {
                gotoxy(centerX - 40, centerY - 4);
                for (int i = 1; i <= password.length(); i++) {
                    std::cout << " ";
                }
                password = "";
                gotoxy(centerX + 20, centerY - 4);
                highlightRed();
                std::cout << "Weak Password\n";
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
            std::string phoneNumberSuffix="";
            char c;
            do {
                c = _getch();
                if (c >= char('0')&& c<= char('9')) phoneNumberSuffix += c;
                else if (c == '\b'&&phoneNumberSuffix.length()>0) {
                    gotoxy(centerX - 30 + phoneNumberSuffix.length(), centerY - 3);
                    std::cout << " ";
                    phoneNumberSuffix.pop_back();
                }

                (phoneNumberSuffix.length() == 8) ? highlightGreen() : highlightRed();
                gotoxy(centerX + 50, centerY-3);
                std::cout << "Character Count: " << phoneNumberSuffix.length()+2 << " " << std::endl;
                resetHighlight();

                
                if ((c < char('0') || c > char('9')) && c!='\b' && c!='\r') {
                    gotoxy(centerX + 50, centerY-2);
                    highlightRed();  std::cout << "Please Enter Numbers Only!";
                    resetHighlight();
                }
                else{
                    gotoxy(centerX + 50, centerY-2); std::cout << "                           ";
                }

                gotoxy(centerX - 50, centerY - 3);
                std::cout << "Phone Number: +977-98" << phoneNumberSuffix;
                gotoxy(centerX - 29+ phoneNumberSuffix.length(), centerY - 3);
            }while (c != '\r');
            phonenumber = "+977_98" + phoneNumberSuffix;

            // Validate the phone number suffix
            if (!isValidPhoneNumber(phoneNumberSuffix)) {
                // Overwrite the number with blank space
                gotoxy(centerX - 50+21, centerY - 3);
                for (int i = 0; i < phoneNumberSuffix.length(); i++) {
                    std::cout << " ";
                }
                gotoxy(centerX + 20, centerY - 3);
                highlightRed();
                std::cout << "Invalid Number\n";
                resetHighlight();
                phoneNumberSuffix = "";
                continue;
            }

            else {
                gotoxy(centerX + 50, centerY - 3);
                std::cout << "                                    ";//Overwrite Character Count
                gotoxy(centerX + 20, centerY - 3);
                highlightGreen();
                std::cout << "Valid Number  ";
                resetHighlight();
                break;
            }
        }

        while (!isValidEmail(email)) {
            email = ""; // Clear the email variable before capturing a new email address

            gotoxy(centerX - 50, centerY - 2);
            std::cout << "Email: ";

            char c;
            do {
                c = _getch();
                if (c != '\b' && c != '\r') {
                    gotoxy(centerX - 43 + email.length(), centerY - 2);
                    std::cout << c;
                    email += c;
                }
                else if (c == '\b' && !email.empty()) {
                    email.pop_back();
                    gotoxy(centerX - 43 + email.length(), centerY - 2);
                    std::cout << " ";
                }
            } while (c != '\r');

            if (!isValidEmail(email)) {
                gotoxy(centerX + 20, centerY - 2);
                highlightRed();
                std::cout << "Invalid Email";
                resetHighlight();
                _getch();
                gotoxy(centerX + 20, centerY - 2);
                std::cout << "                ";
            }
        }

        
        std::string id;
        // Generate a unique ID for the new user
        int maxId = 00;
        std::string userline;
        while (std::getline(user1, userline)) {
            std::stringstream iss(userline);
            std::string userId;
            std::getline(iss, userId, ',');
            int userIdInt = std::stoi(userId);
            maxId = max(maxId, userIdInt);
        }
        int newId = maxId + 01;
        id = std::to_string(newId);


        system("cls");
        Title("Movie-Ticket Booking System", centerY - 12);
        Title("Your account has been created successfully", centerY + 2);
        _getch();
        // Write the user data to the file
        std::ostringstream UserData;
        user << id << "," << username << "," << password << "," << phonenumber << "," << email << std::endl;
        user << UserData.str();
        if (user.fail()) {
            std::cout << "Error occurred while writing user data to the file." << std::endl;
            return;
        }
    }

}

void User::CustomerDetails() {
    std::cout <<"  " << username << " | " << phonenumber << " | " << email << "  ";
}


void User::Login() {
    system("cls");  presentTime();
    Title("Movie-Ticket Booking System", centerY - 14);
    Title("LOGIN", centerY - 8);
    gotoxy(centerX - 50, centerY - 5);
    std::cout << "Username: ";
    std::getline(std::cin, username);
    gotoxy(centerX - 50, centerY - 4);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    std::ifstream user(USER_FILE, std::ios::in);
    std::ifstream admin(ADMIN_FILE, std::ios::in);

    if (!user || !admin) {
        std::cout << "File could not open";
        return;
    }

    if (username.empty() || password.empty()) {
        system("cls");
        gotoxy(centerX, centerY);
        std::cout << "Invalid Username or Password\n";
        _getch();
        return;
    }


    bool isAdmin = false;
    bool found = false;

    // Check if the user is an admin
    std::string adminLine;
    while (std::getline(admin, adminLine)) {
        size_t pos = adminLine.find(",");
        std::string adminUsername = adminLine.substr(0, pos);
        std::string adminPassword = adminLine.substr(pos + 1);
        if (adminUsername == username && adminPassword == password) {
            isAdmin = true;
            found = true;
            break;
        }
    }
    admin.close();

    if (!found) {
        // Check if the user is a customer
        std::string userLine;
        std::string storedUsername, storedPassword;

        while (std::getline(user, userLine)) {
            std::stringstream iss(userLine);
            std::getline(iss, storedUsername, ',');
            std::getline(iss, storedPassword, ',');
            if (storedUsername == username && storedPassword == password) {
                found = true;
                currentlyLoggedUser = username;
                std::getline(iss, this->phonenumber, ',');
                std::getline(iss, this->email, ',');
                break;
            }
        }
        user.close();
    }

    if (found) {
        if (isAdmin) {
            char choice;
            do {
                system("cls");  presentTime();
                choice = menuInput({ "List of Movies for Modification", "Customer Details", "Add New Movie","Logout" }, centerX - 50, centerY - 4);
                movie m;//instance of movie created for adding new movie option
                switch (choice) {
                case 1:
                    system("cls"); presentTime();
                    gotoxy(centerX - 10, 3);
                    std::cout << "Movie List";
                    find(movieMenu(search(""), 10, 10)).moviePageForAdmin();
                    break;
                case 2:
                    system("cls"); presentTime();
                    //admin.CustomerDetails();
                    // _getch();
                    break;
                case 3:
                    system("cls"); presentTime();
                    gotoxy(centerX - 10, 3);
                    std::cout << "Add movie:";
                    gotoxy(centerX - 10, 4);
                    //movie m;
                    m.add();
                    break;
                case 4:
                    return;
                }
            } while (true);
        }
        else {
            char choice;
            do {
                system("cls"); presentTime();
                Title("Movie-Ticket Booking System", centerY - 12);
                gotoxy(centerX - 50, centerY - 8);
                std::cout << "Welcome ";
                CustomerDetails();
                choice = menuInput({ "Available Movies","Search Movies","Your tickets","Logout" }, centerX - 55, centerY - 4);

                std::string keyword;
                switch (choice) {
                case 1://Available Movies
                    system("cls"); presentTime();
                    gotoxy(centerX - 10, 3);
                    std::cout << "Movie List";
                    find(movieMenu(search(""), 10, 10)).moviePageForUser();
                    break;
                case 2:///Search Movies
                    system("cls"); presentTime();
                    gotoxy(centerX - 10, 3);
                    std::cout << "Movie Search";
                    std::cout << "Enter the Keyword to search: "; std::cin >> keyword;
                    find(movieMenu(search(keyword), 10, 10)).moviePageForUser();
                    break;

                case 3://Your Details
                    /*gotoxy(centerX - 10, 3);
                    std::cout << "Your info";*/
                    loadTickets();
                    displayTickets();
                    break;
                case 4://Logout
                    return;
                }
                _getch();
            } while (true);
        }
    }
    else {
        std::cout << "Invalid username or password. Please try again." << std::endl;
        _getch();
    }
}

void ticket::displayTicket(int sx, int sy) {
    movie m;
    m = find(movieName);
    printQr(id.c_str(), sx, sy, Black, Default_white);
    sy += 2; gotoxy(sx + 50, sy);
    std::cout << "Ticket Id: " << id;
    sy += 2; gotoxy(sx + 50, sy); 
    std::cout << "Name: " << movieName;
    sy += 2; gotoxy(sx+50, sy);
    std::cout << "Movie Start Time: " << m.schedule[scheduleIndex].startTime.dateString();
    sy += 2; gotoxy(sx+50, sy);
    std::cout << "Movie Length: " << m.length;
    std::cout << "\t\tValid Seat: " << std::boolalpha << (m.schedule[scheduleIndex].s[seatNo].id == this->id);
    sy += 2; gotoxy(sx + 50, sy);
}

void User::loadTickets() {
    std::ifstream user(USER_FILE, std::ios::in);
    if (!user) {
        std::cout << "File could not open";
        return;
    }
    
    std::string userLine, temp;
    std::string storedUsername;
    tickets = {};
    while (std::getline(user, userLine)) {
        std::stringstream iss(userLine);
        std::getline(iss, storedUsername, ',');
        for(int i=0; i<3; i++) std::getline(iss, temp, ',');
        if (storedUsername == username) {
            std::string id, movieName, scheduleIndex, seatNo;
            while (!iss.eof()) {
                 std::getline(iss, id, ',');
                 std::getline(iss, movieName, ',');
                 std::getline(iss, scheduleIndex, ',');
                 std::getline(iss, seatNo, ',');
                tickets.push_back({ id,movieName,std::stoi(scheduleIndex),std::stoi(seatNo) });
            }
            break;
        }
    }
    user.close();
}

void User::displayTickets() {
    if (tickets.size() == 0) return;
    int index = 0;
    char keyPressed;
    system("cls");  presentTime();
    tickets.at(index).displayTicket(20, 10);
    std::cout << "<" << std::setw(2) << index + 1 << '\\' << std::setw(2) << tickets.size() << ">";
    while (true) {
        do {
            keyPressed = _getch();
            if (keyPressed == -32) {
                keyPressed = _getch();
                if (keyPressed == 75 && index > 0)  index--;
                if (keyPressed == 77 && index < tickets.size()-1) index++;
            }
            else if (keyPressed == 'd') {//delete button
                deleteTicket(tickets.at(index));
                loadTickets();  displayTickets(); return;
            }
            else if (keyPressed == char(27)) return;
        } while (keyPressed != 75 && keyPressed != 77 && keyPressed != char(27) && keyPressed != 'd');
        system("cls");  presentTime();
        tickets.at(index).displayTicket(20, 10);
        std::cout << "<" << std::setw(2) << index + 1 << '\\' << std::setw(2) << tickets.size() << ">";
    }
}

