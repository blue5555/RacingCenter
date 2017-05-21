#ifndef cCUAdapter_H
#define cCUAdapter_H

#include <libCommon/stdafx.h>
#include <libCommon/cThing.h>
#include <libCommon/sCUData.h>
#include "libCommon/cTimeStamp.h"
#include "libCommon/cFileWriter.h"
#include <libConfig/cConfig.h>
#include <libConfig/cSerialportInfo.h>
#include <libSerialConnector/cSerialConnector.h>

#include "cTestGenerator.h"

namespace RacingCenter
{

class cCUAdapter : public cThing
{
	tBool			 m_bInit;
	tBool			 m_bSendProgrammWord;
	tBool			 m_bToggle;

	tUInt			 m_nErrorCounter;

	cFileWriter		 m_oFileWriter;

	cRawData		 m_oTempRawData;

	tTimeStamp		 m_oCurrentTimeStamp;

	tInt16			 m_i16TimerIntervall;
	cSerialportInfo  m_oSerialPortInfo;

	tBool			 m_bTestData;
	cTestGenerator   m_oTestGenerator;

	cSerialConnector m_oSerialConnector;

	cQueue<cRawData>  m_oRawDataQueue;
	cQueue<sData>&  m_oCUDataQueue;

	const sData ProcessControllerData(const cRawData& i_oRawData);
	const sData ProcessCUWord(const cRawData& i_oRawData);
	const sData ProcessCUDriver(const cRawData& i_oRawData);
	const sData ProcessCUVersion(const cRawData& i_oRawData);
	const sData ProcessProgramData(const cRawData& i_oRawData);

	const tUInt32 ConvertTimerValue(const QByteArray& i_oCharData) const;

	const tUInt16 CalculateCheckSum(const QByteArray& i_oWord, int i_iOffset) const;

    QByteArray SendData(const eDataSource& i_eDataSOurce);
	
public:
    cCUAdapter(cQueue<sData>& i_opCUDataQueue);
	~cCUAdapter();

	tBool Init(const tInt16& i_i16TimerIntervall, const cSerialportInfo& i_oSerialPortInfo, const tBool& i_bTestData);
	tBool DeInit();

	tBool Clear();

	cSerialConnector* GetSerialConnector();

	void  CallControlUnit(const eDataSource i_eDataSource);
	void  ConvertRawData();

    tBool SetSerialPortInfo(const cSerialportInfo& i_oSerialPortInfo);

	void ActivateChaos();
	void DeactivateChaos();

    void  SendProgrammWord(const tInt8 i_iController, const tInt8 i_iProgrammWord, const tInt8 i_iValue);
	void  SendShortProgrammWord(const tInt8 i_iController, const tInt8 i_iProgrammWord, const tInt8 i_iValue);

};

}

#endif // cCUAdapter_H