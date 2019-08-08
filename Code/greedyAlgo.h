#include "Student.h"
#include "AdjacencyMatrix.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

string GetFilename();
void ReadAndProcessFile(vector<Student> &studentlist, vector<string> &subjectlist);
void ReadStudent(ifstream &myfile,vector<Student> &studentlist, vector<string> &subjectlist);