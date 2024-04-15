#include "User.h"
#include "DatabaseConnection.h"
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include <Windows.h> // Pour utiliser les fonctions MessageBox
#include <regex> // Pour la validation de l'e-mail
#include <string>


using namespace System;
using namespace System::Data::SqlClient;
using namespace System::Windows::Forms;

User::User(String^ username, String^ firstName, String^ lastName, String^ email, String^ password)
    : username(gcnew String(username)), firstName(gcnew String(firstName)), lastName(gcnew String(lastName)), email(gcnew String(email)), password(gcnew String(password)) {
    // Initialize class members if needed
}

User::User() {
	// Initialisez les membres de la classe si nécessaire
	username = "";
	firstName = "";
	lastName = "";
	email = "";
	password = "";
}


bool User::InsertUser(String^ username, String^ firstName, String^ lastName, String^ email, String^ password) {
	// Check data validity
	if (String::IsNullOrEmpty(username) || String::IsNullOrEmpty(firstName) || String::IsNullOrEmpty(lastName) ||
		String::IsNullOrEmpty(email) || String::IsNullOrEmpty(password)) {
		MessageBox::Show("All fields must be filled.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;
	}

	std::string usernameStr = msclr::interop::marshal_as<std::string>(username);
	std::string firstNameStr = msclr::interop::marshal_as<std::string>(firstName);
	std::string lastNameStr = msclr::interop::marshal_as<std::string>(lastName);
	std::string emailStr = msclr::interop::marshal_as<std::string>(email);
	std::string passwordStr = msclr::interop::marshal_as<std::string>(password);

	if (!IsValidEmail(emailStr)) {
		MessageBox::Show("Invalid email address.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;
	}

	if (!IsStrongPassword(passwordStr)) {
		MessageBox::Show("Password must be at least 8 characters long and contain uppercase, lowercase, digits, and special characters.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;
	}

	// Encrypt password
	std::string encryptedPassword = EncryptPassword(passwordStr);

	try {
		SqlConnection^ connection = DatabaseConnection::GetConnection();
		SqlCommand^ command = gcnew SqlCommand();
		command->Connection = connection;

		connection->Open();

		String^ query = "INSERT INTO users (username, firstname, lastname, email, password) VALUES (@username, @firstName, @lastName, @email, @password)";
		command->CommandText = query;
		command->Parameters->AddWithValue("@username", username);
		command->Parameters->AddWithValue("@firstName", firstName);
		command->Parameters->AddWithValue("@lastName", lastName);
		command->Parameters->AddWithValue("@email", email);
		command->Parameters->AddWithValue("@password", gcnew String(encryptedPassword.c_str()));

		command->ExecuteNonQuery();

		connection->Close();

		MessageBox::Show("User inserted successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return true;
	}
	catch (Exception^ ex) {
		Console::WriteLine("Error: " + ex->Message);
		MessageBox::Show("Database error.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;
	}
	return false;
}

bool User::IsValidEmail(const std::string& email) {
	// Regular expression for email validation
	std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
	return std::regex_match(email, pattern);
}

bool User::IsStrongPassword(const std::string& password) {
	// Check if password has minimum length of 8 characters and contains at least one uppercase, one lowercase, one digit, and one special character
	return password.length() >= 8 && std::regex_search(password, std::regex("[A-Z]")) &&
		std::regex_search(password, std::regex("[a-z]")) && std::regex_search(password, std::regex("[0-9]")) &&
		std::regex_search(password, std::regex("[^a-zA-Z0-9]"));
}

// Fonction de cryptage de mot de passe (à remplacer par un vrai algorithme de cryptage)
std::string encryptPassword(const std::string& password) {
	std::string encryptedPassword = password; // Initialise la chaîne cryptée avec le mot de passe d'origine

	// Schéma de substitution (exemple)
	const std::string substitutionKey = "bcdefghijklmnopqrstuvwxyzaABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	// Parcours de chaque caractère du mot de passe
	for (char& c : encryptedPassword) {
		// Vérifie si le caractère est une lettre ou un chiffre
		if (isalpha(c) || isdigit(c)) {
			// Effectue le chiffrement par substitution
			size_t index = substitutionKey.find(c);
			if (index != std::string::npos) {
				c = substitutionKey[(index + 3) % substitutionKey.size()]; // Exemple de décalage de 3 caractères
			}
		}
	}

	return encryptedPassword;
}

std::string decryptPassword(const std::string& encryptedPassword) {
	std::string decryptedPassword = encryptedPassword; // Initialise la chaîne décryptée avec la chaîne cryptée

	// Schéma de substitution (exemple)
	const std::string substitutionKey = "bcdefghijklmnopqrstuvwxyzaABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	// Parcours de chaque caractère de la chaîne cryptée
	for (char& c : decryptedPassword) {
		// Vérifie si le caractère est une lettre ou un chiffre
		if (isalpha(c) || isdigit(c)) {
			// Effectue le déchiffrement par substitution
			size_t index = substitutionKey.find(c);
			if (index != std::string::npos) {
				c = substitutionKey[(index - 3 + substitutionKey.size()) % substitutionKey.size()]; // Décalage inverse de 3 caractères
			}
		}
	}

	return decryptedPassword;
}

bool User::CheckLogin(System::String^ username, System::String^ password) {
	try {
		SqlConnection^ connection = DatabaseConnection::GetConnection();
		SqlCommand^ command = gcnew SqlCommand();
		command->Connection = connection;

		connection->Open();


		String^ query = "SELECT * FROM users WHERE username = @username";
		command->CommandText = query;
		command->Parameters->AddWithValue("@username", username);

		SqlDataReader^ reader = command->ExecuteReader();

		if (reader->Read()) {
			String^ fetchedPassword = safe_cast<String^>(reader["password"]);

			// Compare passwords
			if (fetchedPassword == password) {
				MessageBox::Show("Login successful.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return true;
			}
			else {
				MessageBox::Show("Incorrect username or password.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return false;
			}
		}
		else {
			MessageBox::Show("Incorrect username or password.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}

		reader->Close();
		connection->Close();
	}
	catch (Exception^ ex) {
		Console::WriteLine("Error: " + ex->Message);
		MessageBox::Show("Database error.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;
	}
	return false;
}

User^ User::GetUserByUsername(String^ username) {
	try {
		SqlConnection^ connection = DatabaseConnection::GetConnection();
		SqlCommand^ command = gcnew SqlCommand();
		command->Connection = connection;

		connection->Open();

		String^ query = "SELECT * FROM users WHERE username = @username";
		command->CommandText = query;
		command->Parameters->AddWithValue("@username", username);

		SqlDataReader^ reader = command->ExecuteReader();

		if (reader->Read()) {
			String^ fetchedUsername = safe_cast<String^>(reader["username"]);
			String^ firstName = safe_cast<String^>(reader["first_name"]);
			String^ lastName = safe_cast<String^>(reader["last_name"]);
			String^ email = safe_cast<String^>(reader["email"]);
			String^ password = safe_cast<String^>(reader["password"]);

			return gcnew User(fetchedUsername, firstName, lastName, email, password);
		}
		else {
			MessageBox::Show("User not found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return nullptr;
		}

		reader->Close();
		connection->Close();
	}
	catch (Exception^ ex) {
		Console::WriteLine("Error: " + ex->Message);
		MessageBox::Show("Database error.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return nullptr;
	}
	return nullptr;
}

