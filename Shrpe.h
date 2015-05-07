/*
  Shrpe.cpp
  - Library for usage together with the SHRPE shield.
  Authors: Andreas Drotth & Soded Alatia, 
  Created Date: April 9, 2015.
  [license, domain etc?]
*/

#ifndef Shrpe_h
#define Shrpe_h

#include "Arduino.h"

class Shrpe
{
  public:
    Shrpe();
    void logIn();
	void uploadObject();
	void logOut();
};

#endif

