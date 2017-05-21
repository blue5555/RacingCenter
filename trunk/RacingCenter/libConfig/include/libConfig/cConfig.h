#ifndef cConfig_H
#define cConfig_H

#include "libCommon/stdafx.h"
#include "libCommon/cThing.h"
#include "cSerialportInfo.h"

#define SHOW_POSITION		0x00000001
#define SHOW_LAPS			0x00000002
#define SHOW_TIME2LEADER	0x00000004
#define SHOW_LAST_LAP		0x00000008
#define SHOW_BEST_LAP		0x00000010
#define SHOW_FUEL_LEVEL		0x00000020
#define SHOW_ACCIDENTS		0x00000040
#define SHOW_CURRENT_TIME   0x00000080
#define SHOW_PROGRESS_BAR   0x00000100
#define SHOW_PROG_SPEED		0x00000200

enum eDisplayRatio
{
	RATIO_4_3  = 0
   ,RATIO_16_9 = 1
};

enum eBaudRate
{
	BAUDRATE_19200 = 0,
	BAUDRATE_38400 = 1
};

/*static char* BAUDRATE_NAMES_STR[] = 
{
	"19200",
	"38400"
};
*/

//static char* ROW_NAMES_STR[] = 
//{
//	"Position",
//	"Laps",
//	"Time2Leader",
//	"Last Lap",
//	"Best Lap",
//	"Fuel",
//	"Accidents",
//	"Current Time"
//};

struct sRaceDisplayConfig
{
	tUInt32				    nRowBitMask;
	//eDisplayRatio		    eRatio;
	tUInt16				    nWidth;
	tUInt16				    nHeight;
	map<tUInt,tUInt>	    oPositions;
	map<tUInt,std::string>	oNames;
	tUInt					oColors[6];
	tUInt					oDisplay[6];

	sRaceDisplayConfig()
	{
		nRowBitMask = 0;
		//eRatio = RATIO_16_9;
		nWidth = 1280;
		nHeight = 720;
	}

	void Init()
	{
		oNames[SHOW_POSITION]	  = "Position";
		oNames[SHOW_LAPS]		  = "Laps";
		oNames[SHOW_TIME2LEADER]  = "Time2Leader";
		oNames[SHOW_LAST_LAP]	  = "Last Lap";
		oNames[SHOW_BEST_LAP]	  = "Best Lap";
		oNames[SHOW_FUEL_LEVEL]	  = "Fuel";
		oNames[SHOW_ACCIDENTS]	  = "Accidents";
		oNames[SHOW_CURRENT_TIME] = "Current Time";
		oNames[SHOW_PROG_SPEED]   = "Speed";

		//oPositions[1] = SHOW_POSITION;
		//oPositions[2] = SHOW_LAPS;
		//oPositions[3] = SHOW_LAST_LAP;
		//oPositions[4] = SHOW_BEST_LAP;
		//oPositions[5] = SHOW_FUEL_LEVEL;
		//oPositions[6] = SHOW_TIME2LEADER;
		//oPositions[7] = SHOW_CURRENT_TIME;

	}

	//tUInt getNumberOfFields()
	//{
	//	tUInt nNumberOfFiels = 0;

	//	if(nRowBitMask & SHOW_POSITION	 ) nNumberOfFiels++;
	//	if(nRowBitMask & SHOW_LAPS		 ) nNumberOfFiels++;
	//	if(nRowBitMask & SHOW_TIME2LEADER) nNumberOfFiels++;
	//	if(nRowBitMask & SHOW_LAST_LAP	 ) nNumberOfFiels++;
	//	if(nRowBitMask & SHOW_BEST_LAP	 ) nNumberOfFiels++;
	//	if(nRowBitMask & SHOW_FUEL_LEVEL ) nNumberOfFiels++;
	//	if(nRowBitMask & SHOW_ACCIDENTS	 ) nNumberOfFiels++;
	//	if(nRowBitMask & SHOW_CURRENT_TIME) nNumberOfFiels++;

	//	return nNumberOfFiels;
	//}
};

