#ifndef cSQLConnector_H
#define cSQLConnector_H

#include "libCommon/stdafx.h"
#include "libCommon/cThing.h"

#include "cDatabaseDriver.h"
#include "cDatabaseCar.h"

#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"

namespace RacingCenter
{

class cSQLConnector : public cThing
{
	QSqlDatabase m_oDatabase;
	QSqlQuery	 m_oQuery;

public:
    cSQLConnector();
    ~cSQLConnector();

	tBool LoadDatabase(const std::string& i_strDatabase);

	tBool AddDriver(const std::string& i_strName);
	cDatabaseDriver GetDriver();
	tBool DeleteDriver(const std::string& i_strName);

	tBool AddCar(const std::string& i_strName);
	cDatabaseCar GetCar();
	tBool DeleteCar(const std::string& i_strName);

};

}

#endif // cXMLDatabase_H