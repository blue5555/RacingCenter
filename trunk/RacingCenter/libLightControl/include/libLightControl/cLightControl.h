#ifndef cLightControl_H
#define cLightControl_H

#include <libCommon/stdafx.h>
#include "libSerialConnector/cSerialConnector.h"

namespace RacingCenter
{

class cLightControl : public QObject, public cThing
{
	Q_OBJECT

	sRGB  m_oTargetDimRBG;
	tUInt m_nTargetDimID;

	sRGB m_oLight;

	QTimer m_oTimerLightWave;
	QTimer m_oTimerDimmer;
	QTimer m_oTimerTribuene;
	QTimer m_oTimerBox;

	tBool m_bLightShowTribuene;
	tBool m_bLightShowBox;

	tUInt m_nCurrentID;
	map<tUInt,tUInt>::iterator itCurrentLight;

	tBool m_bToogle;

	tUInt nLightState;
	tBool m_bRisingFlag;

	char m_oLightWort[7];

	cSerialConnector* m_opSerialConnector;
	
	map<tUInt,tUInt> m_oLightIdTable;
	map<tUInt,sRGB> m_oLights;

public:
	cLightControl();
	~cLightControl();
	
	tResult Init(cSerialConnector* i_opSerialConnector);

	tResult ClearLights();

	tResult StartDim(tUInt i_nID, const sRGB& i_oRGB);

	tResult SetLight(tUInt i_nID, const sRGB& i_oRGB);
	tResult UpdateLights();

	tResult StartLightTribuene(const tFloat64& i_f64Duration);
	tResult StopLightTribuene();

	tResult StartLightBox(const tFloat64& i_f64Duration);
	tResult StopLightBox();

	tResult StartLightWave(const tFloat64& i_f64Duration);
	tResult StopLightWave();

public slots:
	void ProcessLightWave();

	void ProcessLightTribuene();
	void ProcessLightBox();

	void LightsDim();

};

}

#endif // cLightControl_H