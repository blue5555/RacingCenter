#include "cDatabaseRace.h"
#include "libDataCore/cRace.h"

using namespace RacingCenter;

cDatabaseRace::cDatabaseRace() :
 m_eRaceMode(MODE_TRAINING)
,m_oStartDate(0)
,m_nDuration(0)
,m_nRounds(0)
,m_nTime(0)
,m_eRaceFinish(FINISH_ROUNDS)
,m_eFuelMode(FUELMODE_OFF)
,m_nChaosCounter(0)
,m_bDriveFinish(false)
{
}

cDatabaseRace::cDatabaseRace(const cRace* i_opRace) :
 m_eRaceMode(i_opRace->RaceMode())
,m_oStartDate(i_opRace->GetStartTimeStamp())
,m_nDuration(0)
,m_nRounds(i_opRace->Rounds())
,m_nTime(i_opRace->Time())
,m_eRaceFinish(i_opRace->RaceFinish())
,m_eFuelMode(i_opRace->FuelMode())
,m_nChaosCounter(i_opRace->GetChaosCounter())
,m_bDriveFinish(i_opRace->GetDriveFinish())
{
}

cDatabaseRace::~cDatabaseRace()
{
}
