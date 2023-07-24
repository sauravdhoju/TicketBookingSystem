
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

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

// Prints the given QrCode object to the console.
inline static void printQr(const char* text, unsigned int sx, unsigned int sy) {
	const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;  
	const QrCode qr = QrCode::encodeText(text, errCorLvl);
	//std::cout << toSvgString(qr, 4) << std::endl;
	int border = 1;
	const char block[3] = { char(219),char(219),'\0' };
	for (int y = -border; y < qr.getSize() + border; y++) {
		gotoxy(sx, sy + y);
		for (int x = -border; x < qr.getSize() + border; x++) {
			std::cout << (qr.getModule(x, y) ? "  " : block);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
