#ifndef LOGIN_H
#define LOGIN_H

static const std::string USER_FILE {"UserData/users.txt"};
static const std::string ADMIN_FILE {"UserData/admin.txt"};

class User {
	int id=0 ;
	std::string username;
	std::string password;
	std::string phonenumber;
	std::string email;
	std::string storedUsername, storedPassword;
public:
	void getUserInfo();
	void CustomerDetails();
	void customerPortal();
	void Login();
	

};

#endif
