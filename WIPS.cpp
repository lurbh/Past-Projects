#include "WIPS.h"

int main()
{
  std::string config, cityloc, cloudcover, pressuere;
  int x, y, choice;
  bool quit = false;
  Gridinfo **Map = nullptr;
  std::map<int,std::string> CityList;
  do
  {
    printmenu();
    choice = GetChoice();
    quit = HandleChoice(Map, config, cityloc, cloudcover, pressuere, x, y, choice, CityList);
  }while(!quit);
  
  return 0;
}

// Function that processes the config file
void ProcessConfigFile(std::string &filename, std::string &cityloc, 
std::string &cloudcover, std::string &pressuere, int &x, int &y)
{
  // opens file
  inData.open(filename.c_str());
  // exits if file cannot be open
  if(!inData)
  {
    std::cerr << "Error opening : " << filename << std::endl << std::endl;
    filename = GetConfigFile();
    ProcessConfigFile(filename,cityloc,cloudcover,pressuere,x,y);
  }
  
  int datacounter = 0;
  
  // while not at the end of the file
  while(!inData.eof())
  {
    std::string data;
    getline(inData, data);
    
    // if line is not a comment or a blank line
    if(data.size() > 1  && data.find_first_of("/") == std::string::npos)
    {
      ++datacounter;
      if(data.find_first_of("-") != std::string::npos)
      {
        std::string value;
        // gets the x or y value
        value = data.substr(data.find_first_of("-")+1);
        
        // stores the x or y value depending on the line
        switch(datacounter)
        {
          case 1:
            x = std::stoi(value) + 1;
            std::cout << "Reading in GridX_IdxRange : " << data[data.find_first_of("=") + 1]
            << "-" << x - 1 << " ... done!" << std::endl;
            break;
          case 2:
            y = std::stoi(value) + 1;
            std::cout << "Reading in GridY_IdxRange : " << data[data.find_first_of("=") + 1]
            << "-" << y - 1 << " ... done!" << std::endl << std::endl;
            break;
        }
      }
      else
      {
        // Saves the filename for processing
        switch(datacounter)
        {
          case 3:
            cityloc = data;
            cityloc.pop_back();
            break;
          case 4:
            cloudcover = data;
            cloudcover.pop_back();
            break;
          case 5:
            pressuere = data;
            pressuere.pop_back();
            break;
          default:
            break;
        }
      }
    }
  }
  inData.close();
}

// A function that creates memory for the 2D array of GridInfo based on the x and y values. 
Gridinfo** LoadArrayMemory(int x, int y)
{
  // creating memory for map
  Gridinfo **Map = new Gridinfo*[x];
  for(int i = 0; i < x; i++)
    Map[i] = new Gridinfo[y];
  // initialise values in map
  for(int i = 0; i < x; i++)
    for(int j = 0; j < y; j++)
      Map[i][j] = Gridinfo{i,j,0,0,0};
  return Map;
}

// A function that takes the name of a citylocation file and accesses and stores the data in the file
std::map<int,std::string> ProcessCitylocFile(const std::string &filename, 
Gridinfo **array, int maxX, int maxY)
{
  std::map<int,std::string> citylist;
  // opens file
  inData.open(filename.c_str());
  // exits if file cannot be open
  if(!inData)
  {
    std::cerr << "Error opening : " << filename << std::endl;
    exit(-1);
  }
  int x,y,no;
  
  // while not at the end of the file
  while(!inData.eof())
  {
    std::string data, value;
    int pos1, pos2;
    getline(inData, data);
    // if not a blank line
    if(data.size() > 1)
    {
      // get the x value
      pos1 = data.find_first_of("[") + 1;
      pos2 = data.find_first_of(",");
      value = data.substr(pos1, pos2 - pos1);
      x = std::stoi(value);
      
      // get the y value
      pos1 = data.find_first_of(",") + 1;
      pos2 = data.find_first_of("]");
      value = data.substr(pos1, pos2 - pos1);
      y = std::stoi(value);
      
      // get the city id
      pos1 = data.find_first_of("-") + 1;
      pos2 = data.find_last_of("-");
      value = data.substr(pos1, pos2 - pos1);
      no = std::stoi(value);
      
      if( x < maxX && x >= 0 && y < maxY && y >= 0)
        array[x][y].state = no;
      // get city name
      value = data.substr(data.find_last_of("-") +1);
      // saves the city details in a map
      citylist.insert(std::pair<int,std::string>(no,value));
    }
  }
  std::cout << filename << " ... done!" << std::endl; 
  inData.close();
  return citylist;
}

