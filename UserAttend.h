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
	/// Summary for UserAttend
	/// </summary>
	public ref class UserAttend : public System::Windows::Forms::Form
	{
		String ^ id;
		String ^ name;

		void UpdateList();

	private: OleDbConnection ^ connection = gcnew OleDbConnection();
	private: System::Windows::Forms::Label^  UName;
	private: System::Windows::Forms::Button^  MMenuBtn;
	private: System::Windows::Forms::ListBox^  DataList;

	public:
		UserAttend(void)
		{
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
			UpdateList();
		}

		UserAttend(String ^ idtext, String ^ nametext)
		{
			id = idtext;
			name = nametext;
			connection->ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0; Data Source = TestEvent.accdb; Persist Security Info = False;";
			InitializeComponent();
			UpdateList();
			this->UName->Text = L"User: " + name + "(" + id + ")";
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UserAttend()
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
			this->UName = (gcnew System::Windows::Forms::Label());
			this->MMenuBtn = (gcnew System::Windows::Forms::Button());
			this->DataList = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// UName
			// 
			this->UName->AutoSize = true;
			this->UName->Location = System::Drawing::Point(33, 37);
			this->UName->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->UName->Name = L"UName";
			this->UName->Size = System::Drawing::Size(35, 13);
			this->UName->TabIndex = 0;
			this->UName->Text = L"Name";
			// 
			// MMenuBtn
			// 
			this->MMenuBtn->Location = System::Drawing::Point(37, 300);
			this->MMenuBtn->Margin = System::Windows::Forms::Padding(4);
			this->MMenuBtn->Name = L"MMenuBtn";
			this->MMenuBtn->Size = System::Drawing::Size(100, 28);
			this->MMenuBtn->TabIndex = 26;
			this->MMenuBtn->Text = L"Main Menu";
			this->MMenuBtn->UseVisualStyleBackColor = true;
			this->MMenuBtn->Click += gcnew System::EventHandler(this, &UserAttend::MMenu_Click);
			// 
			// DataList
			// 
			this->DataList->FormattingEnabled = true;
			this->DataList->Location = System::Drawing::Point(36, 82);
			this->DataList->Name = L"DataList";
			this->DataList->Size = System::Drawing::Size(475, 160);
			this->DataList->TabIndex = 27;
			// 
			// UserAttend
			// 
			this->ClientSize = System::Drawing::Size(570, 350);
			this->Controls->Add(this->DataList);
			this->Controls->Add(this->MMenuBtn);
			this->Controls->Add(this->UName);
			this->Name = L"UserAttend";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"User Joined Events";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	#pragma endregion
	private: System::Void MMenu_Click(System::Object^  sender, System::EventArgs^  e);
};
}
