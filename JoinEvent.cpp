#include "JoinEvent.h"

void CSITGroupAssignment::JoinEvent::UpdateList()
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

System::Void CSITGroupAssignment::JoinEvent::JEvent_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if(this->EventList->Text != "")
		if (MessageBox::Show("Do you really want to join this event?", "Are You Sure?", MessageBoxButtons::YesNo, MessageBoxIcon::Question) ==
			System::Windows::Forms::DialogResult::Yes)
		{
			bool joined = false;
			try
			{
				String^ sqlstr = "SELECT * FROM [EventAttendees]";
				connection->Open();
				OleDbCommand ^ command = gcnew OleDbCommand(sqlstr, connection);
				OleDbDataReader^ reader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
				while (reader->Read())
				{
					if (reader["Event Name"]->ToString() == EventList->Text && reader["User ID"]->ToString() == id)
					{
						joined = true;
						MessageBox::Show("You have joined the event before", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
						break;
					}
				}
				connection->Close();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->ToString());
				connection->Close();
			}
			if (!joined)
			{
				try
				{
					connection->Open();
					OleDbCommand ^ command = gcnew OleDbCommand();
					command->Connection = connection;
					command->CommandText = "insert into EventAttendees ([Event Name], [User ID], [Username]) values( '"
						+ EventList->Text + "','" + id + "','" + name + "')";
					command->ExecuteNonQuery();
					String ^ date = DateTime::Now.ToString("dd/MM/yy");
					String ^ time = DateTime::Now.ToString("HH:mm");
					command->CommandText = "insert into UserHistory ([User ID], [His Date], [His Time], [History])  values( '" + id + "','" + date + "','" + time + "','User joined " + EventList->Text + ".')";
					command->ExecuteNonQuery();
					MessageBox::Show("Event Joined", "Event Joined");
					connection->Close();
				}
				catch (Exception^ er)
				{
					MessageBox::Show(er->ToString());
					MessageBox::Show("Error cannot join Event", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					connection->Close();
				}
			}
			
		}
}

System::Void CSITGroupAssignment::JoinEvent::MainMenu_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Close();
}
