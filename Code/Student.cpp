#include "Student.h"

Student::Student(string name)
  :name{name}
{

}

void Student::addSubject(string subject)
{
  subjects.push_back(subject);
}

string Student::getName() const
{
  return name;
}

string Student::getSubject(int i) const
{
  return subjects[i];
}

int Student::getNoofSubject() const
{
  return subjects.size();
}

bool Student::findSubject(string subject)
{
  for (string s : subjects)
  {
    if(s == subject)
      return true;
  }
  return false;
}

void Student::PrintStudent()
{
  cout << name << endl;
  for (string subject : subjects)
    cout << subject << endl;
}