#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Student
{
  string name;
  vector<string> subjects;

public:
  Student(string name);
  void addSubject(string subject);

  string getName() const;
  string getSubject(int i) const;
  int getNoofSubject() const;

  void PrintStudent();
  bool findSubject(string subject);
};