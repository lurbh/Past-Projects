#include "CreateUser.h"

System::Void CSITGroupAssignment::CreateUser::Back_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (MessageBox::Show("Do you really want to exit creating user ?", "Are You Sure?", MessageBoxButtons::YesNo, MessageBoxIcon::Question) ==
		System::Windows::Forms::DialogResult::Yes)
	{
		Close();
	}
}

System::Void CSITGroupAssignment::CreateUser::CUser_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (IDInput->Text == "")
		MessageBox::Show("No ID entered");
	else if (NameInput->Text == "")
		MessageBox::Show("No Username entered");
	else if (PassInput->Text == "")
		MessageBox::Show("No Password entered");
	else
	{
		try
		{
			connection->Open();
			OleDbCommand ^ command = gcnew OleDbCommand();
			command->Connection = connection;
			command->CommandText = "insert into UserDatabase ([User ID], [Username], [Password])  values( '" + 
				IDInput->Text + "','" + NameInput->Text + "','" + PassInput->Text + "')";
			command->ExecuteNonQuery();
			String ^ date = DateTime::Now.ToString("dd/MM/yy");
			String ^ time = DateTime::Now.ToString("HH:mm");
			command->CommandText = "insert into UserHistory ([User ID], [His Date], [His Time], [History])  values( '" + 
				IDInput->Text + "','" + date + "','" + time + "','User Created.')";
			command->ExecuteNonQuery();
			MessageBox::Show("User Created", "User Created");
			connection->Close();
			Close();
		}
		catch (Exception^ er)
		{
			MessageBox::Show(er->ToString());
			MessageBox::Show("Error cannot create User", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			connection->Close();
		}
	}
}
