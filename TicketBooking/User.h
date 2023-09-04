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
public:
	User(){}
	User(std::string username, std::string password, std::string phonenumber, std::string email){}
	void CustomerDetails();
    void getUserInfo();
	void Login();
};
#endif
