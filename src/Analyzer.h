/* Analyzer Header file */

#ifndef ANALYZER_H_
#define ANALYZER_H_


#include <iomanip>
#include <string.h>

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> // E
#include <net/if.h>           // interface
#include <sys/ioctl.h>        // to change interface properties
#include <linux/if_packet.h>

#include "Packet.h"

using namespace std;

class Analyzer
{
    public:
        Analyzer();
        Analyzer(  const string& inAddr, const int& inPort, const string& inDevice  );

        //  establish socket
        void connect();

        //
        void run();

        //  output vector
        void displayPackets();

        //  set interface details & the type of packets you would want to collect
        void set( const string& inAddr, const int& inPort, const string& inDevice );
        void set( const string& inAddr, const int& inPort);
        void setDevice( const string& inDevice );

        //  get interface details
        string getAddress() const;
        int getPort() const;
        string getDeviceName() const;

        ~Analyzer();

    private:
        static int gCount;        //  Global count of Analyzer objects created (should be 1 initially)
        const int mId;            //  ID of Analyzer object
        string mAddr;
        int mPort;
        string mDevice;


        //  socket file descriptor for this Analyzer object
        int mSockfd;

        //  each Analyzer object holds a string with received Packet
        unsigned char mData[65536];

        //  hold a list of Packets received
        vector<Packet*> mPacketList;

};

class emptyMembers
{
public:
    emptyMembers(){}
    emptyMembers(string inMsg) : msg(inMsg){}
    string getMsg(){return msg;}
private:
    string msg;

};

#endif
