#include "CreateEvent.h"


System::Void CSITGroupAssignment::CreateEvent::EnterDate_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (this->SessionsInput->Text != "")
	{
		DT1->Text = "";
		DT2->Text = "";
		DT3->Text = "";
		DT4->Text = "";
		DT5->Text = "";
		DT6->Text = "";
		DT7->Text = "";
		DT8->Text = "";
		DT9->Text = "";
		DT10->Text = "";
		int no = int::Parse(this->SessionsInput->Text);
		for (int i = 0; i < no; i++)
		{
			DateAndTime^ dt = gcnew DateAndTime;
			dt->ShowDialog();
			String ^ date = dt->GetDate();
			String ^ time = dt->GetTime();
			switch (i)
			{
			case 0:
				DT1->Text = "Session 1:     Date : " + date + "     Time : " + time;
				break;
			case 1:
				DT2->Text = "Session 2:     Date : " + date + "     Time : " + time;
				break;
			case 2:
				DT3->Text = "Session 3:     Date : " + date + "     Time : " + time;
				break;
			case 3:
				DT4->Text = "Session 4:     Date : " + date + "     Time : " + time;
				break;
			case 4:
				DT5->Text = "Session 5:     Date : " + date + "     Time : " + time;
				break;
			case 5:
				DT6->Text = "Session 6:     Date : " + date + "     Time : " + time;
				break;
			case 6:
				DT7->Text = "Session 7:     Date : " + date + "     Time : " + time;
				break;
			case 7:
				DT8->Text = "Session 8:     Date : " + date + "     Time : " + time;
				break;
			case 8:
				DT9->Text = "Session 9:     Date : " + date + "     Time : " + time;
				break;
			case 9:
				DT10->Text = "Session 10:     Date : " + date + "     Time : " + time;
				break;
			default:
				break;
			}
		}
	}
}

