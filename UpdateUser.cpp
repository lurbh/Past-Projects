#include "UpdateUser.h"

void CSITGroupAssignment::UpdateUser::LoadData()
{
	try
	{
		String^ sqlstr = "SELECT * FROM [UserDatabase]";
		connection->Open();
		OleDbCommand ^ command = gcnew OleDbCommand(sqlstr, connection);
		OleDbDataReader^ reader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
		while (reader->Read())
		{
			if (reader["User ID"]->ToString() == id)
			{
				IDInput->Text = reader["User ID"]->ToString();
				NameInput->Text = reader["Username"]->ToString();
				PassInput->Text = reader["Password"]->ToString();
				
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
}

System::Void CSITGroupAssignment::UpdateUser::UUser_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	try
	{
		connection->Open();
		String^ cmd = "UPDATE UserDatabase SET [User ID] = '" + IDInput->Text + "', [Username] = '" + NameInput->Text + "', [Password] = '" 
			+ PassInput->Text + "' WHERE [User ID] = '" + id + "'";
		OleDbCommand ^ command = gcnew OleDbCommand(cmd, connection);
		command->ExecuteNonQuery();
		command->CommandText = "UPDATE EventAttendees SET [User ID] = '" + IDInput->Text + "' WHERE [User ID] = '" + id + "'";
		command->ExecuteNonQuery();
		command->CommandText = "UPDATE UserHistory SET [User ID] = '" + IDInput->Text + "' WHERE [User ID] = '" + id + "'";
		command->ExecuteNonQuery();
		String ^ date = DateTime::Now.ToString("dd/MM/yy");
		String ^ time = DateTime::Now.ToString("HH:mm");
		command->CommandText = "insert into UserHistory ([User ID], [His Date], [His Time], [History])  values( '" + id + "','" + date + "','" + time + "','User Updated.')";
		command->ExecuteNonQuery();
		MessageBox::Show("User Updated", "User Updated");
		connection->Close();
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->ToString());
		connection->Close();
	}
}

System::Void CSITGroupAssignment::UpdateUser::Back_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Close();
}

System::Void CSITGroupAssignment::UpdateUser::UpdateUser_FormClosed(System::Object ^ sender, System::Windows::Forms::FormClosedEventArgs ^ e)
{

}
