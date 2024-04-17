#include "User.h"
#include "DatabaseConnection.h"
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include <Windows.h> // Pour utiliser les fonctions MessageBox
#include <regex> // Pour la validation de l'e-mail
#include <string>

using namespace System::Windows::Forms;


User::User(std::string username, std::string firstName, std::string lastName, std::string email, std::string password)
	: username(username), firstName(firstName), lastName(lastName), email(email), password(password) {
	// Initialisez les membres de la classe si n�cessaire
}

// Fonction de cryptage de mot de passe (� remplacer par un vrai algorithme de cryptage)
std::string encryptPassword(const std::string& password) {
	std::string encryptedPassword = password; // Initialise la cha�ne crypt�e avec le mot de passe d'origine

	// Sch�ma de substitution (exemple)
	const std::string substitutionKey = "bcdefghijklmnopqrstuvwxyzaABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	// Parcours de chaque caract�re du mot de passe
	for (char& c : encryptedPassword) {
		// V�rifie si le caract�re est une lettre ou un chiffre
		if (isalpha(c) || isdigit(c)) {
			// Effectue le chiffrement par substitution
			size_t index = substitutionKey.find(c);
			if (index != std::string::npos) {
				c = substitutionKey[(index + 3) % substitutionKey.size()]; // Exemple de d�calage de 3 caract�res
			}
		}
	}

	return encryptedPassword;
}

std::string decryptPassword(const std::string& encryptedPassword) {
	std::string decryptedPassword = encryptedPassword; // Initialise la cha�ne d�crypt�e avec la cha�ne crypt�e

	// Sch�ma de substitution (exemple)
	const std::string substitutionKey = "bcdefghijklmnopqrstuvwxyzaABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	// Parcours de chaque caract�re de la cha�ne crypt�e
	for (char& c : decryptedPassword) {
		// V�rifie si le caract�re est une lettre ou un chiffre
		if (isalpha(c) || isdigit(c)) {
			// Effectue le d�chiffrement par substitution
			size_t index = substitutionKey.find(c);
			if (index != std::string::npos) {
				c = substitutionKey[(index - 3 + substitutionKey.size()) % substitutionKey.size()]; // D�calage inverse de 3 caract�res
			}
		}
	}
	std::cout << decryptedPassword;
	return decryptedPassword;
}


// V�rifie si l'e-mail est valide
bool isValidEmail(const std::string& email) {
	// Expression r�guli�re pour la validation de l'e-mail
	std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
	return std::regex_match(email, pattern);
}

// V�rifie si le mot de passe est fort
bool isStrongPassword(const std::string& password) {
	// V�rifie si le mot de passe a une longueur minimale de 8 caract�res et contient au moins une majuscule, une minuscule, un chiffre et un caract�re sp�cial
	return password.length() >= 8 && std::regex_search(password, std::regex("[A-Z]")) && std::regex_search(password, std::regex("[a-z]")) &&
		std::regex_search(password, std::regex("[0-9]")) && std::regex_search(password, std::regex("[^a-zA-Z0-9]"));
}

