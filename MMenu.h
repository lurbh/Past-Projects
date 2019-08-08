#pragma once
#include "Login.h"
#include "CreateEvent.h"
#include "ModEvent.h"
#include "DelEvent.h"
#include "JoinEvent.h"
#include "ViewEvent.h"
#include "ViewAttendees.h"
#include "Account.h"
#include "ExitEvent.h"
#include "UserAttend.h"

namespace CSITGroupAssignment {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MMenu
	/// </summary>
	public ref class MMenu : public System::Windows::Forms::Form
	{
	public:
		String ^ id;
		String ^ name;

	private: OleDbConnection^ connection = gcnew OleDbConnection();
	private: System::Windows::Forms::Button^  Option2;
	private: System::Windows::Forms::Button^  Option1;
	private: System::Windows::Forms::Button^  Option3;
	private: System::Windows::Forms::Button^  Option4;
	private: System::Windows::Forms::Button^  Option5;
	private: System::Windows::Forms::Button^  Option7;
	private: System::Windows::Forms::Button^  Option6;
	private: System::Windows::Forms::Button^  Exit;
	private: System::Windows::Forms::Button^  LogOut;
	private: System::Windows::Forms::Label^  Ulabel;
	private: System::Windows::Forms::Label^  Nlabel;
	private: System::Windows::Forms::Button^  AccountBtn;
	private: System::Windows::Forms::Button^  Option8;


	public:
		MMenu(String ^ idtext, String ^ nametext)
		{
			id = idtext;
			name = nametext;
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
			this->Nlabel->Text = L" " + name + "(" + id + ")";
			
		}

		MMenu(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MMenu()
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
			this->Ulabel = (gcnew System::Windows::Forms::Label());
			this->Nlabel = (gcnew System::Windows::Forms::Label());
			this->Option1 = (gcnew System::Windows::Forms::Button());
			this->Option2 = (gcnew System::Windows::Forms::Button());
			this->Option3 = (gcnew System::Windows::Forms::Button());
			this->Option4 = (gcnew System::Windows::Forms::Button());
			this->Option5 = (gcnew System::Windows::Forms::Button());
			this->Option7 = (gcnew System::Windows::Forms::Button());
			this->Exit = (gcnew System::Windows::Forms::Button());
			this->LogOut = (gcnew System::Windows::Forms::Button());
			this->AccountBtn = (gcnew System::Windows::Forms::Button());
			this->Option6 = (gcnew System::Windows::Forms::Button());
			this->Option8 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Ulabel
			// 
			this->Ulabel->AutoSize = true;
			this->Ulabel->Location = System::Drawing::Point(24, 23);
			this->Ulabel->Name = L"Ulabel";
			this->Ulabel->Size = System::Drawing::Size(35, 13);
			this->Ulabel->TabIndex = 0;
			this->Ulabel->Text = L"User: ";
			// 
			// Nlabel
			// 
			this->Nlabel->AutoSize = true;
			this->Nlabel->Location = System::Drawing::Point(65, 23);
			this->Nlabel->Name = L"Nlabel";
			this->Nlabel->Size = System::Drawing::Size(35, 13);
			this->Nlabel->TabIndex = 0;
			// 
			// Option1
			// 
			this->Option1->Location = System::Drawing::Point(68, 67);
			this->Option1->Name = L"Option1";
			this->Option1->Size = System::Drawing::Size(126, 37);
			this->Option1->TabIndex = 1;
			this->Option1->Text = L"1. Create a Event";
			this->Option1->UseVisualStyleBackColor = true;
			this->Option1->Click += gcnew System::EventHandler(this, &MMenu::button2_Click);
			// 
			// Option2
			// 
			this->Option2->Location = System::Drawing::Point(68, 126);
			this->Option2->Name = L"Option2";
			this->Option2->Size = System::Drawing::Size(126, 37);
			this->Option2->TabIndex = 1;
			this->Option2->Text = L"2. Modify Event";
			this->Option2->UseVisualStyleBackColor = true;
			this->Option2->Click += gcnew System::EventHandler(this, &MMenu::button1_Click);
			// 
			// Option3
			// 
			this->Option3->Location = System::Drawing::Point(68, 189);
			this->Option3->Name = L"Option3";
			this->Option3->Size = System::Drawing::Size(126, 37);
			this->Option3->TabIndex = 1;
			this->Option3->Text = L"3. View Event";
			this->Option3->UseVisualStyleBackColor = true;
			this->Option3->Click += gcnew System::EventHandler(this, &MMenu::button3_Click);
			// 
			// Option4
			// 
			this->Option4->Location = System::Drawing::Point(68, 257);
			this->Option4->Name = L"Option4";
			this->Option4->Size = System::Drawing::Size(126, 37);
			this->Option4->TabIndex = 1;
			this->Option4->Text = L"4. Delete Event";
			this->Option4->UseVisualStyleBackColor = true;
			this->Option4->Click += gcnew System::EventHandler(this, &MMenu::button4_Click);
			// 
			// Option5
			// 
			this->Option5->Location = System::Drawing::Point(241, 67);
			this->Option5->Name = L"Option5";
			this->Option5->Size = System::Drawing::Size(126, 37);
			this->Option5->TabIndex = 1;
			this->Option5->Text = L"5. Join Event";
			this->Option5->UseVisualStyleBackColor = true;
			this->Option5->Click += gcnew System::EventHandler(this, &MMenu::button5_Click);
			// 
			// Option7
			// 
			this->Option7->Location = System::Drawing::Point(241, 189);
			this->Option7->Name = L"Option7";
			this->Option7->Size = System::Drawing::Size(126, 37);
			this->Option7->TabIndex = 1;
			this->Option7->Text = L"7. View Event Attendees";
			this->Option7->UseVisualStyleBackColor = true;
			this->Option7->Click += gcnew System::EventHandler(this, &MMenu::button7_Click);
			// 
			// Exit
			// 
			this->Exit->Location = System::Drawing::Point(331, 344);
			this->Exit->Name = L"Exit";
			this->Exit->Size = System::Drawing::Size(75, 23);
			this->Exit->TabIndex = 2;
			this->Exit->Text = L"Exit";
			this->Exit->UseVisualStyleBackColor = true;
			this->Exit->Click += gcnew System::EventHandler(this, &MMenu::button8_Click);
			// 
			// LogOut
			// 
			this->LogOut->Location = System::Drawing::Point(241, 344);
			this->LogOut->Name = L"LogOut";
			this->LogOut->Size = System::Drawing::Size(75, 23);
			this->LogOut->TabIndex = 2;
			this->LogOut->Text = L"Log Out";
			this->LogOut->UseVisualStyleBackColor = true;
			this->LogOut->Click += gcnew System::EventHandler(this, &MMenu::button9_Click);
			// 
			// AccountBtn
			// 
			this->AccountBtn->Location = System::Drawing::Point(68, 344);
			this->AccountBtn->Name = L"AccountBtn";
			this->AccountBtn->Size = System::Drawing::Size(75, 23);
			this->AccountBtn->TabIndex = 3;
			this->AccountBtn->Text = L"Account";
			this->AccountBtn->UseVisualStyleBackColor = true;
			this->AccountBtn->Click += gcnew System::EventHandler(this, &MMenu::Account_Click);
			// 
			// Option6
			// 
			this->Option6->Location = System::Drawing::Point(241, 126);
			this->Option6->Name = L"Option6";
			this->Option6->Size = System::Drawing::Size(126, 37);
			this->Option6->TabIndex = 1;
			this->Option6->Text = L"6. Quit Event";
			this->Option6->UseVisualStyleBackColor = true;
			this->Option6->Click += gcnew System::EventHandler(this, &MMenu::button6_Click);
			// 
			// Option8
			// 
			this->Option8->Location = System::Drawing::Point(241, 257);
			this->Option8->Name = L"Option8";
			this->Option8->Size = System::Drawing::Size(126, 37);
			this->Option8->TabIndex = 1;
			this->Option8->Text = L"8. View Events Joined";
			this->Option8->UseVisualStyleBackColor = true;
			this->Option8->Click += gcnew System::EventHandler(this, &MMenu::EventJoined_Click);
			// 
			// MMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(450, 392);
			this->Controls->Add(this->AccountBtn);
			this->Controls->Add(this->LogOut);
			this->Controls->Add(this->Exit);
			this->Controls->Add(this->Option6);
			this->Controls->Add(this->Option8);
			this->Controls->Add(this->Option7);
			this->Controls->Add(this->Option3);
			this->Controls->Add(this->Option5);
			this->Controls->Add(this->Option2);
			this->Controls->Add(this->Option4);
			this->Controls->Add(this->Option1);
			this->Controls->Add(this->Nlabel);
			this->Controls->Add(this->Ulabel);
			this->Name = L"MMenu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UOW Event Booking System";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MMenu::MMenu_FormClosed);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MMenu_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
	private: System::Void Account_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void EventJoined_Click(System::Object^  sender, System::EventArgs^  e);
};
}
