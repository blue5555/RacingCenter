#ifndef cDatabaseDriver_H
#define cDatabaseDriver_H

#include <libCommon/stdafx.h>
#include "cDatabaseBaseElement.h"

struct cDatabaseDriver : public cDatabaseBaseElement
{

	tBool Init();

protected:
	tUInt		m_nPoints;
	tUInt		m_nDrivingRaces;
    tUInt		m_nWinRaces;
    tUInt		m_nDrivingChampionships;
    tUInt		m_nWinChampionships;

public:
    cDatabaseDriver(const std::string& i_strName);
    ~cDatabaseDriver();

	tBool		Set(const QStringList& i_oValues);
	QStringList GetColumnValues() const;

    tUInt GetPoints() const { return m_nPoints; }
    void  SetPoints(tUInt16 val) { m_nPoints = val; }

    tUInt GetDrivingRaces() const { return m_nDrivingRaces; }
    void  SetDrivingRaces(tUInt val) { m_nDrivingRaces = val; }

    tUInt GetWinRaces() const { return m_nWinRaces; }
    void  SetWinRaces(tUInt val) { m_nWinRaces = val; }

    tUInt GetDrivingChampionships() const { return m_nDrivingChampionships; }
    void  SetDrivingChampionships(tUInt val) { m_nDrivingChampionships = val; }

    tUInt GetWinChampionships() const { return m_nWinChampionships; }
    void  SetWinChampionships(tUInt val) { m_nWinChampionships = val; }

};

#endif