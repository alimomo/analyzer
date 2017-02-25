#include "GUI.h"


UserConsole::UserConsole()
//  default ctor
{

}


UserConsole::UserConsole(const string& inAddr, const int& inPort, const string& inDevice) : mAddr(inAddr), mPort(inPort), mDevice(inDevice)
//  ctor - address. port & device name!
{

}


void UserConsole::startAnalysis()
//  construct 1 Analyzer object per GUI application, call it's 'run()' method & 'displayPackets()' method
{
    //  create Analyzer object & set parameters
    Analyzer alpha;

    //  set parameters
    alpha.set("127.0.0.1", 8088, "enp0s3");

    //  run Analyzer object
    alpha.run();

    alpha.displayPackets();

    //  display Analyzer object
}



UserConsole::~UserConsole()
//  destroy Analyzer objects (vector elements)
{

}
