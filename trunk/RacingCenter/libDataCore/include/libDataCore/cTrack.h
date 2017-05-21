#ifndef cTrack_H
#define cTrack_H

#include <libCommon/stdafx.h>
#include "cBasicData.h"

namespace RacingCenter
{

class cTrack : public cThing
{
	tFloat64    m_f64RoundRecord;

	public:
		cTrack();
		~cTrack();
};

}


#endif //cTrack_H