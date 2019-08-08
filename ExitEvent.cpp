#include "ExitEvent.h"

void CSITGroupAssignment::ExitEvent::UpdateList()
{
	this->EventList->Items->Clear();
	try
	{
		String^ sqlstr = "SELECT * FROM [EventAttendees]";
		connection->Open();
		OleDbCommand ^ command = gcnew OleDbCommand(sqlstr, connection);
		OleDbDataReader^ reader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
		while (reader->Read())
		{
			if(id == reader["User ID"]->ToString())
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

System::Void CSITGroupAssignment::ExitEvent::EEvent_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (this->EventList->Text != "")
		if (MessageBox::Show("Do you really want to exit this event?", "Are You Sure?", MessageBoxButtons::YesNo, MessageBoxIcon::Question) ==
			System::Windows::Forms::DialogResult::Yes)
		{
			try
			{
				connection->Open();
				OleDbCommand ^ command = gcnew OleDbCommand("DELETE FROM EventAttendees WHERE [Event Name] = '" + EventList->Text + "' AND [User ID] ='" + id + "'", connection);
				command->ExecuteNonQuery();
				String ^ date = DateTime::Now.ToString("dd/MM/yy");
				String ^ time = DateTime::Now.ToString("HH:mm");
				command->CommandText = "insert into UserHistory ([User ID], [His Date], [His Time], [History])  values( '" + id + "','" + date + "','" + time + "','User left " + EventList->Text + ".')";
				command->ExecuteNonQuery();
				MessageBox::Show("Event Deleted", "Event Deleted");
				connection->Close();
				UpdateList();
			}
			catch (Exception^ er)
			{
				MessageBox::Show(er->ToString());
				MessageBox::Show("Error cannot exit Event", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				connection->Close();
			}
		}
}

System::Void CSITGroupAssignment::ExitEvent::MainMenu_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Close();
}
