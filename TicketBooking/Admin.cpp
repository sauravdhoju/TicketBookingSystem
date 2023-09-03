
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>

#include "Admin.h"
#include "Title.h"
#include "ConsoleSize.h"
#include "ConsoleColor.h"
#include "User.h"
#include "MenuAndTime.h"

void Admin::ListOfMovies() {
    char choice;
    std::string line;
    int selectedMovieIndex = 0;

    std::ifstream movieFile(MOVIES_NAME);
    std::vector<std::string> movieNames;

    // Read movie names from the file
    while (std::getline(movieFile, line)) {
        movieNames.push_back(line);
    }

    movieFile.close();

    system("cls");
    presentTime();

    do {
        Title("Movie-Ticket Booking System", centerY - 12);
        for (int i = 0; i < movieNames.size(); i++) {
            gotoxy(centerX - 30, centerY - 8 + i);
            if (i == selectedMovieIndex) {
                highlightGreen();  // Highlight the selected movie name
            }
            std::cout << i + 1 << ". " << movieNames[i] << std::endl;
            resetHighlight();
        }

        choice = _getch();

        switch (choice) {
        case 72:  // Arrow key: Up
            if (selectedMovieIndex > 0) {
                selectedMovieIndex--;
            }
            break;
        case 80:  // Arrow key: Down
            if (selectedMovieIndex < movieNames.size() - 1) {
                selectedMovieIndex++;
            }
            break;

        case '\r':  // Enter key: Select movie
            if (selectedMovieIndex < movieNames.size()) {
                if (selectedMovieIndex == movieNames.size() - 1) {
                    // Go Back option selected
                    return;  // Exit the function to go back
                }
                else {
                    std::string movieDetailsFile = std::string("moviesDetailsDir/") + movieNames[selectedMovieIndex] + ".txt";
                    std::string command = "notepad " + movieDetailsFile;
                    system(command.c_str());
                }
            }
            break;
        }
    } while (true);
}

void Admin::CustomerDetails() {
    system("cls");  presentTime();
    Title("Movie-Ticket Booking System", centerY - 12);
    int id;
    Title("Customer Details", centerY - 8);
    std::ifstream file(USER_FILE, std::ios::in);
    gotoxy(centerX - 10, centerY - 6);
    std::cout << "ID? ";
    std::cin >> id;
    if (!file.is_open()) {
        std::cout << "File could not open\n";
    }
    else {
        std::string line;
        bool found = false;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<std::string> customerData;
            std::string field;

            while (std::getline(iss, field, ',')) {
                customerData.push_back(field);
            }
            //check whether given id is validate or not if calidation successfull then it promts single term into their name their credentials
            if (!customerData.empty() && std::stoi(customerData[0]) == id) {
                std::cout << "ID            : " << customerData[0] << std::endl;
                std::cout << "Name          : " << customerData[1] << std::endl;
                //dont need to show password so directly 3
                std::cout << "Phone Number  : " << customerData[3] << std::endl;
                std::cout << "Email         : " << customerData[4] << std::endl;
                //need to wtite ticket 
                //need to show their booked ticket and booked movies with time 
                found = true;
                break;
            }
        }
        if (!found) {
            system("cls");  presentTime();
            Title("Movie-Ticket Booking System", centerY - 12);
            Title("No Data", centerY + 2);
            _getch();
        }
    }
    file.close();
    _getch();
}