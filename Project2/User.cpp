#include "User.h"
#include "DatabaseConnection.h"
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include <Windows.h> // Pour utiliser les fonctions MessageBox
#include <regex> // Pour la validation de l'e-mail
#include <string>

User::User(std::string username, std::string firstName, std::string lastName, std::string email, std::string password)
	: username(username), firstName(firstName), lastName(lastName), email(email), password(password) {
	// Initialisez les membres de la classe si nécessaire
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


// Vérifie si l'e-mail est valide
bool isValidEmail(const std::string& email) {
	// Expression régulière pour la validation de l'e-mail
	std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
	return std::regex_match(email, pattern);
}

// Vérifie si le mot de passe est fort
bool isStrongPassword(const std::string& password) {
	// Vérifie si le mot de passe a une longueur minimale de 8 caractères et contient au moins une majuscule, une minuscule, un chiffre et un caractère spécial
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
			// Afficher un message si l'utilisateur n'est pas trouvé
			MessageBox(NULL, L"L'utilisateur n'existe pas.", L"Erreur", MB_OK | MB_ICONERROR);
		}

		reader->Close();
		connection->Close();
	}
	catch (Exception^ ex) {
		Console::WriteLine("Error: " + ex->Message);
		// Afficher un message en cas d'erreur de base de données
		MessageBox(NULL, L"Erreur de base de données.", L"Erreur", MB_OK | MB_ICONERROR);
	}

	return user;
}

bool User::InsertUser(std::string username, std::string firstName, std::string lastName, std::string email, std::string password) {
	// Vérification de la validité des données
	if (username.empty() || firstName.empty() || lastName.empty() || email.empty() || password.empty()) {
		MessageBox(NULL, L"Tous les champs doivent être remplis.", L"Erreur", MB_OK | MB_ICONERROR);
		return false;
	}

	if (!isValidEmail(email)) {
		MessageBox(NULL, L"L'adresse e-mail n'est pas valide.", L"Erreur", MB_OK | MB_ICONERROR);
		return false;
	}

	if (!isStrongPassword(password)) {
		MessageBox(NULL, L"Le mot de passe doit contenir au moins 8 caractères, y compris une majuscule, une minuscule, un chiffre et un caractère spécial.", L"Erreur", MB_OK | MB_ICONERROR);
		return false;
	}

	// Vérification de l'existence de l'e-mail et de l'unicité du nom d'utilisateur dans la base de données
	// Vous devez implémenter ces vérifications en fonction de la structure de votre base de données.

	// Crypter le mot de passe avant de l'insérer dans la base de données
	std::string encryptedPassword = encryptPassword(password);

	// Insérer l'utilisateur dans la base de données avec le mot de passe crypté
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
		MessageBox(NULL, L"Utilisateur inséré avec succès.", L"Succès", MB_OK | MB_ICONINFORMATION);
		// Réafficher la fenêtre d'authentification
		// Créer une instance de la nouvelle fenêtre SignUp

		return true;
	}
	catch (Exception^ ex) {
		Console::WriteLine("Error: " + ex->Message);
		// Afficher un message en cas d'erreur de base de données
		MessageBox(NULL, L"Erreur de base de données.", L"Erreur", MB_OK | MB_ICONERROR);
		return false;
	}
}
