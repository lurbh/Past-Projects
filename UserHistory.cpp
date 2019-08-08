#include "UserHistory.h"

void CSITGroupAssignment::UserHistory::LoadData()
{
	try
	{
		String^ sqlstr = "SELECT * FROM [UserHistory]";
		connection->Open();
		OleDbCommand ^ command = gcnew OleDbCommand(sqlstr, connection);
		OleDbDataReader^ reader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
		while (reader->Read())
		{
			if (reader["User ID"]->ToString() == id)
			{
				String ^ details = reader["User ID"]->ToString() + "        | " + reader["His Date"]->ToString() + "    | " + reader["His Time"]->ToString() + "    | " + reader["History"]->ToString();
				this->HistoryDetails->Items->Add(details);
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

System::Void CSITGroupAssignment::UserHistory::ExitBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Close();
}
