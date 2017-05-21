#include "libCore/cDataProcessor.h"

#define _FILENAME_ "cDataProcesor: "
#define NUMBER_OF_DISPLAYS 2

using namespace RacingCenter;

cDataProcessor::cDataProcessor() :
 m_oCUAdapter(m_oCUDataQueue)
,m_bInit(false)
,m_opConfig(cConfig::instance())
,m_bStarted(false)
,m_bProcessing(false)
,m_opRaceResults(NULL)
,m_opStartLight(NULL)
,m_nControllerState(0)
,m_nErrorCounter(0)
{	
}

cDataProcessor::~cDataProcessor()
{
	m_oThreadDataProccessor.quit();
	m_oThreadDataProccessor.wait();

    m_oThreadSerialData.quit();
    m_oThreadSerialData.wait();
}

tBool cDataProcessor::Start(const tInt16& i_i16TimerIntervall, const cSerialportInfo& i_oSerialportInfo, const tBool i_bTestData)
{
	if(m_bStarted)
	{
		return true;
	}

	tBool bOk = true;

    m_bDebug	   = m_opConfig->m_oDebugMessages.bDataProcessor;
	m_bDebugTiming = m_opConfig->m_oDebugMessagesTiming.bDataProcessor;

	m_bInit = false;
	m_bTestData = i_bTestData;

	m_nControllerState = 0;

    // set data for serial connector
    m_oTimerSerialData.setInterval(i_i16TimerIntervall);
    m_oTimerSerialData.moveToThread(&m_oThreadSerialData);

    connect(&m_oTimerSerialData,  SIGNAL(timeout()),  this, SLOT( GetData() ) );
    connect(&m_oThreadSerialData, SIGNAL(started()),  &m_oTimerSerialData, SLOT(start()));
    connect(&m_oThreadSerialData, SIGNAL(finished()), &m_oTimerSerialData, SLOT(stop()));

    // set data for data processor
	m_oTimerDataProcessor.setInterval(i_i16TimerIntervall);
	m_oTimerDataProcessor.moveToThread(&m_oThreadDataProccessor);

	connect(&m_oTimerDataProcessor,   SIGNAL(timeout()),  this, SLOT( ProcessData() ) );
	connect(&m_oThreadDataProccessor, SIGNAL(started()),  &m_oTimerDataProcessor, SLOT(start()));
	connect(&m_oThreadDataProccessor, SIGNAL(finished()), &m_oTimerDataProcessor, SLOT(stop()));

	if(m_oRace.RaceFinish() == FINISH_TIME)
	{
		// set data for data processor
		m_oTimerRace.setInterval(m_opConfig->m_oRaceConfig.nTime * 60 * 1000);
		connect(&m_oTimerRace,   SIGNAL(timeout()),  this, SLOT( RaceOver() ) );
	}

	bOk = m_oCUAdapter.Init(i_i16TimerIntervall,i_oSerialportInfo,i_bTestData);

	if(bOk)
	{
		m_oLightControl.Init(m_oCUAdapter.GetSerialConnector());
		m_oLightControl.ClearLights();

		m_oLightControl.StartDim(0, sRGB(255,255,0));
		m_oLightControl.StartLightTribuene(0.75);
		m_oLightControl.StartLightBox(0.75);
	}

	if(bOk)
	{
		m_oEventController.Init(&m_oRace, 0);
	}

	if (bOk)
	{
		m_oDataLogger.Init(&m_oRace);
	}

	if(bOk)
	{
		m_oThreadSerialData.start();
		m_oThreadDataProccessor.start();
		m_bStarted = true;
	}

	return bOk;
}

void cDataProcessor::StartProcessing()
{
	QMutexLocker locker(&m_oMutex);
	m_bProcessing = true;

	m_oCUDataQueue.clean();
	m_oRace.Init();

	m_oDataLogger.StartLogging();

	for (tUInt8 nDisplayID = 0; nDisplayID < NUMBER_OF_DISPLAYS; nDisplayID++)
	{
		tDriverMapPointer oDriverMap = m_oRace.GetDriverMapByDisplayID(nDisplayID);
		if(oDriverMap.size() > 0)
		{
			cRaceDisplaySimple* opRaceDisplay = new cRaceDisplaySimple(oDriverMap, &m_oRace);
			connect(this, SIGNAL( UpdateDriverDisplay(sDriverMessage) ), opRaceDisplay, SLOT( UpdateDriverRaceDisplay(sDriverMessage) ) );
			connect(opRaceDisplay, SIGNAL(Closed()), this, SLOT(RaceOver()) );
			opRaceDisplay->show();
			opRaceDisplay->showMaximized();
			m_opRaceDisplays.insert( make_pair( nDisplayID, opRaceDisplay ) );
		}
	}

	if(m_opStartLight == NULL)
	{
		m_opStartLight = new cStartLight();
	}

	UpdateDisplays(0);
}

