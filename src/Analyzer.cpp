/* Analyzer Definition */

#include "Analyzer.h"


Analyzer::Analyzer() : mId(gCount) , mAddr("") , mPort(0) , mDevice("")
//  PRE:  global count is 0
{
    //  throw an exception if you try to create more than 1 Analyzer object
    try{
        if (gCount != 0)
        {
            throw gCount;
        }

        gCount++;
    }catch(int c)
    {
        cout << "Only 1 Analyzer object can be created! " << endl;
        exit(1);
    }
}

Analyzer::Analyzer( const string& inAddr, const int& inPort, const string& inDevice ) : mId(gCount)
//  PRE:  global count is 0
{
    //  throw an exception if you try to create more than 1 Analyzer object
    try{
        if (gCount != 0)
        {
            throw gCount;
        }

        gCount++;

        mAddr = inAddr;
        mPort = inPort;
        mDevice = inDevice;

    }catch(int c)
    {
        cout << "Only 1 Analyzer object can be created! " << endl;
        exit(1);
    }
}

void Analyzer::run()
//  PRE:  data members are all set
{
    //  check data members are set
    try{

        if (mAddr == "" || mPort == 0 || mDevice == "")
        {
            throw gCount;
        }

    }catch(int c)
    {
        cout << " Analyzer data members not set " << endl;
        exit(1);
    }

    //  create socket object

    //  call Packet.decodePacket() on each received message

    //  add to vector of Packets.

}

string Analyzer::getAddress() const{ return mAddr; }
string Analyzer::getDeviceName() const{ return mDevice; }
int Analyzer::getPort() const{ return mPort; }



void Analyzer::set(const string& inAddr, const int& inPort, const string& inDevice)
//  set data members for address, port & device name
{
    mAddr = inAddr;
    mPort = inPort;
    mDevice = inDevice;
}

void Analyzer::setDevice(const string& inDevice)
//  set device data variable
{
    mDevice = inDevice;
}



Analyzer::~Analyzer()
{

}


int Analyzer::gCount = 0;
