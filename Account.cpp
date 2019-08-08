#include "Account.h"

System::Void CSITGroupAssignment::Account::ExitBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Close();
}

System::Void CSITGroupAssignment::Account::Update_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	UpdateUser^ upuser = gcnew UpdateUser(id, name);
	upuser->ShowDialog();
	change = true;
}

System::Void CSITGroupAssignment::Account::History_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	UserHistory^ userhistory = gcnew UserHistory(id, name);
	userhistory->ShowDialog();
}

System::Void CSITGroupAssignment::Account::Account_FormClosed(System::Object ^ sender, System::Windows::Forms::FormClosedEventArgs ^ e)
{
	if (change)
	{
		MessageBox::Show("User Details modified. Log in again to continue");
		connection->Open();
		OleDbCommand ^ command = gcnew OleDbCommand();
		command->Connection = connection;
		String ^ date = DateTime::Now.ToString("d", CultureInfo::CreateSpecificCulture("fr-FR"));
		String ^ time = DateTime::Now.ToString("t", CultureInfo::CreateSpecificCulture("hr-HR"));
		command->CommandText = "insert into UserHistory ([User ID], [His Date], [His Time], [History])  values( '" + id + "','" + date + "','" + time + "','User Logout.')";
		command->ExecuteNonQuery();
		connection->Close();
		Application::Restart();
	}
		
}
