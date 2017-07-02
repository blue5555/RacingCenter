#include <cDatabaseDriver.h>

cDatabaseDriver::cDatabaseDriver(const std::string& i_strName) : cDatabaseBaseElement(i_strName)
{
    m_nDrivingChampionships = 0;
    m_nDrivingRaces = 0;
    m_nPoints = 0;
    m_nWinChampionships = 0;
    m_nWinRaces = 0;

	Init();
}

cDatabaseDriver::~cDatabaseDriver()
{

}

tBool cDatabaseDriver::Init()
{
	AddColumn("Name", "TEXT");
	AddColumn("DrivingChampionships", "INTEGER");
	AddColumn("DrivingRaces", "INTEGER");
	AddColumn("Points", "INTEGER");
	AddColumn("WinChampionships", "INTEGER");
	AddColumn("WinRaces", "INTEGER");

	return true;
}

tBool cDatabaseDriver::Set(const QStringList& i_oValues)
{
	SetName(i_oValues.at(0).toStdString());
	SetDrivingChampionships(i_oValues.at(1).toInt());
	SetDrivingRaces(i_oValues.at(2).toInt());
	SetPoints(i_oValues.at(3).toInt());
	SetWinChampionships(i_oValues.at(4).toInt());
	SetWinRaces(i_oValues.at(5).toInt());

	return true;
}

QStringList cDatabaseDriver::GetColumnValues() const
{
	QStringList oValues;

	oValues.append(GetName().c_str());
	oValues.append(QString::number(m_nDrivingChampionships));
	oValues.append(QString::number(m_nDrivingRaces));
	oValues.append(QString::number(m_nPoints));
	oValues.append(QString::number(m_nWinChampionships));
	oValues.append(QString::number(m_nWinRaces));

	return oValues;
}
