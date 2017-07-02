#ifndef commonConnectionTypes_H
#define commonConnectionTypes_H

#include "types.h"
#include <string.h>

using namespace std;

#define NUMBER_OF_PACKAGES 10

#define HEADER_MAJOR_VERSION 1
#define HEADER_MINOR_VERSION 0

enum eMesageType
{
	MESSAGE_CONTROL = 0,
	MESSAGE_DRIVER = 1,
	//MESSAGE_CONTROLLER = ,
	MESSAGE_DRIVER_LIST = 2,
	MESSAGE_CAR_LIST = 3
};

enum eControlMessage
{
	CONTROL_START = 0,
	CONTROL_PAUSE,
	CONTROL_STOP,
	CONTROL_GET_DRIVERLIST,
	CONTROL_GET_CARLIST
};

#pragma pack(1) // 1 byte alignment
struct sConnectionMessageHeader
{
	tInt8  nMajorVersion;					// 0
	tInt8  nMinorVersion;					// 1
	tInt8  nFrameCounter;					// 2
	tInt16 nMessageSize;					// 3
	tInt64 n64TimeStamp;					// 5
	tInt8  nNumberOfPackages;				// 13
	tInt8  nPackages[NUMBER_OF_PACKAGES];	// 14 
	sConnectionMessageHeader()
	{
		nMajorVersion = HEADER_MAJOR_VERSION;
		nMinorVersion = HEADER_MINOR_VERSION;
		nFrameCounter = 0;
		n64TimeStamp  = 0;
		nNumberOfPackages = 0;
		memset(nPackages,0,NUMBER_OF_PACKAGES);
	}

	void clear() 
	{
		nMajorVersion = HEADER_MAJOR_VERSION;
		nMinorVersion = HEADER_MINOR_VERSION;
		nFrameCounter = 0;
		n64TimeStamp  = 0;
		nNumberOfPackages = 0;
		memset(nPackages,0,NUMBER_OF_PACKAGES);
	}
};
//#pragma pack(pop) // 1 byte alignment

#pragma pack(1) // 1 byte alignment
struct sControlMessage
{
	tInt8 m_nMessageID;
	tInt8 m_nValue;
	sControlMessage()
	{
		m_nMessageID = 0;
		m_nValue = 0;
	}
};

/*
#pragma pack(1) // 1 byte alignment
struct sControllerMessage
{
	tInt8 m_ID;
	tInt8 m_Speed;
	tBool m_Button;
	sControllerMessage()
	{
		m_ID = -1;
		m_Speed = 0;
		m_Button = false;
	}
};
*/

#pragma pack(1) // 1 byte alignment
struct sDriverMessage
{
	char		m_strName[32];
	tInt8		m_iID;
	tInt8		m_nPosition;
	tInt8		m_nProgSpeed;
	tInt16		m_nRounds;
	tInt16		m_nRaceRounds;
	tUInt		m_nRaceMode;
	tInt8		m_bIsInBox;
	tInt8		m_bIsDisqualified;

	tTimeStamp	m_nTimeStamp;

	tFloat32	m_f32FuelLevel;
	tFloat32	m_f32FuelCapacity;
	tFloat32	m_f32Time2Leader;
	tFloat32	m_f32LastLapTime;
	tFloat32	m_f32BestLapTime;
	
	tFloat32	m_f32CurrentRoundTime;

	tBool		m_bChoas;

	sController	m_oController;
	
	sDriverMessage()
	{
		memset(m_strName,0,32);
		m_iID = -1;
		m_nPosition = -1;
		m_nProgSpeed = 0;
		m_nRounds = 0;
		m_bIsInBox = false;
		m_bIsDisqualified = false;

		m_f32FuelLevel = 0;
		m_f32FuelCapacity = 0;
		m_f32Time2Leader = 0;
		m_f32LastLapTime = 0;
		m_f32BestLapTime = 0;

		m_f32CurrentRoundTime = 0;

		m_bChoas = false;
	}
};

#pragma pack() // default Alignment

#endif // commonConnectionTypes_H