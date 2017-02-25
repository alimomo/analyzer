

/* Packet Header file */

#ifndef PACKET_H_
#define PACKET_H_

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <net/ethernet.h>
#include <string>

using namespace std;

class Packet
{
    public:
      Packet();
      Packet(u_int8_t *data, int size);
      Packet(char data[65536], int size);     //  copy entire packet into this function
      char *getsrcIP();
      char *getdstIP();
      bool isTCP();
      bool isUDP();
      ~Packet();
    private:
        //  actual packet
        //  ethernet struct
        //  ip struct
        struct ether_header *ethHdr;
        struct ip *ipHeader;
        u_int8_t *payload;              //  store the pointer to actual data packet
        u_int32_t payloadLength;
        char srcIP[INET_ADDRSTRLEN];
        char dstIP[INET_ADDRSTRLEN];
        bool tcp_flag;
        bool udp_flag;


};


#endif
