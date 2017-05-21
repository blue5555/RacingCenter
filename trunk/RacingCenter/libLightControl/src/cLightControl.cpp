#include "libLightControl/cLightControl.h"
#include <stdio.h>

#define NUM_LIGHTS 67
#define DIM_STEP_SIZE 2

using namespace RacingCenter;

cLightControl::cLightControl() :
 m_opSerialConnector(NULL)
,m_bLightShowTribuene(false)
,m_bLightShowBox(false)
,m_nCurrentID(0)
,m_bRisingFlag(true)
,m_bToogle(false)
{
	m_bDebug = true;

	connect(&m_oTimerLightWave,	SIGNAL(timeout()),	this, SLOT( ProcessLightWave() ) );

	connect(&m_oTimerDimmer,	SIGNAL(timeout()),	this, SLOT( ProcessLightDimmer() ) );

	connect(&m_oTimerTribuene,	SIGNAL(timeout()),	this, SLOT( ProcessLightTribuene() ) );
	connect(&m_oTimerBox,		SIGNAL(timeout()),	this, SLOT( ProcessLightBox() ) );

	m_oLightIdTable[0]	= 0;

	m_oLightIdTable[1] = 0;
	m_oLightIdTable[2] = 0;
	m_oLightIdTable[3] = 0;
	m_oLightIdTable[4] = 0;
	m_oLightIdTable[5] = 0;
	m_oLightIdTable[6] = 0;
	m_oLightIdTable[7] = 0;
	m_oLightIdTable[8] = 0;

	m_oLightIdTable[10] = 0;
	m_oLightIdTable[11] = 0;
	m_oLightIdTable[12] = 0;
	m_oLightIdTable[13] = 0;
	m_oLightIdTable[14] = 0;
	m_oLightIdTable[15] = 0;
	m_oLightIdTable[16] = 0;
	m_oLightIdTable[17] = 0;
	m_oLightIdTable[18] = 0;
	m_oLightIdTable[19] = 0;

	m_oLightIdTable[20] = 0;
	m_oLightIdTable[21] = 0;
	m_oLightIdTable[22] = 0;
	m_oLightIdTable[23] = 0;
	m_oLightIdTable[24] = 0;
	m_oLightIdTable[25] = 0;
	m_oLightIdTable[26] = 0;
	m_oLightIdTable[27] = 0;

	m_oLightIdTable[30] = 24;
	m_oLightIdTable[31] = 25;
	m_oLightIdTable[32] = 26;
	m_oLightIdTable[33] = 27;
	m_oLightIdTable[34] = 28;
	m_oLightIdTable[35] = 29;

	m_oLightIdTable[36] = 0;
	m_oLightIdTable[37] = 0;
	m_oLightIdTable[38] = 0;

	m_oLightIdTable[40]	= 4;
	m_oLightIdTable[41]	= 5;
	m_oLightIdTable[42]	= 6;

	m_oLightIdTable[43] = 12;
	m_oLightIdTable[44] = 13;
	m_oLightIdTable[45] = 14;
	m_oLightIdTable[46] = 15;
	m_oLightIdTable[47] = 16;
	m_oLightIdTable[48] = 17;
	m_oLightIdTable[49] = 18;
	m_oLightIdTable[50] = 19;

	m_oLightIdTable[51] = 30;
	m_oLightIdTable[52] = 31;
	m_oLightIdTable[53] = 32;

	m_oLightIdTable[60]	= 7;
	m_oLightIdTable[61]	= 8;
	m_oLightIdTable[62]	= 10;
	m_oLightIdTable[63]	= 9;
	m_oLightIdTable[64] = 11;
	m_oLightIdTable[65] = 1;
	m_oLightIdTable[66]	= 3;
	m_oLightIdTable[67]	= 2;

	// Tribüne
	m_oLightIdTable[100] = 20;
	m_oLightIdTable[101] = 21;
	m_oLightIdTable[102] = 22;
	m_oLightIdTable[103] = 23;

	// Boxengebäude
	m_oLightIdTable[110] = 33;
	m_oLightIdTable[111] = 34;
	m_oLightIdTable[112] = 35;

	m_oLightIdTable[255] = 255;

}

