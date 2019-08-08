#include "ViewAttendees.h"

void CSITGroupAssignment::ViewAttendees::UpdateList()
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

System::Void CSITGroupAssignment::ViewAttendees::SEvent_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->ClientSize = System::Drawing::Size(570, 350);
	this->MMenuBtn->Location = System::Drawing::Point(37, 300);
	try
	{
		DataList->Items->Clear();
		String^ sqlstr = "SELECT * FROM [EventAttendees]";
		connection->Open();
		OleDbCommand ^ command = gcnew OleDbCommand(sqlstr, connection);
		OleDbDataReader^ reader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
		while (reader->Read())
		{
			if (reader["Event Name"]->ToString() == EventList->Text)
			{
				String ^ detail = "Event Name : " + reader["Event Name"] + "    |     User ID: " + reader["User ID"] + "    |    Name: " + reader["Username"];
				DataList->Items->Add(detail);
			}
		}
		connection->Close();
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->ToString());
		connection->Close();
	}
}

System::Void CSITGroupAssignment::ViewAttendees::MMenu_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Close();
}
