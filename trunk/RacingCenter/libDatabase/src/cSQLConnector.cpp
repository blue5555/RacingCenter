#include "libDatabase/cSQLConnector.h"

using namespace RacingCenter;

#define _FILENAME_ "cSQLConnector: "

#define RACING_CENTER_DATABASE "RacingCenterDatabase"

#define ADD_COLUMN(TABLE, NAME, TYPE) "ALTER TABLE " + QString(TABLE) + " ADD COLUMN " + QString(NAME) + " " + QString(TYPE)

#define ADD_ROW(TABLE, COLUMN, VALUES) "INSERT INTO " + QString(TABLE) + " ( " + QString(COLUMN) +  " ) VALUES ( " + QString(VALUES) + " )"
#define DELETE_ROW(TABLE, CONDITION) "DELETE FROM " + QString(TABLE) + " WHERE " + QString(CONDITION)

#define UPDATE_ROW(TABLE, COLUMN, VALUE, CONDITION) "UPDATE " + QString(TABLE) + " SET " + QString(COLUMN) + " " + QString(VALUE) + " WHERE " + QString(CONDITION)

#define SELECT_WHERE(COLUMN, TABLE, CONDITION) "SELECT " + QString(COLUMN) + " FROM " + QString(TABLE) + " WHERE " + QString(CONDITION)
#define SELECT(COLUMN, TABLE) "SELECT " + QString(COLUMN) + " FROM " + QString(TABLE)

#define SELECT_ALL_WHERE(TABLE, CONDITION) SELECT_WHERE("*", TABLE, CONDITION)
#define SELECT_ALL(TABLE) SELECT("*", TABLE)


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
		InitDatabase();

		int a = GetNumberOfEntries("Drivers");
		int b = GetNumberOfEntries("Cars");

		int c = 2;
	}
	return true;
}

tBool cSQLConnector::InitDatabase()
{
	QSqlQuery oQuery(m_oDatabase);
	if(oQuery.exec("CREATE TABLE IF NOT EXISTS Drivers( Name TEXT );"))
	{
		cDatabaseDriver oDatabaseDriver("");
		const QStringList& oColumnName = oDatabaseDriver.GetColumnNames();
		const QStringList& oColumnType = oDatabaseDriver.GetColumnType();
		for (tUInt n = 0; n < oColumnName.size(); n++)
		{		
			oQuery.exec(ADD_COLUMN("Drivers", oColumnName.at(n), oColumnType.at(n)));
		}
	}
	else
	{
		qDebug() << oQuery.lastError().text();
	}

	if(oQuery.exec("CREATE TABLE IF NOT EXISTS Cars ( Name TEXT );"))
	{
		cDatabaseCar oCar("");
		const QStringList& oColumnName = oCar.GetColumnNames();
		const QStringList& oColumnType = oCar.GetColumnType();

		tUInt k = oColumnName.size();

		for (tUInt n = 0; n < oColumnName.size(); n++)
		{		
			oQuery.exec(ADD_COLUMN("Cars", oColumnName.at(n), oColumnType.at(n)));
		}
	}
	else
	{
		qDebug() << oQuery.lastError().text();
	}

	if(oQuery.exec("CREATE TABLE IF NOT EXISTS Races;"))
	{

	}
	else
	{
		qDebug() << oQuery.lastError().text();
	}

	return true;
}

tBool cSQLConnector::EntityExists(const std::string& i_strEntity, const std::string& i_strName)
{
	QSqlQuery oQuery;
	if(ExecQuery( SELECT_ALL(i_strEntity.c_str()), oQuery) )
	{
		tUInt nCounter = 0;
		while(oQuery.next())
		{
			if(oQuery.value(0).toString().toStdString() == i_strName)
			{
				return true;
			}
		}
		return false;
	}
	return false;	
}

tUInt cSQLConnector::GetNumberOfEntries(const std::string& i_strEntry)
{
	QSqlQuery oQuery;
	if(ExecQuery( SELECT_ALL(i_strEntry.c_str()), oQuery) )
	{
		tUInt nCounter = 0;
		while(oQuery.next())
		{
			nCounter++;
		}
		return nCounter;
	}
	return 0;
}

tBool cSQLConnector::AddDriver(const cDatabaseDriver& i_oDatabaseDriver)
{
	if(ExecQuery( ADD_ROW("Drivers", "Name", QString("'%1'").arg(i_oDatabaseDriver.GetName().c_str() ) ) ) )
	{
		return true;
	}
	return false;
}

