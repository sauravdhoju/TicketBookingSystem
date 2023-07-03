
#include <iostream>
#include <conio.h>
#include <Windows.h>
extern bool debug = true;
#include "Message.h"
#include "Login.h"
#include "ConsoleSize.h"
#include "seat.h"

int main() {
    setConsoleSizeAndCenter();
    //hall h;
    //initiateHall(h);
   // controlHallSeat(h);
    char choice;
    std::string username, password;
    
    User user;
        welcome("Movie-Ticket Booking System", centerY);
        _getch();
        do {
            system("cls");
            welcome("Movie-Ticket Booking System", centerY - 4);
            welcome("1. Login", centerY);
            welcome("   2. Register", centerY + 1);
            welcome("3. Exit", centerY + 2);

            gotoxy(centerX, centerY + 4);
        
                choice = _getch();  //automatically stores value and open next page
       
        
            switch (choice) {
            case '1':
                system("cls");
                welcome("Movie-Ticket Booking System", centerY - 12);
                welcome("LOGIN", centerY - 8);
                user.Login();
                break;

            case '2':
                system("cls");
                welcome("Movie-Ticket Booking System", centerY - 12);
                welcome("CREATE ACCOUNT", centerY - 8);
                user.getUserInfo();
                std::cout << "Registration Successfull";
                break;
            
            }
        } while (choice != '3');

        return 0;
}