void cDataProcessor::StopProcessing()
{
	QMutexLocker locker(&m_oMutex);
	m_bProcessing = false;

	if(m_opStartLight)
	{
		delete m_opStartLight;
		m_opStartLight = NULL;
	}

	for(map<tUInt8,cRaceDisplaySimple*>::iterator itDisplay = m_opRaceDisplays.begin(); itDisplay != m_opRaceDisplays.end(); itDisplay++)
	{
		if(itDisplay->second != NULL)
		{
			itDisplay->second->disconnect();
			itDisplay->second->close();
			delete itDisplay->second;
			itDisplay->second = NULL;
		}
	}	
	m_opRaceDisplays.clear();
}

tBool cDataProcessor::Processing() const
{
	return m_bProcessing;
}

tUInt cDataProcessor::GetControllerState() const
{
	return m_nControllerState;
}

void cDataProcessor::Stop()
{
	m_bStarted = false;
	m_bProcessing = false;

	m_oTimerRace.stop();

	m_oTimerDataProcessor.stop();

	m_oThreadDataProccessor.quit();
	m_oThreadDataProccessor.wait();

	m_oCUAdapter.DeInit();

	StopProcessing();

}

void cDataProcessor::GetData()
{
	QMutexLocker oMutex(&m_oMutex);

	if(m_bDebugTiming) {
		m_i64StartProcess = cTimeStamp::GetTimeStamp();
		qDebug() << _FILENAME_ << "----- START: GET DATA -----";
		qDebug() << _FILENAME_ << m_i64StartProcess;
	}

	if(m_bStarted) 
    {
		m_nErrorCounter++;
		if(m_nErrorCounter > 100)
		{
			m_nErrorCounter = 100;
		}
		m_oCUAdapter.CallControlUnit( m_opConfig->m_eDataSource );
	}
}

void cDataProcessor::RaceOver()
{
    Stop();

	if(m_opRaceResults == NULL)
	{
		m_opRaceResults = new cRaceResults(NULL, &m_oRace, &m_oDataLogger);
		m_opRaceResults->show();
		m_opRaceResults->showMaximized();
		connect(m_opRaceResults, SIGNAL( ClosedRaceResults() ), this, SLOT( ClosedRaceResults() ) );
	}
}

void cDataProcessor::ClosedRaceDisplay()
{
	StopProcessing();
}

void cDataProcessor::ClosedRaceResults()
{
	m_oDataLogger.Clear();

	if(m_opRaceResults != NULL)
	{
		m_opRaceResults->disconnect();
		m_opRaceResults->close();
		delete m_opRaceResults;
		m_opRaceResults = NULL;

		m_oRace.Reset();
	}
}

void cDataProcessor::ProcessData()
{
	qint64 iStart = cTimeStamp::GetTimeStamp();
	if(m_bDebugTiming) 
    {
		qDebug() << "cDataProcessor: Start Process: " << iStart;
	}

	if(m_bProcessing)
	{
		sEvent oEvent;
		if(m_oEventController.CheckForEvent(iStart, oEvent))
		{
			sData oData(iStart, DT_EVENT);
			oData.eType = DT_EVENT;
			oData.oEvent = oEvent;
			m_oCUDataQueue.push(oData);
		}

		m_oCUAdapter.ConvertRawData();

		tTimeStamp timeStamp = 0;
		while (!m_oCUDataQueue.isEmpty())
		{
			if(!m_oCUDataQueue.isEmpty()) 
			{
				sData oCUData	= m_oCUDataQueue.pull();
				m_oRace.UpdateRace(oCUData);

				for (tUInt n = 0; n < 6; n++)
				{
					cDriver* opDriver = m_oRace.GetDriver(n);
					if(opDriver != NULL)
					{
						m_oDataLogger.AddMessage(opDriver->CreateDisplayMessage(oCUData.nTimeStamp));
					}
				}

				switch(oCUData.eType)
				{
				case DT_CU_WORD:
					ProcessStartLight(oCUData);
					break;
				case  DT_CU_DRIVER:
					UpdateDisplays(oCUData.nTimeStamp);
					if(m_oRace.RaceMode() == MODE_QUALITFYING)
					{
						m_oLightControl.StopLightWave();
						m_oLightControl.StartLightWave( m_oRace.GetBestTime() );
					}
					break;
				case DT_CONTROLLER:
					CheckForChoas(oCUData);
					break;
				case DT_CU_PROGRAM_WORD:
					if(m_oProgramWords.size() > 0)
					{
						if(oCUData.oProgramWord.nCommand == m_oCurrentProgramWord.nCommand &&
						   oCUData.oProgramWord.nID      == m_oCurrentProgramWord.nID &&
						   oCUData.oProgramWord.nValue   == m_oCurrentProgramWord.nValue)
						{
							m_oProgramWords.pop_front();
						}

					}
					break;
				}

				m_nErrorCounter--;
				m_nErrorCounter--;
				if(m_nErrorCounter < 0)
				{
					m_nErrorCounter = 0;
				}

				vector<sProgrammWord> oProgramWords;
				if(m_oRace.CheckForProgramUpdate(oProgramWords))
				{
					for (tUInt n = 0; n < oProgramWords.size(); n++)
					{
						InsertProgramWord(oProgramWords.at(n), m_oProgramWords);
					}
				}

				if(m_oProgramWords.size() > 0)
				{
					m_oCurrentProgramWord = *(m_oProgramWords.begin());
					SendProgrammWord(m_oProgramWords.begin()->nID, m_oProgramWords.begin()->nCommand, m_oProgramWords.begin()->nValue);
				}
			}
		}

		DEBUGMSG("ErrorCounter: " << m_nErrorCounter);

		if(m_oRace.IsRaceOver())
		{
			RaceOver();
		}

		if(m_bDebugTiming) 
		{
			qint64 iEnd = cTimeStamp::GetTimeStamp();
			qDebug() << _FILENAME_ << "----- END ----";
			qDebug() << _FILENAME_ << "----- DELTA: " << static_cast<tFloat32>(iEnd - m_i64StartProcess) / 1000 << "-----";
		}
	}
	else
	{
		if(m_oCUDataQueue.count() > 0)
		{
			m_nControllerState = 1;
		}
		else
		{
			m_nControllerState = 0;
		}

		m_oCUAdapter.Clear();
		m_oCUDataQueue.clean();
	}
}

