#pragma once
#include <iostream>
#include <iomanip>
#include "seat.h"
#include "Title.h"

const int totalseats = 120;
const double PREMIUM_PRICE = 2000;
const double NON_PREMIUM_PRICE = 1000;

struct Seat {
    bool isBooked;
    bool isPremium;
};
//
//void paymentPage(run&  h) {
//    Seat seats[totalseats];
//
//    // Initialize all seats as unbooked
//    for (int i = 0; i < totalseats; i++) {
//        seats[i].isBooked = false;
//        seats[i].isPremium = false;
//    }
//
//    int totalBookedSeats = 0;
//    int totalBookedPremiumSeats = 0;
//    int totalBookedNonPremiumSeats = 0;
//
//    Title("ticket booking", centerY-6);
//    while (true) {
//        int seatNumber;
//        int seat;
//
//        cout << "Enter seat number (1-" << totalseats << "): ";
//        cin >> seatNumber;
//
//        if (seatNumber < 1 || seatNumber > totalseats) {
//            cout << "Invalid seat number. Please try again.\n";
//            continue;
//        }
//
//        // Check if the seat is already booked
//        if (seats[seatNumber - 1].isBooked) {
//            cout << "Seat " << seatNumber << " is already booked. Please select a different seat.\n";
//            continue;
//        }
//
//        if (0 < seat < 90)
//        {
//            seats[seatNumber - 1].isPremium = false;
//            totalBookedNonPremiumSeats++;
//        }
//        else if (91 <= seat < totalseats)
//        {
//            seats[seatNumber - 1].isPremium = true;
//            totalBookedPremiumSeats++;
//        }
//        else
//        {
//            cout << "Invalid seat type. Please try again.\n";
//            continue;
//        }
//        seats[seatNumber - 1].isBooked = true;
//        totalBookedSeats++;
//
//        char continueBooking;
//        std::cout << "Do you want to book another seat? (Y/N): ";
//        std::cin >> continueBooking;
//
//        if (continueBooking == 'N' || continueBooking == 'n' || totalBookedSeats == 5)
//        {
//            break;
//        }
//    }
//
//    std::cout << "Seat Booking:" << std::endl;
//    std::cout << "Total booked seats: " << totalBookedSeats << std::endl;
//    std::cout << "Total booked premium seats: " << totalBookedPremiumSeats << std::endl;
//    std::cout << "Total booked non-premium seats: " << totalBookedNonPremiumSeats << std::endl;
//
//    double totalAmount = totalBookedPremiumSeats * PREMIUM_PRICE + totalBookedNonPremiumSeats * NON_PREMIUM_PRICE;
//    cout << "Total= " << totalAmount << std::endl;
//
//    return 0;
//}
//
//
