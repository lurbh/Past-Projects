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
	/// Summary for UserHistory
	/// </summary>
	public ref class UserHistory : public System::Windows::Forms::Form
	{
		String ^ id;
		String ^ name;

		void LoadData();

	private: OleDbConnection ^ connection = gcnew OleDbConnection();
	private: System::Windows::Forms::ListBox^  HistoryDetails;
	private: System::Windows::Forms::Label^  Namedetails;
	private: System::Windows::Forms::Button^  ExitBtn;
	private: System::Windows::Forms::Label^  Details;

	public:
		UserHistory(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		UserHistory(String ^ idtext, String ^ nametext)
		{
			id = idtext;
			name = nametext;
			InitializeComponent();
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			LoadData();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UserHistory()
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
			this->HistoryDetails = (gcnew System::Windows::Forms::ListBox());
			this->Namedetails = (gcnew System::Windows::Forms::Label());
			this->ExitBtn = (gcnew System::Windows::Forms::Button());
			this->Details = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// HistoryDetails
			// 
			this->HistoryDetails->FormattingEnabled = true;
			this->HistoryDetails->ItemHeight = 16;
			this->HistoryDetails->Location = System::Drawing::Point(35, 81);
			this->HistoryDetails->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->HistoryDetails->Name = L"HistoryDetails";
			this->HistoryDetails->Size = System::Drawing::Size(528, 132);
			this->HistoryDetails->TabIndex = 0;
			// 
			// Namedetails
			// 
			this->Namedetails->AutoSize = true;
			this->Namedetails->Location = System::Drawing::Point(31, 25);
			this->Namedetails->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->Namedetails->Name = L"Namedetails";
			this->Namedetails->Size = System::Drawing::Size(49, 17);
			this->Namedetails->TabIndex = 1;
			this->Namedetails->Text = L"Name:";
			// 
			// ExitBtn
			// 
			this->ExitBtn->Location = System::Drawing::Point(464, 240);
			this->ExitBtn->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->ExitBtn->Name = L"ExitBtn";
			this->ExitBtn->Size = System::Drawing::Size(100, 28);
			this->ExitBtn->TabIndex = 2;
			this->ExitBtn->Text = L"Exit";
			this->ExitBtn->UseVisualStyleBackColor = true;
			this->ExitBtn->Click += gcnew System::EventHandler(this, &UserHistory::ExitBtn_Click);
			// 
			// Details
			// 
			this->Details->AutoSize = true;
			this->Details->Location = System::Drawing::Point(33, 64);
			this->Details->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->Details->Name = L"Details";
			this->Details->Size = System::Drawing::Size(351, 17);
			this->Details->TabIndex = 1;
			this->Details->Text = L"User id          | Date                 | Time      | History Detail";
			// 
			// UserHistory
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(603, 283);
			this->Controls->Add(this->ExitBtn);
			this->Controls->Add(this->Details);
			this->Controls->Add(this->Namedetails);
			this->Controls->Add(this->HistoryDetails);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"UserHistory";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"User History";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ExitBtn_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