User* User::GetUserByUsername(std::string username) {
	User* user = nullptr;
	String^ managedUsername = gcnew String(username.c_str());

	try {
		SqlConnection^ connection = DatabaseConnection::GetConnection();
		SqlCommand^ command = gcnew SqlCommand();
		command->Connection = connection;

		connection->Open();

		String^ query = "SELECT * FROM user WHERE username = @username";
		command->CommandText = query;
		command->Parameters->AddWithValue("@username", managedUsername);

		SqlDataReader^ reader = command->ExecuteReader();

		if (reader->Read()) {
			std::string fetchedUsername = msclr::interop::marshal_as<std::string>(reader["username"]->ToString());
			std::string firstName = msclr::interop::marshal_as<std::string>(reader["first_name"]->ToString());
			std::string lastName = msclr::interop::marshal_as<std::string>(reader["last_name"]->ToString());
			std::string email = msclr::interop::marshal_as<std::string>(reader["email"]->ToString());
			std::string password = msclr::interop::marshal_as<std::string>(reader["password"]->ToString());

			user = new User(fetchedUsername, firstName, lastName, email, password);
		}
		else {
			// Afficher un message si l'utilisateur n'est pas trouv�
			MessageBox::Show("L'utilisateur n'existe pas.", "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

		reader->Close();
		connection->Close();
	}
	catch (Exception^ ex) {
		Console::WriteLine("Error: " + ex->Message);
		// Afficher un message en cas d'erreur de base de donn�es
		MessageBox::Show("Erreur de base de donn�es.", "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

	return user;
}

bool User::InsertUser(std::string username, std::string firstName, std::string lastName, std::string email, std::string password) {
	// V�rification de la validit� des donn�es
	if (username.empty() || firstName.empty() || lastName.empty() || email.empty() || password.empty()) {
		MessageBox::Show("Tous les champs doivent �tre remplis.", "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;
	}

	if (!isValidEmail(email)) {
		MessageBox::Show("L'adresse e-mail n'est pas valide.", "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;
	}

	if (!isStrongPassword(password)) {
		MessageBox::Show("Le mot de passe doit contenir au moins 8 caract�res, y compris une majuscule, une minuscule, un chiffre et un caract�re sp�cial.", "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;
	}

	// V�rification de l'existence de l'e-mail et de l'unicit� du nom d'utilisateur dans la base de donn�es
	// Vous devez impl�menter ces v�rifications en fonction de la structure de votre base de donn�es.

	// Crypter le mot de passe avant de l'ins�rer dans la base de donn�es
	std::string encryptedPassword = encryptPassword(password);

	// Ins�rer l'utilisateur dans la base de donn�es avec le mot de passe crypt�
	String^ managedUsername = gcnew String(username.c_str());
	String^ managedFirstName = gcnew String(firstName.c_str());
	String^ managedLastName = gcnew String(lastName.c_str());
	String^ managedEmail = gcnew String(email.c_str());
	String^ managedPassword = gcnew String(encryptedPassword.c_str());

	try {
		SqlConnection^ connection = DatabaseConnection::GetConnection();
		SqlCommand^ command = gcnew SqlCommand();
		command->Connection = connection;

		connection->Open();

		String^ query = "INSERT INTO users (username, firstname, lastname, email, password) VALUES (@username, @firstName, @lastName, @email, @password)";
		command->CommandText = query;
		command->Parameters->AddWithValue("@username", managedUsername);
		command->Parameters->AddWithValue("@firstName", managedFirstName);
		command->Parameters->AddWithValue("@lastName", managedLastName);
		command->Parameters->AddWithValue("@email", managedEmail);
		command->Parameters->AddWithValue("@password", managedPassword);

		command->ExecuteNonQuery();

		connection->Close();

		std::cout << "User inserted into the database." << std::endl;
		MessageBox::Show("Utilisateur ins�r� avec succ�s.", "Succ�s", MessageBoxButtons::OK, MessageBoxIcon::Information);
		// R�afficher la fen�tre d'authentification
		// Cr�er une instance de la nouvelle fen�tre SignUp

		return true;
	}
	catch (Exception^ ex) {
		Console::WriteLine("Error: " + ex->Message);
		// Afficher un message en cas d'erreur de base de donn�es
		MessageBox::Show("Erreur de base de donn�es.", "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;
	}
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
			// R�cup�rer le mot de passe crypt� depuis la base de donn�es
			String^ fetchedPassword = safe_cast<String^>(reader["password"]);

			// Crypter le mot de passe fourni par l'utilisateur
			std::string encryptedPassword = encryptPassword(msclr::interop::marshal_as<std::string>(password));
			std::cout << encryptedPassword;
			// Comparer les mots de passe crypt�s
			if (fetchedPassword == gcnew String(encryptedPassword.c_str())) {
				MessageBox::Show("Connexion r�ussie.", "Succ�s", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return true;
			}
			else {
				MessageBox::Show("Nom d'utilisateur ou mot de passe incorrect.", "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return false;
			}
		}
		else {
			MessageBox::Show("Nom d'utilisateur ou mot de passe incorrect.", "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}

		reader->Close();
		connection->Close();
	}
	catch (Exception^ ex) {
		Console::WriteLine("Erreur : " + ex->Message);
		MessageBox::Show("Erreur de base de donn�es.", "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;
	}
}

void User::UpdateLevel(int newLevel) {
	// Mettre � jour le champ level dans la table users
	try {
		SqlConnection^ connection = DatabaseConnection::GetConnection();
		SqlCommand^ command = gcnew SqlCommand();
		command->Connection = connection;

		connection->Open();

		String^ query = "UPDATE users SET level = @level WHERE username = @username";
		command->CommandText = query;
		command->Parameters->AddWithValue("@level", newLevel);
		command->Parameters->AddWithValue("@username","rabihrajaa123");

		command->ExecuteNonQuery();

		connection->Close();
	}
	catch (Exception^ ex) {
		Console::WriteLine("Erreur : " + ex->Message);
		MessageBox::Show("Erreur de base de donn�es.", "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
