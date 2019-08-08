#include "UserAttend.h"

void CSITGroupAssignment::UserAttend::UpdateList()
{
	try
	{
		DataList->Items->Clear();
		String^ sqlstr = "SELECT * FROM [EventAttendees]";
		connection->Open();
		OleDbCommand ^ command = gcnew OleDbCommand(sqlstr, connection);
		OleDbDataReader^ reader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
		while (reader->Read())
		{
			if (reader["User ID"]->ToString() == id)
			{
				String ^ detail = "Event Name : " + reader["Event Name"];
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

System::Void CSITGroupAssignment::UserAttend::MMenu_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Close();
}
