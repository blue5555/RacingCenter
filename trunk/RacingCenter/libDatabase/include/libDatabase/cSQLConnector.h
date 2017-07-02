#ifndef cSQLConnector_H
#define cSQLConnector_H

#include "libCommon/stdafx.h"
#include "libCommon/cThing.h"

#include "cDatabaseDriver.h"
#include "cDatabaseCar.h"

#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"
#include "QSqlRecord"

namespace RacingCenter
{

class cSQLConnector : public cThing
{
	QSqlDatabase m_oDatabase;

	tBool InitDatabase();
	tBool ExecQuery(const QString& i_strQuery, QSqlQuery& o_oQuery = QSqlQuery());

public:
    cSQLConnector();
    ~cSQLConnector();

	tBool LoadDatabase(const std::string& i_strDatabase);

	tUInt GetNumberOfEntries(const std::string& i_strEntry);
	tBool EntityExists(const std::string& i_strEntity, const std::string& i_strName);

	std::list<cDatabaseDriver> GetAllDrivers();
	std::list<cDatabaseCar> GetAllCars();

	tBool AddDriver(const cDatabaseDriver& i_oDatabaseDriver);
	tBool UpdateDriver(const cDatabaseDriver& i_oDriver);
	tBool GetDriver(const std::string& i_strName, cDatabaseDriver& o_oDatabaseDriver);
	tBool DeleteDriver(const std::string& i_strName);

	tBool AddCar(const cDatabaseCar& i_oDatabaseCar);
	tBool UpdateCar(const cDatabaseCar& i_oCar);	
	tBool GetCar(const std::string& i_strName, cDatabaseCar& o_oDatabaseCar);
	tBool DeleteCar(const std::string& i_strName);

};

}

#endif // cXMLDatabase_H