#include "driver.h"

int main()
{
  int choice;
  bool quit;
  vector<Point2D*> P2D;
  vector<Point3D*> P3D;
  vector<Line2D*> L2D;
  vector<Line3D*> L3D;
  // States the hold the current filtering and sorting type
  filtertype ft = POINT2D;
  Ptfilter fpt = XVALUE;
  filterLine fl = POINT1;
  bool sort = true;
  do
  {
    printmenu(ft,fpt,fl,sort);
    choice = GetChoice();
    quit = HandleChoice(P2D,P3D,L2D,L3D,ft,fpt,fl,sort,choice);
  }while(!quit);
  // clear memory
  for( auto it : P2D)
    delete it;
  for( auto it : P3D)
    delete it;
  for( auto it : L2D)
    delete it;
  for( auto it : L3D)
    delete it;
}

// function that prints the main menu
void printmenu(filtertype ft, Ptfilter fpt, filterLine fl, bool sort)
{
  cout << "Student ID       : 6232748" << endl;
  cout << "Student Name     : Lur Bing Huii" << endl;
  cout << "-------------------------------------" << endl;
  cout << "Welcome to Assn3 program!" << endl;
  cout << endl;
  cout << " 1)      Read in Data" << endl;
  cout << " 2)      Specify Filtering Criteria (current: " << StringFilterType(ft) << ")" << endl;
  cout << " 3)      Specify Sorting Criteria (current : " << StringFilterType(ft,fpt,fl) << ")" << endl;
  cout << " 4)      Specify Sorting Order (current : " << StringSortOrder (sort) << ")" << endl;
  cout << " 5)      View Data" << endl;
  cout << " 6)      Store Data" << endl;
  cout << " 7)      Delete Data" << endl;
  cout << " 8)      Exit Program" << endl << endl;
}

// Function the gets user the enter a choice
int GetChoice()
{
  int choice;
  bool input = true;
  do
  {
    cout << "Please enter your choice : ";
    cin >> choice;
    if(cin.good())
    {
      // if value is out of bounds
      if(choice < 1 || choice > 8)
      {
        cout << "Enter a value between 1-8. " << endl;
      }
      else
      {
        input = false;
      }
    }
    // if value is not a integer
    else
    {
      cout << "Not an integer." << endl << endl;
      cin.clear();
      cin.ignore(256,'\n');
    }
  }while(input);
  
  cout << endl;
  cin.clear();
  
  return choice;
}

// function that takes in the state and return a certain string
string StringFilterType(filtertype ft)
{
  string s;
  switch(ft)
  {
    case POINT2D:
      s = "Point2D";
      break;
    case POINT3D:
      s = "Point3D";
      break;
    case LINE2D:
      s = "Line2D";
      break;
    case LINE3D:
      s = "Line3D";
      break;
    default:
        break;
  }
  return s;
}

// function that takes in the state and return a certain string
string StringFilterType(filtertype ft,Ptfilter fpt,filterLine fl)
{
  string s;
  switch(ft)
  {
    case POINT2D:
    case POINT3D:
      switch(fpt)
      {
        case XVALUE:
          s = "x-ordinate";
          break;
        case YVALUE:
          s = "y-ordinate";
          break;
        case ZVALUE:
          s = "z-ordinate";
          break;
        case DIST:
          s = "distFrOrigin";
          break;

      }
      break;
    case LINE2D:
    case LINE3D:
      switch(fl)
      {
        case POINT1:
          s = "Pt. 1";
          break;
        case POINT2:
          s = "Pt. 2";
          break;
        case LENGTH:
          s = "Length";
          break;
      }
      break;
    default:
        break;
  }
  return s;
}

// function that takes in the state and return a certain string
string StringSortOrder(bool sort)
{
  if(sort)
    return "ASC";
  else
    return "DSC";
}

