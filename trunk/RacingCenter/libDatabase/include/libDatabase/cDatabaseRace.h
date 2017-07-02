#ifndef cDatabaseRace_H
#define cDatabaseRace_H

#include <libCommon/stdafx.h>
#include "cDatabaseRaceDriver.h"

namespace RacingCenter
{

class cRace;

class cDatabaseRace
{
    eRaceMode	m_eRaceMode;
    tTimeStamp	m_oStartDate;
	tTimeStamp	m_nDuration;
	tUInt		m_nRounds;
	tUInt		m_nTime;
	eRaceFinish m_eRaceFinish;
	eFuelMode	m_eFuelMode;
	tUInt		m_nChaosCounter;
	tBool		m_bDriveFinish;

	map<tUInt, cDatabaseRaceDriver>	m_oDrivers;

	tBool Init();

public:
	cDatabaseRace();
	cDatabaseRace(const cRace* i_opRace);
	~cDatabaseRace();

	tBool Set(const QStringList& i_oValues);
	QStringList GetColumnValues() const;


};


}

#endif