tBool cDataProcessor::InsertProgramWord(const sProgrammWord& i_oProgramWord, list<sProgrammWord>& io_oProgramWords)
{
	tBool isInside = false;
	for(list<sProgrammWord>::iterator it = io_oProgramWords.begin(); it != io_oProgramWords.end(); it++)
	{
		if(i_oProgramWord.nCommand == it->nCommand &&
		   i_oProgramWord.nID      == it->nID &&
		   i_oProgramWord.nValue   == it->nValue)
		{
			isInside = true;
		}
	}

	if(!isInside)
	{
		io_oProgramWords.push_back(i_oProgramWord);
		return true;
	}
	else
	{
		return false;
	}

}

tBool cDataProcessor::UpdateDisplays(const tTimeStamp& i_nTimeStamp)
{
	sDriverMessage oDriverMessage;
	for( tUInt8 n = 0; n < 6; n++)
	{
		if(m_oRace.GetDriver(n) != NULL)
		{
			if(m_oRace.CreateDriverMessage(n, i_nTimeStamp, oDriverMessage))
			{
				emit UpdateDriverDisplay( oDriverMessage );
			}
		}
	}

	return true;
}

tBool cDataProcessor::ProcessStartLight(const sData& i_oCUWord)
{
	if(m_opStartLight)
	{
		m_opStartLight->UpdateState(i_oCUWord.oCUWord.m_nStartLight);
	}
    return true;
}

void cDataProcessor::SendProgrammWord(int i_iController, int i_iProgrammWord, int i_iValue)
{
	qDebug() << "Send ProgrammWord ID: " << i_iController << " Word: " << i_iProgrammWord << " Value: " << i_iValue;
	m_oCUAdapter.SendShortProgrammWord(i_iController, i_iProgrammWord, i_iValue);
}

void cDataProcessor::CheckForChoas(const sData& oCUData )
{
	tBool isChaos = false;
	for(tUInt n = 0; n < 6; n++)
	{
		if(oCUData.oController[n].m_Chaos)
		{
			isChaos = true;
			if(m_oRace.GetRaceState() == RACE_STATE_NORMAL)
			{
				qDebug() << "Activate Chaos";
				m_oRace.ActivateChaos(n);
				m_oCUAdapter.ActivateChaos();
			}
			else if(m_oRace.GetRaceState() == RACE_STATE_READY4NORMAL && m_oRace.GetChaosDriverID() == n)
			{
				qDebug() << "Deactivate Chaos";
				m_oRace.DeactivateChaos();
				m_oCUAdapter.DeactivateChaos();
				m_oRace.SetRaceState(RACE_STATE_READY4SETNORMAL);
			}
		}
	}
	if(!isChaos)
	{
		if(m_oRace.GetRaceState() == RACE_STATE_CHAOS)
		{
			qDebug() << "Set Race: Ready2Go";
			m_oRace.SetRaceState(RACE_STATE_READY4NORMAL);
		}
		if(m_oRace.GetRaceState() == RACE_STATE_READY4SETNORMAL)
		{
			qDebug() << "Set Race: Normal";
			m_oRace.SetRaceState(RACE_STATE_NORMAL);
		}
	}
}