// function the handles the user choice
bool HandleChoice(vector<Point2D*>& P2D,vector<Point3D*>& P3D,vector<Line2D*>& L2D,vector<Line3D*>& L3D,
  filtertype& ft,Ptfilter& fpt,filterLine& fl,bool& sort,int choice)
{
  bool quit = false; 
  char c ;
  switch(choice)
  {
    case 1:
    {
      ReadInData(P2D,P3D,L2D,L3D);
      unsigned no = P2D.size() + P3D.size() + L2D.size() + L3D.size();
      cout << no << " records read in successfully!" << endl << endl;
      cout << "Going back to main menu …" << endl << endl;
      break;
    }
    case 2:
    {
      cout << "[ Specifying Filtering Criteria (current : " << StringFilterType(ft) << ") ]" << endl << endl;
      DisplayFliterMenu();
      c = GetFliterChoice();
      ft = HandleFliterChoice(c);
      SetSort(ft,fpt,fl);
      cout << "Filter Criteria successfully set to '" << StringFilterType(ft) << "'!" << endl << endl;
      break;
    }
    case 3:
    {
      cout << "[ Specifying Sorting Criteria (current : " << StringFilterType(ft,fpt,fl) << ") ]" << endl << endl;
      DisplaySortMenu(ft);
      c = GetSortChoice(ft);
      HandleSortChoice(c,ft,fpt,fl);
      cout << "Sorting Criteria successfully set to '" << StringFilterType(ft,fpt,fl) << "'!" << endl << endl;
      break;
    }
    case 4:
    {
      cout << "[ Specifying Sorting Order (current : " << StringSortOrder (sort) << ") ]" << endl << endl;
      DisplaySortOrderMenu();
      c = GetSortOrderChoice();
      sort = HandleSortOrderChoice(c);
      cout << "Sorting Order successfully set to '" << StringSortOrder (sort) << "'!" << endl << endl;;
      break;
    }
    case 5:
    {
      cout << "[ View data … ]" << endl;
      cout << "Filtering Criteria : " << StringFilterType(ft) << endl;
      cout << "Sorting Criteria : " <<  StringFilterType(ft,fpt,fl) << endl;
      cout << "Sorting Order : " << StringSortOrder (sort) << endl << endl;
      switch(ft)
      {
        case POINT2D:
          SortData(P2D,fpt,sort);
          PrintData(P2D);
          break;
        case POINT3D:
          SortData(P3D,fpt,sort);
          PrintData(P3D);
          break;
        case LINE2D:
          SortData(L2D,fl,sort);
          PrintData(L2D);
          break;
        case LINE3D:
          SortData(L3D,fl,sort);
          PrintData(L3D);
          break;
        default:
          break;
      }
      cout << endl;
      pressKey();
      break;
    }
    case 6:
    {
      string filename = GetFilename();
      switch(ft)
      {
        case POINT2D:
          SortData(P2D,fpt,sort);
          StoreData(P2D,filename);
          cout << P2D.size() << " records output successfully!" << endl;
          break;
        case POINT3D:
          SortData(P3D,fpt,sort);
          StoreData(P3D,filename);
          cout << P3D.size() << " records output successfully!" << endl;
          break;
        case LINE2D:
          SortData(L2D,fl,sort);
          StoreData(L2D,filename);
          cout << L2D.size() << " records output successfully!" << endl;
          break;
        case LINE3D:
          SortData(L3D,fl,sort);
          StoreData(L3D,filename);
          cout << L3D.size() << " records output successfully!" << endl;
          break;
        default:
          break;
      }
      cout << "Going back to main menu …" << endl << endl;
      break;
    }
    case 7:
    {
      cout << "[ Deleting data … ]" << endl;
      DeleteData(P2D,P3D,L2D,L3D);
      cout << endl;
      break;
    }
    case 8:
    {
      quit = true;
      break;
    }
  }
  return quit;
}

// Function that displays the fliter menu
void DisplayFliterMenu()
{
  cout << "    a)        Point2D records" << endl;
  cout << "    b)        Point3D records" << endl;
  cout << "    c)        Line2D records" << endl;
  cout << "    d)        Line3D records" << endl;
}

// Function that get user to enter a choice for filtering
char GetFliterChoice()
{
  char choice;
  bool input = true;
  do
  {
    cout << "Please enter your criteria (a – d) : ";
    cin >> choice;
    if(cin.good())
    {
      // if value is out of bounds
      if(choice <= 'd' && choice >= 'a')
        input = false;
      else
        cout << "Enter a valid Character " << endl;
    }
    // if value is not a char
    else
    {
      cout << "Not an Character." << endl << endl;
      cin.clear();
      cin.ignore(256,'\n');
    }
  }while(input);
  
  cout << endl;
  cin.clear();
  
  return choice;
}

