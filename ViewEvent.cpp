#include "ViewEvent.h"

void CSITGroupAssignment::ViewEvent::UpdateList()
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

System::Void CSITGroupAssignment::ViewEvent::SEvent_Click(System::Object ^ sender, System::EventArgs ^ e)
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
			this->ClientSize = System::Drawing::Size(570, 630);
			this->EName2->Visible = true;
			this->NameInput->Visible = true;
			this->EVenue->Visible = true;
			this->VenueInput->Visible = true;
			this->EPrice->Visible = true;
			this->PriceInput->Visible = true;
			this->ECapacity->Visible = true;
			this->CapcityInput->Visible = true;
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
			this->MMenuBtn->Location = System::Drawing::Point(37, 580);
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->ToString());
			connection->Close();
		}
	}
}

System::Void CSITGroupAssignment::ViewEvent::MMenu_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Close();
}
