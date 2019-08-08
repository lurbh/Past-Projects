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
	/// Summary for ViewAttendees
	/// </summary>
	public ref class ViewAttendees : public System::Windows::Forms::Form
	{
		void UpdateList();

	private: OleDbConnection^ connection = gcnew OleDbConnection();
	private: System::Windows::Forms::Label^  EName;
	private: System::Windows::Forms::ComboBox^  EventList;
	private: System::Windows::Forms::Button^  SEvent;
	private: System::Windows::Forms::Button^  MMenuBtn;
	private: System::Windows::Forms::ListBox^  DataList;

	public:
		ViewAttendees(void)
		{
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
			UpdateList();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ViewAttendees()
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
			this->MMenuBtn = (gcnew System::Windows::Forms::Button());
			this->EventList = (gcnew System::Windows::Forms::ComboBox());
			this->SEvent = (gcnew System::Windows::Forms::Button());
			this->DataList = (gcnew System::Windows::Forms::ListBox());
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
			// MMenuBtn
			// 
			this->MMenuBtn->Location = System::Drawing::Point(35, 75);
			this->MMenuBtn->Margin = System::Windows::Forms::Padding(4);
			this->MMenuBtn->Name = L"MMenuBtn";
			this->MMenuBtn->Size = System::Drawing::Size(100, 28);
			this->MMenuBtn->TabIndex = 26;
			this->MMenuBtn->Text = L"Main Menu";
			this->MMenuBtn->UseVisualStyleBackColor = true;
			this->MMenuBtn->Click += gcnew System::EventHandler(this, &ViewAttendees::MMenu_Click);
			// 
			// EventList
			// 
			this->EventList->FormattingEnabled = true;
			this->EventList->Location = System::Drawing::Point(171, 37);
			this->EventList->Margin = System::Windows::Forms::Padding(4);
			this->EventList->Name = L"EventList";
			this->EventList->Size = System::Drawing::Size(337, 21);
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
			this->SEvent->Click += gcnew System::EventHandler(this, &ViewAttendees::SEvent_Click);
			// 
			// DataList
			// 
			this->DataList->FormattingEnabled = true;
			this->DataList->Location = System::Drawing::Point(36, 130);
			this->DataList->Name = L"DataList";
			this->DataList->Size = System::Drawing::Size(475, 108);
			this->DataList->TabIndex = 27;
			// 
			// ViewAttendees
			// 
			this->ClientSize = System::Drawing::Size(570, 120);
			this->Controls->Add(this->DataList);
			this->Controls->Add(this->MMenuBtn);
			this->Controls->Add(this->EName);
			this->Controls->Add(this->SEvent);
			this->Controls->Add(this->EventList);
			this->Name = L"ViewAttendees";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"View Attendees";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SEvent_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MMenu_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
