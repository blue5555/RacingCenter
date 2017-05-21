#include "cTimeStamp.h"

cTimeStamp::cTimeStamp()
{

}

cTimeStamp::~cTimeStamp()
{

}

const tTimeStamp cTimeStamp::GetTime()
{
	return  static_cast<tTimeStamp>(QDateTime::currentMSecsSinceEpoch());
}

const tTimeStamp cTimeStamp::GetTimeStamp()
{
	return  static_cast<tTimeStamp>(QDateTime::currentMSecsSinceEpoch() % 10000000);
}