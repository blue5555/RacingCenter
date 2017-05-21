#include "cXMLConfig.h"

#define _FILENAME_ "cXMLConfig: "

#define RACING_CENTER_CONFIG "RacingCenterConfig"

#define RACE_CONFIG "RaceConfig"
#define RACE_CONFIG_BLINK_CAR "BlinkCar"
#define RACE_CONFIG_COUNT_GHOST_CAR "CountGhostCar"
#define RACE_CONFIG_DRIVE_FINISH "DriveFinish"
#define RACE_CONFIG_FUEL_SIMULATION "FuelSimulation"
#define RACE_CONFIG_RACE_FINISH "RaceFinish"
#define RACE_CONFIG_RACE_MODE "RaceMode"
#define RACE_CONFIG_ROUNDS "Rounds"
#define RACE_CONFIG_TIME "Time"
#define RACE_CONFIG_TIMING_INTERVAL "TimingInterval"
#define RACE_CONFIG_LAST_DRIVERS "LastDrivers"

#define RACE_CONFIG_LAST_DRIVER_ENABLED "Enabled"
#define RACE_CONFIG_LAST_DRIVER_NAME "Name"
#define RACE_CONFIG_LAST_DRIVER_CAR "Car"
#define RACE_CONFIG_LAST_DRIVER_DISPLAY "Display"

#define RACE_CONFIG_LAST_POINTS "Points"

#define COM_CONFIG "COMConfig"
#define COM_CONFIG_PORTNAME "PortName"
#define COM_CONFIG_BAUTRATE "BaudRate"

#define RACE_DISPLAY_CONFIG "RaceDisplay"
#define RACE_DISPLAY_CONFIG_HEIGHT "Height"

#define RACE_DISPLAY_CONFIG_WIDTH "Width"
#define RACE_DISPLAY_CONFIG_BITMASK "BitMask"

#define RACE_DISPLAY_CONFIG_COLOR0 "Color0"
#define RACE_DISPLAY_CONFIG_COLOR1 "Color1"
#define RACE_DISPLAY_CONFIG_COLOR2 "Color2"
#define RACE_DISPLAY_CONFIG_COLOR3 "Color3"
#define RACE_DISPLAY_CONFIG_COLOR4 "Color4"
#define RACE_DISPLAY_CONFIG_COLOR5 "Color5"

#define RACE_DISPLAY_CONFIG_DISPLAY0 "Display0"
#define RACE_DISPLAY_CONFIG_DISPLAY1 "Display1"
#define RACE_DISPLAY_CONFIG_DISPLAY2 "Display2"
#define RACE_DISPLAY_CONFIG_DISPLAY3 "Display3"
#define RACE_DISPLAY_CONFIG_DISPLAY4 "Display4"
#define RACE_DISPLAY_CONFIG_DISPLAY5 "Display5"

#define FUEL_CONFIG "FuelConfig"
#define FUEL_CONFIG_COUNT_ROUNDS_BY_EMPTY_FUEL "CountRoundsByEmptyFuel"
#define FUEL_CONFIG_PROGRAMM_CAR_BY_FUEL "ProgrammCarByFuel"
#define FUEL_CONFIG_SIMULATION_FUEL "SimulationFuel"
#define FUEL_CONFIG_SPEED_IN_BOX "SpeedInBox"
#define FUEL_CONFIG_SPEEDLIMITER_IN_BOX "SpeedLimiterInBox"
#define FUEL_CONFIG_LEVEL_RED "FuelLevelRed"
#define FUEL_CONFIG_LEVEL_YELLOW "FuelLevelYellow"
#define FUEL_CONFIG_FLASH_CARLIGHT "FlashCarLight"

#define DATA_SOURCE_CONFIG "DataSourceConfig"

cXMLConfig::cXMLConfig() : cThing(true, false)
{

}

cXMLConfig::~cXMLConfig()
{

}

