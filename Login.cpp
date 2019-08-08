#include "Login.h"

System::Void CSITGroupAssignment::Login::button2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (MessageBox::Show("Do you really want to close the program?", "Are You Sure?", MessageBoxButtons::YesNo, MessageBoxIcon::Question) ==
		System::Windows::Forms::DialogResult::Yes)
	{
		Application::Exit();
	}
}

System::Void CSITGroupAssignment::Login::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (IDInput->Text == "" || PassInput->Text == "")
	{
		MessageBox::Show("Please enter ID and password!","Invalid Data", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
	else
	{
		bool login = false;
		try
		{
			String^ sqlstr = "SELECT * FROM [UserDatabase]";
			connection->Open();
			OleDbCommand ^ command = gcnew OleDbCommand(sqlstr, connection);
			OleDbDataReader^ reader = command->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
			while (reader->Read())
			{
				if (reader["User ID"]->ToString() == IDInput->Text && reader["Password"]->ToString() == PassInput->Text)
				{
					login = true;
					MMenu ^ menu = gcnew MMenu(reader["User ID"]->ToString(), reader["Username"]->ToString());
					reader->Close();
					command->Connection = connection;
					connection->Open();
					String ^ date = DateTime::Now.ToString("dd/MM/yy");
					String ^ time = DateTime::Now.ToString("HH:mm");
					command->CommandText = "insert into UserHistory ([User ID], [His Date], [His Time], [History])  values( '" + 
						IDInput->Text + "','" + date + "','" + time + "','User Login.')";
					command->ExecuteNonQuery();
					menu->Show();
					Hide();
					break;
				}
			}
			reader->Close();
			connection->Close();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->ToString());
			connection->Close();
		}
		if(!login)
			MessageBox::Show("Invalid User ID or Password","Login Error",MessageBoxButtons::OK,MessageBoxIcon::Error);
	}
	
}

System::Void CSITGroupAssignment::Login::Login_FormClosed(System::Object ^ sender, System::Windows::Forms::FormClosedEventArgs ^ e)
{
	Application::Exit();
}

System::Void CSITGroupAssignment::Login::CUser_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	CreateUser ^ createuser = gcnew CreateUser;
	createuser->ShowDialog();
}

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CSITGroupAssignment::Login mp;
	Application::Run(%mp);

}