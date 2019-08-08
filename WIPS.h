#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>

static std::ifstream inData;

struct Gridinfo
{
  int x;
  int y;
  int state;
  int CC;
  int P;
};

void ProcessConfigFile(std::string &, std::string &, 
std::string &, std::string &, int &, int &);

Gridinfo** LoadArrayMemory(int , int );

std::map<int,std::string> ProcessCitylocFile(const std::string &, 
Gridinfo **, int , int );

void ProcessFile(const std::string &, Gridinfo **, int , int , int );

char GetLMHsymbol(int );

void DisplayCityMap(Gridinfo **, int , int , int);

double CalculateAverage(int , Gridinfo **, int , int , int );

int rainprob(char , char );

void printgraphics(int );

void WeatherForecastSummaryReport(std::map<int,std::string> , Gridinfo **, int , int );

void pressEnter();

void printmenu();

std::string GetConfigFile();

int GetChoice();

bool HandleChoice(Gridinfo ** &, std::string &, std::string &, std::string &, 
std::string &, int &, int &, int, std::map<int,std::string> & );