// function the handles the user choice for filtering
filtertype HandleFliterChoice(char c)
{
  switch(c)
  {
    case 'a':
      return POINT2D;
    case 'b':
      return POINT3D;
    case 'c':
      return LINE2D;
    case 'd':
      return LINE3D;
  }
  return POINT2D;
}

// Function that display the sorting menu
void DisplaySortMenu(filtertype ft)
{
  switch(ft)
  {
    case POINT2D:
      cout << "    a)        x-ordinate value" << endl;
      cout << "    b)        y-ordinate value" << endl;
      cout << "    c)        Distance value" << endl;
      break;
    case POINT3D:
      cout << "    a)        x-ordinate value" << endl;
      cout << "    b)        y-ordinate value" << endl;
      cout << "    c)        z-ordinate value" << endl;
      cout << "    d)        Distance value" << endl;
      break;
    case LINE2D:
    case LINE3D:
      cout << "    a)        Pt. 1’s (x, y) values" << endl;
      cout << "    b)        Pt. 2’s (x, y) values" << endl;
      cout << "    c)        Length value" << endl;
      break;
    default:
      break;
  }
}

// Function that gets the user to enter the sorting choice
char GetSortChoice(filtertype ft)
{
  char choice;
  bool input = true;
  do
  {
    switch(ft)
    {
      case POINT2D:
      case LINE2D:
      case LINE3D:
        cout << "Please enter your criteria (a – c) : ";
        break;
      case POINT3D:
        cout << "Please enter your criteria (a – d) : ";
        break;
      default:
        break;
    }
    cin >> choice;
    if(cin.good())
    {
      switch(ft)
      {
        case POINT2D:
        case LINE2D:
        case LINE3D:
          // if value is out of bounds
          if(choice <= 'c' && choice >= 'a')
            input = false;
          else
            cout << "Enter a valid Character " << endl;
          break;
        case POINT3D:
          // if value is out of bounds
          if(choice <= 'd' && choice >= 'a')
            input = false;
          else
            cout << "Enter a valid Character " << endl;
          break;
        default:
          break;
      }
    }
    // if value is not a char
    else
    {
      cout << "Not an Character." << endl << endl;
      cin.clear();
      cin.ignore(256,'\n');
    }
  }while(input);
  
  cout << endl;
  cin.clear();
  
  return choice;
}

// Function that handles the sorting choice
void HandleSortChoice(char c, filtertype ft,Ptfilter& fpt,filterLine& fl)
{
  switch(ft)
  {
    case POINT2D:
      switch(c)
      {
        case 'a':
          fpt = XVALUE;
          break;
        case 'b':
          fpt = YVALUE;
          break;
        case 'c':
          fpt = DIST;
          break;
      }
      break;
    case POINT3D:
      switch(c)
      {
        case 'a':
          fpt = XVALUE;
          break;
        case 'b':
          fpt = YVALUE;
          break;
        case 'c':
          fpt = ZVALUE;
          break;
        case 'd':
          fpt = DIST;
          break;
      }
      break;
    case LINE2D:
    case LINE3D:
      switch(c)
      {
        case 'a':
          fl = POINT1;
          break;
        case 'b':
          fl = POINT2;
          break;
        case 'c':
          fl = LENGTH;
          break;
      }
      break;
    default:
        break;
  }
}

//  Function that set the sorting choice
void SetSort(filtertype ft,Ptfilter& fpt,filterLine& fl)
{
  switch(ft)
  {
    case POINT2D:
      fpt = XVALUE;
      break;
    case POINT3D:
      fpt = XVALUE;
      break;
    case LINE2D:
      fl = POINT1;
      break;
    case LINE3D:
      fl = POINT1;
      break;
    default:
        break;
  }
}

// Function the prints the sorting order menu
void DisplaySortOrderMenu()
{
  cout << "    a)        ASC (Ascending order)" << endl;
  cout << "    b)        DSC (Descending order)" << endl;
}

// Function that gets user to enter sorting order choice
char GetSortOrderChoice()
{
  char choice;
  bool input = true;
  do
  {
    cout << "Please enter your criteria (a – b) : ";
    cin >> choice;
    if(cin.good())
    {
      // if value is out of bounds
      if(choice <= 'b' && choice >= 'a')
        input = false;
      else
        cout << "Enter a valid Character " << endl;
    }
    // if value is not a char
    else
    {
      cout << "Not an Character." << endl << endl;
      cin.clear();
      cin.ignore(256,'\n');
    }
  }while(input);
  
  cout << endl;
  cin.clear();
  
  return choice;
}

