#pragma once
#include <vector> // Pour utiliser std::vector
#include <cstdlib> // Pour utiliser la fonction rand
#include <ctime> // Pour initialiser le générateur de nombres aléatoires
#include <iostream>
#include <string>
#include <msclr\marshal_cppstd.h> // Pour convertir System::String en std::string
#include <Windows.h> // Pour utiliser MessageBox
#include <vcclr.h> // Pour gérer la conversion entre System::String et std::string

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
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::Panel^  panel3;
			 int score = 0;
	public:
		Game(void)
		{
			InitializeComponent();

			head = nullptr;
			tail = nullptr;
			count = 0;
			maxSize = 8; // Taille maximale de la liste

			// Initialiser le générateur de nombres aléatoires avec le temps actuel
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

			// Afficher une image aléatoire lorsque le formulaire est chargé pour la première fois
			AfficherImageAleatoire();
			AfficherPieces();
		}

	private:
		void DecalageForme(String^ forme) {
			// Vérifier si la liste de pièces est vide
			if (head == nullptr) {
				MessageBox::Show("La liste de pièces est vide", "Erreur");
				return;
			}

			// Taille maximale du tableau
			const int maxSize = 15;

			// Tableaux pour stocker les couleurs et les tags
			array<String^>^ colorsArray = gcnew array<String^>(maxSize);
			array<String^>^ tagsArray = gcnew array<String^>(maxSize);

			// Indice pour parcourir le tableau
			int index = 0;

			// Parcourir la liste des pièces pour stocker les couleurs et les tags
			Piece^ currentPiece = head;
			while (currentPiece != nullptr) {
				// Vérifier si la pièce a la forme spécifiée
				if (currentPiece->forme == forme) {
					// Ajouter la couleur et le tag au tableau respectif
					colorsArray[index] = currentPiece->color;
					tagsArray[index] = currentPiece->path;

					// Incrémenter l'indice
					index++;

					// Vérifier si on a atteint la taille maximale du tableau
					if (index >= maxSize) {
						break;
					}
				}
				currentPiece = currentPiece->next;
			}

			// Si aucune couleur n'a été trouvée pour la forme spécifiée, afficher un message
			if (index == 0) {
				MessageBox::Show("Aucune pièce de la forme spécifiée n'a été trouvée", "Info");
				return;
			}

			// Parcourir à nouveau la liste des pièces pour affecter les couleurs et les tags stockés dans les tableaux
			currentPiece = head;
			int colorIndex = 1; // Commencer par l'index 1 dans le tableau des couleurs
			while (currentPiece != nullptr) {
				// Vérifier si la pièce a la forme spécifiée
				if (currentPiece->forme == forme) {
					// Affecter la couleur et le tag stockés dans les tableaux à cette pièce
					currentPiece->color = colorsArray[colorIndex];
					currentPiece->path = tagsArray[colorIndex];
					MessageBox::Show(currentPiece->color);
					// Incrémenter l'indice du tableau des couleurs
					colorIndex = (colorIndex + 1) % index; // Réinitialiser à 0 si on atteint la fin du tableau
				}

				currentPiece = currentPiece->next;
			}

			AfficherPieces();
		}

		void DecalageCouleur(String^ couleur) {
			// Vérifier si la liste de pièces est vide
			if (head == nullptr) {
				MessageBox::Show("La liste de pièces est vide", "Erreur");
				return;
			}

			// Taille maximale du tableau
			const int maxSize = 15;

			// Tableaux pour stocker les formes et les tags
			array<String^>^ formesArray = gcnew array<String^>(maxSize);
			array<String^>^ tagsArray = gcnew array<String^>(maxSize);

			// Indice pour parcourir le tableau
			int index = 0;

			// Parcourir la liste des pièces pour stocker les formes et les tags
			Piece^ currentPiece = head;
			while (currentPiece != nullptr) {
				// Vérifier si la pièce a la couleur spécifiée
				if (currentPiece->color == couleur) {
					// Ajouter la forme et le tag au tableau respectif
					formesArray[index] = currentPiece->forme;
					tagsArray[index] = currentPiece->path;

					// Incrémenter l'indice
					index++;

					// Vérifier si on a atteint la taille maximale du tableau
					if (index >= maxSize) {
						break;
					}
				}
				currentPiece = currentPiece->next;
			}

			// Si aucune forme n'a été trouvée pour la couleur spécifiée, afficher un message
			if (index == 0) {
				MessageBox::Show("Aucune pièce de la couleur spécifiée n'a été trouvée", "Info");
				return;
			}

			// Parcourir à nouveau la liste des pièces pour affecter les formes et les tags stockés dans les tableaux
			currentPiece = head;
			int formeIndex = 1; // Commencer par l'index 1 dans le tableau des formes
			while (currentPiece != nullptr) {
				// Vérifier si la pièce a la couleur spécifiée
				if (currentPiece->color == couleur) {
					// Affecter la forme et le tag stockés dans les tableaux à cette pièce
					currentPiece->forme = formesArray[formeIndex];
					currentPiece->path = tagsArray[formeIndex];
					MessageBox::Show(currentPiece->forme);
					// Incrémenter l'indice du tableau des formes
					formeIndex = (formeIndex + 1) % index; // Réinitialiser à 0 si on atteint la fin du tableau
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

				// Vérifier si les trois pièces ont la même couleur ou la même forme
				if (firstPiece->color == secondPiece->color && secondPiece->color == thirdPiece->color) {
					// Supprimer les trois pièces de la liste
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
					count -= 3; // Mettre à jour le nombre de pièces dans la liste
					score++;
					label3->Text = "Score: " + score;
					// Détruire les objets supprimés pour éviter les fuites de mémoire
					delete firstPiece;
					delete secondPiece;
					delete thirdPiece;
					// Repositionner le pointeur actuel pour continuer la vérification
					currentPiece = (firstPiece->previous != nullptr) ? firstPiece->previous : head;
				}
				else if (firstPiece->forme == secondPiece->forme && secondPiece->forme == thirdPiece->forme) {
					// Supprimer les trois pièces de la liste
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
					count -= 3; // Mettre à jour le nombre de pièces dans la liste
					score++;
					label3->Text = "Score: " + score;
					// Détruire les objets supprimés pour éviter les fuites de mémoire
					delete firstPiece;
					delete secondPiece;
					delete thirdPiece;
					// Repositionner le pointeur actuel pour continuer la vérification
					currentPiece = (firstPiece->previous != nullptr) ? firstPiece->previous : head;
				}
				else {
					// Avancer au prochain ensemble de pièces
					currentPiece = currentPiece->next;
				}
			}
			// Mettre à jour l'affichage des PictureBoxes
			AfficherPieces();
		}

		void ObtenirFormeEtCouleur(PictureBox^ pictureBox, String^% forme, String^% color) {
			// Récupérer le chemin de l'image de pictureBox
			String^ cheminImage = safe_cast<String^>(pictureBox->Tag);

			// Vérifier si le chemin de l'image est valide
			if (!String::IsNullOrEmpty(cheminImage)) {
				String^ nomImage = Path::GetFileNameWithoutExtension(cheminImage); // Récupérer le nom de l'image sans l'extension
				array<String^>^ parties = nomImage->Split('_'); // Diviser le nom en fonction du caractère '_'

				// Vérifier s'il y a au moins deux parties dans le nom de l'image
				if (parties->Length >= 2) {
					forme = parties[0]; // Stocker la première partie dans la variable forme
					color = parties[1]; // Stocker la deuxième partie dans la variable color
				}
				else {
					// Gérer le cas où le nom de l'image n'a pas été divisé correctement
					MessageBox::Show("Le nom de l'image n'a pas été divisé correctement.");
				}
			}
		}

		// Fonction pour afficher une image aléatoire dans pictureBox1
		void AfficherImageAleatoire()
		{
			// Générer un indice aléatoire entre 0 et 15 inclusivement
			int index = rand() % 16;
			// Charger l'image correspondante à l'indice aléatoire dans pictureBox1
			pictureBox1->BackgroundImage = Image::FromFile(imagePaths[index]);
			pictureBox1->Image = nullptr;
			pictureBox1->Tag = imagePaths[index];
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
				// La liste est pleine, ne peut pas ajouter plus de pièces
				MessageBox::Show("La liste est pleine, ne peut pas ajouter plus de pièces.");
			}
		}

		void AfficherPieces() {
			Piece^ currentPiece = head; // Commencer à partir de la première pièce
			int i = 0; // Compteur pour le nombre de pièces affichées

			// Parcourir les 8 PictureBoxes
			while (i < 8 && currentPiece != nullptr) {
				String^ path = currentPiece->path; // Récupérer le chemin de l'image de la pièce

				// Affecter le chemin de l'image au background du PictureBox correspondant
				switch (i) {
				case 0:
					pictureBox2->BackgroundImage = (path != nullptr) ? Image::FromFile(path) : nullptr;
					pictureBox2->Tag = path; // Ajout du chemin d'accès à l'image dans le tag
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
				}

				currentPiece = currentPiece->next; // Passer à la pièce suivante
				i++;
			}

			// Mettre les BackgroundImages restants à null
			while (i < 8) {
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
				// La liste est pleine, ne peut pas ajouter plus de pièces
				MessageBox::Show("La liste est pleine, ne peut pas ajouter plus de pièces.");
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
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
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
			this->panel3->SuspendLayout();
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
			this->button1->Location = System::Drawing::Point(611, 14);
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
			this->label3->Location = System::Drawing::Point(329, 415);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(175, 46);
			this->label3->TabIndex = 14;
			this->label3->Text = L"Score: 0";
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel1->Controls->Add(this->button1);
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(811, 64);
			this->panel1->TabIndex = 15;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Game::panel1_Paint);
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
			this->pictureBox1->Tag = L"C:/Users/rajaa/source/repos/Project2/carre_rouge.png";
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
			this->button3->Location = System::Drawing::Point(755, 180);
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
			this->nextpanel->Size = System::Drawing::Size(109, 114);
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
			this->panel2->Controls->Add(this->pictureBox9);
			this->panel2->Controls->Add(this->pictureBox8);
			this->panel2->Controls->Add(this->pictureBox7);
			this->panel2->Controls->Add(this->pictureBox6);
			this->panel2->Controls->Add(this->pictureBox5);
			this->panel2->Controls->Add(this->pictureBox4);
			this->panel2->Controls->Add(this->pictureBox3);
			this->panel2->Controls->Add(this->pictureBox2);
			this->panel2->Location = System::Drawing::Point(52, 256);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(727, 105);
			this->panel2->TabIndex = 29;
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
			this->label2->Text = L"Faire un décalage par: ";
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
			this->panel3->Location = System::Drawing::Point(348, 97);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(475, 59);
			this->panel3->TabIndex = 33;
			// 
			// Game
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ClientSize = System::Drawing::Size(841, 499);
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
			this->panel1->ResumeLayout(false);
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
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	}

