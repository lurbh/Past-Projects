#pragma once
#include "DateAndTime.h"

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
	/// Summary for CreateEvent
	/// </summary>
	public ref class CreateEvent : public System::Windows::Forms::Form
	{
	public:
		String ^ id;
	private: OleDbConnection^ connection = gcnew OleDbConnection();
	private: System::Windows::Forms::Label^  EName;
	private: System::Windows::Forms::Label^  EVenue;
	private: System::Windows::Forms::Label^  EPrice;
	private: System::Windows::Forms::Label^  ECapacity;
	private: System::Windows::Forms::Label^  ESessionsNo;
	private: System::Windows::Forms::TextBox^  NameInput;
	private: System::Windows::Forms::TextBox^  VenueInput;
	private: System::Windows::Forms::TextBox^  PriceInput;
	private: System::Windows::Forms::TextBox^  CapcityInput;
	private: System::Windows::Forms::ComboBox^  SessionsInput;
	private: System::Windows::Forms::Button^  EnterDate;
	private: System::Windows::Forms::Label^  DT1;
	private: System::Windows::Forms::Label^  DT2;
	private: System::Windows::Forms::Label^  DT3;
	private: System::Windows::Forms::Label^  DT4;
	private: System::Windows::Forms::Label^  DT5;
	private: System::Windows::Forms::Label^  DT6;
	private: System::Windows::Forms::Label^  DT7;
	private: System::Windows::Forms::Label^  DT8;
	private: System::Windows::Forms::Label^  DT9;
	private: System::Windows::Forms::Label^  DT10;
	private: System::Windows::Forms::Button^  CreateEventBtn;
	private: System::Windows::Forms::Button^  MMenuBtn;


	public:
		CreateEvent(String ^ userid)
		{
			id = userid;
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
		}

		CreateEvent(void)
		{
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CreateEvent()
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
			this->EName = (gcnew System::Windows::Forms::Label());
			this->EVenue = (gcnew System::Windows::Forms::Label());
			this->EPrice = (gcnew System::Windows::Forms::Label());
			this->ECapacity = (gcnew System::Windows::Forms::Label());
			this->ESessionsNo = (gcnew System::Windows::Forms::Label());
			this->NameInput = (gcnew System::Windows::Forms::TextBox());
			this->VenueInput = (gcnew System::Windows::Forms::TextBox());
			this->PriceInput = (gcnew System::Windows::Forms::TextBox());
			this->CapcityInput = (gcnew System::Windows::Forms::TextBox());
			this->SessionsInput = (gcnew System::Windows::Forms::ComboBox());
			this->EnterDate = (gcnew System::Windows::Forms::Button());
			this->DT1 = (gcnew System::Windows::Forms::Label());
			this->DT2 = (gcnew System::Windows::Forms::Label());
			this->DT3 = (gcnew System::Windows::Forms::Label());
			this->DT4 = (gcnew System::Windows::Forms::Label());
			this->DT5 = (gcnew System::Windows::Forms::Label());
			this->DT6 = (gcnew System::Windows::Forms::Label());
			this->DT7 = (gcnew System::Windows::Forms::Label());
			this->DT8 = (gcnew System::Windows::Forms::Label());
			this->DT9 = (gcnew System::Windows::Forms::Label());
			this->DT10 = (gcnew System::Windows::Forms::Label());
			this->CreateEventBtn = (gcnew System::Windows::Forms::Button());
			this->MMenuBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// EName
			// 
			this->EName->AutoSize = true;
			this->EName->Location = System::Drawing::Point(20, 20);
			this->EName->Name = L"EName";
			this->EName->Size = System::Drawing::Size(72, 13);
			this->EName->TabIndex = 0;
			this->EName->Text = L"Event Name :";
			// 
			// EVenue
			// 
			this->EVenue->AutoSize = true;
			this->EVenue->Location = System::Drawing::Point(20, 50);
			this->EVenue->Name = L"EVenue";
			this->EVenue->Size = System::Drawing::Size(75, 13);
			this->EVenue->TabIndex = 0;
			this->EVenue->Text = L"Event Venue :";
			// 
			// EPrice
			// 
			this->EPrice->AutoSize = true;
			this->EPrice->Location = System::Drawing::Point(20, 80);
			this->EPrice->Name = L"EPrice";
			this->EPrice->Size = System::Drawing::Size(68, 13);
			this->EPrice->TabIndex = 0;
			this->EPrice->Text = L"Event Price :";
			// 
			// ECapacity
			// 
			this->ECapacity->AutoSize = true;
			this->ECapacity->Location = System::Drawing::Point(20, 110);
			this->ECapacity->Name = L"ECapacity";
			this->ECapacity->Size = System::Drawing::Size(85, 13);
			this->ECapacity->TabIndex = 0;
			this->ECapacity->Text = L"Event Capacity :";
			// 
			// ESessionsNo
			// 
			this->ESessionsNo->AutoSize = true;
			this->ESessionsNo->Location = System::Drawing::Point(20, 140);
			this->ESessionsNo->Name = L"ESessionsNo";
			this->ESessionsNo->Size = System::Drawing::Size(84, 13);
			this->ESessionsNo->TabIndex = 0;
			this->ESessionsNo->Text = L"No of Sessions :";
			// 
			// NameInput
			// 
			this->NameInput->Location = System::Drawing::Point(135, 20);
			this->NameInput->Name = L"NameInput";
			this->NameInput->Size = System::Drawing::Size(275, 20);
			this->NameInput->TabIndex = 1;
			// 
			// VenueInput
			// 
			this->VenueInput->Location = System::Drawing::Point(135, 50);
			this->VenueInput->Name = L"VenueInput";
			this->VenueInput->Size = System::Drawing::Size(275, 20);
			this->VenueInput->TabIndex = 1;
			// 
			// PriceInput
			// 
			this->PriceInput->Location = System::Drawing::Point(135, 80);
			this->PriceInput->Name = L"PriceInput";
			this->PriceInput->Size = System::Drawing::Size(275, 20);
			this->PriceInput->TabIndex = 1;
			// 
			// CapcityInput
			// 
			this->CapcityInput->Location = System::Drawing::Point(135, 110);
			this->CapcityInput->Name = L"CapcityInput";
			this->CapcityInput->Size = System::Drawing::Size(275, 20);
			this->CapcityInput->TabIndex = 1;
			// 
			// SessionsInput
			// 
			this->SessionsInput->FormattingEnabled = true;
			this->SessionsInput->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8",
					L"9", L"10"
			});
			this->SessionsInput->Location = System::Drawing::Point(135, 140);
			this->SessionsInput->Name = L"SessionsInput";
			this->SessionsInput->Size = System::Drawing::Size(125, 21);
			this->SessionsInput->TabIndex = 2;
			// 
			// EnterDate
			// 
			this->EnterDate->Location = System::Drawing::Point(293, 137);
			this->EnterDate->Name = L"EnterDate";
			this->EnterDate->Size = System::Drawing::Size(75, 23);
			this->EnterDate->TabIndex = 3;
			this->EnterDate->Text = L"Enter Dates";
			this->EnterDate->UseVisualStyleBackColor = true;
			this->EnterDate->Click += gcnew System::EventHandler(this, &CreateEvent::EnterDate_Click);
			// 
			// DT1
			// 
			this->DT1->AutoSize = true;
			this->DT1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT1->Location = System::Drawing::Point(20, 170);
			this->DT1->Name = L"DT1";
			this->DT1->Size = System::Drawing::Size(0, 13);
			this->DT1->TabIndex = 4;
			this->DT1->Click += gcnew System::EventHandler(this, &CreateEvent::DT1_Click);
			// 
			// DT2
			// 
			this->DT2->AutoSize = true;
			this->DT2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT2->Location = System::Drawing::Point(20, 200);
			this->DT2->Name = L"DT2";
			this->DT2->Size = System::Drawing::Size(0, 13);
			this->DT2->TabIndex = 4;
			this->DT2->Click += gcnew System::EventHandler(this, &CreateEvent::DT2_Click);
			// 
			// DT3
			// 
			this->DT3->AutoSize = true;
			this->DT3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT3->Location = System::Drawing::Point(20, 230);
			this->DT3->Name = L"DT3";
			this->DT3->Size = System::Drawing::Size(0, 13);
			this->DT3->TabIndex = 4;
			this->DT3->Click += gcnew System::EventHandler(this, &CreateEvent::DT3_Click);
			// 
			// DT4
			// 
			this->DT4->AutoSize = true;
			this->DT4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT4->Location = System::Drawing::Point(20, 260);
			this->DT4->Name = L"DT4";
			this->DT4->Size = System::Drawing::Size(0, 13);
			this->DT4->TabIndex = 4;
			this->DT4->Click += gcnew System::EventHandler(this, &CreateEvent::DT4_Click);
			// 
			// DT5
			// 
			this->DT5->AutoSize = true;
			this->DT5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT5->Location = System::Drawing::Point(20, 290);
			this->DT5->Name = L"DT5";
			this->DT5->Size = System::Drawing::Size(0, 13);
			this->DT5->TabIndex = 4;
			this->DT5->Click += gcnew System::EventHandler(this, &CreateEvent::DT5_Click);
			// 
			// DT6
			// 
			this->DT6->AutoSize = true;
			this->DT6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT6->Location = System::Drawing::Point(20, 320);
			this->DT6->Name = L"DT6";
			this->DT6->Size = System::Drawing::Size(0, 13);
			this->DT6->TabIndex = 4;
			this->DT6->Click += gcnew System::EventHandler(this, &CreateEvent::DT6_Click);
			// 
			// DT7
			// 
			this->DT7->AutoSize = true;
			this->DT7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT7->Location = System::Drawing::Point(20, 350);
			this->DT7->Name = L"DT7";
			this->DT7->Size = System::Drawing::Size(0, 13);
			this->DT7->TabIndex = 4;
			this->DT7->Click += gcnew System::EventHandler(this, &CreateEvent::DT7_Click);
			// 
			// DT8
			// 
			this->DT8->AutoSize = true;
			this->DT8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT8->Location = System::Drawing::Point(20, 380);
			this->DT8->Name = L"DT8";
			this->DT8->Size = System::Drawing::Size(0, 13);
			this->DT8->TabIndex = 4;
			this->DT8->Click += gcnew System::EventHandler(this, &CreateEvent::DT8_Click);
			// 
			// DT9
			// 
			this->DT9->AutoSize = true;
			this->DT9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT9->Location = System::Drawing::Point(20, 410);
			this->DT9->Name = L"DT9";
			this->DT9->Size = System::Drawing::Size(0, 13);
			this->DT9->TabIndex = 4;
			this->DT9->Click += gcnew System::EventHandler(this, &CreateEvent::DT9_Click);
			// 
			// DT10
			// 
			this->DT10->AutoSize = true;
			this->DT10->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT10->Location = System::Drawing::Point(20, 440);
			this->DT10->Name = L"DT10";
			this->DT10->Size = System::Drawing::Size(0, 13);
			this->DT10->TabIndex = 4;
			this->DT10->Click += gcnew System::EventHandler(this, &CreateEvent::DT10_Click);
			// 
			// CreateEventBtn
			// 
			this->CreateEventBtn->Location = System::Drawing::Point(317, 465);
			this->CreateEventBtn->Name = L"CreateEventBtn";
			this->CreateEventBtn->Size = System::Drawing::Size(93, 23);
			this->CreateEventBtn->TabIndex = 5;
			this->CreateEventBtn->Text = L"Create Event";
			this->CreateEventBtn->UseVisualStyleBackColor = true;
			this->CreateEventBtn->Click += gcnew System::EventHandler(this, &CreateEvent::CreateEventBtn_Click);
			// 
			// MMenuBtn
			// 
			this->MMenuBtn->Location = System::Drawing::Point(23, 465);
			this->MMenuBtn->Name = L"MMenuBtn";
			this->MMenuBtn->Size = System::Drawing::Size(75, 23);
			this->MMenuBtn->TabIndex = 6;
			this->MMenuBtn->Text = L"Main Menu";
			this->MMenuBtn->UseVisualStyleBackColor = true;
			this->MMenuBtn->Click += gcnew System::EventHandler(this, &CreateEvent::MMenu_Click);
			// 
			// CreateEvent
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(444, 500);
			this->Controls->Add(this->MMenuBtn);
			this->Controls->Add(this->CreateEventBtn);
			this->Controls->Add(this->DT10);
			this->Controls->Add(this->DT9);
			this->Controls->Add(this->DT8);
			this->Controls->Add(this->DT7);
			this->Controls->Add(this->DT6);
			this->Controls->Add(this->DT5);
			this->Controls->Add(this->DT4);
			this->Controls->Add(this->DT3);
			this->Controls->Add(this->DT2);
			this->Controls->Add(this->DT1);
			this->Controls->Add(this->EnterDate);
			this->Controls->Add(this->SessionsInput);
			this->Controls->Add(this->CapcityInput);
			this->Controls->Add(this->PriceInput);
			this->Controls->Add(this->VenueInput);
			this->Controls->Add(this->NameInput);
			this->Controls->Add(this->ESessionsNo);
			this->Controls->Add(this->ECapacity);
			this->Controls->Add(this->EPrice);
			this->Controls->Add(this->EVenue);
			this->Controls->Add(this->EName);
			this->Name = L"CreateEvent";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Create Event";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void EnterDate_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DT1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DT2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DT3_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DT4_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DT5_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DT6_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DT7_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DT8_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DT9_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DT10_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void CreateEventBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MMenu_Click(System::Object^  sender, System::EventArgs^  e);
};
}
