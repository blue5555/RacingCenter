#include <cDatabaseRaceDriver.h>

cDatabaseRaceDriver::cDatabaseRaceDriver()
{
    m_strName = "";
    m_strCarName = "";

    m_oRoundTimes.clear();
    
    m_f64BestTime = 999;
    m_nPosition = 0;

}

cDatabaseRaceDriver::~cDatabaseRaceDriver()
{

}
