#pragma once
#include "User.h"
#include <vector> // Pour utiliser std::vector
#include <cstdlib> // Pour utiliser la fonction rand
#include <ctime> // Pour initialiser le g�n�rateur de nombres al�atoires
#include <iostream>
#include <string>
#include <msclr\marshal_cppstd.h> // Pour convertir System::String en std::string
#include <Windows.h> // Pour utiliser MessageBox
#include <vcclr.h> // Pour g�rer la conversion entre System::String et std::string

namespace Project2 {
	using namespace System::IO;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Game
	/// </summary>
	public ref class Game : public System::Windows::Forms::Form
	{
		// Tableau pour stocker les chemins d'images
		array<String^>^ imagePaths;
		// liste chainee
		ref struct Piece {
			String^ forme;
			String^ color;
			String^ path;
			Piece^ previous;
			Piece^ next;
		};
		Piece^ head;
		Piece^ tail;
		int count;
		int maxSize;
		bool premierAppel = true;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::PictureBox^  pictureBox16;
	private: System::Windows::Forms::PictureBox^  pictureBox15;
	private: System::Windows::Forms::PictureBox^  pictureBox13;
	private: System::Windows::Forms::PictureBox^  pictureBox12;
	private: System::Windows::Forms::PictureBox^  pictureBox14;
	private: System::Windows::Forms::PictureBox^  pictureBox11;
	private: System::Windows::Forms::PictureBox^  pictureBox10;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::PictureBox^  pictureBox20;
	private: System::Windows::Forms::PictureBox^  pictureBox19;
	private: System::Windows::Forms::PictureBox^  pictureBox18;
	private: System::Windows::Forms::PictureBox^  pictureBox17;
	private: System::Windows::Forms::Label^  label4;
			 int score = 0;
	public:
		Game(void)
		{
			InitializeComponent();

			head = nullptr;
			tail = nullptr;
			count = 0;
			maxSize = 15; // Taille maximale de la liste

			// Initialiser le g�n�rateur de nombres al�atoires avec le temps actuel
			srand(time(0));

			// Initialiser le tableau de chemins d'images avec 16 images
			imagePaths = gcnew array<String^>(16);
			// Remplir le tableau avec les chemins d'images
			imagePaths[0] = "C:/Users/rajaa/source/repos/Project2/t_b.png";
			imagePaths[1] = "C:/Users/rajaa/source/repos/Project2/t_r.png";
			imagePaths[2] = "C:/Users/rajaa/source/repos/Project2/t_j.png";
			imagePaths[3] = "C:/Users/rajaa/source/repos/Project2/t_v.png";
			imagePaths[4] = "C:/Users/rajaa/source/repos/Project2/ca_j.jpeg";
			imagePaths[5] = "C:/Users/rajaa/source/repos/Project2/c_j.png";
			imagePaths[6] = "C:/Users/rajaa/source/repos/Project2/c_v.png";
			imagePaths[7] = "C:/Users/rajaa/source/repos/Project2/c_b.png";
			imagePaths[8] = "C:/Users/rajaa/source/repos/Project2/c_r.png";
			imagePaths[9] = "C:/Users/rajaa/source/repos/Project2/l_v.png";
			imagePaths[10] = "C:/Users/rajaa/source/repos/Project2/l_b.png";
			imagePaths[11] = "C:/Users/rajaa/source/repos/Project2/l_j.png";
			imagePaths[12] = "C:/Users/rajaa/source/repos/Project2/l_r.png";
			imagePaths[13] = "C:/Users/rajaa/source/repos/Project2/ca_r.png";
			imagePaths[14] = "C:/Users/rajaa/source/repos/Project2/ca_b.jpg";
			imagePaths[15] = "C:/Users/rajaa/source/repos/Project2/ca_v.jpg";

			// Afficher une image al�atoire lorsque le formulaire est charg� pour la premi�re fois
			AfficherImageAleatoire();
			AfficherPieces();
		}

	private:
		void DecalageForme(String^ forme) {
			// V�rifier si la liste de pi�ces est vide
			if (head == nullptr) {
				MessageBox::Show("La liste de pi�ces est vide", "Erreur");
				return;
			}

			// Taille maximale du tableau
			const int maxSize = 15;

			// Tableaux pour stocker les couleurs et les tags
			array<String^>^ colorsArray = gcnew array<String^>(maxSize);
			array<String^>^ tagsArray = gcnew array<String^>(maxSize);

			// Indice pour parcourir le tableau
			int index = 0;

			// Parcourir la liste des pi�ces pour stocker les couleurs et les tags
			Piece^ currentPiece = head;
			while (currentPiece != nullptr) {
				// V�rifier si la pi�ce a la forme sp�cifi�e
				if (currentPiece->forme == forme) {
					// Ajouter la couleur et le tag au tableau respectif
					colorsArray[index] = currentPiece->color;
					tagsArray[index] = currentPiece->path;

					// Incr�menter l'indice
					index++;

					// V�rifier si on a atteint la taille maximale du tableau
					if (index >= maxSize) {
						break;
					}
				}
				currentPiece = currentPiece->next;
			}

			// Si aucune couleur n'a �t� trouv�e pour la forme sp�cifi�e, afficher un message
			if (index == 0) {
				MessageBox::Show("Aucune pi�ce de la forme sp�cifi�e n'a �t� trouv�e", "Info");
				return;
			}

			// Parcourir � nouveau la liste des pi�ces pour affecter les couleurs et les tags stock�s dans les tableaux
			currentPiece = head;
			int colorIndex = 1; // Commencer par l'index 1 dans le tableau des couleurs
			while (currentPiece != nullptr) {
				// V�rifier si la pi�ce a la forme sp�cifi�e
				if (currentPiece->forme == forme) {
					// Affecter la couleur et le tag stock�s dans les tableaux � cette pi�ce
					currentPiece->color = colorsArray[colorIndex];
					currentPiece->path = tagsArray[colorIndex];
					MessageBox::Show(currentPiece->color);
					// Incr�menter l'indice du tableau des couleurs
					colorIndex = (colorIndex + 1) % index; // R�initialiser � 0 si on atteint la fin du tableau
				}

				currentPiece = currentPiece->next;
			}

			AfficherPieces();
		}

		void DecalageCouleur(String^ couleur) {
			// V�rifier si la liste de pi�ces est vide
			if (head == nullptr) {
				MessageBox::Show("La liste de pi�ces est vide", "Erreur");
				return;
			}

			// Taille maximale du tableau
			const int maxSize = 15;

			// Tableaux pour stocker les formes et les tags
			array<String^>^ formesArray = gcnew array<String^>(maxSize);
			array<String^>^ tagsArray = gcnew array<String^>(maxSize);

			// Indice pour parcourir le tableau
			int index = 0;

			// Parcourir la liste des pi�ces pour stocker les formes et les tags
			Piece^ currentPiece = head;
			while (currentPiece != nullptr) {
				// V�rifier si la pi�ce a la couleur sp�cifi�e
				if (currentPiece->color == couleur) {
					// Ajouter la forme et le tag au tableau respectif
					formesArray[index] = currentPiece->forme;
					tagsArray[index] = currentPiece->path;

					// Incr�menter l'indice
					index++;

					// V�rifier si on a atteint la taille maximale du tableau
					if (index >= maxSize) {
						break;
					}
				}
				currentPiece = currentPiece->next;
			}

			// Si aucune forme n'a �t� trouv�e pour la couleur sp�cifi�e, afficher un message
			if (index == 0) {
				MessageBox::Show("Aucune pi�ce de la couleur sp�cifi�e n'a �t� trouv�e", "Info");
				return;
			}

			// Parcourir � nouveau la liste des pi�ces pour affecter les formes et les tags stock�s dans les tableaux
			currentPiece = head;
			int formeIndex = 1; // Commencer par l'index 1 dans le tableau des formes
			while (currentPiece != nullptr) {
				// V�rifier si la pi�ce a la couleur sp�cifi�e
				if (currentPiece->color == couleur) {
					// Affecter la forme et le tag stock�s dans les tableaux � cette pi�ce
					currentPiece->forme = formesArray[formeIndex];
					currentPiece->path = tagsArray[formeIndex];
					MessageBox::Show(currentPiece->forme);
					// Incr�menter l'indice du tableau des formes
					formeIndex = (formeIndex + 1) % index; // R�initialiser � 0 si on atteint la fin du tableau
				}

				currentPiece = currentPiece->next;
			}

			AfficherPieces();
		}

		void RemoveThreeAdjacentPieces() {
			Piece^ currentPiece = head;
			while (currentPiece != nullptr && currentPiece->next != nullptr && currentPiece->next->next != nullptr) {
				Piece^ firstPiece = currentPiece;
				Piece^ secondPiece = currentPiece->next;
				Piece^ thirdPiece = currentPiece->next->next;

				// V�rifier si les trois pi�ces ont la m�me couleur ou la m�me forme
				if (firstPiece->color == secondPiece->color && secondPiece->color == thirdPiece->color) {
					// Supprimer les trois pi�ces de la liste
					if (firstPiece->previous != nullptr) {
						firstPiece->previous->next = thirdPiece->next;
					}
					else {
						head = thirdPiece->next;
					}
					if (thirdPiece->next != nullptr) {
						thirdPiece->next->previous = firstPiece->previous;
					}
					else {
						tail = firstPiece->previous;
					}
					count -= 3; // Mettre � jour le nombre de pi�ces dans la liste
					score++;
					label3->Text = "Score: " + score;
					// D�truire les objets supprim�s pour �viter les fuites de m�moire
					delete firstPiece;
					delete secondPiece;
					delete thirdPiece;
					// Repositionner le pointeur actuel pour continuer la v�rification
					currentPiece = (firstPiece->previous != nullptr) ? firstPiece->previous : head;
				}
				else if (firstPiece->forme == secondPiece->forme && secondPiece->forme == thirdPiece->forme) {
					// Supprimer les trois pi�ces de la liste
					if (firstPiece->previous != nullptr) {
						firstPiece->previous->next = thirdPiece->next;
					}
					else {
						head = thirdPiece->next;
					}
					if (thirdPiece->next != nullptr) {
						thirdPiece->next->previous = firstPiece->previous;
					}
					else {
						tail = firstPiece->previous;
					}
					count -= 3; // Mettre � jour le nombre de pi�ces dans la liste
					score++;
					label3->Text = "Score: " + score;
					// D�truire les objets supprim�s pour �viter les fuites de m�moire
					delete firstPiece;
					delete secondPiece;
					delete thirdPiece;
					// Repositionner le pointeur actuel pour continuer la v�rification
					currentPiece = (firstPiece->previous != nullptr) ? firstPiece->previous : head;
				}
				else {
					// Avancer au prochain ensemble de pi�ces
					currentPiece = currentPiece->next;
				}
			}
			// Mettre � jour l'affichage des PictureBoxes
			AfficherPieces();
		}

		void ObtenirFormeEtCouleur(PictureBox^ pictureBox, String^% forme, String^% color) {
			// R�cup�rer le chemin de l'image de pictureBox
			String^ cheminImage = safe_cast<String^>(pictureBox->Tag);

			// V�rifier si le chemin de l'image est valide
			if (!String::IsNullOrEmpty(cheminImage)) {
				String^ nomImage = Path::GetFileNameWithoutExtension(cheminImage); // R�cup�rer le nom de l'image sans l'extension
				array<String^>^ parties = nomImage->Split('_'); // Diviser le nom en fonction du caract�re '_'

				// V�rifier s'il y a au moins deux parties dans le nom de l'image
				if (parties->Length >= 2) {
					forme = parties[0]; // Stocker la premi�re partie dans la variable forme
					color = parties[1]; // Stocker la deuxi�me partie dans la variable color
				}
				else {
					// G�rer le cas o� le nom de l'image n'a pas �t� divis� correctement
					MessageBox::Show("Le nom de l'image n'a pas �t� divis� correctement.");
				}
			}
		}

		// Fonction pour afficher une image al�atoire dans pictureBox1
		void AfficherImageAleatoire()
		{
			// G�n�rer un indice al�atoire entre 0 et 15 inclusivement
			int index = rand() % 16;

			// R�cup�rer le chemin de l'image correspondante � l'indice al�atoire
			String^ imagePath = imagePaths[index];
			pictureBox1->Image = nullptr;

			// Pour le premier appel, mettre � jour toutes les PictureBox
			if (premierAppel)
			{
				// PictureBox1
				pictureBox1->BackgroundImage = Image::FromFile(imagePaths[rand() % 16]);
				pictureBox1->Tag = imagePaths[rand() % 16];

				// PictureBox17
				pictureBox17->BackgroundImage = Image::FromFile(imagePaths[rand() % 16]);
				pictureBox17->Tag = imagePaths[rand() % 16];

				// PictureBox18
				pictureBox18->BackgroundImage = Image::FromFile(imagePaths[rand() % 16]);
				pictureBox18->Tag = imagePaths[rand() % 16];

				// PictureBox19
				pictureBox19->BackgroundImage = Image::FromFile(imagePaths[rand() % 16]);
				pictureBox19->Tag = imagePaths[rand() % 16];

				// PictureBox20
				pictureBox20->BackgroundImage = Image::FromFile(imagePaths[rand() % 16]);
				pictureBox20->Tag = imagePaths[rand() % 16];

				premierAppel = false; // Marquer le premier appel comme effectu�
			}
			else
			{
				// Sauvegarder l'image de pictureBox1
				pictureBox1->BackgroundImage = pictureBox17->BackgroundImage;
				pictureBox1->Tag = pictureBox17->Tag;

				// D�placer l'image de pictureBox17 � pictureBox18
				pictureBox17->BackgroundImage = pictureBox18->BackgroundImage;
				pictureBox17->Tag = pictureBox18->Tag;

				// D�placer l'image de pictureBox18 � pictureBox19
				pictureBox18->BackgroundImage = pictureBox19->BackgroundImage;
				pictureBox18->Tag = pictureBox19->Tag;

				// D�placer l'image de pictureBox19 � pictureBox20
				pictureBox19->BackgroundImage = pictureBox20->BackgroundImage;
				pictureBox19->Tag = pictureBox20->Tag;

				// Charger la nouvelle image dans pictureBox20
				pictureBox20->BackgroundImage = Image::FromFile(imagePath);
				pictureBox20->Tag = imagePath;
			}
		}



		void AddPieceAtBeginning(String^ forme, String^ color, String^ path) {
			if (count < maxSize) {
				Piece^ newPiece = gcnew Piece();
				newPiece->forme = forme;
				newPiece->color = color;
				newPiece->path = path;
				newPiece->previous = nullptr;
				newPiece->next = head;

				if (head != nullptr) {
					head->previous = newPiece;
				}
				head = newPiece;

				if (tail == nullptr) {
					tail = newPiece;
				}

				count++;
				AfficherImageAleatoire();
				RemoveThreeAdjacentPieces();
			}
			else {
				// La liste est pleine, ne peut pas ajouter plus de pi�ces
				MessageBox::Show("La liste est pleine, ne peut pas ajouter plus de pi�ces.");
			}
		}

		void AfficherPieces() {
			Piece^ currentPiece = head; // Commencer � partir de la premi�re pi�ce
			int i = 0; // Compteur pour le nombre de pi�ces affich�es

			// Parcourir les PictureBoxes
			while (i < 16 && currentPiece != nullptr) {
				String^ path = currentPiece->path; // R�cup�rer le chemin de l'image de la pi�ce

				// Affecter le chemin de l'image au background du PictureBox correspondant
				switch (i) {
				case 0:
					pictureBox2->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox2->Tag = path; // Ajout du chemin d'acc�s � l'image dans le tag
					break;
				case 1:
					pictureBox3->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox3->Tag = path;
					break;
				case 2:
					pictureBox4->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox4->Tag = path;
					break;
				case 3:
					pictureBox5->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox5->Tag = path;
					break;
				case 4:
					pictureBox6->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox6->Tag = path;
					break;
				case 5:
					pictureBox7->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox7->Tag = path;
					break;
				case 6:
					pictureBox8->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox8->Tag = path;
					break;
				case 7:
					pictureBox9->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox9->Tag = path;
					break;
				case 8:
					pictureBox10->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox10->Tag = path;
					break;
				case 9:
					pictureBox11->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox11->Tag = path;
					break;
				case 10:
					pictureBox12->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox12->Tag = path;
					break;
				case 11:
					pictureBox13->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox13->Tag = path;
					break;
				case 12:
					pictureBox14->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox14->Tag = path;
					break;
				case 13:
					pictureBox15->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox15->Tag = path;
					break;
				case 14:
					pictureBox16->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox16->Tag = path;
					break;
				}

				currentPiece = currentPiece->next; // Passer � la pi�ce suivante
				i++;
			}

			// Mettre les BackgroundImages restants � null
			while (i < 16) {
				switch (i) {
				case 0:
					pictureBox2->BackgroundImage = nullptr;
					pictureBox2->Tag = nullptr; // Affectation de null au tag
					break;
				case 1:
					pictureBox3->BackgroundImage = nullptr;
					pictureBox3->Tag = nullptr;
					break;
				case 2:
					pictureBox4->BackgroundImage = nullptr;
					pictureBox4->Tag = nullptr;
					break;
				case 3:
					pictureBox5->BackgroundImage = nullptr;
					pictureBox5->Tag = nullptr;
					break;
				case 4:
					pictureBox6->BackgroundImage = nullptr;
					pictureBox6->Tag = nullptr;
					break;
				case 5:
					pictureBox7->BackgroundImage = nullptr;
					pictureBox7->Tag = nullptr;
					break;
				case 6:
					pictureBox8->BackgroundImage = nullptr;
					pictureBox8->Tag = nullptr;
					break;
				case 7:
					pictureBox9->BackgroundImage = nullptr;
					pictureBox9->Tag = nullptr;
					break;
				case 8:
					pictureBox10->BackgroundImage = nullptr;
					pictureBox10->Tag = nullptr;
					break;
				case 9:
					pictureBox11->BackgroundImage = nullptr;
					pictureBox11->Tag = nullptr;
					break;
				case 10:
					pictureBox12->BackgroundImage = nullptr;
					pictureBox12->Tag = nullptr;
					break;
				case 11:
					pictureBox13->BackgroundImage = nullptr;
					pictureBox13->Tag = nullptr;
					break;
				case 12:
					pictureBox14->BackgroundImage = nullptr;
					pictureBox14->Tag = nullptr;
					break;
				case 13:
					pictureBox15->BackgroundImage = nullptr;
					pictureBox15->Tag = nullptr;
					break;
				case 14:
					pictureBox16->BackgroundImage = nullptr;
					pictureBox16->Tag = nullptr;
					break;
				}
				i++;
			}
		}

		void AddPieceAtEnd(String^ forme, String^ color, String^ path) {
			if (count < maxSize) {
				Piece^ newPiece = gcnew Piece();
				newPiece->forme = forme;
				newPiece->color = color;
				newPiece->path = path;
				newPiece->previous = tail;
				newPiece->next = nullptr;

				if (tail != nullptr) {
					tail->next = newPiece;
				}
				tail = newPiece;

				if (head == nullptr) {
					head = newPiece;
				}

				count++;
				AfficherImageAleatoire();
				RemoveThreeAdjacentPieces();
			}
			else {
				// La liste est pleine, ne peut pas ajouter plus de pi�ces
				MessageBox::Show("La liste est pleine, ne peut pas ajouter plus de pi�ces.");
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Game()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Panel^  nextpanel;
	private: System::Windows::Forms::PictureBox^  pictureBox9;
	private: System::Windows::Forms::Panel^  panel2;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Game::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->nextpanel = (gcnew System::Windows::Forms::Panel());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox16 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox15 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox13 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox14 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox20 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox19 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox18 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox17 = (gcnew System::Windows::Forms::PictureBox());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			this->nextpanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox14))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->button1->FlatAppearance->BorderSize = 3;
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(1122, 19);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(186, 38);
			this->button1->TabIndex = 12;
			this->button1->Text = L"STOP PLAYING";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Game::button1_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 27.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label3->Location = System::Drawing::Point(537, 400);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(175, 46);
			this->label3->TabIndex = 14;
			this->label3->Text = L"Score: 0";
			this->label3->TextChanged += gcnew System::EventHandler(this, &Game::label3_TextChanged);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Location = System::Drawing::Point(3, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1336, 64);
			this->panel1->TabIndex = 15;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Game::panel1_Paint);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 21.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::Crimson;
			this->label4->Location = System::Drawing::Point(12, 7);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(129, 36);
			this->label4->TabIndex = 35;
			this->label4->Text = L"Level: 0";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(9, 15);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(80, 80);
			this->pictureBox1->TabIndex = 16;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Tag = L"";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(22, 105);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(68, 23);
			this->label1->TabIndex = 17;
			this->label1->Text = L"Next : ";
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.BackgroundImage")));
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox2->Location = System::Drawing::Point(18, 13);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(80, 80);
			this->pictureBox2->TabIndex = 18;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.BackgroundImage")));
			this->pictureBox3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox3->Location = System::Drawing::Point(104, 13);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(80, 80);
			this->pictureBox3->TabIndex = 19;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox3_DoubleClick);
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.BackgroundImage")));
			this->pictureBox4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox4->Location = System::Drawing::Point(190, 13);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(80, 80);
			this->pictureBox4->TabIndex = 20;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox4_DoubleClick);
			// 
			// pictureBox5
			// 
			this->pictureBox5->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.BackgroundImage")));
			this->pictureBox5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox5->Location = System::Drawing::Point(276, 13);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(80, 80);
			this->pictureBox5->TabIndex = 21;
			this->pictureBox5->TabStop = false;
			this->pictureBox5->Click += gcnew System::EventHandler(this, &Game::pictureBox5_Click);
			this->pictureBox5->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox5_DoubleClick);
			// 
			// pictureBox6
			// 
			this->pictureBox6->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox6.BackgroundImage")));
			this->pictureBox6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox6->Location = System::Drawing::Point(362, 13);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(80, 80);
			this->pictureBox6->TabIndex = 22;
			this->pictureBox6->TabStop = false;
			this->pictureBox6->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox6_DoubleClick);
			// 
			// pictureBox7
			// 
			this->pictureBox7->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.BackgroundImage")));
			this->pictureBox7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox7->Location = System::Drawing::Point(448, 13);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(80, 80);
			this->pictureBox7->TabIndex = 23;
			this->pictureBox7->TabStop = false;
			this->pictureBox7->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox7_DoubleClick);
			// 
			// pictureBox8
			// 
			this->pictureBox8->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox8.BackgroundImage")));
			this->pictureBox8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox8->Location = System::Drawing::Point(534, 13);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(80, 80);
			this->pictureBox8->TabIndex = 24;
			this->pictureBox8->TabStop = false;
			this->pictureBox8->Click += gcnew System::EventHandler(this, &Game::pictureBox8_Click);
			this->pictureBox8->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox8_DoubleClick);
			// 
			// button2
			// 
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(12, 180);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(56, 54);
			this->button2->TabIndex = 25;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Game::button2_Click);
			// 
			// button3
			// 
			this->button3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.BackgroundImage")));
			this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button3->FlatAppearance->BorderSize = 0;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(1257, 167);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(56, 54);
			this->button3->TabIndex = 26;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Game::button3_Click);
			// 
			// nextpanel
			// 
			this->nextpanel->Controls->Add(this->pictureBox1);
			this->nextpanel->Location = System::Drawing::Point(96, 82);
			this->nextpanel->Name = L"nextpanel";
			this->nextpanel->Size = System::Drawing::Size(100, 109);
			this->nextpanel->TabIndex = 27;
			this->nextpanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Game::panel2_Paint);
			// 
			// pictureBox9
			// 
			this->pictureBox9->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox9.BackgroundImage")));
			this->pictureBox9->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox9->Location = System::Drawing::Point(620, 13);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(80, 80);
			this->pictureBox9->TabIndex = 28;
			this->pictureBox9->TabStop = false;
			this->pictureBox9->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox9_DoubleClick);
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::Gray;
			this->panel2->Controls->Add(this->pictureBox16);
			this->panel2->Controls->Add(this->pictureBox15);
			this->panel2->Controls->Add(this->pictureBox13);
			this->panel2->Controls->Add(this->pictureBox12);
			this->panel2->Controls->Add(this->pictureBox14);
			this->panel2->Controls->Add(this->pictureBox11);
			this->panel2->Controls->Add(this->pictureBox10);
			this->panel2->Controls->Add(this->pictureBox9);
			this->panel2->Controls->Add(this->pictureBox8);
			this->panel2->Controls->Add(this->pictureBox7);
			this->panel2->Controls->Add(this->pictureBox6);
			this->panel2->Controls->Add(this->pictureBox5);
			this->panel2->Controls->Add(this->pictureBox4);
			this->panel2->Controls->Add(this->pictureBox3);
			this->panel2->Controls->Add(this->pictureBox2);
			this->panel2->Location = System::Drawing::Point(12, 256);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1312, 105);
			this->panel2->TabIndex = 29;
			// 
			// pictureBox16
			// 
			this->pictureBox16->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox16.BackgroundImage")));
			this->pictureBox16->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox16->Location = System::Drawing::Point(1221, 13);
			this->pictureBox16->Name = L"pictureBox16";
			this->pictureBox16->Size = System::Drawing::Size(80, 80);
			this->pictureBox16->TabIndex = 28;
			this->pictureBox16->TabStop = false;
			this->pictureBox16->Click += gcnew System::EventHandler(this, &Game::pictureBox16_Click);
			this->pictureBox16->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox9_DoubleClick);
			// 
			// pictureBox15
			// 
			this->pictureBox15->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox15.BackgroundImage")));
			this->pictureBox15->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox15->Location = System::Drawing::Point(1135, 13);
			this->pictureBox15->Name = L"pictureBox15";
			this->pictureBox15->Size = System::Drawing::Size(80, 80);
			this->pictureBox15->TabIndex = 28;
			this->pictureBox15->TabStop = false;
			this->pictureBox15->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox15_DoubleClick);
			// 
			// pictureBox13
			// 
			this->pictureBox13->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox13.BackgroundImage")));
			this->pictureBox13->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox13->Location = System::Drawing::Point(964, 13);
			this->pictureBox13->Name = L"pictureBox13";
			this->pictureBox13->Size = System::Drawing::Size(80, 80);
			this->pictureBox13->TabIndex = 28;
			this->pictureBox13->TabStop = false;
			this->pictureBox13->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox13_DoubleClick);
			// 
			// pictureBox12
			// 
			this->pictureBox12->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox12.BackgroundImage")));
			this->pictureBox12->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox12->Location = System::Drawing::Point(878, 13);
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->Size = System::Drawing::Size(80, 80);
			this->pictureBox12->TabIndex = 28;
			this->pictureBox12->TabStop = false;
			this->pictureBox12->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox12_DoubleClick);
			// 
			// pictureBox14
			// 
			this->pictureBox14->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox14.BackgroundImage")));
			this->pictureBox14->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox14->Location = System::Drawing::Point(1049, 13);
			this->pictureBox14->Name = L"pictureBox14";
			this->pictureBox14->Size = System::Drawing::Size(80, 80);
			this->pictureBox14->TabIndex = 28;
			this->pictureBox14->TabStop = false;
			this->pictureBox14->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox14_DoubleClick);
			// 
			// pictureBox11
			// 
			this->pictureBox11->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox11.BackgroundImage")));
			this->pictureBox11->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox11->Location = System::Drawing::Point(792, 13);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(80, 80);
			this->pictureBox11->TabIndex = 28;
			this->pictureBox11->TabStop = false;
			this->pictureBox11->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox11_DoubleClick);
			// 
			// pictureBox10
			// 
			this->pictureBox10->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox10.BackgroundImage")));
			this->pictureBox10->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox10->Location = System::Drawing::Point(706, 13);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(80, 80);
			this->pictureBox10->TabIndex = 28;
			this->pictureBox10->TabStop = false;
			this->pictureBox10->DoubleClick += gcnew System::EventHandler(this, &Game::pictureBox10_DoubleClick);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(13, 15);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(210, 23);
			this->label2->TabIndex = 30;
			this->label2->Text = L"Faire un d�calage par: ";
			this->label2->Click += gcnew System::EventHandler(this, &Game::label2_Click);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton1->ForeColor = System::Drawing::Color::Navy;
			this->radioButton1->Location = System::Drawing::Point(255, 13);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(85, 27);
			this->radioButton1->TabIndex = 31;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Forme";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioButton2->ForeColor = System::Drawing::Color::Navy;
			this->radioButton2->Location = System::Drawing::Point(361, 13);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(99, 27);
			this->radioButton2->TabIndex = 32;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Couleur";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel3->Controls->Add(this->radioButton2);
			this->panel3->Controls->Add(this->label2);
			this->panel3->Controls->Add(this->radioButton1);
			this->panel3->Location = System::Drawing::Point(838, 97);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(475, 59);
			this->panel3->TabIndex = 33;
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->panel4->Controls->Add(this->pictureBox20);
			this->panel4->Controls->Add(this->pictureBox19);
			this->panel4->Controls->Add(this->pictureBox18);
			this->panel4->Controls->Add(this->pictureBox17);
			this->panel4->Location = System::Drawing::Point(202, 82);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(363, 109);
			this->panel4->TabIndex = 34;
			// 
			// pictureBox20
			// 
			this->pictureBox20->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox20.BackgroundImage")));
			this->pictureBox20->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox20->Location = System::Drawing::Point(270, 15);
			this->pictureBox20->Name = L"pictureBox20";
			this->pictureBox20->Size = System::Drawing::Size(80, 80);
			this->pictureBox20->TabIndex = 35;
			this->pictureBox20->TabStop = false;
			// 
			// pictureBox19
			// 
			this->pictureBox19->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox19.BackgroundImage")));
			this->pictureBox19->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox19->Location = System::Drawing::Point(184, 15);
			this->pictureBox19->Name = L"pictureBox19";
			this->pictureBox19->Size = System::Drawing::Size(80, 80);
			this->pictureBox19->TabIndex = 35;
			this->pictureBox19->TabStop = false;
			// 
			// pictureBox18
			// 
			this->pictureBox18->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox18.BackgroundImage")));
			this->pictureBox18->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox18->Location = System::Drawing::Point(98, 15);
			this->pictureBox18->Name = L"pictureBox18";
			this->pictureBox18->Size = System::Drawing::Size(80, 80);
			this->pictureBox18->TabIndex = 35;
			this->pictureBox18->TabStop = false;
			// 
			// pictureBox17
			// 
			this->pictureBox17->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox17.BackgroundImage")));
			this->pictureBox17->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox17->Location = System::Drawing::Point(12, 15);
			this->pictureBox17->Name = L"pictureBox17";
			this->pictureBox17->Size = System::Drawing::Size(80, 80);
			this->pictureBox17->TabIndex = 35;
			this->pictureBox17->TabStop = false;
			// 
			// Game
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ClientSize = System::Drawing::Size(1339, 499);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->nextpanel);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel1);
			this->Name = L"Game";
			this->Text = L"Game";
			this->Load += gcnew System::EventHandler(this, &Game::Game_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			this->nextpanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			this->panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox14))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	}