private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
//	pictureBox8->BackgroundImage = Image::FromFile("C:/Users/rajaa/source/repos/Project2/c_r.png");

	// Récupérer le chemin de l'image de pictureBox1
	String^ cheminImage = safe_cast<String^>(pictureBox1->Tag);

	// Vérifier si le chemin de l'image est valide
	if (!String::IsNullOrEmpty(cheminImage)) {
		String^ nomImage = Path::GetFileNameWithoutExtension(cheminImage); // Récupérer le nom de l'image sans l'extension
		array<String^>^ parties = nomImage->Split('_'); // Diviser le nom en fonction du caractère '_'

		String^ forme;
		String^ color;

		// Vérifier s'il y a au moins deux parties dans le nom de l'image
		if (parties->Length >= 2) {
			forme = parties[0]; // Stocker la première partie dans la variable forme
			color = parties[1]; // Stocker la deuxième partie dans la variable color

			// Afficher les valeurs des variables forme et color
		}
		else {
			// Gérer le cas où le nom de l'image n'a pas été divisé correctement
			MessageBox::Show("Le nom de l'image n'a pas été divisé correctement.");
		}

		// Affecter le chemin de l'image de pictureBox1 au pictureBox2
		//pictureBox8->BackgroundImage = Image::FromFile(cheminImage);
		AddPieceAtEnd(forme, color, cheminImage);
	}
	else {
		// Afficher un message d'erreur si le chemin de l'image est invalide ou non défini
		MessageBox::Show("Le chemin de l'image est invalide ou non défini.");
	}

}
private: System::Void panel2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
private: System::Void pictureBox8_Click(System::Object^  sender, System::EventArgs^  e) {
	
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	//	pictureBox8->BackgroundImage = Image::FromFile("C:/Users/rajaa/source/repos/Project2/c_r.png");

	// Récupérer le chemin de l'image de pictureBox1
	String^ cheminImage = safe_cast<String^>(pictureBox1->Tag);

	// Vérifier si le chemin de l'image est valide
	if (!String::IsNullOrEmpty(cheminImage)) {
		String^ nomImage = Path::GetFileNameWithoutExtension(cheminImage); // Récupérer le nom de l'image sans l'extension
		array<String^>^ parties = nomImage->Split('_'); // Diviser le nom en fonction du caractère '_'

		String^ forme;
		String^ color;

		// Vérifier s'il y a au moins deux parties dans le nom de l'image
		if (parties->Length >= 2) {
			forme = parties[0]; // Stocker la première partie dans la variable forme
			color = parties[1]; // Stocker la deuxième partie dans la variable color

			// Afficher les valeurs des variables forme et color
		}
		else {
			// Gérer le cas où le nom de l'image n'a pas été divisé correctement
			MessageBox::Show("Le nom de l'image n'a pas été divisé correctement.");
		}

		// Affecter le chemin de l'image de pictureBox1 au pictureBox2
		//pictureBox8->BackgroundImage = Image::FromFile(cheminImage);
		AddPieceAtBeginning(forme, color, cheminImage);
	}
	else {
		// Afficher un message d'erreur si le chemin de l'image est invalide ou non défini
		MessageBox::Show("Le chemin de l'image est invalide ou non défini.");
	}
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	// Afficher une boîte de dialogue pour demander à l'utilisateur s'il souhaite quitter le jeu
	System::Windows::Forms::DialogResult result = MessageBox::Show("Do you want to leave the game?", "Exit Game", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

	// Vérifier la réponse de l'utilisateur
	if (result == System::Windows::Forms::DialogResult::Yes) {
		// Masquer la fenêtre actuelle (la fenêtre de jeu)
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
	// Vérifier si l'utilisateur veut effectuer un décalage en fonction de la forme ou de la couleur
	if (radioButton1->Checked) {
		// Décalage en fonction de la forme
		DecalageForme(forme);
	}
	else if (radioButton2->Checked) {
		DecalageCouleur(color);
	}
	else {
		// Aucune option sélectionnée, afficher un message d'erreur
		MessageBox::Show("Veuillez sélectionner une option (forme ou couleur) pour effectuer un décalage.");
	}
}
};
}
