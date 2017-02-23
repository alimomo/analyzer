/* Analyzer Header file */

#ifndef ANALYZER_H_
#define ANALYZER_H_

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

class Analyzer
{
    public:
        Analyzer();
        Analyzer(  const string& inAddr, const int& inPort, const string& inDevice  );


        void run();

        void displayPackets();

        //  SETTERS - don't modify parameters
        void set( const string& inAddr, const int& inPort, const string& inDevice );
        void set( const string& inAddr, const int& inPort);
        void setDevice( const string& inDevice );

        //  GETTERS - don't modify data members & return a value
        string getAddress() const;
        int getPort() const;
        string getDeviceName() const;

        ~Analyzer();
    private:
        static int gCount;        //  Global count of Analyzer objects created (should be 1 initially)


        const int mId;        //  ID of Analyzer object
        string mAddr;
        int mPort;
        string mDevice;

};

#endif
