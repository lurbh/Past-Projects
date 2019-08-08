#pragma once
#include "MMenu.h"
#include "CreateUser.h"

namespace CSITGroupAssignment {

	using namespace System;
	using namespace System::Globalization;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Login
	/// </summary>
	public ref class Login : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Label^  IDLabel;
	private: System::Windows::Forms::Label^  NameLabel;
	private: System::Windows::Forms::TextBox^  IDInput;
	private: System::Windows::Forms::TextBox^  PassInput;
	private: System::Windows::Forms::Button^  Loginbutton;
	private: System::Windows::Forms::Button^  ExitButton;
	private: System::Windows::Forms::Button^  CUser;
	private: OleDbConnection ^ connection = gcnew OleDbConnection();

	public:
		Login(void)
		{
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Login()
		{
			if (components)
			{
				delete components;
			}
		}

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
			this->IDLabel = (gcnew System::Windows::Forms::Label());
			this->NameLabel = (gcnew System::Windows::Forms::Label());
			this->IDInput = (gcnew System::Windows::Forms::TextBox());
			this->PassInput = (gcnew System::Windows::Forms::TextBox());
			this->Loginbutton = (gcnew System::Windows::Forms::Button());
			this->ExitButton = (gcnew System::Windows::Forms::Button());
			this->CUser = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// IDLabel
			// 
			this->IDLabel->AutoSize = true;
			this->IDLabel->Location = System::Drawing::Point(29, 31);
			this->IDLabel->Name = L"IDLabel";
			this->IDLabel->Size = System::Drawing::Size(63, 17);
			this->IDLabel->TabIndex = 0;
			this->IDLabel->Text = L"User ID: ";
			// 
			// NameLabel
			// 
			this->NameLabel->AutoSize = true;
			this->NameLabel->Location = System::Drawing::Point(29, 63);
			this->NameLabel->Name = L"NameLabel";
			this->NameLabel->Size = System::Drawing::Size(77, 17);
			this->NameLabel->TabIndex = 0;
			this->NameLabel->Text = L"Password :";
			// 
			// IDInput
			// 
			this->IDInput->Location = System::Drawing::Point(117, 31);
			this->IDInput->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->IDInput->Name = L"IDInput";
			this->IDInput->Size = System::Drawing::Size(376, 22);
			this->IDInput->TabIndex = 1;
			// 
			// PassInput
			// 
			this->PassInput->Location = System::Drawing::Point(117, 63);
			this->PassInput->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->PassInput->Name = L"PassInput";
			this->PassInput->Size = System::Drawing::Size(376, 22);
			this->PassInput->TabIndex = 1;
			this->PassInput->UseSystemPasswordChar = true;
			// 
			// Loginbutton
			// 
			this->Loginbutton->Location = System::Drawing::Point(420, 110);
			this->Loginbutton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Loginbutton->Name = L"Loginbutton";
			this->Loginbutton->Size = System::Drawing::Size(75, 23);
			this->Loginbutton->TabIndex = 2;
			this->Loginbutton->Text = L"Login";
			this->Loginbutton->UseVisualStyleBackColor = true;
			this->Loginbutton->Click += gcnew System::EventHandler(this, &Login::button1_Click);
			// 
			// ExitButton
			// 
			this->ExitButton->Location = System::Drawing::Point(19, 110);
			this->ExitButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->ExitButton->Name = L"ExitButton";
			this->ExitButton->Size = System::Drawing::Size(75, 23);
			this->ExitButton->TabIndex = 2;
			this->ExitButton->Text = L"Exit";
			this->ExitButton->UseVisualStyleBackColor = true;
			this->ExitButton->Click += gcnew System::EventHandler(this, &Login::button2_Click);
			// 
			// CUser
			// 
			this->CUser->Location = System::Drawing::Point(310, 110);
			this->CUser->Name = L"CUser";
			this->CUser->Size = System::Drawing::Size(104, 23);
			this->CUser->TabIndex = 3;
			this->CUser->Text = L"Create User";
			this->CUser->UseVisualStyleBackColor = true;
			this->CUser->Click += gcnew System::EventHandler(this, &Login::CUser_Click);
			// 
			// Login
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(531, 142);
			this->Controls->Add(this->CUser);
			this->Controls->Add(this->ExitButton);
			this->Controls->Add(this->Loginbutton);
			this->Controls->Add(this->PassInput);
			this->Controls->Add(this->IDInput);
			this->Controls->Add(this->NameLabel);
			this->Controls->Add(this->IDLabel);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"Login";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UOW Event Booking System Login";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Login::Login_FormClosed);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Login_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
	private: System::Void CUser_Click(System::Object^  sender, System::EventArgs^  e);
};
}