// Function that handles the user sorting order choice
bool HandleSortOrderChoice(char c)
{
  switch(c)
  {
    case 'a':
      return true;
    case 'b':
      return false;
  }
  return true;
}

// function that gets the user to enter a filename
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

// Function that handles the reading in of data from a file
void ReadInData(vector<Point2D*>& P2D,vector<Point3D*>& P3D,vector<Line2D*>& L2D,vector<Line3D*>& L3D)
{
  string filename = GetFilename();
  ifstream myfile;
  myfile.open (filename.c_str());
  // if file cannot be open
  if(!myfile)
  {
    cerr << "Error opening : " << filename << endl << endl;
    myfile.close();
    ReadInData(P2D,P3D,L2D,L3D);
    return;
  }
  // while not at the end of the file
  while(!myfile.eof())
  {
    string line, data;
    int pos1;
    getline(myfile, line);
    // get the object type
    pos1 = line.find_first_of(",");
    data = line.substr(0,pos1);
    filtertype ft = CheckDataType(data);
    // switch based on the type of object read
    switch(ft)
    {
      case POINT2D:
        HandleP2DData(P2D,line);
        break;
      case POINT3D:
        HandleP3DData(P3D,line);
        break;
      case LINE2D:
        HandleL2DData(L2D,line);
        break;
      case LINE3D:
        HandleL3DData(L3D,line);
        break;
      default:
        break;
    }
  }
  myfile.close();
}

// Get filter type from the string
filtertype CheckDataType(string data)
{
  if(data.compare("Point2D") == 0)
    return POINT2D;
  else if(data.compare("Point3D") == 0)
    return POINT3D;
  else if (data.compare("Line2D") == 0)
    return LINE2D;
  else if (data.compare("Line3D") == 0)
    return LINE3D;
  return NIL;
}

// function that reads the data if the obj is a Point2D
void HandleP2DData(vector<Point2D*>& P2D,string line)
{
  string data;
  int pos1,pos2,x,y;
  pos1 = line.find_first_of("[");
  pos2 = line.find_first_of("]") + 1;
  // get the string between []
  data = line.substr(pos1, pos2 - pos1);
  pos1 = data.find_first_of("[") + 1;
  pos2 = data.find_first_of(",");
  // get x value
  x = stoi(data.substr(pos1, pos2 - pos1));
  pos1 = data.find_first_of(",") + 2;
  pos2 = data.find_first_of("]");
  // get y value
  y = stoi(data.substr(pos1, pos2 - pos1));
  Point2D newpt{x,y};
  // check if duplicate
  for(auto it : P2D)
    if (*it == Point2D{x,y}) // it->operator==(newpt)
    {
      return;
    }
  // create and push back the Point2D
  P2D.push_back(new Point2D{x,y});
}

// function that reads the data if the obj is a Point3D
void HandleP3DData(vector<Point3D*>& P3D,string line)
{
  string data;
  int pos1,pos2,x,y,z;
  // get the string between []
  pos1 = line.find_first_of("[");
  pos2 = line.find_first_of("]") + 1;
  data = line.substr(pos1, pos2 - pos1);
  pos1 = data.find_first_of("[") + 1;
  pos2 = data.find_first_of(",");
  // get the x value
  x = stoi(data.substr(pos1, pos2 - pos1));
  pos1 = data.find_first_of(",") + 2;
  pos2 = data.find_last_of(",");
  // get the y value
  y = stoi(data.substr(pos1, pos2 - pos1));
  pos1 = data.find_last_of(",") + 2;
  pos2 = data.find_last_of("]");
  // get the z value
  z = stoi(data.substr(pos1, pos2 - pos1));
  Point3D newpt{x,y,z};
  // check if duplicate
  for(auto it : P3D)
    if (*it == newpt)
    {
      return;
    }
  // create and push back the Point3D
  P3D.push_back(new Point3D{x,y,z});
}

