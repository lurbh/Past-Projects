#include "MMenu.h"

System::Void CSITGroupAssignment::MMenu::button9_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (MessageBox::Show("Do you really want to log out?", "Are You Sure?", MessageBoxButtons::YesNo, MessageBoxIcon::Question) ==
		System::Windows::Forms::DialogResult::Yes)
	{
		Close();
	}
}

System::Void CSITGroupAssignment::MMenu::button8_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (MessageBox::Show("Do you really want to close the program?", "Are You Sure?", MessageBoxButtons::YesNo, MessageBoxIcon::Question) ==
		System::Windows::Forms::DialogResult::Yes)
	{
		Close();
		Application::Exit();
	}
}

System::Void CSITGroupAssignment::MMenu::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//MessageBox::Show("Option2");
	ModEvent ^ op2 = gcnew ModEvent(id);
	op2->ShowDialog();
}

System::Void CSITGroupAssignment::MMenu::button2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//MessageBox::Show("Option1");
	CSITGroupAssignment::CreateEvent^ op1 = gcnew CSITGroupAssignment::CreateEvent(id);
	op1->ShowDialog();
}

System::Void CSITGroupAssignment::MMenu::button3_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//MessageBox::Show("Option3");
	CSITGroupAssignment::ViewEvent^ op3 = gcnew CSITGroupAssignment::ViewEvent;
	op3->ShowDialog();
}

System::Void CSITGroupAssignment::MMenu::button4_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//MessageBox::Show("Option4");
	CSITGroupAssignment::DelEvent^ op4 = gcnew CSITGroupAssignment::DelEvent(id);
	op4->ShowDialog();
}

System::Void CSITGroupAssignment::MMenu::button5_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//MessageBox::Show("Option5");
	CSITGroupAssignment::JoinEvent^ op5 = gcnew CSITGroupAssignment::JoinEvent(id,name);
	op5->ShowDialog();
}

System::Void CSITGroupAssignment::MMenu::button7_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//MessageBox::Show("Option6");
	CSITGroupAssignment::ViewAttendees^ op7 = gcnew CSITGroupAssignment::ViewAttendees;
	op7->ShowDialog();
	
}

System::Void CSITGroupAssignment::MMenu::button6_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	CSITGroupAssignment::ExitEvent^ op6 = gcnew CSITGroupAssignment::ExitEvent(id, name);
	op6->ShowDialog();
}

System::Void CSITGroupAssignment::MMenu::MMenu_FormClosed(System::Object ^ sender, System::Windows::Forms::FormClosedEventArgs ^ e)
{
	//Application::Restart();
	Login^ login = gcnew Login;
	login->Show();
	connection->Open();
	OleDbCommand ^ command = gcnew OleDbCommand();
	command->Connection = connection;
	String ^ date = DateTime::Now.ToString("dd/MM/yy");
	String ^ time = DateTime::Now.ToString("HH:mm");
	command->CommandText = "insert into UserHistory ([User ID], [His Date], [His Time], [History])  values( '" + id + "','" + date + "','" + time + "','User Logout.')";
	command->ExecuteNonQuery();
	connection->Close();
}

System::Void CSITGroupAssignment::MMenu::Account_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Account^ act = gcnew Account(id, name);
	act->ShowDialog();
}

System::Void CSITGroupAssignment::MMenu::EventJoined_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	UserAttend ^ attend = gcnew UserAttend(id, name);
	attend->ShowDialog();
}

