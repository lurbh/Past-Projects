#include "ShapeTwoD.h"

// Non-Default Constructor for ShapeTwoD that takes in a string and a bool
ShapeTwoD::ShapeTwoD(string name, bool containsWarpSpace)
  : id{0}, name{name}, containsWarpSpace{containsWarpSpace}, area{0}
{
  
}

// Non-Default Constructor for ShapeTwoD that takes in a string, bool and a unsigned int
ShapeTwoD::ShapeTwoD(string name, bool containsWarpSpace, unsigned id)
  : id{id}, name{name}, containsWarpSpace{containsWarpSpace}, area{0}
{
  
}

// Non-Default Constructor for ShapeTwoD that takes in a string and a unsigned int
ShapeTwoD::ShapeTwoD(string name, unsigned id)
  : id{id}, name{name}, containsWarpSpace{false}, area{0}
{
  
}

// Destructor for ShapeTwoD
ShapeTwoD::~ShapeTwoD()
{
  InShape.clear();
  OnShape.clear();
}

// A getter function to get name
string ShapeTwoD::getName() const
{
  return this->name;
}

// A getter function to get containsWarpSpace
bool ShapeTwoD::getContainsWarpSpace() const
{
  return this->containsWarpSpace;
}

// A getter function to get area
double ShapeTwoD::getArea() const
{
  return this->area;
}

// A getter function to get id
unsigned ShapeTwoD::getShapeId() const
{
  return this->id;
}

// A getter function to get a vector of Grids InShape
vector<Grid> ShapeTwoD::getInShape()
{
  return this->InShape;
}

// A getter function to get a vector of Grids OnShape
vector<Grid> ShapeTwoD::getOnShape()
{
  return this->OnShape;
}

// A setter function to set name
void ShapeTwoD::setName(string name) 
{
  this->name = name;
}

// A setter function to set containsWarpSpace
void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace)
{
  this->containsWarpSpace = containsWarpSpace;
}

// A setter function to set area
void ShapeTwoD::setArea(double area)
{
  this->area = area;
}

// A function that converts ShapeTwoD into a string
string ShapeTwoD::toString() const
{
  ostringstream oss;
  
  oss << "Shape [" << id << "]" << endl;
  oss << "Name : " << name << endl;
  oss << "Special Type : " << stringWarpSpace() << endl;
  oss << "Area : " << std::fixed << std::setprecision(2) << area << " units square" << endl;
  
  return (oss.str());
}

// A function that converts containsWarpSpace into a string
string ShapeTwoD::stringWarpSpace() const
{
  if(containsWarpSpace)
    return "WS";
  else
    return "NS";
}

// A function that converts all the Grids in vector InShape to a string
string ShapeTwoD::stringInShape() const
{
  ostringstream oss;
  if(InShape.size())
    for (unsigned i = 0; i < InShape.size(); i++)
    {
      oss << InShape[i].toString();
      if(i < InShape.size() -1)
        oss <<   ", ";
    }
  else
    oss << "none!";
  return (oss.str());
}

// A function that converts all the Grids in vector OnShape to a string
string ShapeTwoD::stringOnShape() const
{
  ostringstream oss;
  if(OnShape.size())
    for (unsigned i = 0; i < OnShape.size(); i++)
    {
      oss << OnShape[i].toString();
      if(i < OnShape.size() -1)
        oss <<   ", ";
    }
  else
    oss << "none!";
   return (oss.str());
}

// A function that reads data from a file for 
void ShapeTwoD::Read(ifstream& s)
{
  s.read((char*)&containsWarpSpace, sizeof(bool));
}

// A function that writes data to a file
void ShapeTwoD::Write(ofstream& s) const
{
  s.write((char*)&containsWarpSpace, sizeof(bool));
}