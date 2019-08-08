#pragma once

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
	/// Summary for DelEvent
	/// </summary>
	public ref class DelEvent : public System::Windows::Forms::Form
	{
		String ^ id;
		void UpdateList();

	private: OleDbConnection^ connection = gcnew OleDbConnection();
	private: System::Windows::Forms::Label^  EName;
	private: System::Windows::Forms::ComboBox^  EventList;
	private: System::Windows::Forms::Button^  DEvent;
	private: System::Windows::Forms::Button^  MMenuBtn;


	public:
		DelEvent(void)
		{
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
			UpdateList();
		}

		DelEvent(String ^ userid)
		{
			id = userid;
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
			UpdateList();
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DelEvent()
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
			this->DEvent = (gcnew System::Windows::Forms::Button());
			this->MMenuBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// EName
			// 
			this->EName->AutoSize = true;
			this->EName->Location = System::Drawing::Point(33, 37);
			this->EName->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->EName->Name = L"EName";
			this->EName->Size = System::Drawing::Size(136, 13);
			this->EName->TabIndex = 0;
			this->EName->Text = L"Select the Event to delete: ";
			// 
			// EventList
			// 
			this->EventList->FormattingEnabled = true;
			this->EventList->Location = System::Drawing::Point(227, 37);
			this->EventList->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->EventList->Name = L"EventList";
			this->EventList->Size = System::Drawing::Size(281, 21);
			this->EventList->TabIndex = 1;
			// 
			// DEvent
			// 
			this->DEvent->Location = System::Drawing::Point(400, 74);
			this->DEvent->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->DEvent->Name = L"DEvent";
			this->DEvent->Size = System::Drawing::Size(111, 28);
			this->DEvent->TabIndex = 2;
			this->DEvent->Text = L"Delete Event";
			this->DEvent->UseVisualStyleBackColor = true;
			this->DEvent->Click += gcnew System::EventHandler(this, &DelEvent::SEvent_Click);
			// 
			// MMenuBtn
			// 
			this->MMenuBtn->Location = System::Drawing::Point(36, 74);
			this->MMenuBtn->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->MMenuBtn->Name = L"MMenuBtn";
			this->MMenuBtn->Size = System::Drawing::Size(111, 28);
			this->MMenuBtn->TabIndex = 2;
			this->MMenuBtn->Text = L"Main Menu";
			this->MMenuBtn->UseVisualStyleBackColor = true;
			this->MMenuBtn->Click += gcnew System::EventHandler(this, &DelEvent::MMenu_Click);
			// 
			// DelEvent
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(570, 120);
			this->Controls->Add(this->MMenuBtn);
			this->Controls->Add(this->DEvent);
			this->Controls->Add(this->EventList);
			this->Controls->Add(this->EName);
			this->Name = L"DelEvent";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Delete Event";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SEvent_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MMenu_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