cLightControl::~cLightControl()
{

}

tResult cLightControl::Init(cSerialConnector* i_opSerialConnector)
{
	m_opSerialConnector = i_opSerialConnector;
	m_nCurrentID = 0;
	RETURN_NO_ERROR;
}

tResult cLightControl::ClearLights()
{
	for (tUInt n = 0; n < NUM_LIGHTS; n++)
	{
		m_oLights[n] = sRGB(0, 0,0);
	}
	SetLight(0, m_oLights[0]);
	UpdateLights();
	RETURN_NO_ERROR;
}

tResult cLightControl::StartDim(tUInt i_nID, const sRGB& i_oRGB)
{
	m_oTargetDimRBG = i_oRGB;
	m_nTargetDimID  = i_nID;

	disconnect(this, SLOT(LightsDim()));

	m_oTimerDimmer.setInterval(100);
	connect(&m_oTimerDimmer,	SIGNAL(timeout()),	this, SLOT( LightsDim() ) );
	m_oTimerDimmer.start();

	RETURN_NO_ERROR;
}

void cLightControl::LightsDim()
{
	if(m_nTargetDimID == 0)
	{
		tUInt n = 0;
		tBool bFinish = true;

		//for (tUInt n = 1; n < NUM_LIGHTS; n++)
		{
			const sRGB& oRGB = m_oLights[n];

			tInt16 nR = m_oTargetDimRBG.r - oRGB.r;
			tInt16 nG = m_oTargetDimRBG.g - oRGB.g; 
			tInt16 nB = m_oTargetDimRBG.b - oRGB.b; 

			if(abs(nR) > DIM_STEP_SIZE)
			{
				nR = nR > 0 ? DIM_STEP_SIZE : -DIM_STEP_SIZE;
			}

			if(abs(nG) > DIM_STEP_SIZE)
			{
				nG = nG > 0 ? DIM_STEP_SIZE : -DIM_STEP_SIZE;
			}

			if(abs(nB) > DIM_STEP_SIZE)
			{
				nB = nB > 0 ? DIM_STEP_SIZE : -DIM_STEP_SIZE;
			}

			if(nR != 0 || nG != 0 || nB != 0)
			{
				bFinish = false;
			}

			sRGB oSendRGB;
			oSendRGB.r = oRGB.r + nR;
			if(oRGB.r + nR > 255) {
				oSendRGB.r = 255;
			}
			else if(oRGB.r + nR < 0) {
				oSendRGB.r = 0;
			}

			oSendRGB.g = oRGB.g + nG;
			if(oRGB.g + nG > 255) {
				oSendRGB.g = 255;
			}
			else if(oRGB.g + nG < 0) {
				oSendRGB.g = 0;
			}

			oSendRGB.b = oRGB.b + nB;
			if(oRGB.b + nB > 255) {
				oSendRGB.b = 255;
			}
			else if(oRGB.b + nB < 0) {
				oSendRGB.b = 0;
			}

			m_oLights[n] = oSendRGB;
			SetLight(n, m_oLights[n]);
		}

		UpdateLights();

		if(bFinish)
		{
			m_oTimerDimmer.stop();
		}
	}
}

tResult cLightControl::StartLightWave(const tFloat64& i_f64Duration)
{
	m_oTimerLightWave.stop();
	disconnect();

	itCurrentLight = m_oLightIdTable.begin();
	itCurrentLight++;

	tFloat64 f64Interval = i_f64Duration * 1000 / (m_oLightIdTable.size() - 2);

	m_oTimerLightWave.setInterval(f64Interval);
	m_oTimerLightWave.start();

	RETURN_NO_ERROR;
}

