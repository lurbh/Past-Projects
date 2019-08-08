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
	/// Summary for ModEvent
	/// </summary>
	public ref class ModEvent : public System::Windows::Forms::Form
	{
		String ^ id;
		String ^ EventName;
		void UpdateList();

	private: OleDbConnection^ connection = gcnew OleDbConnection();
	private: System::Windows::Forms::Label^  EName;
	private: System::Windows::Forms::ComboBox^  EventList;
	private: System::Windows::Forms::Button^  SEvent;
	private: System::Windows::Forms::Label^  EName2;
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
	private: System::Windows::Forms::Label^  DT10;
	private: System::Windows::Forms::Label^  DT9;
	private: System::Windows::Forms::Label^  DT8;
	private: System::Windows::Forms::Label^  DT7;
	private: System::Windows::Forms::Label^  DT6;
	private: System::Windows::Forms::Label^  DT5;
	private: System::Windows::Forms::Label^  DT4;
	private: System::Windows::Forms::Label^  DT3;
	private: System::Windows::Forms::Label^  DT2;
	private: System::Windows::Forms::Label^  DT1;
	private: System::Windows::Forms::Button^  MMenuBtn;

	private: System::Windows::Forms::Button^  SaveChanges;

	public:
		ModEvent(String ^ userid)
		{
			id = userid;
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
			UpdateList();
			this->Location = System::Drawing::Point((Screen::PrimaryScreen->Bounds.Width - this->Size.Width) / 2 + (this->Size.Width / 4), 250);
		}

		ModEvent(void)
		{
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
			UpdateList();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ModEvent()
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
			this->EventList = (gcnew System::Windows::Forms::ComboBox());
			this->SEvent = (gcnew System::Windows::Forms::Button());
			this->EName2 = (gcnew System::Windows::Forms::Label());
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
			this->DT10 = (gcnew System::Windows::Forms::Label());
			this->DT9 = (gcnew System::Windows::Forms::Label());
			this->DT8 = (gcnew System::Windows::Forms::Label());
			this->DT7 = (gcnew System::Windows::Forms::Label());
			this->DT6 = (gcnew System::Windows::Forms::Label());
			this->DT5 = (gcnew System::Windows::Forms::Label());
			this->DT4 = (gcnew System::Windows::Forms::Label());
			this->DT3 = (gcnew System::Windows::Forms::Label());
			this->DT2 = (gcnew System::Windows::Forms::Label());
			this->DT1 = (gcnew System::Windows::Forms::Label());
			this->MMenuBtn = (gcnew System::Windows::Forms::Button());
			this->SaveChanges = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// EName
			// 
			this->EName->AutoSize = true;
			this->EName->Location = System::Drawing::Point(33, 37);
			this->EName->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->EName->Name = L"EName";
			this->EName->Size = System::Drawing::Size(137, 13);
			this->EName->TabIndex = 0;
			this->EName->Text = L"Select the Event to modify: ";
			// 
			// EventList
			// 
			this->EventList->FormattingEnabled = true;
			this->EventList->Location = System::Drawing::Point(227, 37);
			this->EventList->Margin = System::Windows::Forms::Padding(4);
			this->EventList->Name = L"EventList";
			this->EventList->Size = System::Drawing::Size(281, 21);
			this->EventList->TabIndex = 1;
			// 
			// SEvent
			// 
			this->SEvent->Location = System::Drawing::Point(400, 74);
			this->SEvent->Margin = System::Windows::Forms::Padding(4);
			this->SEvent->Name = L"SEvent";
			this->SEvent->Size = System::Drawing::Size(111, 28);
			this->SEvent->TabIndex = 2;
			this->SEvent->Text = L"Select Event";
			this->SEvent->UseVisualStyleBackColor = true;
			this->SEvent->Click += gcnew System::EventHandler(this, &ModEvent::SEvent_Click);
			// 
			// EName2
			// 
			this->EName2->AutoSize = true;
			this->EName2->Location = System::Drawing::Point(33, 118);
			this->EName2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->EName2->Name = L"EName2";
			this->EName2->Size = System::Drawing::Size(72, 13);
			this->EName2->TabIndex = 9;
			this->EName2->Text = L"Event Name :";
			this->EName2->Visible = false;
			// 
			// EVenue
			// 
			this->EVenue->AutoSize = true;
			this->EVenue->Location = System::Drawing::Point(33, 155);
			this->EVenue->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->EVenue->Name = L"EVenue";
			this->EVenue->Size = System::Drawing::Size(75, 13);
			this->EVenue->TabIndex = 8;
			this->EVenue->Text = L"Event Venue :";
			this->EVenue->Visible = false;
			// 
			// EPrice
			// 
			this->EPrice->AutoSize = true;
			this->EPrice->Location = System::Drawing::Point(33, 192);
			this->EPrice->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->EPrice->Name = L"EPrice";
			this->EPrice->Size = System::Drawing::Size(68, 13);
			this->EPrice->TabIndex = 7;
			this->EPrice->Text = L"Event Price :";
			this->EPrice->Visible = false;
			// 
			// ECapacity
			// 
			this->ECapacity->AutoSize = true;
			this->ECapacity->Location = System::Drawing::Point(33, 229);
			this->ECapacity->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->ECapacity->Name = L"ECapacity";
			this->ECapacity->Size = System::Drawing::Size(85, 13);
			this->ECapacity->TabIndex = 6;
			this->ECapacity->Text = L"Event Capacity :";
			this->ECapacity->Visible = false;
			// 
			// ESessionsNo
			// 
			this->ESessionsNo->AutoSize = true;
			this->ESessionsNo->Location = System::Drawing::Point(33, 266);
			this->ESessionsNo->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->ESessionsNo->Name = L"ESessionsNo";
			this->ESessionsNo->Size = System::Drawing::Size(84, 13);
			this->ESessionsNo->TabIndex = 5;
			this->ESessionsNo->Text = L"No of Sessions :";
			this->ESessionsNo->Visible = false;
			// 
			// NameInput
			// 
			this->NameInput->Location = System::Drawing::Point(187, 118);
			this->NameInput->Margin = System::Windows::Forms::Padding(4);
			this->NameInput->Name = L"NameInput";
			this->NameInput->Size = System::Drawing::Size(365, 20);
			this->NameInput->TabIndex = 13;
			this->NameInput->Visible = false;
			// 
			// VenueInput
			// 
			this->VenueInput->Location = System::Drawing::Point(187, 155);
			this->VenueInput->Margin = System::Windows::Forms::Padding(4);
			this->VenueInput->Name = L"VenueInput";
			this->VenueInput->Size = System::Drawing::Size(365, 20);
			this->VenueInput->TabIndex = 12;
			this->VenueInput->Visible = false;
			// 
			// PriceInput
			// 
			this->PriceInput->Location = System::Drawing::Point(187, 192);
			this->PriceInput->Margin = System::Windows::Forms::Padding(4);
			this->PriceInput->Name = L"PriceInput";
			this->PriceInput->Size = System::Drawing::Size(365, 20);
			this->PriceInput->TabIndex = 11;
			this->PriceInput->Visible = false;
			// 
			// CapcityInput
			// 
			this->CapcityInput->Location = System::Drawing::Point(187, 229);
			this->CapcityInput->Margin = System::Windows::Forms::Padding(4);
			this->CapcityInput->Name = L"CapcityInput";
			this->CapcityInput->Size = System::Drawing::Size(365, 20);
			this->CapcityInput->TabIndex = 10;
			this->CapcityInput->Visible = false;
			// 
			// SessionsInput
			// 
			this->SessionsInput->FormattingEnabled = true;
			this->SessionsInput->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8",
					L"9", L"10"
			});
			this->SessionsInput->Location = System::Drawing::Point(187, 266);
			this->SessionsInput->Margin = System::Windows::Forms::Padding(4);
			this->SessionsInput->Name = L"SessionsInput";
			this->SessionsInput->Size = System::Drawing::Size(165, 21);
			this->SessionsInput->TabIndex = 14;
			this->SessionsInput->Visible = false;
			// 
			// EnterDate
			// 
			this->EnterDate->Location = System::Drawing::Point(397, 262);
			this->EnterDate->Margin = System::Windows::Forms::Padding(4);
			this->EnterDate->Name = L"EnterDate";
			this->EnterDate->Size = System::Drawing::Size(100, 28);
			this->EnterDate->TabIndex = 15;
			this->EnterDate->Text = L"Enter Dates";
			this->EnterDate->UseVisualStyleBackColor = true;
			this->EnterDate->Visible = false;
			this->EnterDate->Click += gcnew System::EventHandler(this, &ModEvent::EnterDate_Click);
			// 
			// DT10
			// 
			this->DT10->AutoSize = true;
			this->DT10->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT10->Location = System::Drawing::Point(48, 650);
			this->DT10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT10->Name = L"DT10";
			this->DT10->Size = System::Drawing::Size(0, 13);
			this->DT10->TabIndex = 16;
			this->DT10->Visible = false;
			this->DT10->Click += gcnew System::EventHandler(this, &ModEvent::DT10_Click);
			// 
			// DT9
			// 
			this->DT9->AutoSize = true;
			this->DT9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT9->Location = System::Drawing::Point(48, 613);
			this->DT9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT9->Name = L"DT9";
			this->DT9->Size = System::Drawing::Size(0, 13);
			this->DT9->TabIndex = 17;
			this->DT9->Visible = false;
			this->DT9->Click += gcnew System::EventHandler(this, &ModEvent::DT9_Click);
			// 
			// DT8
			// 
			this->DT8->AutoSize = true;
			this->DT8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT8->Location = System::Drawing::Point(48, 576);
			this->DT8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT8->Name = L"DT8";
			this->DT8->Size = System::Drawing::Size(0, 13);
			this->DT8->TabIndex = 18;
			this->DT8->Visible = false;
			this->DT8->Click += gcnew System::EventHandler(this, &ModEvent::DT8_Click);
			// 
			// DT7
			// 
			this->DT7->AutoSize = true;
			this->DT7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT7->Location = System::Drawing::Point(48, 539);
			this->DT7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT7->Name = L"DT7";
			this->DT7->Size = System::Drawing::Size(0, 13);
			this->DT7->TabIndex = 19;
			this->DT7->Visible = false;
			this->DT7->Click += gcnew System::EventHandler(this, &ModEvent::DT7_Click);
			// 
			// DT6
			// 
			this->DT6->AutoSize = true;
			this->DT6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT6->Location = System::Drawing::Point(48, 502);
			this->DT6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT6->Name = L"DT6";
			this->DT6->Size = System::Drawing::Size(0, 13);
			this->DT6->TabIndex = 20;
			this->DT6->Visible = false;
			this->DT6->Click += gcnew System::EventHandler(this, &ModEvent::DT6_Click);
			// 
			// DT5
			// 
			this->DT5->AutoSize = true;
			this->DT5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT5->Location = System::Drawing::Point(48, 465);
			this->DT5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT5->Name = L"DT5";
			this->DT5->Size = System::Drawing::Size(0, 13);
			this->DT5->TabIndex = 21;
			this->DT5->Visible = false;
			this->DT5->Click += gcnew System::EventHandler(this, &ModEvent::DT5_Click);
			// 
			// DT4
			// 
			this->DT4->AutoSize = true;
			this->DT4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT4->Location = System::Drawing::Point(48, 428);
			this->DT4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT4->Name = L"DT4";
			this->DT4->Size = System::Drawing::Size(0, 13);
			this->DT4->TabIndex = 22;
			this->DT4->Visible = false;
			this->DT4->Click += gcnew System::EventHandler(this, &ModEvent::DT4_Click);
			// 
			// DT3
			// 
			this->DT3->AutoSize = true;
			this->DT3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT3->Location = System::Drawing::Point(48, 391);
			this->DT3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT3->Name = L"DT3";
			this->DT3->Size = System::Drawing::Size(0, 13);
			this->DT3->TabIndex = 23;
			this->DT3->Visible = false;
			this->DT3->Click += gcnew System::EventHandler(this, &ModEvent::DT3_Click);
			// 
			// DT2
			// 
			this->DT2->AutoSize = true;
			this->DT2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT2->Location = System::Drawing::Point(48, 354);
			this->DT2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT2->Name = L"DT2";
			this->DT2->Size = System::Drawing::Size(0, 13);
			this->DT2->TabIndex = 24;
			this->DT2->Visible = false;
			this->DT2->Click += gcnew System::EventHandler(this, &ModEvent::DT2_Click);
			// 
			// DT1
			// 
			this->DT1->AutoSize = true;
			this->DT1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->DT1->Location = System::Drawing::Point(48, 318);
			this->DT1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT1->Name = L"DT1";
			this->DT1->Size = System::Drawing::Size(0, 13);
			this->DT1->TabIndex = 25;
			this->DT1->Visible = false;
			this->DT1->Click += gcnew System::EventHandler(this, &ModEvent::DT1_Click);
			// 
			// MMenuBtn
			// 
			this->MMenuBtn->Location = System::Drawing::Point(35, 75);
			this->MMenuBtn->Margin = System::Windows::Forms::Padding(4);
			this->MMenuBtn->Name = L"MMenuBtn";
			this->MMenuBtn->Size = System::Drawing::Size(100, 28);
			this->MMenuBtn->TabIndex = 26;
			this->MMenuBtn->Text = L"Main Menu";
			this->MMenuBtn->UseVisualStyleBackColor = true;
			this->MMenuBtn->Click += gcnew System::EventHandler(this, &ModEvent::MMenu_Click);
			// 
			// SaveChanges
			// 
			this->SaveChanges->Location = System::Drawing::Point(409, 694);
			this->SaveChanges->Margin = System::Windows::Forms::Padding(4);
			this->SaveChanges->Name = L"SaveChanges";
			this->SaveChanges->Size = System::Drawing::Size(127, 28);
			this->SaveChanges->TabIndex = 27;
			this->SaveChanges->Text = L"Save Changes";
			this->SaveChanges->UseVisualStyleBackColor = true;
			this->SaveChanges->Click += gcnew System::EventHandler(this, &ModEvent::SaveChanges_Click);
			// 
			// ModEvent
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(570, 120);
			this->Controls->Add(this->SaveChanges);
			this->Controls->Add(this->MMenuBtn);
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
			this->Controls->Add(this->EName2);
			this->Controls->Add(this->SEvent);
			this->Controls->Add(this->EventList);
			this->Controls->Add(this->EName);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"ModEvent";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Modify Event";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SEvent_Click(System::Object^  sender, System::EventArgs^  e);
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
	private: System::Void MMenu_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SaveChanges_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void EnterDate_Click(System::Object^  sender, System::EventArgs^  e);
};
}
