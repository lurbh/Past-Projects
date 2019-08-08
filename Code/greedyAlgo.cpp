#include "greedyAlgo.h"

int main()
{
  vector <Student> studentlist;
  vector <string> subjectlist;
  // get file and store the data
  ReadAndProcessFile(studentlist,subjectlist);
  // sort the subjects
  sort(subjectlist.begin(),subjectlist.end());
  int size = (int)subjectlist.size();
  map <string,int> subjectlistindex;
  // create a map to link subject with a no
  for(int i = 0; i < size; i++)
    subjectlistindex.insert(pair<string,int>(subjectlist[i],i));
  AdjacencyMatrix adjMat(size);
  // go thtough students to create Adjacency Matrix
  for(auto s: studentlist)
  {
    int no = s.getNoofSubject();
    // loop for how many subjects a student has
    for(int i = 0; i < no; i++)
    {
      string subject = s.getSubject(i);
      int id = subjectlistindex.find(subject)->second;
      adjMat.add_edge(id,id);
      // form the connections
      for(int j = i + 1; j < no; j++)
      {
        string subject = s.getSubject(j);
        int id2 = subjectlistindex.find(subject)->second;
        adjMat.add_edge(id,id2);
        adjMat.add_edge(id2,id);
      }
    }
  }
  map <int,string> subjectlistindexr;
  // create a map to link no with a subject
  for(auto s: subjectlistindex)
  {
    subjectlistindexr.insert(pair<int,string>(s.second,s.first));
  }
  multimap <int,string> NCNodes;
  for(auto s: subjectlistindex)
  {
    int count = adjMat.checkline(s.second);
    NCNodes.insert(pair<int,string>(count,s.first));
  }
  vector<string> examinationslot;
  // loop till all subjects area given a slot
  while(!NCNodes.empty())
  {
    // get the subject with the highest number of inconnectivity
    string subject = NCNodes.rbegin()->second;
    examinationslot.push_back(subject);
    // erase the last object
    NCNodes.erase(--NCNodes.end());

    int id = subjectlistindex.find(subject)->second;
    int sub;
    bool check =  true;
    // check for a subject with no clashed with previous subject
    for(int i = 0; check; i++)
    {
      if(NCNodes.empty())
        check = false;
      sub = adjMat.getblank(id,i);
      // if no subject
      if(sub == 100)
      {
        break;
      }
      subject = subjectlistindexr.find(sub)->second;
      // check if the subject has not been given a slot 
      for(auto it = NCNodes.rbegin(); it != NCNodes.rend(); ++it)
        if(it->second == subject)
          check = false;
    }
    if(!NCNodes.empty())
      examinationslot.push_back(subject);
    // delete the subject that has been placed in
    for (auto it = NCNodes.begin(); it != NCNodes.end();)
    {
      // you have to do this because iterators are invalidated
      auto erase_it = it++;
      // removes all even values
      if (erase_it->second == subject)
        NCNodes.erase(erase_it);
    }
  }
  while(examinationslot.size() > subjectlistindexr.size())
    examinationslot.erase(examinationslot.begin());
  vector <string> Subjectstudent;
  vector <int> studentno;
  for(unsigned i = 0; i < examinationslot.size(); i++)
  {
    for(auto s: studentlist)
    {
      if(s.findSubject(examinationslot[i]))
        Subjectstudent.push_back(s.getName());
    }
    if(i % 2 == 1 || i == examinationslot.size() -1)
    {
      sort(Subjectstudent.begin(), Subjectstudent.end());
      Subjectstudent.erase(unique(Subjectstudent.begin(), Subjectstudent.end()),Subjectstudent.end());
      studentno.push_back(Subjectstudent.size());
      Subjectstudent.clear();
    }
  }
  // print out the slots
  for(unsigned i = 0; i < examinationslot.size(); i++)
  {
    if(i % 2 == 0)
      cout << "Slot " << i / 2 + 1 << ": ";
    cout << examinationslot[i];
    if(i % 2 == 0 && i != examinationslot.size() -1)
      cout << ", ";
    else if(i != examinationslot.size() -1)
      cout << "\t" << studentno[i/2] << endl;
    else 
      cout << string(examinationslot[i].length() + 2, ' ' ) << "\t" << studentno[i/2] << endl;
  }
}

void ReadAndProcessFile(vector<Student> &studentlist, vector<string> &subjectlist)
{
  string filename = GetFilename();
  ifstream myfile;
  myfile.open (filename.c_str());
  if(!myfile)
  {
    cerr << "Error opening : " << filename << endl << endl;
    myfile.close();
    ReadAndProcessFile(studentlist,subjectlist);
  }
  else
  {
    string line;
    getline(myfile, line);
    int no = stoi(line);
    for(int i = 0; i < no; i++)
      ReadStudent(myfile,studentlist,subjectlist);
    myfile.close();
  }
}

string GetFilename()
{
  string filename;
  bool input = true;
  do
  {
    cout << "Please enter a filename : ";
    cin >> filename;
    if(cin.good())
    {
      input = false;
    }
    else
    {
      cout << "Enter a valid filename." << endl << endl;
      cin.clear();
      cin.ignore(256,'\n');
    }
  }while(input);
  
  cout << endl;
  cin.clear();
  
  return filename;
}

void ReadStudent(ifstream &myfile,vector<Student> &studentlist, vector<string> &subjectlist)
{
  string line, name;
  int pos, no;
  getline(myfile, line);
  pos = line.find_first_of(",");
  name = line.substr(0,pos);
  no = stoi(line.substr(pos+2));
  pos = studentlist.size();
  studentlist.push_back(Student{name});
  for(int i = 0; i < no; i++)
  {
    getline(myfile, line);
    line.pop_back();
    studentlist[pos].addSubject(line);
    bool inlist = false;
    for (string subject :subjectlist)
      if(subject == line)
        inlist = true;
    if(!inlist)
      subjectlist.push_back(line);
  }
}