// A function that takes the name of a file and accesses and 
// stores the data in the file the data can be of cloudcover or pressure
void ProcessFile(const std::string &filename, Gridinfo **array, int maxX, int maxY, int type)
{
  // opens file
  inData.open(filename.c_str());
  // exits if file cannot be open
  if(!inData)
  {
    std::cerr << "Error opening : " << filename << std::endl;
    exit(-1);
  }
  int x,y,no;
  
  // while not at the end of the file
  while(!inData.eof())
  {
    std::string data, value;
    int pos1, pos2;
    getline(inData, data);
    // if line is not blank
    if(data.size() > 1)
    {
      // get the x value
      pos1 = data.find_first_of("[") + 1;
      pos2 = data.find_first_of(",");
      value = data.substr(pos1, pos2 - pos1);
      x = std::stoi(value);
      
      // get the y value
      pos1 = data.find_first_of(",") + 1;
      pos2 = data.find_first_of("]");
      value = data.substr(pos1, pos2 - pos1);
      y = std::stoi(value);
      
      // get the data value
      value = data.substr(data.find_first_of("-") +1);
      no = std::stoi(value);
      
      // check if out of grid
      if( x < maxX && x >= 0 && y < maxY && y >= 0)
        // switch for saving cloudcover or pressure data
        switch(type)
        {
          case 1:
            array[x][y].CC = no;
            break;
          case 2:
            array[x][y].P = no;
            break;
        }
        
    }
  }
  std::cout << filename << " ... done!" << std::endl; 
  inData.close();
}

// A function that gives a L, M or H based on a given value
char GetLMHsymbol(int value)
{
  if(value < 35)
    return 'L';
  else if (value < 65)
    return 'M';
  else
    return 'H';
}

// A function that displays the city map
void DisplayCityMap(Gridinfo **array, int maxX, int maxY, int type = 0)
{
  std::cout << "   ";
  // printing border
  for(int i = 0; i < maxX + 2; i++)
    std::cout << "#  ";
  std::cout << std::endl;
  for( int j = maxY -1; j >= 0 ; j--)
  {
    // printing y grid value and border
    if( j < 10)
      std::cout << j << "  " << "#  ";
    else
      std::cout << j << " " << "#  ";
    for( int i = 0; i < maxX; i++)
    {
      switch(type)
      {
        // citymap display
        case 1:
          if(array[i][j].state)
            std::cout << array[i][j].state << "  ";
          else
            std::cout << "   ";
          break;
        // cloudcover value display
        case 2:
          if(array[i][j].CC)
            std::cout << array[i][j].CC / 10 << "  ";
          else
            std::cout << "   ";
          break;
        // cloudcover LMH display
        case 3:
          if(array[i][j].CC)
            std::cout << GetLMHsymbol(array[i][j].CC) << "  ";
          else
            std::cout << "   ";
          break;
        // pressure value display
        case 4:
          if(array[i][j].P)
            std::cout << array[i][j].P / 10 << "  ";
          else
            std::cout << "   ";
          break;
        // pressure LMH display
        case 5:
          if(array[i][j].P)
            std::cout << GetLMHsymbol(array[i][j].P) << "  ";
          else
            std::cout << "   ";
          break;
        default:
            std::cout << "   ";
      }
      
    }
    std::cout << "#" << std::endl;
  }
  std::cout << "   ";
  // printing border
  for(int i = 0; i < maxX + 2; i++)
    std::cout << "#  ";
  std::cout << std::endl;
  std::cout << "      ";
  // printing x grid value
  for(int i = 0; i < maxX ; i++)
    std::cout << i <<"  ";
  std::cout << std::endl << std::endl;
}

