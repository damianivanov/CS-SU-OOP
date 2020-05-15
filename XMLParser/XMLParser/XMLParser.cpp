// XMLParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Repl.h"

using namespace std;

int main()
{
    Repl repl;
    repl.REPL();

	/* Tests    
    //open C:\Users\Damian's PC\Documents\GitHub\CS-SU-OOP\XMLParser\XMLParser\Test.xml
    > xpath 1 person/age
		- 21
    > xpath 1 person/tel
    - 0886500
    > xpath 1 person/address
    - USA
    - Bulgaria
    - Bulgaria
    - Bulgaria
    - Bulgaria
    - Bulgaria
    > xpath 1 person/city[0]
    - Sofia
    > xpath 1 person/address/city[1]
    -Sofia
    > xpath 1 person/address/city
     - Sofia
     - Sofia
     - Burgas

    > xpath 1 person / city[1] //INVALID
    > xpath 1 person / city[2]/ /INVALID
    */

}

