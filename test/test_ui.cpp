
/*
 *  Test UI application in analyzer program
 *
 */

#define CATCH_CONFIG_MAIN // this tells 'Catch' to provide a main()
#include "catch.hpp"

using namespace std;


TEST_CASE("resizing a vector", "[vector]")
{
    //  a vector with 5 elements of value 0
    vector<int> v( 5 );

    //  test size & capacity of vector
    REQUIRE( v.size() == 5 );
    REQUIRE( v.capacity() >= 5 );

    //  modify vector & change tests
    SECTION(" test resizing (greater) method ")
    {
        v.resize( 10 );

        REQUIRE( v.size() == 10 );
        REQUIRE( v.capacity() >= 10 );
    }

    //  modify vector & change tests
    SECTION(" test resizing (smaller) method ")
    {
        v.resize( 0 );

        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 5 );
    }
}

TEST_CASE("modifying the data in a vector", "[vector]")
{
    //  a vector with 5 elements of value 0
    vector<int> v( 5);

    //  test that vector is empty
    REQUIRE_FALSE(v.empty());

    //  modify vector elements
    SECTION(" test changing all data elements")
    {
        //  set all vector elements to 5
        for(auto& i : v){ i = 5; }
        //  test all elements are 5
        for (auto& i : v) { REQUIRE(i == 5); }
    }

    //  modify vector elements
    SECTION(" test changing 1 data element")
    {
        //  set all vector elements to 5
        v[2] = 4;
        //  test all elements are 5
        REQUIRE(v.at(2) == 4);
    }


}
