#include <cTestGenerator.h>

using namespace RacingCenter;

cTestGenerator::cTestGenerator()
{
	m_oLastValues[0] = 0;
	m_oLastValues[1] = 0;
	m_oLastValues[2] = 0;
	m_oLastValues[3] = 0;
	m_oLastValues[4] = 0;
	m_oLastValues[5] = 0;
}

cTestGenerator::~cTestGenerator()
{

}

tUInt16 cTestGenerator::randInt(tUInt16 low, tUInt16 high)
{
	// Random number between low and high
	return qrand() % ((high + 1) - low) + low;
}

sData cTestGenerator::CreateDriverData(const tUInt8 i_nDriverID)
{
	tTimeStamp nTimeStamp = cTimeStamp::GetTimeStamp();

	sData oCUData(nTimeStamp, DT_CU_DRIVER);
	sCUDriver oDriver;

	oDriver.m_iID = i_nDriverID;
	oDriver.m_nSensorID = 0;

	tUInt16 nRandomValue = randInt(5000, 10000);
	tTimeStamp newTimerValue = m_oLastValues[i_nDriverID] +nRandomValue;
	
	oDriver.m_n64Timervalue = newTimerValue;

	m_oLastValues[i_nDriverID] = newTimerValue;

	oCUData.oCUDriver = oDriver;

	return oCUData;
}

sData cTestGenerator::CreateControllerData(const tUInt8 i_nDriverID)
{
	tTimeStamp nTimeStamp = cTimeStamp::GetTimeStamp();

	sData oCUData(nTimeStamp, DT_CONTROLLER);

	for(uint i = 0; i < 6; i++)
	{
		sController oController;
		tUInt16 newValue = randInt(0,15);
		oController.m_ID = i;
		oController.m_Speed = newValue;
		oController.m_Button = false;
		oCUData.oController[i] = oController;
	}

	return oCUData;

}