#ifndef LOGIN_H
#define LOGIN_H

static const std::string USER_FILE {"UserData/users.txt"};
static const std::string ADMIN_FILE {"UserData/admin.txt"};


struct ticket {
	int movieId[20];
	char ticketId[10];
};

class User {
	int id=0 ;
	ticket tickets[20];
	std::string username;
	std::string password;
	std::string phonenumber;
	std::string email;
	std::string storedUsername, storedPassword;
public:
	User(){}
	User(std::string username, std::string password, std::string phonenumber, std::string email){}
	void CustomerDetails();
	void customerPortal();
    void getUserInfo();
	void Login();
};
/*

User registerUser(){
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
            gotoxy(centerX - 50, centerY - 2);
            std::cout << "Email: ";
            do {
                c = _getch();
                if (c != '\b'&&c!='\r') {
                    gotoxy(centerX - 43 + email.length(), centerY - 2);
                    std::cout << c;
                    email += c;
                }
                else if(c=='\b'&&email.length()>0){
                    email.pop_back();
                    gotoxy(centerX - 43 + email.length(), centerY - 2);
                    std::cout << " ";
                }

                gotoxy(centerX + 20, centerY - 2);
                if(isValidEmail(email)){
                    highlightGreen(); std::cout << "Valid Email  "; 
                } 
                else {
                    highlightRed(); std::cout << "Invalid Email"; 
                }
                resetHighlight();

                gotoxy(centerX - 43 + email.length(), centerY - 2);
            } while (c != '\r');
        }
        system("cls");
        Title("Your account has been created successfully", centerY + 2);
        _getch();
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
*/
#endif
