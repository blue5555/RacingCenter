#include "cDatabase.h"
#include "cXMLDatabase.h"

#define _FILENAME_ "cDatabase: "
#define DATABASENAME "/database.xml"
#define SQLDATABASENAME "/sqDatabase.db"

using namespace RacingCenter;

cDatabase* cDatabase::m_opDatabase = NULL;

void cDatabase::Init()
{
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
    return true;
}

tUInt cDatabase::GetNumberOfCars()
{
	return m_oSQLConnector.GetNumberOfEntries("Cars");
}

tUInt cDatabase::GetNumberOfDrivers()
{
	return m_oSQLConnector.GetNumberOfEntries("Drivers");
}

std::list<cDatabaseDriver> cDatabase::GetAllDrivers()
{
    return m_oSQLConnector.GetAllDrivers();
}

std::list<cDatabaseCar> cDatabase::GetAllCars()
{
    return m_oSQLConnector.GetAllCars();
}

std::list<std::string> cDatabase::GetAllDriverNames()
{
    std::list<std::string> oDriverNames;
	std::list<cDatabaseDriver> oDrivers = GetAllDrivers();
    for (std::list<cDatabaseDriver>::iterator itDriver = oDrivers.begin(); itDriver != oDrivers.end(); itDriver++)
    {
        oDriverNames.push_back(itDriver->GetName());
    }
    oDriverNames.sort();
    return oDriverNames;
}

std::list<std::string> cDatabase::GetAllCarNames()
{
    std::list<std::string> oCarNames;
	std::list<cDatabaseCar> oCars = GetAllCars();
    for (std::list<cDatabaseCar>::iterator itCar = oCars.begin(); itCar != oCars.end(); itCar++)
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
	if(!EntityExists("Drivers", i_strName))
    {
		m_oSQLConnector.AddDriver(i_strName);
		return true;
	} else {
		return false;
	}
}

cDatabaseDriver cDatabase::GetDriver(const std::string& i_strName)
{
	cDatabaseDriver oDatabaseDriver("");
	m_oSQLConnector.GetDriver(i_strName, oDatabaseDriver);
	return oDatabaseDriver;
}

tBool cDatabase::EntityExists(const std::string& i_strEntity, const std::string& i_strName)
{
	return m_oSQLConnector.EntityExists(i_strEntity, i_strName);
}

tBool cDatabase::UpdateDriver(const cDatabaseDriver& i_oDriver)
{
	return m_oSQLConnector.UpdateDriver(i_oDriver);
}

tBool cDatabase::DeleteDriver(const std::string& i_strName)
{
	return m_oSQLConnector.DeleteDriver(i_strName);
}

tBool cDatabase::AddCar(const std::string& i_strName)
{
	return m_oSQLConnector.AddCar(i_strName);
}

cDatabaseCar cDatabase::GetCar(const std::string& i_strName)
{
	cDatabaseCar oDatabaseCar("");
	m_oSQLConnector.GetCar(i_strName,oDatabaseCar);
	return oDatabaseCar;
}

tBool cDatabase::UpdateCar(const cDatabaseCar& i_oCar)
{
	return m_oSQLConnector.UpdateCar(i_oCar);
}

tBool cDatabase::DeleteCar(const std::string& i_strName)
{
    return m_oSQLConnector.DeleteCar(i_strName);
}

tBool cDatabase::SaveResults(const cDatabaseRace& i_oDatabaseRace)
{
	//m_oRaces.push_back(i_oDatabaseRace);
	return true;
}