// function that reads the data if the obj is a Line2D
void HandleL2DData(vector<Line2D*>& L2D,string line)
{
  string data;
  int pos1,pos2,x,y;
  // get the string between [] for first point
  pos1 = line.find_first_of("[");
  pos2 = line.find_first_of("]") + 1;
  data = line.substr(pos1, pos2 - pos1);
  pos1 = data.find_first_of("[") + 1;
  pos2 = data.find_first_of(",");
  // get the x value
  x = stoi(data.substr(pos1, pos2 - pos1));
  pos1 = data.find_first_of(",") + 2;
  pos2 = data.find_first_of("]");
  // get the y value
  y = stoi(data.substr(pos1, pos2 - pos1));
  // create the point
  Point2D pt1{x,y};
  // get the string between [] for second point
  pos1 = line.find_last_of("[");
  pos2 = line.find_last_of("]") + 1;
  data = line.substr(pos1, pos2 - pos1);
  pos1 = data.find_first_of("[") + 1;
  pos2 = data.find_first_of(",");
  // get the x value
  x = stoi(data.substr(pos1, pos2 - pos1));
  pos1 = data.find_first_of(",") + 2;
  pos2 = data.find_first_of("]");
  // get the y value
  y = stoi(data.substr(pos1, pos2 - pos1));
  // create the point
  Point2D pt2{x,y};
  Line2D newln{pt1,pt2};
  // check for dupcliate
  for(auto it : L2D)
    if (*it == newln)
    {
      return;
    }
  // create and push back the Line2D
  L2D.push_back(new Line2D{pt1,pt2});
}

// function that reads the data if the obj is a Line3D
void HandleL3DData(vector<Line3D*>& L3D,string line)
{
  string data;
  int pos1,pos2,x,y,z;
  // get the string between [] for first point
  pos1 = line.find_first_of("[");
  pos2 = line.find_first_of("]") + 1;
  data = line.substr(pos1, pos2 - pos1);
  pos1 = data.find_first_of("[") + 1;
  pos2 = data.find_first_of(",");
  // get x value
  x = stoi(data.substr(pos1, pos2 - pos1));
  pos1 = data.find_first_of(",") + 2;
  pos2 = data.find_last_of(",");
  // get y value
  y = stoi(data.substr(pos1, pos2 - pos1));
  pos1 = data.find_last_of(",") + 2;
  pos2 = data.find_last_of("]");
  // get z value
  z = stoi(data.substr(pos1, pos2 - pos1));
  // create point
  Point3D pt1{x,y,z};
  // get the string between [] for second point
  pos1 = line.find_last_of("[");
  pos2 = line.find_last_of("]") + 1;
  data = line.substr(pos1, pos2 - pos1);
  pos1 = data.find_first_of("[") + 1;
  pos2 = data.find_first_of(",");
  // get x value
  x = stoi(data.substr(pos1, pos2 - pos1));
  pos1 = data.find_first_of(",") + 2;
  pos2 = data.find_last_of(",");
  // get y value
  y = stoi(data.substr(pos1, pos2 - pos1));
  pos1 = data.find_last_of(",") + 2;
  pos2 = data.find_last_of("]");
  // get z value
  z = stoi(data.substr(pos1, pos2 - pos1));
  // create point
  Point3D pt2{x,y,z};
  Line3D newln{pt1,pt2};
  // check for dupcliate
  for(auto it : L3D)
    if (*it == Line3D{pt1,pt2})
    {
      return;
    }
  // create and push back the Line3D
  L3D.push_back(new Line3D{pt1,pt2});
}

// function that handles the sorting of Point2D by x value
bool Point2DSortA (Point2D* pt1 , Point2D* pt2)
{
  if(pt1->getX() == pt2->getX())
    return pt1->getY() < pt2->getY();
  else
    return pt1->getX() < pt2->getX();
}

// function that handles the sorting of Point3D by x value
bool Point3DSortA(Point3D* pt1 , Point3D* pt2)
{
  if(pt1->getX() == pt2->getX())
    if (pt1->getY() == pt2->getY())
      return pt1->getZ() < pt2->getZ();
    else
      return pt1->getY() < pt2->getY();
  else
    return pt1->getX() < pt2->getX();
}

// function that handles the sorting of Point2D by y value
bool Point2DSortB (Point2D* pt1 , Point2D* pt2)
{
  if(pt1->getY() == pt2->getY())
    return pt1->getX() < pt2->getX();
  else
    return pt1->getY() < pt2->getY();
}

// function that handles the sorting of Point3D by y value
bool Point3DSortB(Point3D* pt1 , Point3D* pt2)
{
  if(pt1->getY() == pt2->getY())
    if (pt1->getZ() == pt2->getZ())
      return pt1->getX() < pt2->getX();
    else
      return pt1->getZ() < pt2->getZ();
  else
    return pt1->getY() < pt2->getY();
}

