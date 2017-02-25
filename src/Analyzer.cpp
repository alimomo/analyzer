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
        //(*this).connect();
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
        (*this).connect();
        this->mAddr = inAddr;
        this->mPort = inPort;
        this->mDevice = inDevice;

    }catch(int c)
    {
        cout << "Only 1 Analyzer object can be created! " << endl;
        exit(1);
    }
}



void Analyzer::connect()
//  PRE   :   data members are all set
//  POST  :   vector has up o 10 elements
{

    //  Data Members Exception
    try{

        if (mAddr == "" || mPort == 0 || mDevice == "")
        {
            throw emptyMembers("you must use set() to specify Address, Port & Device Name");
        }

    }catch(emptyMembers e){
        cout << e.getMsg() << endl;
        exit(1);
    }

    cout << "device id = " << mDevice << endl;

    // Needed for promiscuous mode
    struct ifreq ifopts;

    this->mSockfd = 0;

    //  create a raw socket
    this->mSockfd = socket( AF_PACKET, SOCK_RAW, htons( ETH_P_ALL) );

    //  check if socket is created
    if( this->mSockfd < 0 ) {
        std::cerr << "Error creating raw socket. Probably not root.\n";
        exit( 1 );
    }

    //  copy interface flags
    strncpy(ifopts.ifr_name, mDevice.c_str(), IFNAMSIZ);
    //cout << ifopts.ifr_flags < endl;

    if( ioctl( this->mSockfd, SIOCGIFFLAGS, &ifopts ) == -1 ) {
        std::cerr << "Error reading interface (" + mDevice + ") flags.\n";
        exit( 2 );
    }

    // Set interface to promiscuous mode
    ifopts.ifr_flags |= IFF_PROMISC;
    if( ioctl( this->mSockfd, SIOCSIFFLAGS, &ifopts ) == -1 ) {
        std::cerr << "Error setting promiscuous flag on interface (" + mDevice + ").\n";
        exit( 3 );
    }

    // Set socket to be reusable
    int sockopt = 0;
    if( setsockopt( this->mSockfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(sockopt) ) == -1 ) {
        std::cerr << "Cannot set socket to be reusable.\n";
        exit( 4 );
    }

    //  put network card into "PROMISCUOUS" mode so it forwards ALL packets (diff ethernet dst) to the OS, SOCK_RAW to get MAC info

    cout << "Raw socket created " << endl;
}


void Analyzer::run()
//  read Packets
{
    cout << "Checking for packets..." << endl;

    // Stores address info about packet received
    struct sockaddr_ll src_addr = { 0 };
    socklen_t addr_len = sizeof( struct sockaddr_ll );

    //  get packet from 'src' addr
    int data_size = recvfrom( this->mSockfd, this->mData, sizeof( this->mData ), 0, ( struct sockaddr* ) &src_addr, &addr_len );

    //  check if packet has error
    if( data_size < 0 ) {
        std::cerr << strerror( errno );
        exit(1);
    }

    /*TODO: Exception handling if Packet object is not created */
    this->mPacketList.push_back(new Packet(this->mData,data_size));



    cout << "Packet Received! " << endl;

}

void Analyzer::displayPackets()
{
    cout << "displaying packets..\n";
    vector<Packet*>::iterator p = mPacketList.begin();
    int i = 0;
    Packet* temp;




    for (p = mPacketList.begin(); p != mPacketList.end(); p++)
    {
        temp = *p;
        cout << "SRC IP: " << temp->getsrcIP() << "\tDST IP: " << temp->getdstIP() << endl;
    }
}

string Analyzer::getAddress() const{ return mAddr; }
string Analyzer::getDeviceName() const{ return mDevice; }
int Analyzer::getPort() const{ return mPort; }
void Analyzer::set(const string& inAddr, const int& inPort, const string& inDevice)
//  set data members for address, port & device name
{
    this->mAddr = inAddr;
    this->mPort = inPort;
    this->mDevice = inDevice;
    (*this).connect();
}
void Analyzer::setDevice(const string& inDevice)
//  set device data variable
{
    this->mDevice = inDevice;
}

Analyzer::~Analyzer()
//  remove
{
    //  close Socket if it's open
    if( this->mSockfd >= 0 ) {
        close(this->mSockfd);
        cout << "Raw socket closed " << endl;    }
}


int Analyzer::gCount = 0;
