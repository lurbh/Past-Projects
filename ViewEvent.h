#pragma once

namespace CSITGroupAssignment {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::OleDb;

	/// <summary>
	/// Summary for ViewEvent
	/// </summary>
	public ref class ViewEvent : public System::Windows::Forms::Form
	{
	private: OleDbConnection^ connection = gcnew OleDbConnection();
	private: System::Windows::Forms::Label^  EName;
	private: System::Windows::Forms::ComboBox^  EventList;
	private: System::Windows::Forms::Button^  SEvent;
	private: System::Windows::Forms::Label^  EName2;
	private: System::Windows::Forms::Label^  EVenue;
	private: System::Windows::Forms::Label^  EPrice;
	private: System::Windows::Forms::Label^  ECapacity;
	private: System::Windows::Forms::Label^  NameInput;
	private: System::Windows::Forms::Label^  VenueInput;
	private: System::Windows::Forms::Label^  PriceInput;
	private: System::Windows::Forms::Label^  CapcityInput;
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

	private:
		void UpdateList();
	public:
		ViewEvent(void)
		{
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
			UpdateList();
			this->Location = System::Drawing::Point((Screen::PrimaryScreen->Bounds.Width - this->Size.Width) / 2 + (this->Size.Width / 4), 250);
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ViewEvent()
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
			this->NameInput = (gcnew System::Windows::Forms::Label());
			this->VenueInput = (gcnew System::Windows::Forms::Label());
			this->PriceInput = (gcnew System::Windows::Forms::Label());
			this->CapcityInput = (gcnew System::Windows::Forms::Label());
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
			this->SuspendLayout();
			// 
			// EName
			// 
			this->EName->AutoSize = true;
			this->EName->Location = System::Drawing::Point(33, 37);
			this->EName->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->EName->Name = L"EName";
			this->EName->Size = System::Drawing::Size(130, 13);
			this->EName->TabIndex = 0;
			this->EName->Text = L"Select the Event to View: ";
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
			this->SEvent->Click += gcnew System::EventHandler(this, &ViewEvent::SEvent_Click);
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
			// NameInput
			// 
			this->NameInput->Location = System::Drawing::Point(120, 118);
			this->NameInput->Margin = System::Windows::Forms::Padding(4);
			this->NameInput->Name = L"NameInput";
			this->NameInput->Size = System::Drawing::Size(365, 20);
			this->NameInput->TabIndex = 13;
			this->NameInput->Visible = false;
			// 
			// VenueInput
			// 
			this->VenueInput->Location = System::Drawing::Point(120, 155);
			this->VenueInput->Margin = System::Windows::Forms::Padding(4);
			this->VenueInput->Name = L"VenueInput";
			this->VenueInput->Size = System::Drawing::Size(365, 20);
			this->VenueInput->TabIndex = 12;
			this->VenueInput->Visible = false;
			// 
			// PriceInput
			// 
			this->PriceInput->Location = System::Drawing::Point(120, 192);
			this->PriceInput->Margin = System::Windows::Forms::Padding(4);
			this->PriceInput->Name = L"PriceInput";
			this->PriceInput->Size = System::Drawing::Size(365, 20);
			this->PriceInput->TabIndex = 11;
			this->PriceInput->Visible = false;
			// 
			// CapcityInput
			// 
			this->CapcityInput->Location = System::Drawing::Point(120, 229);
			this->CapcityInput->Margin = System::Windows::Forms::Padding(4);
			this->CapcityInput->Name = L"CapcityInput";
			this->CapcityInput->Size = System::Drawing::Size(365, 20);
			this->CapcityInput->TabIndex = 10;
			this->CapcityInput->Visible = false;
			// 
			// DT10
			// 
			this->DT10->AutoSize = true;
			this->DT10->Location = System::Drawing::Point(48, 540);
			this->DT10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT10->Name = L"DT10";
			this->DT10->Size = System::Drawing::Size(0, 13);
			this->DT10->TabIndex = 16;
			this->DT10->Visible = false;
			// 
			// DT9
			// 
			this->DT9->AutoSize = true;
			this->DT9->Location = System::Drawing::Point(48, 510);
			this->DT9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT9->Name = L"DT9";
			this->DT9->Size = System::Drawing::Size(0, 13);
			this->DT9->TabIndex = 17;
			this->DT9->Visible = false;
			// 
			// DT8
			// 
			this->DT8->AutoSize = true;
			this->DT8->Location = System::Drawing::Point(48, 480);
			this->DT8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT8->Name = L"DT8";
			this->DT8->Size = System::Drawing::Size(0, 13);
			this->DT8->TabIndex = 18;
			this->DT8->Visible = false;
			// 
			// DT7
			// 
			this->DT7->AutoSize = true;
			this->DT7->Location = System::Drawing::Point(48, 450);
			this->DT7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT7->Name = L"DT7";
			this->DT7->Size = System::Drawing::Size(0, 13);
			this->DT7->TabIndex = 19;
			this->DT7->Visible = false;
			// 
			// DT6
			// 
			this->DT6->AutoSize = true;
			this->DT6->Location = System::Drawing::Point(48, 420);
			this->DT6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT6->Name = L"DT6";
			this->DT6->Size = System::Drawing::Size(0, 13);
			this->DT6->TabIndex = 20;
			this->DT6->Visible = false;
			// 
			// DT5
			// 
			this->DT5->AutoSize = true;
			this->DT5->Location = System::Drawing::Point(48, 390);
			this->DT5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT5->Name = L"DT5";
			this->DT5->Size = System::Drawing::Size(0, 13);
			this->DT5->TabIndex = 21;
			this->DT5->Visible = false;
			// 
			// DT4
			// 
			this->DT4->AutoSize = true;
			this->DT4->Location = System::Drawing::Point(48, 360);
			this->DT4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT4->Name = L"DT4";
			this->DT4->Size = System::Drawing::Size(0, 13);
			this->DT4->TabIndex = 22;
			this->DT4->Visible = false;
			// 
			// DT3
			// 
			this->DT3->AutoSize = true;
			this->DT3->Location = System::Drawing::Point(48, 330);
			this->DT3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT3->Name = L"DT3";
			this->DT3->Size = System::Drawing::Size(0, 13);
			this->DT3->TabIndex = 23;
			this->DT3->Visible = false;
			// 
			// DT2
			// 
			this->DT2->AutoSize = true;
			this->DT2->Location = System::Drawing::Point(48, 300);
			this->DT2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT2->Name = L"DT2";
			this->DT2->Size = System::Drawing::Size(0, 13);
			this->DT2->TabIndex = 24;
			this->DT2->Visible = false;
			// 
			// DT1
			// 
			this->DT1->AutoSize = true;
			this->DT1->Location = System::Drawing::Point(48, 270);
			this->DT1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->DT1->Name = L"DT1";
			this->DT1->Size = System::Drawing::Size(0, 13);
			this->DT1->TabIndex = 25;
			this->DT1->Visible = false;
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
			this->MMenuBtn->Click += gcnew System::EventHandler(this, &ViewEvent::MMenu_Click);
			// 
			// ViewEvent
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(572, 118);
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
			this->Controls->Add(this->CapcityInput);
			this->Controls->Add(this->PriceInput);
			this->Controls->Add(this->VenueInput);
			this->Controls->Add(this->NameInput);
			this->Controls->Add(this->ECapacity);
			this->Controls->Add(this->EPrice);
			this->Controls->Add(this->EVenue);
			this->Controls->Add(this->EName2);
			this->Controls->Add(this->SEvent);
			this->Controls->Add(this->EventList);
			this->Controls->Add(this->EName);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"ViewEvent";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"View Event";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SEvent_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MMenu_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
