#ifndef cTimeStamp_H
#define cTimeStamp_H

#include "stdafx.h"

class cTimeStamp
{
public:
	cTimeStamp();
	~cTimeStamp();

	static const tTimeStamp GetTime();
    static const tTimeStamp GetTimeStamp();
};

#endif
