#include "seat.h"
#include "Title.h"
#include "ConsoleColor.h"
#include "ConsoleSize.h"

void initiateHall(hall& h) {
    for (int i = (row - premiumRowSeats) * column; i < totalSeat; i++) {
        h.s[i].qlt = PREMIUM;
    }
}
void drawSeat(int x, int y, colorCode c) {
    int Block = 219;
    gotoxy(x, y);
    highlight(c);
    std::cout << char(Block) << char(Block) << " ";//size 1
    resetHighlight();
}

inline void drawHall(hall& h, int current, int npSeats, int pSeats) {
    int startX = centerX - hallLength / 2;
    int x = startX, y = centerY - hallBreadth / 2;
    colorCode c = Default_white;

    int Block = 219;
    gotoxy(0, y);
    std::cout << "Available Seat   \n"<<"Selected Seat    \n" <<"Booked Seat      \n" <<"Premium Seat    ";
    drawSeat(17, y, Default_white); 
    drawSeat(17, y+1, Green); 
    drawSeat(17, y+2, Red); 
    drawSeat(17, y+3, yellow); 
   
    gotoxy(0, y + 10);
    std::cout << " W " << char(24) << std::endl;
    std::cout << " A " << char(27) << std::endl;
    std::cout << " S " << char(25) << std::endl;
    std::cout << " D " << char(26) << std::endl;

    gotoxy(x+hallLength+50, y-10);
    std::cout<<"Non-Premium Seats: "<<npSeats<<std::endl;
    std::cout<<"Premium Seats:     "<<pSeats<<std::endl;
    std::cout<<"Total   Seats:     "<<npSeats+pSeats<<std::endl;
    for (int i = 0; i < totalSeat; i++) {
        if (i == current) c = Bright_blue;
        else if (h.s[i].selected == true) c = Green;
        else if (h.s[i].available == false) c = Red;
        else {
            if (h.s[i].qlt == NON_PREMIUM) c = Default_white;
            else if (h.s[i].qlt == PREMIUM) c = yellow;
        }
        drawSeat(x, y, c);
        //columnPartition=column/column division 12/4 = 3
        if ((i % columnPartition) == columnPartition - 1) x += corridorGap;
        if (i % column == column - 1) {
            if (i == ((row - premiumRowSeats) * column) - 1) y += 3;
            y += 2;
            x = startX;
        }
        else x += 3;
    }
}

inline void controlHallSeat(hall& h) {
    char keyPressed;
    int index = totalSeat/2;
    int premiumSelected = 0;
    int nonPremiumSelected = 0;
    drawHall(h,totalSeat/2,0,0);
    while (true) {
        do {
            keyPressed = _getch();
        } while (
            keyPressed != 'w' && keyPressed != 'a' && keyPressed != 's' && keyPressed != 'd' &&
            keyPressed != '\r' && keyPressed != char(27) && keyPressed != char(32));
        //      enter                          escape                    space         
        if ((keyPressed == 'w' || keyPressed == 'W') && index > column - 1) {
            index -= column;
        }
        if ((keyPressed == 's' || keyPressed == 'S') && index < ((row - 1) * column) - 1) {
            index += column;
        }
        if ((keyPressed == 'a' || keyPressed == 'A') && index % column > 0) {
            index -= 1;
        }
        if ((keyPressed == 'd' || keyPressed == 'D') && index % column < column - 1) {
            index += 1;
        }
        if (keyPressed == '\r' && h.s[index].selected == false && h.s[index].available == true) {
            h.s[index].selected = true;
            if (h.s[index].qlt == PREMIUM) premiumSelected++;
            if (h.s[index].qlt == NON_PREMIUM) nonPremiumSelected++;
        }
        if (keyPressed == char(27)) {//esc button
            for (int i = 0; i < totalSeat; i++) {
                if (h.s[i].selected) h.s[i].selected = false;
            }
            premiumSelected = 0;
            nonPremiumSelected = 0;
        }
        drawHall(h, index,nonPremiumSelected,premiumSelected);
    }
}



