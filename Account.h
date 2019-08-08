#pragma once

#include "UpdateUser.h"
#include "UserHistory.h"
#include "MMenu.h"

namespace CSITGroupAssignment {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::OleDb;
	using namespace System::Globalization;

	/// <summary>
	/// Summary for Account
	/// </summary>
	public ref class Account : public System::Windows::Forms::Form
	{
		String ^ id;
		String ^ name;
		bool change;

	private: System::Windows::Forms::Button^  ExitBtn;
	private: System::Windows::Forms::Button^  Update;
	private: System::Windows::Forms::Button^  History;
	private: OleDbConnection ^ connection = gcnew OleDbConnection();

	public:
		Account(void)
		{
			InitializeComponent();
		}

		Account(String ^ idtext, String ^ nametext)
		{
			id = idtext;
			name = nametext;
			change = false;
			InitializeComponent();
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
		}
		

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Account()
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
			this->ExitBtn = (gcnew System::Windows::Forms::Button());
			this->Update = (gcnew System::Windows::Forms::Button());
			this->History = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// ExitBtn
			// 
			this->ExitBtn->Location = System::Drawing::Point(16, 28);
			this->ExitBtn->Margin = System::Windows::Forms::Padding(4);
			this->ExitBtn->Name = L"ExitBtn";
			this->ExitBtn->Size = System::Drawing::Size(127, 31);
			this->ExitBtn->TabIndex = 0;
			this->ExitBtn->Text = L"Exit";
			this->ExitBtn->UseVisualStyleBackColor = true;
			this->ExitBtn->Click += gcnew System::EventHandler(this, &Account::ExitBtn_Click);
			// 
			// Update
			// 
			this->Update->Location = System::Drawing::Point(168, 28);
			this->Update->Margin = System::Windows::Forms::Padding(4);
			this->Update->Name = L"Update";
			this->Update->Size = System::Drawing::Size(127, 31);
			this->Update->TabIndex = 0;
			this->Update->Text = L"Update Account";
			this->Update->UseVisualStyleBackColor = true;
			this->Update->Click += gcnew System::EventHandler(this, &Account::Update_Click);
			// 
			// History
			// 
			this->History->Location = System::Drawing::Point(317, 28);
			this->History->Margin = System::Windows::Forms::Padding(4);
			this->History->Name = L"History";
			this->History->Size = System::Drawing::Size(127, 31);
			this->History->TabIndex = 0;
			this->History->Text = L"History";
			this->History->UseVisualStyleBackColor = true;
			this->History->Click += gcnew System::EventHandler(this, &Account::History_Click);
			// 
			// Account
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(460, 80);
			this->Controls->Add(this->History);
			this->Controls->Add(this->Update);
			this->Controls->Add(this->ExitBtn);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"Account";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Account";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Account::Account_FormClosed);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void ExitBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Update_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void History_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Account_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);

};
}