tBool cXMLConfig::ReadConfig(cConfig* i_opConfig, const std::string& i_strFileName)
{
	QFile oFile(i_strFileName.c_str());

    if(!oFile.open(QIODevice::ReadOnly)) 
    {
		DEBUGMSG("Can't open config file.");
		DEBUGMSG("Create new config file:" << i_strFileName.c_str());
		SaveConfig(i_opConfig, i_strFileName);
        return false;
    } 
    else if( !m_oDomDocument.setContent(&oFile)) 
    {
		DEBUGMSG("Can't set content");
		oFile.close();
        return false;
    }

    const QDomElement& oRaceConfigElement = m_oDomDocument.elementsByTagName(RACE_CONFIG).item(0).toElement();
    ReadRaceConfig( oRaceConfigElement, i_opConfig->m_oRaceConfig );

	const QDomElement& oFuelConfigElement = m_oDomDocument.elementsByTagName(FUEL_CONFIG).item(0).toElement();
	ReadFuelConfig( oFuelConfigElement, i_opConfig->m_oFuelConfig );

	const QDomElement& oCOMConfigElement = m_oDomDocument.elementsByTagName(COM_CONFIG).item(0).toElement();
	ReadCOMConfig( oCOMConfigElement, i_opConfig->m_oSerialportInfo );

	const QDomElement& oRaceDisplayConfigElement = m_oDomDocument.elementsByTagName(RACE_DISPLAY_CONFIG).item(0).toElement();
	ReadRaceDisplayConfig( oRaceDisplayConfigElement, i_opConfig->m_oRaceDisplayConfig );

	const QDomElement& oDataSourceElement = m_oDomDocument.elementsByTagName(DATA_SOURCE_CONFIG).item(0).toElement();
	i_opConfig->m_eDataSource = static_cast<eDataSource>(oDataSourceElement.attribute("DataSource").toInt());

	oFile.close();
	DEBUGMSG("Readed config file succesfully.");

    return true;
}

tBool cXMLConfig::SaveConfig(cConfig* i_opConfig, const std::string& i_strFileName)
{
	QFile oFile(i_strFileName.c_str());

	QDomDocument oDomDocument;

	QDomElement oRacingCenterConfig = oDomDocument.createElement(RACING_CENTER_CONFIG);

	QDomElement oRaceConfig = oDomDocument.createElement(RACE_CONFIG);
	SaveRaceConfig( oRaceConfig, i_opConfig->m_oRaceConfig );
	oRacingCenterConfig.appendChild(oRaceConfig);

	QDomElement oFuelConfig = oDomDocument.createElement(FUEL_CONFIG);
	SaveFuelConfig( oFuelConfig, i_opConfig->m_oFuelConfig );
	oRacingCenterConfig.appendChild(oFuelConfig);

	QDomElement oCOMConfig = oDomDocument.createElement(COM_CONFIG);
	SaveCOMConfig( oCOMConfig, i_opConfig->m_oSerialportInfo );
	oRacingCenterConfig.appendChild(oCOMConfig);

	QDomElement oRaceDisplayConfig = oDomDocument.createElement(RACE_DISPLAY_CONFIG);
	SaveRaceDisplayConfig( oRaceDisplayConfig, i_opConfig->m_oRaceDisplayConfig );
	oRacingCenterConfig.appendChild(oRaceDisplayConfig);

	QDomElement oDataSource = oDomDocument.createElement(DATA_SOURCE_CONFIG);
	oDataSource.setAttribute("DataSource", i_opConfig->m_eDataSource);
	oRacingCenterConfig.appendChild(oDataSource);

	oDomDocument.appendChild(oRacingCenterConfig);

	if(oFile.open(QIODevice::WriteOnly))
	{
		QTextStream ts( &oFile );
		ts << oDomDocument.toString();
		oFile.close();
		return true;
	}
	else
	{
		if(m_bDebug) 
		{
			DEBUGERROR("Can't open config file for writing.");
		}
		return false;
	}

}

