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
	/// Summary for ExitEvent
	/// </summary>
	public ref class ExitEvent : public System::Windows::Forms::Form
	{
		String ^ id;
		String ^ name;
		void UpdateList();
	private: OleDbConnection^ connection = gcnew OleDbConnection();
	private: System::Windows::Forms::Label^  EName;
	private: System::Windows::Forms::ComboBox^  EventList;
	private: System::Windows::Forms::Button^  EEvent;
	private: System::Windows::Forms::Button^  MMenuBtn;


	public:
		ExitEvent(void)
		{
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
		}

		ExitEvent(String ^ idtext, String ^ nametext)
		{
			id = idtext;
			name = nametext;
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
			UpdateList();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ExitEvent()
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
			this->EEvent = (gcnew System::Windows::Forms::Button());
			this->MMenuBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// EName
			// 
			this->EName->AutoSize = true;
			this->EName->Location = System::Drawing::Point(33, 37);
			this->EName->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->EName->Name = L"EName";
			this->EName->Size = System::Drawing::Size(124, 13);
			this->EName->TabIndex = 0;
			this->EName->Text = L"Select the Event to Exit: ";
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
			// EEvent
			// 
			this->EEvent->Location = System::Drawing::Point(400, 74);
			this->EEvent->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->EEvent->Name = L"EEvent";
			this->EEvent->Size = System::Drawing::Size(111, 28);
			this->EEvent->TabIndex = 2;
			this->EEvent->Text = L"Exit Event";
			this->EEvent->UseVisualStyleBackColor = true;
			this->EEvent->Click += gcnew System::EventHandler(this, &ExitEvent::EEvent_Click);
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
			this->MMenuBtn->Click += gcnew System::EventHandler(this, &ExitEvent::MainMenu_Click);
			// 
			// ExitEvent
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(570, 120);
			this->Controls->Add(this->MMenuBtn);
			this->Controls->Add(this->EEvent);
			this->Controls->Add(this->EventList);
			this->Controls->Add(this->EName);
			this->Name = L"ExitEvent";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Exit Event";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void EEvent_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MainMenu_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
