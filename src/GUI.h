/* UI Header file */

#ifndef GUI_H_
#define GUI_H_

#include <string>
#include "Analyzer.h"

using namespace std;

class UserConsole
{
  public:
      UserConsole();
      UserConsole( const string& inAddr, const int& inPort, const string& inDevice );

      void startAnalysis(); //  can only start 1 instance of an Analyzer object


      ~UserConsole();
  private:
      string mAddr;
      int mPort;
      string mDevice;
};

#endif
