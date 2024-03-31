#include "Auth.h"

using namespace System;
using namespace Project2; // Utilisez le bon espace de noms

[STAThreadAttribute]
int main() {
	// Crée une instance de la classe Home et lance l'application
	Windows::Forms::Application::Run(gcnew Auth());
	return 0;
}