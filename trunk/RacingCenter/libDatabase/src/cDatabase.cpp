#include "cDatabase.h"
#include "cXMLDatabase.h"

#define _FILENAME_ "cDatabase: "
#define DATABASENAME "/database.xml"
#define SQLDATABASENAME "/sqDatabase.db"

using namespace RacingCenter;

cDatabase* cDatabase::m_opDatabase = NULL;

void cDatabase::Init()
{
	m_oCars.clear();
	m_oDrivers.clear();
}

tBool cDatabase::LoadDatabase(const std::string& i_oConfigPath)
{
    if(i_oConfigPath == "")
    {

    }
    else
    {
        m_strDefaultPath = i_oConfigPath;
    }

	m_oSQLConnector.LoadDatabase(m_strDefaultPath + SQLDATABASENAME);
		
	cXMLDatabase oXMLDatabase;
	oXMLDatabase.ReadDatabase(this, m_strDefaultPath + DATABASENAME);

	return true;
}

tBool cDatabase::SaveDatabase(const std::string& i_oConfigPath)
{
    if(i_oConfigPath == "")
    {

    }
    else
    {
        m_strDefaultPath = i_oConfigPath;
    }
    cXMLDatabase oXMLDatabase;
    oXMLDatabase.SaveDatabase(this, m_strDefaultPath + DATABASENAME);

    return true;
}

tUInt cDatabase::GetNumberOfCars()
{
	return m_oCars.size();
}

tUInt cDatabase::GetNumberOfDrivers()
{
	return m_oDrivers.size();
}

const tDatabaseDrivers cDatabase::GetAllDrivers() const
{
    return m_oDrivers;
}

const tDatabaseCars cDatabase::GetAllCars() const
{
    return m_oCars;
}

std::list<std::string> cDatabase::GetAllDriverNames() const
{
    std::list<std::string> oDriverNames;
    for (tDatabaseDrivers::const_iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++)
    {
        oDriverNames.push_back(itDriver->GetName());
    }

    oDriverNames.sort();

    return oDriverNames;
}

std::list<std::string> cDatabase::GetAllCarNames() const
{
    std::list<std::string> oCarNames;
    for (tDatabaseCars::const_iterator itCar = m_oCars.begin(); itCar != m_oCars.end(); itCar++)
    {
        oCarNames.push_back(itCar->GetName());
    }

    oCarNames.sort();

    return oCarNames;
}

tBool cDatabase::AddRace(const cDatabaseRace& i_oRace)
{
	return true;
}


tBool cDatabase::AddDriver(const std::string& i_strName)
{
	if(GetDriver(i_strName) == NULL) 
    {
		cDatabaseDriver oDatabaseDriver(i_strName);
		m_oDrivers.push_back(oDatabaseDriver);
		return true;
	} else {
		return false;
	}
}

tBool cDatabase::AddDriver(const cDatabaseDriver& i_oDriver)
{
    if(GetDriver(i_oDriver.GetName()) == NULL) 
    {
        m_oDrivers.push_back(i_oDriver);
        return true;
    } else {
        return false;
    }
}

cDatabaseDriver* cDatabase::GetDriver(const std::string& i_strName)
{
    /*   if(m_oDrivers.find(i_strName) != m_oDrivers.end())
    {
    return &m_oDrivers.at(i_strName);
    }*/

    for (tDatabaseDrivers::iterator it = m_oDrivers.begin(); it != m_oDrivers.end(); it++)
    {
        if(i_strName == it->GetName())
        {
            return &(*it);
        }
    }

    return NULL;
}

tBool cDatabase::DeleteDriver(const std::string& i_strName)
{
    //if(m_oDrivers.find(i_strName) != m_oDrivers.end())
    //{
    //    m_oDrivers.erase(m_oDrivers.find(i_strName));
    //    return true;
    //}

    for (tDatabaseDrivers::iterator it = m_oDrivers.begin(); it != m_oDrivers.end(); it++)
    {
        if(i_strName == it->GetName())
        {
            m_oDrivers.erase(it);
            return true;
        }
    }

	return false;
}

tBool cDatabase::AddCar(const std::string& i_strName)
{
	if(GetCar(i_strName) == NULL) 
    {
		cDatabaseCar oDatabaseCar(i_strName);
		m_oCars.push_back(oDatabaseCar);
		return true;
	} else {
		return false;
	}
}

tBool cDatabase::AddCar(const cDatabaseCar& i_oCar)
{
    if(GetDriver(i_oCar.GetName()) == NULL) 
    {
        m_oCars.push_back(i_oCar);
        return true;
    } else {
        return false;
    }
}

cDatabaseCar* cDatabase::GetCar(const std::string& i_strName)
{
    //if(m_oCars.find(i_strName) != m_oCars.end())
    //{
    //    return &m_oCars.at(i_strName);
    //}

    for (tDatabaseCars::iterator it = m_oCars.begin(); it != m_oCars.end(); it++)
    {
        if(i_strName == it->GetName())
        {
            return &(*it);
        }
    }

    return NULL;
}

tBool cDatabase::DeleteCar(const std::string& i_strName)
{
    //if(m_oCars.find(i_strName) != m_oCars.end())
    //{
    //    m_oCars.erase(m_oCars.find(i_strName));
    //    return true;
    //}

    for (tDatabaseCars::iterator it = m_oCars.begin(); it != m_oCars.end(); it++)
    {
        if(i_strName == it->GetName())
        {
            m_oCars.erase(it);
            return true;
        }
    }

    return false;
}

tBool cDatabase::SaveResults(const cDatabaseRace& i_oDatabaseRace)
{
	//m_oRaces.push_back(i_oDatabaseRace);
	return true;
}