tBool cSQLConnector::DeleteDriver(const std::string& i_strName)
{
	QSqlQuery oQuery;
	if(ExecQuery( DELETE_ROW("Drivers", QString("NAME = '%1'").arg(i_strName.c_str() ) ) ) ) 
	{
		return true;
	}
	return false;
}

tBool cSQLConnector::AddCar(const cDatabaseCar& i_oDatabaseCar)
{
	QString columns = i_oDatabaseCar.GetColumnNames().join(", ");
	QString value = i_oDatabaseCar.GetColumnValues().join(", ");

	if(ExecQuery( ADD_ROW("Cars", columns, value) ) )
	{
		return true;
	}
	return false;
}

tBool cSQLConnector::DeleteCar(const std::string& i_strName)
{
	QSqlQuery oQuery;
	if(ExecQuery( DELETE_ROW("Cars", QString("NAME = '%1'").arg(i_strName.c_str() ) ) ) ) 
	{
		return true;
	}
	return false;
}

std::list<cDatabaseDriver> cSQLConnector::GetAllDrivers()
{
	std::list<cDatabaseDriver> oDrivers;
	QSqlQuery oQuery;
	if(ExecQuery( SELECT_ALL("Drivers"), oQuery) )
	{
		while(oQuery.next())
		{
			cDatabaseDriver oDriver("");
			GetDriver(oQuery.value(0).toString().toStdString(), oDriver);
			oDrivers.push_back( oDriver );
		}
	}
	return oDrivers;
}

tBool cSQLConnector::GetDriver(const std::string& i_strName, cDatabaseDriver& o_oDatabaseDriver)
{
	QSqlQuery oQuery;
	if(ExecQuery( SELECT_ALL_WHERE("Drivers", QString("NAME = '%1' ").arg(i_strName.c_str()) ), oQuery ) )
	{
		tUInt nCounter = 0;
		while(oQuery.next())
		{
			if(nCounter == 0)
			{
				QStringList oValues;
				for(tUInt n = 0; n < o_oDatabaseDriver.GetColumnNames().size(); n++)
				{
					oValues.append(oQuery.value(n).toString());
				}
				o_oDatabaseDriver.Set(oValues);
			}
			else
			{
				return false;
			}
			nCounter++;
		}
		return true;
	}

	return false;
}

tBool cSQLConnector::UpdateDriver(const cDatabaseDriver& i_oDriver)
{
	DeleteDriver(i_oDriver.GetName());
	AddDriver(i_oDriver);
	return true;
}

std::list<cDatabaseCar> cSQLConnector::GetAllCars()
{
	std::list<cDatabaseCar> oCars;
	QSqlQuery oQuery;
	if(ExecQuery( SELECT_ALL("Cars"), oQuery) )
	{
		while(oQuery.next())
		{
			cDatabaseCar oCar("");
			GetCar(oQuery.value(0).toString().toStdString(), oCar);
			oCars.push_back( oCar );
		}
	}
	return oCars;
}

tBool cSQLConnector::UpdateCar(const cDatabaseCar& i_oCar)
{
	DeleteCar(i_oCar.GetName());
	AddCar(i_oCar);
	return true;
}

tBool cSQLConnector::GetCar(const std::string& i_strName, cDatabaseCar& o_oDatabaseCar)
{
	QSqlQuery oQuery;
	if(ExecQuery( SELECT_ALL_WHERE("Cars", QString("NAME = '%1' ").arg(i_strName.c_str()) ), oQuery) )
	{
		tUInt nCounter = 0;
		while(oQuery.next())
		{
			if(nCounter == 0)
			{
				QStringList oValues;
				for(tUInt n = 0; n < o_oDatabaseCar.GetColumnNames().size(); n++)
				{
					oValues.append(oQuery.value(n).toString());
				}
				o_oDatabaseCar.Set(oValues);
			}
			else
			{
				return false;
			}
			nCounter++;
		}
		return true;
	}

	return false;
}

tBool cSQLConnector::ExecQuery(const QString& i_strQuery, QSqlQuery& o_oQuery)
{
	qDebug() << "Query: " << i_strQuery;
	o_oQuery = QSqlQuery(m_oDatabase);
	if(o_oQuery.prepare(i_strQuery) )
	{
		o_oQuery.exec(i_strQuery);
		return true;
	}
	else
	{
		qDebug() << o_oQuery.lastError().text();
		return false;
	}
}