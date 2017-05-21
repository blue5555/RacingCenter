#ifndef cTestGenerator_H
#define cTestGenerator_H

#include "libCommon/stdafx.h"
#include "libCommon/cTimeStamp.h"
#include "libCommon/sCUData.h"

namespace RacingCenter
{

class cTestGenerator
{
	tUInt16 randInt(tUInt16 low, tUInt16 high);

	map<tUInt8,tTimeStamp> m_oLastValues;

public:
	cTestGenerator();
	~cTestGenerator();

	sData CreateDriverData(const tUInt8 i_nDriverID);
	sData CreateControllerData(const tUInt8 i_nDriverID);
};

}

#endif	//cTestGenerator_H