// A function that calculate the average cloudcover or pressure of a given city
double CalculateAverage(int s, Gridinfo **array, int maxX, int maxY, int type)
{
  double total = 0;
  int count = 0;
  // Create memory for checking array
  bool **checkarray = new bool*[maxX];
  for(int i = 0; i < maxX; i++)
    checkarray[i] = new bool[maxY];
  
  // initialise values in checking array
  for(int i = 0; i < maxX; i++)
    for(int j = 0; j < maxY; j++)
      checkarray[i][j] = false;
  
  // goes through whole array
  for(int i = 0; i < maxX; i++)
    for(int j = 0; j < maxY; j++)
      // finds citystate
      if(array[i][j].state == s)
        // check surrounding
        for(int x = -1; x < 2; x++)
          for(int y = -1; y < 2; y++)
            // Check for out of bounds
            if(!(i + x < 0 || i + x >= maxX || j + y < 0 || j + y >= maxY))
              // Check for same city or surrounding area
              if(array[i+x][j+y].state == s || array[i+x][j+y].state == 0)
                // check if grid has been added up before
                if(!checkarray[i + x][j + y])
                {
                  // sum the data up if grid has not been added before
                  switch(type)
                  {
                    case 1:
                      total += array[i+x][j+y].CC;
                      break;
                    case 2:
                      total += array[i+x][j+y].P;
                      break;
                  }
                  count++;
                  // save grid the has been added
                  checkarray[i + x][j + y] = true;
                }
  // clear memeory
  for(int i = 0; i < maxX; i++)
    delete[] checkarray[i];
  delete[] checkarray;
  return total / count;
}

// A function the gets the rain probability based on the a L, M or H given for cloudcover or pressure
int rainprob(char ap, char acc)
{
  if(ap == 'L')
  {
    if(acc == 'L')
      return 70;
    else if(acc == 'M')
      return 80;
    if(acc == 'H')
      return 90;
  }
  if(ap == 'M')
  {
    if(acc == 'L')
      return 40;
    else if(acc == 'M')
      return 50;
    if(acc == 'H')
      return 60;
  }
  if(ap == 'H')
  {
    if(acc == 'L')
      return 10;
    else if(acc == 'M')
      return 20;
    if(acc == 'H')
      return 30;
  }
  return 0;
}

// A function that prints the graphic for the probability of rain
void printgraphics(int s)
{
  int i = s / 10;
  switch(i)
  {
    case 1:
      std::cout << "~" << std::endl;
      std::cout << "~~" << std::endl;
      std::cout << "" << std::endl;
      break;
    case 2:
      std::cout << "~~" << std::endl;
      std::cout << "~~~" << std::endl;
      std::cout << "" << std::endl;
      break;
    case 3:
      std::cout << "~~~" << std::endl;
      std::cout << "~~~~" << std::endl;
      std::cout << "" << std::endl;
      break;
    case 4:
      std::cout << "~~~~" << std::endl;
      std::cout << "~~~~~" << std::endl;
      std::cout << "" << std::endl;
      break;
    case 5:
      std::cout << "~~~~" << std::endl;
      std::cout << "~~~~~" << std::endl;
      std::cout << "    \\" << std::endl;
      break;
    case 6:
      std::cout << "~~~~" << std::endl;
      std::cout << "~~~~~" << std::endl;
      std::cout << "   \\\\" << std::endl;
      break;
    case 7:
      std::cout << "~~~~" << std::endl;
      std::cout << "~~~~~" << std::endl;
      std::cout << "  \\\\\\" << std::endl;
      break;
    case 8:
      std::cout << "~~~~" << std::endl;
      std::cout << "~~~~~" << std::endl;
      std::cout << " \\\\\\\\" << std::endl;
      break;
    case 9:
      std::cout << "~~~~" << std::endl;
      std::cout << "~~~~~" << std::endl;
      std::cout << "\\\\\\\\\\" << std::endl;
      break;
  }
}

// A function that generates a summary report for the cities  
void WeatherForecastSummaryReport(std::map<int,std::string> citylist, Gridinfo **array, int row, int col )
{
  std::cout << "Weather Forecast Summary Report" << std::endl;
  std::cout << "-------------------------------" << std::endl;
  for(auto it = citylist.rbegin(); it != citylist.rend(); ++it)
  {
    double acc = CalculateAverage(it->first,array, row, col, 1);
    double ap = CalculateAverage(it->first,array, row, col, 2);
    int rp = rainprob(GetLMHsymbol(ap),GetLMHsymbol(acc));
    std::cout << "City Name : " << it->second << std::endl;
    std::cout << "City ID : " << it->first << std::endl;
    std::cout << "Ave. Cloud Cover (ACC)   : " << std::fixed << std::setprecision(2)
    << acc  << " (" << GetLMHsymbol(acc) << ")" << std::endl;
    std::cout << "Ave. Pressure (AP)       : " << std::fixed << std::setprecision(2)
    << ap << " (" << GetLMHsymbol(ap) << ")" << std::endl;
    std::cout << "Probability of Rain (%)  : " << rp << ".00" << std::endl;
    printgraphics(rp);
    std::cout << std::endl;
  }
}

// A function that gets the user to press enter to continue
void pressEnter()
{
  std::cout << "Press Enter to go back to the main menu";
  std::cin.get();
  std::cin.get();
  std::cin.clear();
  std::cout << std::endl;
}

