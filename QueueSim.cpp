#include <iostream>
#include <iomanip>
#include <queue>
#include <stdlib.h>     
#include <time.h> 

#define SIZE 40
#define RATE1 80
#define RATE2 60

using namespace std;

// random number to place in queue
int GenRandomNum()
{
  return rand() % RATE1 + 1;
}

// random number generator to determine when messages are received
int GenRandomRec()
{
  return rand() % RATE2 + 1;
}

// random number generator to determine whether a given message can be sent
int GenRandomSend()
{
  return rand() % RATE1 + 1;
}

// random number to place in queue
int GenRandomNumProcess()
{
  return rand() % RATE1 + 1;
}

int main()
{
  queue<int> Email;
  srand(time(NULL));
  int minutestorun;
  int totalrecievedmsg = 0;
  int totalsentmsg = 0;
  int totalqueuemsg = 0;
  int totalrequeuemsg = 0;
  bool input = true;
  // loop to ensure a proper value is given
  do
  {
    cout << "Enter the amount of minutes for the program to run : ";
    cin >> minutestorun;
    if(cin.good())
      if(minutestorun < 0)
        cout << "Enter a positive value" << endl;
      else
        input = false;
    else
    {
      cout << "Not an integer." << endl << endl;
      cin.clear();
      cin.ignore(256,'\n');
    }
  }while(input);
  
  cout << endl;
  // arrays to store data
  int sentmsglist[minutestorun];
  int recievemsglist[minutestorun];
  int msgrequeued[minutestorun];
  
  // run for the amount of minutes declared
  for ( int minute = 0 ; minute < minutestorun ; minute++ ) 
  {
    int limit = Email.size() * 25 / 100;
    int sentmsg = 0;
    int recievemsg = 0;
    int requeuemsg = 0;
    // run process per minute
    int size = GenRandomNumProcess();
    
    for(int i = 0; i < size; ++i)
    {
      // get random values
      int r = GenRandomRec();
      int s = GenRandomSend();
      // Add value into queue base on random value generated
      if(r < 30 && Email.size() < SIZE)
      {
        Email.push(GenRandomNum());
        recievemsg++;
      }
      // pop queue based on random value generated
      else if((s > 39) && (int)Email.size() > limit)
      {
        Email.pop();
        sentmsg++;
      }
      // if sending failed requeue 
      else 
      {
        int no = Email.front();
        Email.pop();
        Email.push(no);
        requeuemsg++;
      }
      
    }
    // store the data
    sentmsglist[minute] = sentmsg;
    msgrequeued[minute] = requeuemsg;
    recievemsglist[minute] = recievemsg;
    totalqueuemsg += Email.size();
  }
  // sum the data
  for(int i : sentmsglist)
    totalsentmsg += i;
  for(int i : recievemsglist)
    totalrecievedmsg += i;
  for(int i : msgrequeued)
    totalrequeuemsg += i;
  
  // printing of data
  cout << "Total Messages Processed : " << totalsentmsg + totalrecievedmsg + totalrequeuemsg << endl;
  cout << "Average Arrival Rate per minute : " << totalrecievedmsg / minutestorun << endl;
  cout << "Average Sent Rate per minute : " << totalsentmsg / minutestorun << endl;
  cout << "Average No. of Messages in queue per minute : " << totalqueuemsg / minutestorun << endl;
  cout << "Number of Messages Sent for each attempt : " << endl;
  for(int i = 0; i < minutestorun; i++)
  {
    cout << "    Attempt " << std::left << std::setw(3) << i + 1 << ": " << sentmsglist[i] << endl;
  }
  cout << "Average Number of Messages Requeued : " << totalrequeuemsg / (minutestorun - 1) << endl;
  
  return 0;
}