#pragma once
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "qrcodegen.hpp"
#include "Title.h"
#include "ConsoleColor.h"
using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

// Prints the given QrCode object to the console.
inline static void printQr(const char* text, unsigned int posx, unsigned int posy, colorCode c, colorCode background) {
	const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;  
	const QrCode qr = QrCode::encodeText(text, errCorLvl);
	//std::cout << toSvgString(qr, 4) << std::endl;
	int border = 1;
	const char block[3] = { char(219),char(219),'\0' };
	for (int y = -border; y < qr.getSize() + border; y++) {
		gotoxy(posx, posy + y);
		for (int x = -border; x < qr.getSize() + border; x++) {
			(qr.getModule(x, y)) ? highlight(c) : highlight(background);
			std::cout << block;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	resetHighlight();
}

inline std::string generateRandomString(unsigned int length = 6) {
	std::string s="";
	char c;
	srand(time(NULL));
	for (int i = 0; i < length; i++) {
		if (rand() % 3 == 0) c = char(rand() % 26 + int('a'));
		else if (rand() % 2 == 0) c = char(rand() % 26 + int('A')); 
		else c = char(rand() % 10 + int('0'));
		s.push_back(c);
	}
	return s;
}