System::Void CSITGroupAssignment::CreateEvent::DT1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT1->Text = "Session 1:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::CreateEvent::DT2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT2->Text = "Session 2:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::CreateEvent::DT3_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT3->Text = "Session 3:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::CreateEvent::DT4_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT4->Text = "Session 4:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::CreateEvent::DT5_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT5->Text = "Session 5:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::CreateEvent::DT6_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT6->Text = "Session 6:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::CreateEvent::DT7_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT7->Text = "Session 7:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::CreateEvent::DT8_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT8->Text = "Session 8:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::CreateEvent::DT9_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT9->Text = "Session 9:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::CreateEvent::DT10_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT10->Text = "Session 10:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::CreateEvent::CreateEventBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if(NameInput->Text == "")
		MessageBox::Show("No Event Name");
	else if(VenueInput->Text == "")
		MessageBox::Show("No Event Venue");
	else if (PriceInput->Text == "")
		MessageBox::Show("No Event Price");
	else if (CapcityInput->Text == "")
		MessageBox::Show("No Event max capacity");
	else if (DT1->Text == "")
		MessageBox::Show("No Event Sessions");
	else
	{
		try
		{
			connection->Open();
			OleDbCommand ^ command = gcnew OleDbCommand();
			command->Connection = connection;
			command->CommandText = "insert into EventDetails ([Event Name], [Venue], [Price], [Max Capacity]";
			int no = int::Parse(this->SessionsInput->Text);
			for (int i = 0; i < no; i++)
			{
				switch (i)
				{
				case 0:
					command->CommandText += ", [S1 Date], [S1 Time]";
					break;
				case 1:
					command->CommandText += ", [S2 Date], [S2 Time]";
					break;
				case 2:
					command->CommandText += ", [S3 Date], [S3 Time]";
					break;
				case 3:
					command->CommandText += ", [S4 Date], [S4 Time]";
					break;
				case 4:
					command->CommandText += ", [S5 Date], [S5 Time]";
					break;
				case 5:
					command->CommandText += ", [S6 Date], [S6 Time]";
					break;
				case 6:
					command->CommandText += ", [S7 Date], [S7 Time]";
					break;
				case 7:
					command->CommandText += ", [S8 Date], [S8 Time]";
					break;
				case 8:
					command->CommandText += ", [S9 Date], [S9 Time]";
					break;
				case 9:
					command->CommandText += ", [S10 Date], [S10 Time]";
					break;
				default:
					break;
				}
			}
			command->CommandText += ") values( '" + NameInput->Text + "','" + VenueInput->Text + "','" + PriceInput->Text + "','" + CapcityInput->Text;
			if (DT1->Text != "")
				command->CommandText += "','" + DT1->Text->Substring(DT1->Text->IndexOf("Date : ") + 7, 8) + "','" + DT1->Text->Substring(DT1->Text->IndexOf("Time : ") + 7, 5);
			if (DT2->Text != "")
				command->CommandText += "','" + DT2->Text->Substring(DT2->Text->IndexOf("Date : ") + 7, 8) + "','" + DT2->Text->Substring(DT2->Text->IndexOf("Time : ") + 7, 5);
			if (DT3->Text != "")
				command->CommandText += "','" + DT3->Text->Substring(DT3->Text->IndexOf("Date : ") + 7, 8) + "','" + DT3->Text->Substring(DT3->Text->IndexOf("Time : ") + 7, 5);
			if (DT4->Text != "")
				command->CommandText += "','" + DT4->Text->Substring(DT4->Text->IndexOf("Date : ") + 7, 8) + "','" + DT4->Text->Substring(DT4->Text->IndexOf("Time : ") + 7, 5);
			if (DT5->Text != "")
				command->CommandText += "','" + DT5->Text->Substring(DT5->Text->IndexOf("Date : ") + 7, 8) + "','" + DT5->Text->Substring(DT5->Text->IndexOf("Time : ") + 7, 5);
			if (DT6->Text != "")
				command->CommandText += "','" + DT6->Text->Substring(DT6->Text->IndexOf("Date : ") + 7, 8) + "','" + DT6->Text->Substring(DT6->Text->IndexOf("Time : ") + 7, 5);
			if (DT7->Text != "")
				command->CommandText += "','" + DT7->Text->Substring(DT7->Text->IndexOf("Date : ") + 7, 8) + "','" + DT7->Text->Substring(DT7->Text->IndexOf("Time : ") + 7, 5);
			if (DT8->Text != "")
				command->CommandText += "','" + DT8->Text->Substring(DT8->Text->IndexOf("Date : ") + 7, 8) + "','" + DT8->Text->Substring(DT8->Text->IndexOf("Time : ") + 7, 5);
			if (DT9->Text != "")
				command->CommandText += "','" + DT9->Text->Substring(DT9->Text->IndexOf("Date : ") + 7, 8) + "','" + DT9->Text->Substring(DT9->Text->IndexOf("Time : ") + 7, 5);
			if (DT10->Text != "")
				command->CommandText += "','" + DT10->Text->Substring(DT10->Text->IndexOf("Date : ") + 7, 8) + "','" + DT10->Text->Substring(DT10->Text->IndexOf("Time : ") + 7, 5);

			command->CommandText += "')";
			command->ExecuteNonQuery();
			String ^ date = DateTime::Now.ToString("dd/MM/yy");
			String ^ time = DateTime::Now.ToString("HH:mm");
			command->CommandText = "insert into UserHistory ([User ID], [His Date], [His Time], [History])  values( '" + id + "','" + date + "','" + time + "','" + NameInput->Text + " Created.')";
			command->ExecuteNonQuery();
			MessageBox::Show("Event Created", "Event Created");
			connection->Close();
			Close();
		}
		catch(Exception^ er)
		{
			MessageBox::Show(er->ToString());
			MessageBox::Show("Error cannot create Event","Error",MessageBoxButtons::OK,MessageBoxIcon::Error);
			connection->Close();
		}
	}
	
}

System::Void CSITGroupAssignment::CreateEvent::MMenu_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Close();
}
