#ifndef cEventController_H
#define cEventController_H

#include <libCommon/stdafx.h>
#include "libCommon/sEvent.h"
#include "libCommon/cThing.h"
#include "libDataCore/cRace.h"

namespace RacingCenter
{

class cEventController : public QObject, public cThing
{
	Q_OBJECT

	vector<sEvent> m_oEvents;
	tFloat64 m_f64EventThreshold;

	const cRace* m_opRace;

	tInt64 randInt(tInt64 low, tInt64 high);

public:
	cEventController();
	~cEventController();

	tBool AddEvent(const sEvent& i_oEvent);
	tBool Init(const cRace* i_opRace, tFloat64 i_f64EventThreshold);

	tBool CheckForEvent(const tTimeStamp i_nTimeStamp, sEvent& o_oEvent);

};

}


#endif
