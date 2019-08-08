#include "ModEvent.h"

void CSITGroupAssignment::ModEvent::UpdateList()
{
	this->EventList->Items->Clear();
	try
	{
		String^ sqlstr = "SELECT * FROM [EventDetails]";
		connection->Open();
		OleDbCommand ^ command = gcnew OleDbCommand(sqlstr, connection);
		OleDbDataReader^ reader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
		while (reader->Read())
		{
			this->EventList->Items->Add(reader["Event Name"]);
		}
		connection->Close();
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->ToString());
		connection->Close();
	}
	this->EventList->Text = "";
}


System::Void CSITGroupAssignment::ModEvent::SEvent_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (EventList->Text != "")
	{
		try
		{
			String^ sqlstr = "SELECT * FROM [EventDetails]";
			connection->Open();
			OleDbCommand ^ command = gcnew OleDbCommand(sqlstr, connection);
			OleDbDataReader^ reader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
			while (reader->Read())
			{
				if (reader["Event Name"]->ToString() == EventList->Text)
				{
					EventName = EventList->Text;
					NameInput->Text = reader["Event Name"]->ToString();
					VenueInput->Text = reader["Venue"]->ToString();
					PriceInput->Text = reader["Price"]->ToString();
					CapcityInput->Text = reader["Max Capacity"]->ToString();
					if (reader["S1 Date"]->ToString() != "")
						DT1->Text = "Session 1:     Date : " + reader["S1 Date"]->ToString() + "     Time : " + reader["S1 Time"]->ToString();
					if (reader["S2 Date"]->ToString() != "")
						DT2->Text = "Session 2:     Date : " + reader["S2 Date"]->ToString() + "     Time : " + reader["S2 Time"]->ToString();
					if (reader["S3 Date"]->ToString() != "")
						DT3->Text = "Session 3:     Date : " + reader["S3 Date"]->ToString() + "     Time : " + reader["S3 Time"]->ToString();
					if (reader["S4 Date"]->ToString() != "")
						DT4->Text = "Session 4:     Date : " + reader["S4 Date"]->ToString() + "     Time : " + reader["S4 Time"]->ToString();
					if (reader["S5 Date"]->ToString() != "")
						DT5->Text = "Session 5:     Date : " + reader["S5 Date"]->ToString() + "     Time : " + reader["S5 Time"]->ToString();
					if (reader["S6 Date"]->ToString() != "")
						DT6->Text = "Session 6:     Date : " + reader["S6 Date"]->ToString() + "     Time : " + reader["S6 Time"]->ToString();
					if (reader["S7 Date"]->ToString() != "")
						DT7->Text = "Session 7:     Date : " + reader["S7 Date"]->ToString() + "     Time : " + reader["S7 Time"]->ToString();
					if (reader["S8 Date"]->ToString() != "")
						DT8->Text = "Session 8:     Date : " + reader["S8 Date"]->ToString() + "     Time : " + reader["S8 Time"]->ToString();
					if (reader["S9 Date"]->ToString() != "")
						DT9->Text = "Session 9:     Date : " + reader["S9 Date"]->ToString() + "     Time : " + reader["S9 Time"]->ToString();
					if (reader["S10 Date"]->ToString() != "")
						DT10->Text = "Session 10:     Date : " + reader["S10 Date"]->ToString() + "     Time : " + reader["S10 Time"]->ToString();
				}
			}
			reader->Close();
			connection->Close();
			this->ClientSize = System::Drawing::Size(570, 750);
			this->EName2->Visible = true;
			this->NameInput->Visible = true;
			this->EVenue->Visible = true;
			this->VenueInput->Visible = true;
			this->EPrice->Visible = true;
			this->PriceInput->Visible = true;
			this->ECapacity->Visible = true;
			this->CapcityInput->Visible = true;
			this->ESessionsNo->Visible = true;
			this->SessionsInput->Visible = true;
			this->EnterDate->Visible = true;
			this->DT1->Visible = true;
			this->DT2->Visible = true;
			this->DT3->Visible = true;
			this->DT4->Visible = true;
			this->DT5->Visible = true;
			this->DT6->Visible = true;
			this->DT7->Visible = true;
			this->DT8->Visible = true;
			this->DT9->Visible = true;
			this->DT10->Visible = true;
			this->MMenuBtn->Location = System::Drawing::Point(37, 695);
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->ToString());
			connection->Close();
		}
	}
}

System::Void CSITGroupAssignment::ModEvent::DT1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT1->Text = "Session 1:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::ModEvent::DT2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT2->Text = "Session 2:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::ModEvent::DT3_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT3->Text = "Session 3:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::ModEvent::DT4_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT4->Text = "Session 4:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::ModEvent::DT5_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT5->Text = "Session 5:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::ModEvent::DT6_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT6->Text = "Session 6:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::ModEvent::DT7_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT7->Text = "Session 7:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::ModEvent::DT8_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT8->Text = "Session 8:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::ModEvent::DT9_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT9->Text = "Session 9:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::ModEvent::DT10_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DateAndTime^ dt = gcnew DateAndTime;
	dt->ShowDialog();
	String ^ date = dt->GetDate();
	String ^ time = dt->GetTime();
	DT10->Text = "Session 10:     Date : " + date + "     Time : " + time;
}