// function template that handles the sorting of all types by scalar value
template <typename T>
bool SortC (T* obj1 , T* obj2)
{
  return (obj1->getScalarValue() < obj2->getScalarValue());
}

// function that handles the sorting of Point3D by z value
bool PointSortD (Point3D* pt1 , Point3D* pt2)
{
  if(pt1->getZ() == pt2->getZ())
    if (pt1->getX() == pt2->getX())
      return pt1->getY() < pt2->getY();
    else
      return pt1->getX() < pt2->getX();
  else
    return pt1->getZ() < pt2->getZ();
}

// function template that handles the sorting of all Lines by point 1
template <typename T>
bool LineSortA (T* l1 , T* l2)
{
  if(l1->getPt1() == l2->getPt1())
    return (l1->getPt2() < l2->getPt2());
  else
    return (l1->getPt1() < l2->getPt1());
}

// function template that handles the sorting of all Lines by point 2
template <typename T>
bool LineSortB (T* l1 , T* l2)
{
  if(l1->getPt2() == l2->getPt2())
    return (l1->getPt1() < l2->getPt1());
  else
    return (l1->getPt2() < l2->getPt2());
}

// Function that get user the press enter to continue
void pressKey()
{
  cout << "Press Enter key to go back to the main menu ...";
  cin.get();
  cin.get();
  cin.clear();
  cout << endl;
}

// Function that prints the data for Point2D
void PrintData(vector<Point2D*>& P2D)
{
  cout << right << setw(5) << "X" << right << setw(6) << "Y" << "    Dist. Fr Origin" << endl;
  cout << "- - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
  for(auto pt : P2D)
    cout << *pt << endl;
}

// Function that prints the data for Point3D
void PrintData(vector<Point3D*>& P3D)
{
  cout << right << setw(5) << "X" << right << setw(6) << "Y" << right << setw(6) << "Z" << "    Dist. Fr Origin" << endl;
  cout << "- - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
  for(auto pt : P3D)
    cout << *pt << endl;
}

// Function that prints the data for Line2D
void PrintData(vector<Line2D*>& L2D)
{
  cout << right << setw(5) << "P1-X" << right << setw(6) << "P1-Y";
  cout << right << setw(9) << "P2-X" << right << setw(6) << "P2-Y";
  cout << "    Length" << endl;
  cout << "- - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
  for(auto ln : L2D)
    cout << *ln << endl;
}

// Function that prints the data for Line3D
void PrintData(vector<Line3D*>& L3D)
{
  cout << right << setw(5) << "P1-X" << right << setw(6) << "P1-Y" << right << setw(6) << "P1-Z"; 
  cout << right << setw(9) << "P2-X" << right << setw(6) << "P2-Y" << right << setw(6) << "P2-Z";
  cout << "    Length" << endl;
  cout << "- - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
  for(auto ln : L3D)
    cout << *ln << endl;
}

// function template that handles sorting for all lines
template <typename T>
void SortData(vector<T*>& vec,filterLine fl,bool sortACD)
{
  switch(fl)
  {
    case POINT1:
      sort( vec.begin(), vec.end(),LineSortA<T>);
      break;
    case POINT2:
      sort( vec.begin(), vec.end(),LineSortB<T>);
      break;
    case LENGTH:
      sort( vec.begin(), vec.end(),SortC<T>);
      break;
  }
  if(!sortACD)
    reverse( vec.begin() , vec.end());
}

// function that handles the sorting for Point2D
void SortData(vector<Point2D*>& P2D,Ptfilter fpt,bool sortACD)
{
  switch(fpt)
  {
    case XVALUE:
      sort( P2D.begin(), P2D.end(),Point2DSortA);
      break;
    case YVALUE:
      sort( P2D.begin(), P2D.end(),Point2DSortB);
      break;
    case DIST:
      sort( P2D.begin(), P2D.end(),SortC<Point2D>);
      break;
    default:
      break;
  }
  if(!sortACD)
    reverse( P2D.begin() , P2D.end());
}