private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
//	pictureBox8->BackgroundImage = Image::FromFile("C:/Users/rajaa/source/repos/Project2/c_r.png");

	// R�cup�rer le chemin de l'image de pictureBox1
	String^ cheminImage = safe_cast<String^>(pictureBox1->Tag);

	// V�rifier si le chemin de l'image est valide
	if (!String::IsNullOrEmpty(cheminImage)) {
		String^ nomImage = Path::GetFileNameWithoutExtension(cheminImage); // R�cup�rer le nom de l'image sans l'extension
		array<String^>^ parties = nomImage->Split('_'); // Diviser le nom en fonction du caract�re '_'

		String^ forme;
		String^ color;

		// V�rifier s'il y a au moins deux parties dans le nom de l'image
		if (parties->Length >= 2) {
			forme = parties[0]; // Stocker la premi�re partie dans la variable forme
			color = parties[1]; // Stocker la deuxi�me partie dans la variable color

			// Afficher les valeurs des variables forme et color
		}
		else {
			// G�rer le cas o� le nom de l'image n'a pas �t� divis� correctement
			MessageBox::Show("Le nom de l'image n'a pas �t� divis� correctement.");
		}

		// Affecter le chemin de l'image de pictureBox1 au pictureBox2
		//pictureBox8->BackgroundImage = Image::FromFile(cheminImage);
		AddPieceAtEnd(forme, color, cheminImage);
	}
	else {
		// Afficher un message d'erreur si le chemin de l'image est invalide ou non d�fini
		MessageBox::Show("Le chemin de l'image est invalide ou non d�fini.");
	}

}
private: System::Void panel2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
private: System::Void pictureBox8_Click(System::Object^  sender, System::EventArgs^  e) {
	
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	//	pictureBox8->BackgroundImage = Image::FromFile("C:/Users/rajaa/source/repos/Project2/c_r.png");

	// R�cup�rer le chemin de l'image de pictureBox1
	String^ cheminImage = safe_cast<String^>(pictureBox1->Tag);

	// V�rifier si le chemin de l'image est valide
	if (!String::IsNullOrEmpty(cheminImage)) {
		String^ nomImage = Path::GetFileNameWithoutExtension(cheminImage); // R�cup�rer le nom de l'image sans l'extension
		array<String^>^ parties = nomImage->Split('_'); // Diviser le nom en fonction du caract�re '_'

		String^ forme;
		String^ color;

		// V�rifier s'il y a au moins deux parties dans le nom de l'image
		if (parties->Length >= 2) {
			forme = parties[0]; // Stocker la premi�re partie dans la variable forme
			color = parties[1]; // Stocker la deuxi�me partie dans la variable color

			// Afficher les valeurs des variables forme et color
		}
		else {
			// G�rer le cas o� le nom de l'image n'a pas �t� divis� correctement
			MessageBox::Show("Le nom de l'image n'a pas �t� divis� correctement.");
		}

		// Affecter le chemin de l'image de pictureBox1 au pictureBox2
		//pictureBox8->BackgroundImage = Image::FromFile(cheminImage);
		AddPieceAtBeginning(forme, color, cheminImage);
	}
	else {
		// Afficher un message d'erreur si le chemin de l'image est invalide ou non d�fini
		MessageBox::Show("Le chemin de l'image est invalide ou non d�fini.");
	}
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	// Afficher une bo�te de dialogue pour demander � l'utilisateur s'il souhaite quitter le jeu
	System::Windows::Forms::DialogResult result = MessageBox::Show("Do you want to leave the game?", "Exit Game", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

	// V�rifier la r�ponse de l'utilisateur
	if (result == System::Windows::Forms::DialogResult::Yes) {
		// Masquer la fen�tre actuelle (la fen�tre de jeu)
		this->Hide();
	}
}
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void pictureBox9_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox9, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}


