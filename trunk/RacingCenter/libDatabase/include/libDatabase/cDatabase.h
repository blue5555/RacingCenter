#ifndef cDatabase_H
#define cDatabase_H

#include "libCommon/stdafx.h"
#include "libCommon/cThing.h"
#include "cSQLConnector.h"
#include "cDatabaseCar.h"
#include "cDatabaseDriver.h"
#include "cDatabaseRace.h"
#include "cDatabaseRaceDriver.h"

namespace RacingCenter
{

class cRace;

typedef std::vector<cDatabaseDriver> tDatabaseDrivers;
typedef std::vector<cDatabaseCar>    tDatabaseCars;

class cDatabase : public cThing
{

private:
	cDatabase() { m_strDefaultPath = ""; };
	~cDatabase() 
	{ 
		if(m_opDatabase != NULL) {
			delete m_opDatabase;
		}
	};

	static cDatabase* m_opDatabase;

	cSQLConnector	 m_oSQLConnector;

    tDatabaseCars    m_oCars;
    tDatabaseDrivers m_oDrivers;

    std::string      m_strDefaultPath;

public:

	void  Init();

    tBool LoadDatabase(const std::string& i_oConfigPath);
    tBool SaveDatabase(const std::string& i_oConfigPath = "");

	tUInt		GetNumberOfCars();
	tUInt		GetNumberOfDrivers();

	const tDatabaseDrivers GetAllDrivers() const;
	const tDatabaseCars    GetAllCars() const;

	tBool		     AddRace(const cDatabaseRace& i_oRace);

	tBool		     AddDriver(const std::string& i_strName);
    tBool		     AddDriver(const cDatabaseDriver& i_oDriver);
    cDatabaseDriver* GetDriver(const std::string& i_strName);
	tBool		     DeleteDriver(const std::string& i_strName);

	tBool			AddCar(const std::string& i_strName);
	tBool		    AddCar(const cDatabaseCar& i_oCar);
    cDatabaseCar*	GetCar(const std::string& i_strName);
	tBool			DeleteCar(const std::string& i_strName);

    std::list<std::string> GetAllDriverNames() const;
    std::list<std::string> GetAllCarNames() const;

	tBool			SaveResults(const cDatabaseRace& i_oDatabaseRace);

	static cDatabase* instance()      
	{                 
		if(m_opDatabase == NULL) {
			m_opDatabase = new cDatabase();
			m_opDatabase->Init();
		}
		return m_opDatabase;         
	} 

};

}

#endif //cDatabase_H