tBool cXMLConfig::ReadFuelConfig(const QDomElement& io_oElement, sFuelConfig& i_oFuelConfig )
{
	i_oFuelConfig.bCountRoundsByEmptyFuel = io_oElement.attribute(FUEL_CONFIG_COUNT_ROUNDS_BY_EMPTY_FUEL) == "true" ? true : false;
	i_oFuelConfig.bProgrammCarsByFuel	  = io_oElement.attribute(FUEL_CONFIG_PROGRAMM_CAR_BY_FUEL) == "true" ? true : false;
	i_oFuelConfig.bSimulation			  = io_oElement.attribute(FUEL_CONFIG_SIMULATION_FUEL) == "true" ? true : false;
	i_oFuelConfig.nSpeedInBox			  = io_oElement.attribute(FUEL_CONFIG_SPEED_IN_BOX).toUInt();
	i_oFuelConfig.bSpeedLimiter			  = io_oElement.attribute(FUEL_CONFIG_SPEEDLIMITER_IN_BOX) == "true" ? true : false;
	i_oFuelConfig.nValueRed				  = io_oElement.attribute(FUEL_CONFIG_LEVEL_RED).toUInt();
	i_oFuelConfig.nValueYellow			  = io_oElement.attribute(FUEL_CONFIG_LEVEL_YELLOW).toUInt();
	i_oFuelConfig.bFlashCarLight		  = io_oElement.attribute(FUEL_CONFIG_FLASH_CARLIGHT) == "true" ? true : false;

	return true;
}

tBool cXMLConfig::SaveFuelConfig(QDomElement& io_oElement, const sFuelConfig& i_oFuelConfig )
{
	io_oElement.setAttribute(FUEL_CONFIG_COUNT_ROUNDS_BY_EMPTY_FUEL, i_oFuelConfig.bCountRoundsByEmptyFuel ? "true" : "false");   
	io_oElement.setAttribute(FUEL_CONFIG_PROGRAMM_CAR_BY_FUEL,		 i_oFuelConfig.bProgrammCarsByFuel ? "true" : "false");   
	io_oElement.setAttribute(FUEL_CONFIG_SIMULATION_FUEL,			 i_oFuelConfig.bSimulation ? "true" : "false");
	io_oElement.setAttribute(FUEL_CONFIG_SPEED_IN_BOX,			     i_oFuelConfig.nSpeedInBox);
	io_oElement.setAttribute(FUEL_CONFIG_SPEEDLIMITER_IN_BOX,		 i_oFuelConfig.bSpeedLimiter ? "true" : "false"); 
	io_oElement.setAttribute(FUEL_CONFIG_LEVEL_RED,				     i_oFuelConfig.nValueRed);
	io_oElement.setAttribute(FUEL_CONFIG_LEVEL_YELLOW,				 i_oFuelConfig.nValueYellow);
	io_oElement.setAttribute(FUEL_CONFIG_FLASH_CARLIGHT,			 i_oFuelConfig.bFlashCarLight ? "true" : "false");

	return true;
}

tBool cXMLConfig::ReadRaceDisplayConfig(const QDomElement& io_oElement, sRaceDisplayConfig& i_oRaceDisplayConfig )
{
	i_oRaceDisplayConfig.nHeight		= io_oElement.attribute(RACE_DISPLAY_CONFIG_HEIGHT).toUInt();
	i_oRaceDisplayConfig.nWidth			= io_oElement.attribute(RACE_DISPLAY_CONFIG_WIDTH).toUInt();
	i_oRaceDisplayConfig.nRowBitMask	= io_oElement.attribute(RACE_DISPLAY_CONFIG_BITMASK).toUInt();

	i_oRaceDisplayConfig.oColors[0]		= io_oElement.attribute(RACE_DISPLAY_CONFIG_COLOR0).toUInt();
	i_oRaceDisplayConfig.oColors[1]		= io_oElement.attribute(RACE_DISPLAY_CONFIG_COLOR1).toUInt();
	i_oRaceDisplayConfig.oColors[2]		= io_oElement.attribute(RACE_DISPLAY_CONFIG_COLOR2).toUInt();
	i_oRaceDisplayConfig.oColors[3]		= io_oElement.attribute(RACE_DISPLAY_CONFIG_COLOR3).toUInt();
	i_oRaceDisplayConfig.oColors[4]		= io_oElement.attribute(RACE_DISPLAY_CONFIG_COLOR4).toUInt();
	i_oRaceDisplayConfig.oColors[5]		= io_oElement.attribute(RACE_DISPLAY_CONFIG_COLOR5).toUInt();

	return true;
}