tResult cLightControl::StopLightWave()
{
	m_oTimerLightWave.stop();
	disconnect();

	RETURN_NO_ERROR;
}

void cLightControl::ProcessLightWave()
{
	SetLight(0, sRGB(255, 255, 0));

	if(itCurrentLight->first > 99 || itCurrentLight == m_oLightIdTable.end())
	{
			StopLightWave();
	}
	else if(itCurrentLight->second > 0)
	{
		SetLight(itCurrentLight->first, sRGB(255,0,0));
	}

	UpdateLights();
	itCurrentLight++;
}

tResult cLightControl::StartLightTribuene(const tFloat64& i_f64Duration)
{
	m_oTimerTribuene.stop();
	tFloat64 f64Interval = i_f64Duration * 1000;
	m_oTimerTribuene.setInterval(f64Interval);

	m_bLightShowTribuene = true;

	m_oTimerTribuene.start();

	RETURN_NO_ERROR;
}

tResult cLightControl::StopLightTribuene()
{
	m_bLightShowTribuene = false;
	m_oTimerTribuene.stop();
	RETURN_NO_ERROR;
}

void cLightControl::ProcessLightTribuene()
{
	if(m_bLightShowTribuene)
	{
		SetLight(100, sRGB(qrand() % 255,qrand() % 255,qrand() % 255));
		SetLight(101, sRGB(qrand() % 255,qrand() % 255,qrand() % 255));
		SetLight(102, sRGB(qrand() % 255,qrand() % 255,qrand() % 255));
		SetLight(103, sRGB(qrand() % 255,qrand() % 255,qrand() % 255));

		UpdateLights();
	}
}

tResult cLightControl::StartLightBox(const tFloat64& i_f64Duration)
{
	m_oTimerBox.stop();
	tFloat64 f64Interval = i_f64Duration * 1000;
	m_oTimerBox.setInterval(f64Interval);

	m_bLightShowBox = true;

	m_oTimerBox.start();

	RETURN_NO_ERROR;
}

tResult cLightControl::StopLightBox()
{
	m_bLightShowBox = false;
	m_oTimerBox.stop();
	RETURN_NO_ERROR;
}

void cLightControl::ProcessLightBox()
{
	if(m_bLightShowBox)
	{
		SetLight(110, sRGB(qrand() % 255,qrand() % 255,qrand() % 255));
		SetLight(111, sRGB(qrand() % 255,qrand() % 255,qrand() % 255));
		SetLight(112, sRGB(qrand() % 255,qrand() % 255,qrand() % 255));

		UpdateLights();
	}
}

tResult cLightControl::SetLight(tUInt i_nID, const sRGB& i_oRGB)
{
	if(m_opSerialConnector != NULL)
	{
		m_oLights[i_nID] = i_oRGB;
		
		tUInt nSendId = m_oLightIdTable[i_nID];

		QByteArray oData(7,0);
		oData[0] =  34; // "
		oData[1] =  76; // L
		oData[2] =  nSendId > 254  ? 255 : nSendId  + 1;
		oData[3] =  i_oRGB.r > 254 ? 255 : i_oRGB.r + 1;
		oData[4] =  i_oRGB.g > 254 ? 255 : i_oRGB.g + 1;
		oData[5] =  i_oRGB.b > 254 ? 255 : i_oRGB.b + 1;
		oData[6] = 36; // $
		m_opSerialConnector->SendData(oData);

		if(m_bDebug)
		{
			qDebug() << "Send Light ID: " << i_nID << "R: " << i_oRGB.r << "\tG: " << i_oRGB.g << "\tB: " << i_oRGB.b;
		}
	} 
	else
	{
		qDebug() << "ERROR: m_opSerialConnector == NULL";
	}

	RETURN_NO_ERROR;
}

tResult cLightControl::UpdateLights()
{
	return SetLight(255, sRGB());
}