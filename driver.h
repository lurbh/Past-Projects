#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm> 
#include <string>
#include <vector>
#include <fstream>
#include "Line2D.h"
#include "Line3D.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Enum.h"
#include "MyTemplates.h"

using namespace std;

const char SPACE = 32;

void printmenu(filtertype,Ptfilter,filterLine,bool);
int GetChoice();
string StringFilterType(filtertype);
string StringFilterType(filtertype,Ptfilter,filterLine);
string StringSortOrder(bool);
bool HandleChoice(vector<Point2D*>&,vector<Point3D*>&,vector<Line2D*>&,vector<Line3D*>&,filtertype&,Ptfilter&,filterLine&,bool&,int);
void DisplayFliterMenu();
char GetFliterChoice();
filtertype HandleFliterChoice(char);
void DisplaySortMenu(filtertype ft);
char GetSortChoice(filtertype ft);
void HandleSortChoice(char, filtertype, Ptfilter&, filterLine&);
void SetSort(filtertype, Ptfilter&, filterLine&);
void DisplaySortOrderMenu();
char GetSortOrderChoice();
bool HandleSortOrderChoice(char);
string GetFilename();
void ReadInData(vector<Point2D*>&,vector<Point3D*>&,vector<Line2D*>&,vector<Line3D*>&);
filtertype CheckDataType(string);
void HandleP2DData(vector<Point2D*>&,string);
void HandleP3DData(vector<Point3D*>&,string);
void HandleL2DData(vector<Line2D*>&,string);
void HandleL3DData(vector<Line3D*>&,string);
bool Point2DSortA (Point2D*, Point2D*);
bool Point2DSortB (Point2D* , Point2D*);
bool Point3DSortA (Point3D*, Point3D*);
bool Point3DSortB (Point3D*, Point3D*);
bool PointSortD (Point3D*, Point3D*);
template <typename T>
bool SortC (T *, T*);
template <typename T>
bool LineSortA (T *, T*);
template <typename T>
bool LineSortB (T *, T*);
void pressKey();
void PrintData(vector<Point2D*>&);
void PrintData(vector<Point3D*>&);
void PrintData(vector<Line2D*>&);
void PrintData(vector<Line3D*>&);
template <typename T>
void SortData(vector<T*>& vec,filterLine fl,bool sortACD);
void SortData(vector<Point2D*>&,Ptfilter,bool);
void SortData(vector<Point3D*>&,Ptfilter,bool);
void StoreData(vector<Point2D*>&,string);
void StoreData(vector<Point3D*>&,string);
void StoreData(vector<Line2D*>&,string);
void StoreData(vector<Line3D*>&,string);
void DeleteData(vector<Point2D*>& P2D,vector<Point3D*>& P3D,vector<Line2D*>& L2D,vector<Line3D*>& L3D);
filtertype GetDataType();
void DeleteP2DData(vector<Point2D*>& P2D);
void DeleteP3DData(vector<Point3D*>& P3D);
void DeleteL2DData(vector<Line2D*>& L2D);
void DeleteL3DData(vector<Line3D*>& L3D);
Point2D EnterP2DData ();
Point3D EnterP3DData ();
Line2D EnterL2DData ();
Line3D EnterL3DData ();
bool CheckData(vector<Point2D*>& P2D, Point2D point);
bool CheckData(vector<Point3D*>& P3D, Point3D point);
bool CheckData(vector<Line2D*>& L2D, Line2D line);
bool CheckData(vector<Line3D*>& L3D, Line3D line);
string& WordFormat(string&);