// A function that print the main menu
void printmenu()
{
  std::cout << "Student ID       : 6232748" << std::endl;
  std::cout << "Student Name     : Lur Bing Huii" << std::endl;
  std::cout << "-------------------------------------" << std::endl;

  std::cout << "Welcome to Weather Infomation Processing System!" << std::endl;
  std::cout << std::endl;
  std::cout << "1)     Read in and process a configuration file" << std::endl;
  std::cout << "2)     Display City Map" << std::endl;
  std::cout << "3)     Display Cloud Coverage Map (cloudiness index)" << std::endl;
  std::cout << "4)     Display Cloud Coverage Map (LMH symbols)" << std::endl;
  std::cout << "5)     Display Atmospheric Pressure Map (pressure index)" << std::endl;
  std::cout << "6)     Display Atmospheric Pressure Map (LMH symbols)" << std::endl;
  std::cout << "7)     Show Weather Forecast Summary Report" << std::endl;
  std::cout << "8)     Quit" << std::endl;
  std::cout << std::endl;
}

// function to get config filename
std::string GetConfigFile()
{
  std::string config;

  std::cout << "Please enter configuration filename: ";
  std::cin >> config;
  std::cout << std::endl;

  return config;
}

// function that prompts user to enter choice
int GetChoice()
{
  int choice;
  bool input = true;
  
  do
  {
    std::cout << "Please enter your choice : ";
    std::cin >> choice;
    if(std::cin.good())
    {
      // if value is out of bounds
      if(choice < 1 || choice > 8)
      {
        std::cout << "Enter a value between 1-8. " << std::endl;
      }
      else
      {
        input = false;
      }
    }
    // if value is not a integer
    else
    {
      std::cout << "Not an integer." << std::endl << std::endl;
      std::cin.clear();
      std::cin.ignore(256,'\n');
    }
  }while(input);
  
  std::cout << std::endl;
  std::cin.clear();
  
  return choice;
}

// function that handles the user choice
bool HandleChoice(Gridinfo ** & Map, std::string & config, std::string & cityloc, 
std::string & cloudcover, std::string & pressuere, int & x, int & y, int choice,
std::map<int,std::string> & CityList )
{
  bool quit = false; 
  switch(choice)
  {
    case 1:
      std::cout << "[Read in and process a configuration file]" << std::endl << std::endl;
      config = GetConfigFile();
      // Clear Map if there is one
      if(Map)
      {
        for(int i = 0; i < x; i++)
          delete[] Map[i];
        delete[] Map;
      }
      ProcessConfigFile(config, cityloc, cloudcover, pressuere, x, y);
      Map = LoadArrayMemory(x,y);
      std::cout << "Storing data from input file : " << std::endl;
      CityList = ProcessCitylocFile(cityloc, Map, x, y);
      ProcessFile(cloudcover, Map, x, y, 1);
      ProcessFile(pressuere, Map, x, y, 2);
      std::cout << std::endl << "All records sucessfully stored. Going back to main menu ..." << std::endl << std::endl;
      break;
    case 2:
      std::cout << "[Display City Map]" << std::endl << std::endl;
      DisplayCityMap(Map, x, y, 1);
      pressEnter();
      break;
    case 3:
      std::cout << "[Display Cloud Coverage Map (cloudiness index)]" << std::endl << std::endl;
      DisplayCityMap(Map, x, y, 2);
      pressEnter();
      break;
    case 4:
      std::cout << "[Display Cloud Coverage Map (LMH symbols)]" << std::endl << std::endl;
      DisplayCityMap(Map, x, y, 3);
      pressEnter();
      break;
    case 5:
      std::cout << "[Display Atmospheric Pressure Map (pressure index)]" << std::endl << std::endl;
      DisplayCityMap(Map, x, y, 4);
      pressEnter();
      break;
    case 6:
      std::cout << "[Display Atmospheric Pressure Map (LMH symbols)]" << std::endl << std::endl;
      DisplayCityMap(Map, x, y, 5);
      pressEnter();
      break;
    case 7:
      std::cout << "[Show Weather Forecast Summary Report]" << std::endl << std::endl;
      WeatherForecastSummaryReport(CityList,Map,x,y);
      pressEnter();
      break;
    case 8:
      quit = true;
      if(Map)
      {
        for(int i = 0; i < x; i++)
          delete[] Map[i];
        delete[] Map;
      }
      break;
      default:
      break;   
  }
  return quit;
}