tBool cXMLConfig::SaveRaceDisplayConfig(QDomElement& io_oElement, const sRaceDisplayConfig& i_oRaceDisplayConfig )
{
	io_oElement.setAttribute(RACE_DISPLAY_CONFIG_HEIGHT,  i_oRaceDisplayConfig.nHeight);
	io_oElement.setAttribute(RACE_DISPLAY_CONFIG_WIDTH,   i_oRaceDisplayConfig.nWidth);			
	io_oElement.setAttribute(RACE_DISPLAY_CONFIG_BITMASK, i_oRaceDisplayConfig.nRowBitMask);	

	io_oElement.setAttribute(RACE_DISPLAY_CONFIG_COLOR0, i_oRaceDisplayConfig.oColors[0]);		
	io_oElement.setAttribute(RACE_DISPLAY_CONFIG_COLOR1, i_oRaceDisplayConfig.oColors[1]);		
	io_oElement.setAttribute(RACE_DISPLAY_CONFIG_COLOR2, i_oRaceDisplayConfig.oColors[2]);		
	io_oElement.setAttribute(RACE_DISPLAY_CONFIG_COLOR3, i_oRaceDisplayConfig.oColors[3]);		
	io_oElement.setAttribute(RACE_DISPLAY_CONFIG_COLOR4, i_oRaceDisplayConfig.oColors[4]);		
	io_oElement.setAttribute(RACE_DISPLAY_CONFIG_COLOR5, i_oRaceDisplayConfig.oColors[5]);		

	return true;
}


tBool cXMLConfig::SaveCOMConfig(QDomElement& io_oElement, const cSerialportInfo& i_oCOMConfig )
{
	io_oElement.setAttribute(COM_CONFIG_PORTNAME,	i_oCOMConfig.PortName());
	io_oElement.setAttribute(COM_CONFIG_BAUTRATE,   i_oCOMConfig.BaudRate());

	return true;
}

tBool cXMLConfig::ReadCOMConfig(const QDomElement& i_oElement, cSerialportInfo& i_oCOMConfig )
{
	i_oCOMConfig.BaudRate(i_oElement.attribute(COM_CONFIG_BAUTRATE).toUInt());
	i_oCOMConfig.PortName(i_oElement.attribute(COM_CONFIG_PORTNAME));

	return true;
}

