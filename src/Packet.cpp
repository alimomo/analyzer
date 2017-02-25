/*
 * Packet Sniffer class definition
 *
 *    - Packet object when created has Ethernet, IP, and TCP/UDP information
 *    - 'PacketSniffer' class can create several objects depending on activity
 */

#include "Packet.h"



Packet::Packet( u_int8_t *data, int size )
{

    //  set Packet object's size to ZERO
    this->payload = NULL;
    this->payloadLength = 0;

    //  packet we're creating must be within range
    if( size < 0 || size > 65536 ) {
        std::cerr << "Packet exceeds size limit!\n";
        exit(5);
    }

    // Allocate enough space to hold the data passed
    this->payloadLength = size;
    this->payload = new u_int8_t[size];

    if( payload == NULL ) {
        std::cerr << "Cannot allocate enough memory for packet!\n";
        exit(6);
    }

    // Zero out the new packet buffer
    memset(this->payload, 0, size);

    // Copy the read packet into the buffer
    memcpy(this->payload, data, size);


    // get Ethernet Header
    ethHdr = (struct ether_header*) data;

    /*TODO: Exception handling if IP packet is not found */

    // if ethernet Header type is '8' then it's an IP Packet
    if (ntohs(ethHdr->ether_type) == 0x0800)
    {
        //  get IP Header from payload
        ipHeader = (struct ip*)(this->payload+sizeof(struct ether_header));
        //  get IP source & destination address
        inet_ntop(AF_INET, &(ipHeader->ip_src), srcIP, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ipHeader->ip_dst), dstIP,INET_ADDRSTRLEN);
    }

}

Packet::Packet( char data[65536], int size )
//  copy entire packet bytestream into constructor's parameter (slower)
{
    //  zero out data
    data = NULL;
    size = 0;

    //
    ethHdr = (struct ether_header*) data;

    //
    cout << "eth " << ethHdr->ether_type << endl;


}


char *Packet::getdstIP()
{
    return this->dstIP;
}

char *Packet::getsrcIP()
{
    return this->srcIP;
}



bool Packet::isTCP()
{
    //
}

bool Packet::isUDP()
{
    //
}


Packet::~Packet()
{
    //
}
