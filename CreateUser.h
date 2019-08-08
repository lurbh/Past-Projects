#pragma once

namespace CSITGroupAssignment {

	using namespace System;
	using namespace System::Globalization;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::OleDb;

	/// <summary>
	/// Summary for CreateUser
	/// </summary>
	public ref class CreateUser : public System::Windows::Forms::Form
	{
	private: OleDbConnection ^ connection = gcnew OleDbConnection();
	private: System::Windows::Forms::Label^  userid;
	private: System::Windows::Forms::Label^  username;
	private: System::Windows::Forms::Label^  password;
	private: System::Windows::Forms::TextBox^  IDInput;
	private: System::Windows::Forms::TextBox^  NameInput;
	private: System::Windows::Forms::TextBox^  PassInput;
	private: System::Windows::Forms::Button^  Back;
	private: System::Windows::Forms::Button^  CUser;

	public:
		CreateUser(void)
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
		~CreateUser()
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
			this->userid = (gcnew System::Windows::Forms::Label());
			this->username = (gcnew System::Windows::Forms::Label());
			this->password = (gcnew System::Windows::Forms::Label());
			this->IDInput = (gcnew System::Windows::Forms::TextBox());
			this->NameInput = (gcnew System::Windows::Forms::TextBox());
			this->PassInput = (gcnew System::Windows::Forms::TextBox());
			this->Back = (gcnew System::Windows::Forms::Button());
			this->CUser = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// userid
			// 
			this->userid->AutoSize = true;
			this->userid->Location = System::Drawing::Point(20, 25);
			this->userid->Name = L"userid";
			this->userid->Size = System::Drawing::Size(59, 17);
			this->userid->TabIndex = 0;
			this->userid->Text = L"User ID:";
			// 
			// username
			// 
			this->username->AutoSize = true;
			this->username->Location = System::Drawing::Point(20, 60);
			this->username->Name = L"username";
			this->username->Size = System::Drawing::Size(77, 17);
			this->username->TabIndex = 0;
			this->username->Text = L"Username:";
			// 
			// password
			// 
			this->password->AutoSize = true;
			this->password->Location = System::Drawing::Point(20, 95);
			this->password->Name = L"password";
			this->password->Size = System::Drawing::Size(69, 17);
			this->password->TabIndex = 0;
			this->password->Text = L"Password";
			// 
			// IDInput
			// 
			this->IDInput->Location = System::Drawing::Point(120, 25);
			this->IDInput->Name = L"IDInput";
			this->IDInput->Size = System::Drawing::Size(430, 22);
			this->IDInput->TabIndex = 1;
			// 
			// NameInput
			// 
			this->NameInput->Location = System::Drawing::Point(120, 60);
			this->NameInput->Name = L"NameInput";
			this->NameInput->Size = System::Drawing::Size(430, 22);
			this->NameInput->TabIndex = 1;
			// 
			// PassInput
			// 
			this->PassInput->Location = System::Drawing::Point(120, 95);
			this->PassInput->Name = L"PassInput";
			this->PassInput->Size = System::Drawing::Size(430, 22);
			this->PassInput->TabIndex = 1;
			// 
			// Back
			// 
			this->Back->Location = System::Drawing::Point(22, 143);
			this->Back->Name = L"Back";
			this->Back->Size = System::Drawing::Size(75, 23);
			this->Back->TabIndex = 2;
			this->Back->Text = L"Back";
			this->Back->UseVisualStyleBackColor = true;
			this->Back->Click += gcnew System::EventHandler(this, &CreateUser::Back_Click);
			// 
			// CUser
			// 
			this->CUser->Location = System::Drawing::Point(475, 143);
			this->CUser->Name = L"CUser";
			this->CUser->Size = System::Drawing::Size(75, 23);
			this->CUser->TabIndex = 2;
			this->CUser->Text = L"Create User";
			this->CUser->UseVisualStyleBackColor = true;
			this->CUser->Click += gcnew System::EventHandler(this, &CreateUser::CUser_Click);
			// 
			// CreateUser
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(581, 178);
			this->Controls->Add(this->CUser);
			this->Controls->Add(this->Back);
			this->Controls->Add(this->PassInput);
			this->Controls->Add(this->NameInput);
			this->Controls->Add(this->IDInput);
			this->Controls->Add(this->password);
			this->Controls->Add(this->username);
			this->Controls->Add(this->userid);
			this->Name = L"CreateUser";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CreateUser";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Back_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void CUser_Click(System::Object^  sender, System::EventArgs^  e);
};
}