// function that handles the sorting for Point3D
void SortData(vector<Point3D*>& P3D,Ptfilter fpt,bool sortACD)
{
  switch(fpt)
  {
    case XVALUE:
      sort( P3D.begin(), P3D.end(),Point3DSortA);
      break;
    case YVALUE:
      sort( P3D.begin(), P3D.end(),Point3DSortB);
      break;
    case ZVALUE:
      sort( P3D.begin(), P3D.end(),PointSortD);
      break; 
    case DIST:
      sort( P3D.begin(), P3D.end(),SortC<Point3D>);
      break;
  }
  if(!sortACD)
    reverse( P3D.begin() , P3D.end());
}

// Function that stores the data for Point2D
void StoreData(vector<Point2D*>& P2D,string filename)
{
  ofstream myfile;
  myfile.open (filename.c_str());
  myfile << right << setw(5) << "X" << right << setw(6) << "Y" << "    Dist. Fr Origin" << endl;
  myfile << "- - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
  for(auto pt : P2D)
    myfile << *pt << endl;
  myfile.close();
}

// Function that prints the data for Point3D
void StoreData(vector<Point3D*>& P3D,string filename)
{
  ofstream myfile;
  myfile.open (filename.c_str());
  myfile << right << setw(5) << "X" << right << setw(6) << "Y" << right << setw(6) << "Z" << "    Dist. Fr Origin" << endl;
  myfile << "- - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
  for(auto pt : P3D)
    myfile << *pt << endl;
  myfile.close();
}

// Function that prints the data for Line2D
void StoreData(vector<Line2D*>& L2D,string filename)
{
  ofstream myfile;
  myfile.open (filename.c_str());
  myfile << right << setw(5) << "P1-X" << right << setw(6) << "P1-Y";
  myfile << right << setw(9) << "P2-X" << right << setw(6) << "P2-Y";
  myfile << "    Length" << endl;
  myfile << "- - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
  for(auto ln : L2D)
    myfile << *ln << endl;
  myfile.close();
}

// Function that prints the data for Line3D
void StoreData(vector<Line3D*>& L3D,string filename)
{
  ofstream myfile;
  myfile.open (filename.c_str());
  myfile << right << setw(5) << "P1-X" << right << setw(6) << "P1-Y" << right << setw(6) << "P1-Z"; 
  myfile << right << setw(9) << "P2-X" << right << setw(6) << "P2-Y" << right << setw(6) << "P2-Z";
  myfile << "    Length" << endl;
  myfile << "- - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
  for(auto ln : L3D)
    myfile << *ln << endl;
  myfile.close();
}

// Function that handles the deletion of data
void DeleteData(vector<Point2D*>& P2D,vector<Point3D*>& P3D,vector<Line2D*>& L2D,vector<Line3D*>& L3D)
{
  filtertype ft = GetDataType();
  switch(ft)
    {
      case POINT2D:
        DeleteP2DData(P2D);
        break;
      case POINT3D:
        DeleteP3DData(P3D);
        break;
      case LINE2D:
        DeleteL2DData(L2D);
        break;
      case LINE3D:
        DeleteL3DData(L3D);
        break;
      default:
        break;
    }
}

// Function the gets user to input a data type
filtertype GetDataType()
{
  string input;
  cout << "Enter Data type to delete: ";
  cin >> input;
  WordFormat(input);
  filtertype ft = CheckDataType(input);
  // check input if valid
  if(ft != NIL)
  {
    return ft;
  }
  else
    ft = GetDataType();
  return ft;
}

// function that deletes a given Point2D
void DeleteP2DData(vector<Point2D*>& P2D)
{
  Point2D point = EnterP2DData();
  if(CheckData(P2D,point))
  {
    for( auto it = P2D.begin(); it != P2D.end();++it)
      if(**it == point)
      {
        delete (*it);
        P2D.erase(it);
        break;
      }
    cout << "Point2D [" << point.getX() << ", " << point.getY() << "] Deleted" <<endl;
  }
  else
  {
    cout << "No Point with that values. Please enter again." << endl << endl;
    DeleteP2DData(P2D);
  }
}

// function that deletes a given Point3D
void DeleteP3DData(vector<Point3D*>& P3D)
{
  Point3D point = EnterP3DData();
  if(CheckData(P3D,point))
  {
    for( auto it = P3D.begin(); it != P3D.end();++it)
      if(**it == point)
      {
        delete (*it);
        P3D.erase(it);
        break;
      }
    cout << "Point3D [" << point.getX() << ", " << point.getY() << ", " << point.getZ() << "] Deleted" <<endl;
  }
  else
  {
    cout << "No Point with that values. Please enter again." << endl << endl;
    DeleteP3DData(P3D);
  }
}