private: System::Void Game_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	// V�rifier si le score atteint 10 ou 20

	if (score == 10) {
		User::UpdateLevel(1);
		label4->Text = "Level: 1";
	}
	else if (score == 20) {
		User::UpdateLevel(2);
		label4->Text = "Level: 2";
	}
	else if (score == 40) {
		User::UpdateLevel(2);
		label4->Text = "Level: 3";
	}
	else if (score == 60) {
		User::UpdateLevel(2);
		label4->Text = "Level: 4";
	}
	else if (score == 90) {
		User::UpdateLevel(2);
		label4->Text = "Level: 5";
	}
	else if (score == 120) {
		User::UpdateLevel(2);
		label4->Text = "Level: 6";
	}
}


private: System::Void pictureBox3_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox3, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}
private: System::Void pictureBox4_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox4, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}


private: System::Void pictureBox5_Click(System::Object^  sender, System::EventArgs^  e) {

}

private: System::Void pictureBox5_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox5, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}


private: System::Void pictureBox6_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox6, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}

private: System::Void pictureBox7_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox7, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}


private: System::Void pictureBox8_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox8, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}


private: System::Void pictureBox10_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox10, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}


private: System::Void pictureBox11_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox11, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}


private: System::Void pictureBox12_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox12, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}


private: System::Void pictureBox13_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox13, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}


private: System::Void pictureBox14_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox14, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}
private: System::Void pictureBox15_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox15, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}


private: System::Void pictureBox16_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ forme;
	String^ color;
	ObtenirFormeEtCouleur(pictureBox16, forme, color);
	// Utilisez les variables forme et color comme vous le souhaitez
	MessageBox::Show(forme);
	// V�rifier si l'utilisateur veut effectuer un d�calage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// D�calage en fonction de la forme

		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option s�lectionn�e, afficher un message d'erreur
		MessageBox::Show("Veuillez s�lectionner une option (forme ou couleur) pour effectuer un d�calage.");
	}
}

};
}
