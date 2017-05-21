#ifndef cDatabaseRaceDriver_H
#define cDatabaseRaceDriver_H

#include <libCommon/stdafx.h>

struct cDatabaseRaceDriver
{
	std::string		    m_strName;
	std::string			m_strCarName;
	vector<tFloat64>    m_oRoundTimes;
	tUInt8				m_nPosition;
	tFloat64			m_f64BestTime;

public:
	cDatabaseRaceDriver();
    ~cDatabaseRaceDriver();
};

#endif