struct sDebugMessages
{
	tBool	bMainWindow;
	tBool	bDataProcessor;
	tBool	bCUAdapter;
	tBool	bSerialconnector;
	tBool	bRace;
	tBool	bDriver;
	tBool	bCar;
	tBool	bTrack;
	tBool   bRaceDisplay;
	tBool	bConfig;
	tBool	bDatabase;

	sDebugMessages()
	{
		Init();
	}

	void Init()
	{
		bMainWindow = false;
		bDataProcessor = false;
		bCUAdapter = false;
		bSerialconnector = false;
		bRace = false;
		bDriver = false;
		bCar = false;
		bTrack = false;
		bRaceDisplay = false;
		bConfig = false;
		bDatabase = false;
	}
};

struct sDriverConfig
{
	tBool bEnabled;
	std::string strName;
	std::string strCarName;
	tUInt nDisplayID;
	sDriverConfig(bool i_bEnabled = false, std::string i_strName = "", std::string i_strCarName = "", tUInt i_nDisplayID = 0)
	{
		bEnabled = i_bEnabled;
		strCarName = i_strCarName;
		strName = i_strName;
		nDisplayID = i_nDisplayID;
	};
};

struct sRaceConfig
{
	tUInt	nTime;
	tUInt   nTimingInterval;
	tUInt	nRounds;
	tBool	bDriveFinish;
	tBool	bCountGhost;
	tBool	bBlinkCar;
	tUInt	nRaceFinish;
	tUInt   nRaceMode;
	tUInt	nFuelMode;

    tUInt         oPoints[6];
	sDriverConfig oDrivers[6];

    sRaceConfig() 
    {
        memset(&oDrivers, 0, 6 * sizeof(sDriverConfig));
        memset(&oPoints,  0, 6 * sizeof(tUInt));

        Init();

    }
	
    void Init()
	{
		oPoints[1] = 10;
		oPoints[2] = 8;
		oPoints[3] = 6;
		oPoints[4] = 4;
		oPoints[5] = 2;
		oPoints[6] = 0;

		nTimingInterval = 50;
	}
};

struct sFuelConfig
{
	tBool	bSimulation;
	tBool	bCountRoundsByEmptyFuel;
	tBool	bProgrammCarsByFuel;
	tBool	bSpeedLimiter;
	tBool	bFlashCarLight;
	tUInt	nSpeedInBox;
	tUInt	nValueRed;
	tUInt   nValueYellow;

	sFuelConfig()
	{
		Init();
	}

	void Init()
	{
		bSimulation = false;
		bCountRoundsByEmptyFuel = false;
		bProgrammCarsByFuel = false;
		bSpeedLimiter = false;
		bFlashCarLight = false;
		nSpeedInBox = 0;
		nValueRed = 0;
		nValueYellow = 0;
	}
};

struct sPenalty
{
	tBool	bEnable;
	tBool	bDisqualifiedByEmptyTank;

	sPenalty()
	{
		Init();
	}

	void Init()
	{
		bEnable = false;
		bDisqualifiedByEmptyTank = false;
	}
};

class cConfig : public cThing
{
	//Q_OBJECT

private:
	cConfig() {};
	~cConfig() 
	{ 
		if(m_opConfig != NULL) {
			delete m_opConfig;
		}
	};

	static cConfig* m_opConfig;

public:
    tUInt               m_nMinorVersion;
    tUInt               m_nMajorVersion;

    std::string         m_strDefaultPath;

	sDebugMessages		m_oDebugMessages;
	sDebugMessages		m_oDebugMessagesTiming;
	sRaceDisplayConfig	m_oRaceDisplayConfig;
	sRaceConfig			m_oRaceConfig;
	sFuelConfig			m_oFuelConfig;
	sPenalty			m_oPenalty;
	cSerialportInfo		m_oSerialportInfo;

	eDataSource			m_eDataSource;

	void Init();

	static cConfig* instance()      
	{                 
		if(m_opConfig == NULL) {
			m_opConfig = new cConfig();
			m_opConfig->Init();
		}
		return m_opConfig;         
	} 

    tBool LoadConfig(const std::string& i_oConfigPath = "");
    tBool SaveConfig(const std::string& i_oConfigPath = "");

};

#endif  //cConfig_H