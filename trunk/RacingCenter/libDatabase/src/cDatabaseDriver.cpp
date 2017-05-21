#include <cDatabaseDriver.h>

cDatabaseDriver::cDatabaseDriver(const std::string& i_strName) : cDatabaseBaseElement(i_strName)
{
    m_nDrivingChampionships = 0;
    m_nDrivingRaces = 0;
    m_nPoints = 0;
    m_nWinChampionships = 0;
    m_nWinRaces = 0;
}

cDatabaseDriver::~cDatabaseDriver()
{

}
