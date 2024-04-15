#pragma once
#include "User.h"
#include <msclr\marshal_cppstd.h> // Inclure marshal_cppstd.h pour la conversion de System::String^ en std::string

namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;
	/// <summary>
	/// Summary for Signeup
	/// </summary>
	public ref class Signeup : public System::Windows::Forms::Form
	{
	public:
		Signeup(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Signeup()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox5;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Signeup::typeid));
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Poor Richard", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::Navy;
			this->label4->Location = System::Drawing::Point(377, 9);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(31, 47);
			this->label4->TabIndex = 28;
			this->label4->Text = L"I";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->BackColor = System::Drawing::Color::Transparent;
			this->label10->Font = (gcnew System::Drawing::Font(L"Poor Richard", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::Purple;
			this->label10->Location = System::Drawing::Point(414, 9);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(39, 47);
			this->label10->TabIndex = 27;
			this->label10->Text = L"S";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::Transparent;
			this->label11->Font = (gcnew System::Drawing::Font(L"Poor Richard", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->ForeColor = System::Drawing::Color::Green;
			this->label11->Location = System::Drawing::Point(327, 9);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(44, 47);
			this->label11->TabIndex = 26;
			this->label11->Text = L"R";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->BackColor = System::Drawing::Color::Transparent;
			this->label12->Font = (gcnew System::Drawing::Font(L"Poor Richard", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(273, 9);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(39, 47);
			this->label12->TabIndex = 25;
			this->label12->Text = L"T";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->BackColor = System::Drawing::Color::Transparent;
			this->label13->Font = (gcnew System::Drawing::Font(L"Poor Richard", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(165, 9);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(39, 47);
			this->label13->TabIndex = 24;
			this->label13->Text = L"T";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->BackColor = System::Drawing::Color::Transparent;
			this->label14->Font = (gcnew System::Drawing::Font(L"Poor Richard", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(223, 9);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(41, 47);
			this->label14->TabIndex = 23;
			this->label14->Text = L"E";
			// 
			// panel1
			// 
			this->panel1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->panel1->BackColor = System::Drawing::Color::Transparent;
			this->panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->textBox5);
			this->panel1->Controls->Add(this->label16);
			this->panel1->Controls->Add(this->label15);
			this->panel1->Controls->Add(this->textBox4);
			this->panel1->Controls->Add(this->textBox3);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->textBox2);
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->ForeColor = System::Drawing::Color::Black;
			this->panel1->Location = System::Drawing::Point(94, 59);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(449, 431);
			this->panel1->TabIndex = 22;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Signeup::panel1_Paint);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label16->Font = (gcnew System::Drawing::Font(L"MV Boli", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->ForeColor = System::Drawing::Color::White;
			this->label16->Location = System::Drawing::Point(55, 21);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(124, 27);
			this->label16->TabIndex = 38;
			this->label16->Text = L"First Name";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"MV Boli", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->ForeColor = System::Drawing::Color::White;
			this->label15->Location = System::Drawing::Point(228, 23);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(117, 25);
			this->label15->TabIndex = 37;
			this->label15->Text = L"Last Name";
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::Color::White;
			this->textBox4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox4->Font = (gcnew System::Drawing::Font(L"MV Boli", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox4->ForeColor = System::Drawing::Color::Black;
			this->textBox4->Location = System::Drawing::Point(233, 65);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(172, 34);
			this->textBox4->TabIndex = 36;
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::White;
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"MV Boli", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->ForeColor = System::Drawing::Color::Black;
			this->textBox3->Location = System::Drawing::Point(55, 65);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(172, 34);
			this->textBox3->TabIndex = 35;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"MV Boli", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(59, 296);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(100, 25);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Password";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"MV Boli", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(59, 115);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(103, 25);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Username";
			// 
			// button2
			// 
			this->button2->FlatAppearance->BorderSize = 2;
			this->button2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->button2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"MV Boli", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->Location = System::Drawing::Point(120, 382);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(206, 46);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Signe up";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Signeup::button2_Click);
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::White;
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"MV Boli", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->ForeColor = System::Drawing::Color::Black;
			this->textBox2->Location = System::Drawing::Point(55, 337);
			this->textBox2->Name = L"textBox2";
			this->textBox2->PasswordChar = '*';
			this->textBox2->Size = System::Drawing::Size(349, 34);
			this->textBox2->TabIndex = 1;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::White;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"MV Boli", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->ForeColor = System::Drawing::Color::Black;
			this->textBox1->Location = System::Drawing::Point(55, 155);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(349, 34);
			this->textBox1->TabIndex = 0;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"MV Boli", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(59, 210);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(63, 25);
			this->label3->TabIndex = 40;
			this->label3->Text = L"Email";
			// 
			// textBox5
			// 
			this->textBox5->BackColor = System::Drawing::Color::White;
			this->textBox5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox5->Font = (gcnew System::Drawing::Font(L"MV Boli", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox5->ForeColor = System::Drawing::Color::Black;
			this->textBox5->Location = System::Drawing::Point(55, 250);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(349, 34);
			this->textBox5->TabIndex = 39;
			// 
			// Signeup
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(624, 524);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"Signeup";
			this->Text = L"Signeup";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	// Créer une brosse semi-transparente de couleur bleue
	Color semiTransparentColor = Color::FromArgb(180, 0, 0, 0);
	SolidBrush^ brush = gcnew SolidBrush(semiTransparentColor);

	// Récupérer les dimensions du panneau
	int width = panel1->Width;
	int height = panel1->Height;

	// Dessiner un rectangle semi-transparent à l'intérieur du panneau
	e->Graphics->FillRectangle(brush, System::Drawing::Rectangle(0, 0, width, height));
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	// Collecte des données des textbox
	System::String^ username = textBox1->Text;
	System::String^ firstName = textBox3->Text;
	System::String^ lastName = textBox4->Text;
	System::String^ email = textBox5->Text;
	System::String^ password = textBox2->Text;

	// Appel de la méthode InsertUser pour insérer un nouvel utilisateur
	bool insertionSuccessful = User::InsertUser(username, firstName, lastName, email, password);

	// Vérifier si l'insertion a été réussie
	if (insertionSuccessful) {
		// Afficher un message ou effectuer d'autres actions si l'insertion est réussie
		MessageBox::Show("Utilisateur inséré avec succès.", "Succès", MessageBoxButtons::OK, MessageBoxIcon::Information);
		textBox1->Text = "";
		textBox2->Text = "";
		textBox3->Text = "";
		textBox4->Text = "";
		textBox5->Text = "";
	}
	else {
		// Afficher un message d'erreur si l'insertion a échoué
		MessageBox::Show("Erreur lors de l'insertion de l'utilisateur.", "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}




};
}
