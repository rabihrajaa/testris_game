
#pragma once
#include <string>

public ref class User {
private:
	System::String^ username;
	System::String^ firstName;
	System::String^ lastName;
	System::String^ email;
	System::String^ password;

public:
	User(System::String^ username, System::String^ firstName, System::String^ lastName, System::String^ email, System::String^ password);
	User();
	// CRUD methods
	static bool InsertUser(System::String^ username, System::String^ firstName, System::String^ lastName, System::String^ email, System::String^ password);
	static User^ GetUserByUsername(System::String^ username);
	static bool CheckLogin(System::String^ username, System::String^ password);


private:
	// Helper methods
	static System::String^ EncryptPassword(std::string& password);
	static System::String^ DecryptPassword(std::string& encryptedPassword);

	static bool IsValidEmail(const std::string& email);
	static bool IsStrongPassword(const std::string& password);
};