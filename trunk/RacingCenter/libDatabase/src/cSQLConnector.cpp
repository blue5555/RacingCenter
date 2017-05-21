#include "libDatabase/cSQLConnector.h"

using namespace RacingCenter;

#define _FILENAME_ "cSQLConnector: "

#define RACING_CENTER_DATABASE "RacingCenterDatabase"

cSQLConnector::cSQLConnector() : cThing(true, false)
{
	qDebug() << QSqlDatabase::drivers();
	m_oDatabase = QSqlDatabase::addDatabase("QSQLITE");
}

cSQLConnector::~cSQLConnector()
{

}

tBool cSQLConnector::LoadDatabase(const std::string& i_strDatabase)
{
	m_oDatabase.setDatabaseName(i_strDatabase.c_str());
	if(m_oDatabase.open())
	{
		m_oQuery = QSqlQuery(m_oDatabase);
		if(!m_oQuery.prepare("CREATE TABLE IF NOT EXISTS DRIVERS( ID INT PRIMARY KEY NOT NULL, NAME TEXT NOT NULL);"))
		{
			qDebug() << m_oQuery.lastError().text();
		}
		if( m_oQuery.exec() )
		{
			int a = 3;
		}
		else
		{
			qDebug() << m_oQuery.lastError().text();
		}

		if(m_oQuery.exec("CREATE TABLE IF NOT EXISTS 'Cars';"))
		{

		}

		if(m_oQuery.exec("CREATE TABLE IF NOT EXISTS 'Races';"))
		{

		}


	}

	return true;
}