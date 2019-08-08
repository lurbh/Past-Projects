#pragma once

namespace CSITGroupAssignment {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DateAndTime
	/// </summary>
	public ref class DateAndTime : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Label^  Date;
	private: System::Windows::Forms::Label^  Time;
	private: System::Windows::Forms::DateTimePicker^  TimeInput;
	private: System::Windows::Forms::DateTimePicker^  DateInput;
	private: System::Windows::Forms::Button^  Enter;
	
	public:
		DateAndTime(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		String ^ GetDate()
		{
			return DateInput->Text;
		}

		String ^ GetTime()
		{
			return TimeInput->Text;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DateAndTime()
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
			this->Date = (gcnew System::Windows::Forms::Label());
			this->Time = (gcnew System::Windows::Forms::Label());
			this->TimeInput = (gcnew System::Windows::Forms::DateTimePicker());
			this->DateInput = (gcnew System::Windows::Forms::DateTimePicker());
			this->Enter = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Date
			// 
			this->Date->AutoSize = true;
			this->Date->Location = System::Drawing::Point(37, 28);
			this->Date->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->Date->Name = L"Date";
			this->Date->Size = System::Drawing::Size(38, 17);
			this->Date->TabIndex = 0;
			this->Date->Text = L"Date";
			// 
			// Time
			// 
			this->Time->AutoSize = true;
			this->Time->Location = System::Drawing::Point(37, 66);
			this->Time->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->Time->Name = L"Time";
			this->Time->Size = System::Drawing::Size(39, 17);
			this->Time->TabIndex = 0;
			this->Time->Text = L"Time";
			// 
			// TimeInput
			// 
			this->TimeInput->CustomFormat = L"HH:mm";
			this->TimeInput->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->TimeInput->Location = System::Drawing::Point(156, 66);
			this->TimeInput->Margin = System::Windows::Forms::Padding(4);
			this->TimeInput->Name = L"TimeInput";
			this->TimeInput->ShowUpDown = true;
			this->TimeInput->Size = System::Drawing::Size(159, 22);
			this->TimeInput->TabIndex = 1;
			// 
			// DateInput
			// 
			this->DateInput->CustomFormat = L"dd/MM/yy";
			this->DateInput->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->DateInput->Location = System::Drawing::Point(156, 28);
			this->DateInput->Margin = System::Windows::Forms::Padding(4);
			this->DateInput->Name = L"DateInput";
			this->DateInput->Size = System::Drawing::Size(159, 22);
			this->DateInput->TabIndex = 2;
			// 
			// Enter
			// 
			this->Enter->Location = System::Drawing::Point(379, 94);
			this->Enter->Margin = System::Windows::Forms::Padding(4);
			this->Enter->Name = L"Enter";
			this->Enter->Size = System::Drawing::Size(100, 28);
			this->Enter->TabIndex = 3;
			this->Enter->Text = L"Enter";
			this->Enter->UseVisualStyleBackColor = true;
			this->Enter->Click += gcnew System::EventHandler(this, &DateAndTime::Enter_Click);
			// 
			// DateAndTime
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(493, 135);
			this->Controls->Add(this->Enter);
			this->Controls->Add(this->DateInput);
			this->Controls->Add(this->TimeInput);
			this->Controls->Add(this->Time);
			this->Controls->Add(this->Date);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"DateAndTime";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Date & Time";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Enter_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
