//#include "libDatabase/cXMLDatabase.h"
//
//using namespace RacingCenter;
//
//#define _FILENAME_ "cXMLDatabase: "
//
//#define RACING_CENTER_DATABASE "RacingCenterDatabase"
//
//#define DRIVERS "Drivers"
//#define DRIVER "Driver"
//
//#define CARS "Cars"
//#define CAR "Car"
//
//#define NAME "Name"
//#define DRIVER_POINTS "Points"
//#define DRIVER_CHAMPIONSHIPS "Championships"
//#define DRIVER_RACES "Races"
//
//#define DRIVER_WIN_RACES "WinRaces"
//#define DRIVER_WIN_CHAMPIONSHIPS "WinChampionships"
//
//#define CAR_TANKCAPACITY "TankCapacity"
//#define CAR_TANKSPEED "TankSpeed"
//
//#define CAR_CONSUMPTION "Consumption"
//#define CAR_SPEED "Speed"
//#define CAR_BRAKE "Brake"
//#define CAR_FUEL "Fuel"
//
//cXMLDatabase::cXMLDatabase() : cThing(true, false)
//{
//
//}
//
//cXMLDatabase::~cXMLDatabase()
//{
//
//}
//
//tBool cXMLDatabase::ReadDatabase(cDatabase* i_opDatabase, const std::string& i_oFilePath)
//{
//	QFile oFile(i_oFilePath.c_str());
//
//    if(!oFile.open(QIODevice::ReadOnly)) 
//    {
//		DEBUGMSG("Can't open database file.");
//		DEBUGMSG("Create new database file.");
//		SaveDatabase(i_opDatabase, i_oFilePath);
//		return false;
//	} 
//	else if( !m_oDomDocument.setContent(&oFile)) 
//	{
//		DEBUGMSG("Can't set content");
//		oFile.close();
//		return false;
//    }
//
//    const QDomElement& oDrivers = m_oDomDocument.elementsByTagName(DRIVERS).item(0).toElement();
//    ReadDatabaseDrivers( oDrivers, i_opDatabase );
//
//    const QDomElement& oCars = m_oDomDocument.elementsByTagName(CARS).item(0).toElement();
//    ReadDatabaseCars( oCars, i_opDatabase );
//
//    oFile.close();
//	DEBUGMSG("Readed database file succesfully.");
//
//    return true;
//}
//
//tBool cXMLDatabase::SaveDatabase(cDatabase* i_opDatabase, const std::string& i_oFilePath)
//{
//    QDomDocument oDomDocument;
//
//    QDomElement oRacingCenterDatabase = oDomDocument.createElement(RACING_CENTER_DATABASE);
//
//    QDomElement oDrivers = oDomDocument.createElement(DRIVERS);
//    SaveDatabaseDrivers( oDrivers, i_opDatabase );
//    oRacingCenterDatabase.appendChild(oDrivers);
//
//    QDomElement oCars = oDomDocument.createElement(CARS);
//    SaveDatabaseCars( oCars, i_opDatabase );
//    oRacingCenterDatabase.appendChild(oCars);
//
//    oDomDocument.appendChild(oRacingCenterDatabase);
//
//	QFile oFile(i_oFilePath.c_str());
//
//	if(oFile.open(QIODevice::WriteOnly))
//	{
//		QTextStream ts( &oFile );
//		ts << oDomDocument.toString();
//		oFile.close();
//		return true;
//	}
//	else
//	{
//		if(m_bDebug) 
//		{
//			DEBUGERROR("Can't open config file for writing.");
//		}
//		return false;
//	}
//}
//
//tBool cXMLDatabase::ReadDatabaseDrivers(const QDomElement& i_oElement, cDatabase* io_opDatabase )
//{
//    QDomNodeList oDrivers = i_oElement.childNodes();
//
//    for (tInt64 n = 0; n < oDrivers.size(); n++)
//    {
//        QDomElement oElement = oDrivers.item(n).toElement();
//        io_opDatabase->AddDriver(ReadDriver(oElement));
//    }
//
//    return true;
//}
//
//cDatabaseDriver cXMLDatabase::ReadDriver(const QDomElement& i_oElement)
//{
//    cDatabaseDriver oDriver("");
//    
//    oDriver.SetName(                    i_oElement.attribute(NAME).toStdString() );
//    oDriver.SetPoints(                  i_oElement.attribute(DRIVER_POINTS).toUInt() );
//    oDriver.SetDrivingChampionships(    i_oElement.attribute(DRIVER_CHAMPIONSHIPS).toUInt() );
//    oDriver.SetDrivingRaces(            i_oElement.attribute(DRIVER_RACES).toUInt() );
//
//    oDriver.SetWinRaces(                i_oElement.attribute(DRIVER_WIN_RACES).toUInt() );
//    oDriver.SetWinChampionships(        i_oElement.attribute(DRIVER_WIN_CHAMPIONSHIPS).toUInt() );
//
//    return oDriver;
//}
//
//tBool cXMLDatabase::SaveDatabaseDrivers(QDomElement& i_oDrivers, cDatabase* io_opDatabase)
//{
//    const tDatabaseDrivers& oDrivers = io_opDatabase->GetAllDrivers();
//
//    for (tInt64 n = 0; n < oDrivers.size(); n++)
//    {
//        QDomElement oElement = m_oDomDocument.createElement(DRIVER);
//        const cDatabaseDriver& oDriver = oDrivers[n];
//
//        oElement.setAttribute(NAME,                      oDriver.GetName().c_str());                 
//        oElement.setAttribute(DRIVER_POINTS,             oDriver.GetPoints());
//        oElement.setAttribute(DRIVER_CHAMPIONSHIPS,      oDriver.GetDrivingChampionships());
//        oElement.setAttribute(DRIVER_RACES,              oDriver.GetDrivingRaces());
//
//        oElement.setAttribute(DRIVER_WIN_RACES,          oDriver.GetWinRaces());      
//        oElement.setAttribute(DRIVER_WIN_CHAMPIONSHIPS,  oDriver.GetWinChampionships());     
//
//        i_oDrivers.appendChild(oElement);
//    }
//
//    return true;
//}
//
//tBool cXMLDatabase::ReadDatabaseCars(const QDomElement& i_oElement, cDatabase* io_opDatabase )
//{
//    QDomNodeList oCars = i_oElement.childNodes();
//
//    for (tInt64 n = 0; n < oCars.size(); n++)
//    {
//        QDomElement oElement = oCars.item(n).toElement();
//        io_opDatabase->AddCar(ReadCar(oElement));
//    }
//
//    return true;
//}
//
//cDatabaseCar cXMLDatabase::ReadCar(const QDomElement& i_oElement)
//{
//    cDatabaseCar oCar("");
//
//    oCar.SetName( i_oElement.attribute(NAME).toStdString() );
//
//    oCar.SetTankCapacity( i_oElement.attribute(CAR_TANKCAPACITY).toDouble() );
//
//    QDomElement oConsumption = i_oElement.elementsByTagName(CAR_CONSUMPTION).item(0).toElement();
//    QDomElement oSpeed       = i_oElement.elementsByTagName(CAR_SPEED).item(0).toElement();
//    for (tUInt n = 0; n < 16; n++)
//    {
//        oCar.SetConsumption(n, oConsumption.attribute(CAR_CONSUMPTION + QString("%1").arg(n)).toDouble());
//        oCar.SetSpeed(n, oSpeed.attribute(CAR_SPEED + QString("%1").arg(n)).toUInt());
//    }
//
//    oCar.SetTankSpeed( i_oElement.attribute(CAR_TANKSPEED).toDouble() );
//
//    oCar.SetSpeed(i_oElement.attribute(CAR_SPEED).toUInt());
//    oCar.SetBrake(i_oElement.attribute(CAR_BRAKE).toUInt());
//    oCar.SetFuel( i_oElement.attribute(CAR_FUEL).toUInt());
//
//    return oCar;
//}
//
//tBool cXMLDatabase::SaveDatabaseCars(QDomElement& i_oCars, cDatabase* io_opDatabase)
//{
//
//    const tDatabaseCars& oCars = io_opDatabase->GetAllCars();
//
//    for (tInt64 n = 0; n < oCars.size(); n++)
//    {
//        QDomElement oElement = m_oDomDocument.createElement(CAR);
//        const cDatabaseCar& oCar = oCars[n];
//
//        oElement.setAttribute(NAME,             oCar.GetName().c_str());                 
//        oElement.setAttribute(CAR_TANKCAPACITY, oCar.GetTankCapacity());
//
//        oElement.setAttribute(CAR_TANKSPEED, oCar.GetTankSpeed());  
//
//        oElement.setAttribute(CAR_SPEED, oCar.GetSpeed());      
//        oElement.setAttribute(CAR_BRAKE, oCar.GetBrake());      
//        oElement.setAttribute(CAR_FUEL,  oCar.GetFuel());       
//
//        QDomElement oConsumption = m_oDomDocument.createElement(CAR_CONSUMPTION);
//        QDomElement oSpeed       = m_oDomDocument.createElement(CAR_SPEED);
//        for (tUInt n = 0; n < 16; n++)
//        {
//            oConsumption.setAttribute(CAR_CONSUMPTION + QString("%1").arg(n), oCar.GetConsumption(n)); 
//            oSpeed.setAttribute(CAR_SPEED + QString("%1").arg(n), oCar.GetSpeed(n));
//        }
//
//        oElement.appendChild(oConsumption);
//        oElement.appendChild(oSpeed);
//
//        i_oCars.appendChild(oElement);
//    }
//
//    return true;
//}
//
//