tBool cXMLConfig::ReadRaceConfig(const QDomElement& i_oElement, sRaceConfig& io_oRaceConfig )
{
    io_oRaceConfig.bBlinkCar        = i_oElement.attribute(RACE_CONFIG_BLINK_CAR) == "true" ? true : false;
    io_oRaceConfig.bCountGhost      = i_oElement.attribute(RACE_CONFIG_COUNT_GHOST_CAR) == "true" ? true : false;
    io_oRaceConfig.bDriveFinish     = i_oElement.attribute(RACE_CONFIG_DRIVE_FINISH) == "true" ? true : false;
    
    io_oRaceConfig.nRaceFinish      = static_cast<eRaceFinish>(i_oElement.attribute(RACE_CONFIG_RACE_FINISH).toUInt());       
    io_oRaceConfig.nRaceMode        = static_cast<eRaceMode>(i_oElement.attribute(RACE_CONFIG_RACE_MODE).toUInt());
    
    io_oRaceConfig.nRounds          = i_oElement.attribute(RACE_CONFIG_ROUNDS).toUInt();
    io_oRaceConfig.nTime            = i_oElement.attribute(RACE_CONFIG_TIME).toUInt();

    io_oRaceConfig.nTimingInterval  = i_oElement.attribute(RACE_CONFIG_TIMING_INTERVAL).toUInt();

    QDomNodeList oLastDrivers = i_oElement.elementsByTagName(RACE_CONFIG_LAST_DRIVERS).at(0).childNodes();
    for (tUInt n = 0; n < 6; n++)
    {
        sDriverConfig& oDriverConfig = io_oRaceConfig.oDrivers[n];
        const QDomElement& oElement = oLastDrivers.at(n).toElement();

        oDriverConfig.bEnabled      = oElement.attribute(RACE_CONFIG_LAST_DRIVER_ENABLED) == "true" ? true : false;
        oDriverConfig.strName       = oElement.attribute(RACE_CONFIG_LAST_DRIVER_NAME).toStdString();
        oDriverConfig.strCarName    = oElement.attribute(RACE_CONFIG_LAST_DRIVER_CAR).toStdString();
        oDriverConfig.nDisplayID    = oElement.attribute(RACE_CONFIG_LAST_DRIVER_DISPLAY).toUInt();
    }

    //QDomNodeList oPoints = i_oElement.elementsByTagName(RACE_CONFIG_LAST_POINTS).at(0).childNodes();
    //for (tUInt n = 0; n < 6; n++)
    //{
    //    io_oRaceConfig.oPoints[n] = ;
    //}

    return true;
}

tBool cXMLConfig::SaveRaceConfig(QDomElement& io_oElement, const sRaceConfig& i_oRaceConfig )
{
    io_oElement.setAttribute(RACE_CONFIG_BLINK_CAR,         i_oRaceConfig.bBlinkCar ? "true" : "false");
    io_oElement.setAttribute(RACE_CONFIG_COUNT_GHOST_CAR,   i_oRaceConfig.bCountGhost ? "true" : "false");
    io_oElement.setAttribute(RACE_CONFIG_DRIVE_FINISH,      i_oRaceConfig.bDriveFinish ? "true" : "false");

    io_oElement.setAttribute(RACE_CONFIG_RACE_FINISH,       i_oRaceConfig.nRaceFinish);
    io_oElement.setAttribute(RACE_CONFIG_RACE_MODE,         i_oRaceConfig.nRaceMode); 

    io_oElement.setAttribute(RACE_CONFIG_ROUNDS,            i_oRaceConfig.nRounds);
    io_oElement.setAttribute(RACE_CONFIG_TIME,              i_oRaceConfig.nTime);

    io_oElement.setAttribute(RACE_CONFIG_TIMING_INTERVAL,   i_oRaceConfig.nTimingInterval); 

    
    QDomElement oLastDrivers = m_oDomDocument.createElement("LastDrivers");
    for (tUInt n = 0; n < 6; n++)
    {
        const sDriverConfig& oDriverConfig = i_oRaceConfig.oDrivers[n];
        QDomElement oElement = m_oDomDocument.createElement(QString("Driver%1").arg(n));

        oElement.setAttribute(RACE_CONFIG_LAST_DRIVER_ENABLED,  oDriverConfig.bEnabled  ? "true" : "false");
        oElement.setAttribute(RACE_CONFIG_LAST_DRIVER_NAME,     oDriverConfig.strName.c_str());
        oElement.setAttribute(RACE_CONFIG_LAST_DRIVER_CAR,      oDriverConfig.strCarName.c_str());
        oElement.setAttribute(RACE_CONFIG_LAST_DRIVER_DISPLAY,  oDriverConfig.nDisplayID);

        oLastDrivers.appendChild(oElement);
    }

    io_oElement.appendChild(oLastDrivers);

    //QDomNodeList oPoints = i_oElement.elementsByTagName(RACE_CONFIG_LAST_POINTS).at(0).childNodes();
    //for (tUInt n = 0; n < 6; n++)
    //{
    //    io_oRaceConfig.oPoints[n] = ;
    //}

    return true;
}