System::Void CSITGroupAssignment::ModEvent::MMenu_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Close();
}

System::Void CSITGroupAssignment::ModEvent::SaveChanges_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	try
	{
		connection->Open();
		String^ cmd = "UPDATE EventDetails SET [Event Name] = '" + NameInput->Text + "', [Venue] = '" + VenueInput->Text + "', [Price] = '" + PriceInput->Text
			+ "', [Max Capacity] = '" + CapcityInput->Text + "'";
		if (DT1->Text != "")
			cmd += ", [S1 Date] = '" + DT1->Text->Substring(DT1->Text->IndexOf("Date : ") + 7, 8) +
			"', [S1 Time] = '" + DT1->Text->Substring(DT1->Text->IndexOf("Time : ") + 7, 5) + "'";
		if (DT2->Text != "")
			cmd += ", [S2 Date] = '" + DT2->Text->Substring(DT2->Text->IndexOf("Date : ") + 7, 8) +
			"', [S2 Time] = '" + DT2->Text->Substring(DT2->Text->IndexOf("Time : ") + 7, 5) + "'";
		if (DT3->Text != "")
			cmd += ", [S3 Date] = '" + DT3->Text->Substring(DT3->Text->IndexOf("Date : " ) + 7, 8) +
			"', [S3 Time] = '" + DT3->Text->Substring(DT3->Text->IndexOf("Time : ") + 7, 5) + "'";
		if (DT4->Text != "")
			cmd += ", [S4 Date] = '" + DT4->Text->Substring(DT4->Text->IndexOf("Date : ") + 7, 8) +
			"', [S4 Time] = '" + DT4->Text->Substring(DT4->Text->IndexOf("Time : ") + 7, 5) + "'";
		if (DT5->Text != "")
			cmd += ", [S5 Date] = '" + DT5->Text->Substring(DT5->Text->IndexOf("Date : ") + 7, 8) +
			"', [S5 Time] = '" + DT5->Text->Substring(DT5->Text->IndexOf("Time : " ) + 7, 5) + "'";
		if (DT6->Text != "")
			cmd += ", [S6 Date] = '" + DT6->Text->Substring(DT6->Text->IndexOf("Date : ") + 7, 8) +
			"', [S6 Time] = '" + DT6->Text->Substring(DT6->Text->IndexOf("Time : ") + 7, 5) + "'";
		if (DT7->Text != "")
			cmd += ", [S7 Date] = '" + DT7->Text->Substring(DT7->Text->IndexOf("Date : ") + 7, 8) +
			"', [S7 Time] = '" + DT7->Text->Substring(DT7->Text->IndexOf("Time : ") + 7, 5) + "'";
		if (DT8->Text != "")
			cmd += ", [S8 Date] = '" + DT8->Text->Substring(DT8->Text->IndexOf("Date : ") + 7, 8) +
			"', [S8 Time] = '" + DT8->Text->Substring(DT8->Text->IndexOf("Time : ") + 7, 5) + "'";
		if (DT9->Text != "")
			cmd += ", [S9 Date] = '" + DT9->Text->Substring(DT9->Text->IndexOf("Date : ") + 7, 8) +
			"', [S9 Time] = '" + DT9->Text->Substring(DT9->Text->IndexOf("Time : ") + 7, 5) + "'";
		if (DT10->Text != "")
			cmd += ", [S10 Date] = '" + DT10->Text->Substring(DT10->Text->IndexOf("Date : ") + 7, 8) +
			"', [S10 Time] = '" + DT10->Text->Substring(DT10->Text->IndexOf("Time : ") + 7, 5) + "'";
		cmd += " WHERE [Event Name] = '" + EventName + "'";
		OleDbCommand ^ command = gcnew OleDbCommand(cmd, connection);
		command->ExecuteNonQuery();
		String ^ date = DateTime::Now.ToString("dd/MM/yy");
		String ^ time = DateTime::Now.ToString("HH:mm");
		command->CommandText = "insert into UserHistory ([User ID], [His Date], [His Time], [History])  values( '" + id + "','" + date + "','" + time + "','" + NameInput->Text + " Modified.')";
		command->ExecuteNonQuery();
		MessageBox::Show("Details saved", "Details saved");
		EventList->Text = NameInput->Text;
		connection->Close();
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->ToString());
		MessageBox::Show("Error cannot modify Event", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		connection->Close();
	}
	
}

System::Void CSITGroupAssignment::ModEvent::EnterDate_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (MessageBox::Show("Do you really want to modify the sessions event?", "Are You Sure?", MessageBoxButtons::YesNo, MessageBoxIcon::Question) ==
		System::Windows::Forms::DialogResult::Yes)
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
				DT6->Text = "Session 8:     Date : " + date + "     Time : " + time;
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
