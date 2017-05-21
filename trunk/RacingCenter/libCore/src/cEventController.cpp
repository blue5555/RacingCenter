#include "libCore/cEventController.h"
//#include <QGlobal.h>
#include <QTime>

using namespace RacingCenter;

cEventController::cEventController() :
 m_f64EventThreshold(0)
,m_opRace(NULL)
{
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());
}

cEventController::~cEventController()
{

}

tBool cEventController::Init(const cRace* i_opRace, tFloat64 i_f64EventThreshold)
{
	m_opRace = i_opRace;
	m_f64EventThreshold = i_f64EventThreshold;

	return true;
}

tBool cEventController::AddEvent(const sEvent& i_oEvent)
{
	m_oEvents.push_back(i_oEvent);
	return true;	
}

tBool cEventController::CheckForEvent(const tTimeStamp i_nTimeStamp, sEvent& o_oEvent)
{
	tInt64 nRandomNumber = randInt(0, 100);

	tFloat64 f64RaceState = 0;
	if(m_opRace->RaceFinish() == FINISH_ROUNDS)
	{
		f64RaceState = static_cast<tFloat64>(m_opRace->GetMaxRounds()) / static_cast<tFloat64>(m_opRace->Rounds());
	}

	if(f64RaceState > nRandomNumber && m_oEvents.size() > 0)
	{
		o_oEvent = m_oEvents[0];
		m_oEvents.erase(m_oEvents.begin());
		return true;
	}

	return false;

}

tInt64 cEventController::randInt(tInt64 low, tInt64 high)
{
	// Random number between low and high
	return qrand() % ((high + 1) - low) + low;
}