#ifndef cDataProcessor_H
#define cDataProcessor_H

#include <libCommon/stdafx.h>
#include "libCommon/cTimeStamp.h"
#include <QThread>
#include <libConfig/cConfig.h>
#include <libCUAdapter/cCUAdapter.h>
#include <libDataCore/cRace.h>
#include <libRaceDisplay/cRaceDisplaySimple.h>
#include <libRaceResults/cRaceResults.h>

#include <libStartlight/cStartLightSimple.h>

#include <libLightControl/cLightControl.h>

#include "cDataLogger.h"
#include "cEventController.h"
#include "cSound.h"

namespace RacingCenter
{

class cDataProcessor : private QObject, public cThing
{
	Q_OBJECT

	QTimer  m_oTimerDataProcessor;
	QThread m_oThreadDataProccessor;

    QTimer  m_oTimerSerialData;
    QThread m_oThreadSerialData;

	QTimer  m_oTimerRace;
	QThread m_oThreadRace;

	//cRacingCenterServer m_oServer;
	QMutex		m_oMutex;

	qint64	m_i64StartProcess, m_i64EndProcess; 

	cConfig*			m_opConfig;

	tBool				m_bInit;
	tUInt8				m_nInitCounter;

	tInt8				m_nErrorCounter;

	tBool				m_bStarted;
	tBool				m_bProcessing;
	tBool				m_bTestData;
	tUInt				m_nControllerState;

    cQueue<sData>	    m_oCUDataQueue;
	cCUAdapter			m_oCUAdapter;

	cRace				m_oRace;
	
	cDataLogger			m_oDataLogger;

	cLightControl		m_oLightControl;

	cStartLight*		m_opStartLight;
	//cDriverDisplay*			m_opDriverDisplay;
	map<tUInt8,cRaceDisplaySimple*>         m_opRaceDisplays;
	cRaceResults*				m_opRaceResults;

	cEventController	m_oEventController;

	sProgrammWord m_oCurrentProgramWord;
	list<sProgrammWord> m_oProgramWords;

	void  CheckForChoas(const sData& oCUData );
	tBool ProcessStartLight(const sData& i_oCUWord);
	tBool UpdateDisplays(const tTimeStamp& i_nTimeStamp);

	tBool InsertProgramWord(const sProgrammWord& i_oProgramWord, list<sProgrammWord>& io_oProgramWords);

	public:
		cDataProcessor();
		~cDataProcessor();

		tBool Start(const tInt16& i_i16TimerIntervall, const cSerialportInfo& i_oSerialportInfo, const tBool i_bTestData);
		void  Stop();

		void  StartProcessing();
		void  StopProcessing();
		tBool Processing() const;

		tUInt GetControllerState() const;

		cRace* GetRace() { return &m_oRace; }
		const tBool Started() const { return m_bStarted; }

		const tInt8 GetErrorCounter() { return m_nErrorCounter; }

		cSerialConnector* GetSerialConnector() { return m_oCUAdapter.GetSerialConnector(); }

		cLightControl* GetLightControl() { return &m_oLightControl; }

		//void Started(tBool val) { m_bStarted = val; }

		//StartLightGui* getStartLight() const { return m_opStartLight; }
		//void setStartLight(StartLightGui* val);

		//void SetDriverDisplay(cDriverDisplay* val);

		//void AddRaceDisplay(cRaceDisplaySimple* caceDisplay);

signals:
		void UpdateStartLight(unsigned int i_nStartLightState);
		void UpdateDriverDisplay(sDriverMessage i_oDriverDisplayMessage);
		void UpdateRaceDisplay(sDriverMessage i_oDriverDisplayMessage);
		void UpdateRaceDisplay2(sDriverMessage i_oDriverDisplayMessage);

public slots:
		void GetData();
		void ProcessData();
		void SendProgrammWord(int i_iController, int i_iProgrammWord, int i_iValue);
		void ClosedRaceDisplay();
		void ClosedRaceResults();
		void RaceOver();

};

}

#endif //cDataProcessor_H