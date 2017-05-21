#ifndef sCUData_H
#define sCUData_H

#include "sEvent.h"

namespace RacingCenter
{

enum eDataType
{
	DT_CU_WORD = 0,
	DT_CU_DRIVER,
	DT_CONTROLLER,
	DT_CU_VERSION,
	DT_CU_PROGRAM_WORD,
	DT_EVENT
};

struct sCUDriver
{
	tInt8  m_iID;
	tUInt64 m_n64Timervalue;
	tUInt8  m_nSensorID;
	sCUDriver()
	{
		m_iID = -1;
		m_n64Timervalue = 0;
		m_nSensorID = 0;
	}
	sCUDriver(const tInt8& i_iID,
			  const tUInt64& i_n64Timervalue,
			  const tUInt8& i_nSensorID)
	{
		m_iID = i_iID;
		m_n64Timervalue = i_n64Timervalue;
		m_nSensorID = i_nSensorID;
	}
};

struct sCUWord
{
	tUInt8	  m_oFuel[6];
	tUInt8	  m_nStartLight;
	eFuelMode m_eFuelMode;
	tBool	  m_oIsInBox[6];
	sCUWord()
	{
		memset(m_oFuel,0,sizeof(m_oFuel));
		memset(m_oIsInBox,0,sizeof(m_oIsInBox));
		m_nStartLight = 0;
	}
};

struct sData
{
	tTimeStamp	nTimeStamp;	
	eDataType	eType;

	sCUDriver	oCUDriver;
	sCUWord		oCUWord;
	sController oController[6];
	sProgrammWord oProgramWord;
	sEvent		oEvent;
	tUInt8		nCUVersion;

	sData(tTimeStamp i_nTimeStamp,eDataType i_eDataType)
	{
        nTimeStamp = i_nTimeStamp;
        eType = i_eDataType;
	}
	~sData()
    {
    }

};

}

#endif // sCUData_H