// function that deletes a given Line2D
void DeleteL2DData(vector<Line2D*>& L2D)
{
  Line2D line = EnterL2DData();
  if(CheckData(L2D,line))
  {
    for( auto it = L2D.begin(); it != L2D.end();++it)
      if(**it == line)
      {
        delete (*it);
        L2D.erase(it);
        break;
      }
    cout << "Line2D [" << line.getPt1().getX() << ", " << line.getPt1().getY() << "], ";
    cout << "[" << line.getPt2().getX() << ", " << line.getPt2().getY() << "] Deleted" <<endl;
  }
  else
  {
    cout << "No Line with that values. Please enter again." << endl << endl;
    DeleteL2DData(L2D);
  }
}

// function that deletes a given Line3D
void DeleteL3DData(vector<Line3D*>& L3D)
{
  Line3D line = EnterL3DData();
  if(CheckData(L3D,line))
  {
    for( auto it = L3D.begin(); it != L3D.end();++it)
      if(**it == line)
      {
        delete (*it);
        L3D.erase(it);
        break;
      }
    cout << "Point3D [" << line.getPt1().getX() << ", " << line.getPt1().getY() << ", " << line.getPt1().getZ() << "], ";
    cout << "[" << line.getPt2().getX() << ", " << line.getPt2().getY() << ", " << line.getPt2().getZ() << "] Deleted" <<endl;
  }
  else
  {
    cout << "No Line with that values. Please enter again." << endl << endl;
    DeleteL3DData(L3D);
  }
}

// function that get the user to enter values for a Point2D
Point2D EnterP2DData ()
{
  int x,y;
  do
  {
    cout << "Please enter X-coordinate of Point2D : ";
    cin >> x;
  }while(!cin.good());
  do
  {
    cout << "Please enter Y-coordinate of Point2D : ";
    cin >> y;
  }while(!cin.good());
  cout << endl;
  return Point2D{x,y};
}

// function that get the user to enter values for a Point3D
Point3D EnterP3DData ()
{
  int x,y,z;
  do
  {
    cout << "Please enter X-coordinate of Point3D : ";
    cin >> x;
  }while(!cin.good());
  do
  {
    cout << "Please enter Y-coordinate of Point3D : ";
    cin >> y;
  }while(!cin.good());
  do
  {
    cout << "Please enter Z-coordinate of Point3D : ";
    cin >> z;
  }while(!cin.good());
  cout << endl;
  return Point3D{x,y,z};
}

// function that get the user to enter values for a Line2D
Line2D EnterL2DData ()
{
  Point2D pt1 = EnterP2DData();
  Point2D pt2 = EnterP2DData();
  return Line2D{pt1,pt2};
}

// function that get the user to enter values for a Line3D
Line3D EnterL3DData ()
{
  Point3D pt1 = EnterP3DData();
  Point3D pt2 = EnterP3DData();
  return Line3D{pt1,pt2};
}

// function to check if there is a Point2D in the vector
bool CheckData(vector<Point2D*>& P2D, Point2D point)
{
  for(auto it : P2D)
    if (*it == point)
      return true;
  return false;
}

// function to check if there is a Point3D in the vector
bool CheckData(vector<Point3D*>& P3D, Point3D point)
{
  for(auto it : P3D)
    if (*it == point)
      return true;
  return false;
}

// function to check if there is a Line2D in the vector
bool CheckData(vector<Line2D*>& L2D, Line2D line)
{
  for(auto it : L2D)
    if (*it == line)
      return true;
  return false;
}

// function to check if there is a Line3D in the vector
bool CheckData(vector<Line3D*>& L3D, Line3D line)
{
  for(auto it : L3D)
    if (*it == line)
      return true;
  return false;
}

// Function that Formats the string
string& WordFormat(string& word)
{
  string::iterator it;
  // Goes to every char and uncap them if the char is a big letter
  for (it = word.begin(); it != word.end(); ++it)
    if (*it >= 'A' && *it <= 'Z')
      *it += SPACE;
  // Caps the first letter
  word[0] -= SPACE;
  // Caps the last letter
  word[word.size() -1] -= SPACE;
  return word;
}