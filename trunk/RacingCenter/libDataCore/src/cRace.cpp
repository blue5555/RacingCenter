#include "cRace.h"
#include "libConfig/cConfig.h"

#define _FILENAME_ "cRace: "

using namespace RacingCenter;

cRace::cRace() :
 m_opConfig(NULL)
,m_eFuelMode(FUELMODE_OFF)
,m_bInit(false)
,m_nInitCounter(0)
,m_bRaceOver(false)
,m_eRaceState(RACE_STATE_NORMAL)
,m_nChaosCounter(0)
{
	m_eRaceMode = MODE_TRAINING;
	m_nRounds = 0;
	m_nTime	= 0;
	Init();
}

cRace::cRace(const eRaceFinish& i_eRaceFinish, const tUInt16& i_nValue) : 
 m_opConfig(NULL)
,m_eFuelMode(FUELMODE_OFF)
,m_bInit(false)
,m_nInitCounter(0)
,m_bRaceOver(false)
,m_eRaceState(RACE_STATE_NORMAL)
,m_nChaosCounter(0)
{
	m_eRaceMode = MODE_RACE;
	if(i_eRaceFinish == FINISH_ROUNDS) 
    {
		m_eRaceFinish = i_eRaceFinish;
		m_nRounds     = i_nValue;
		m_nTime	      = 0;
	} 
    else if(i_eRaceFinish == FINISH_TIME) 
    {
		m_eRaceFinish = i_eRaceFinish;
		m_nRounds   = 0;
		m_nTime	    = i_nValue;
	}
	Init();
}

cRace::~cRace()
{

}

tBool cRace::Init()
{
	m_eRaceState= RACE_STATE_NORMAL;

	m_opConfig = cConfig::instance();
	m_bDriveFinish = m_opConfig->m_oRaceConfig.bDriveFinish;
	m_bRaceOver = false;
	m_bInit = false;
	m_nInitCounter = 0;
	m_nStartTime = cTimeStamp::GetTimeStamp();

	m_nChaosCounter = 0;

	if(m_opConfig->m_oFuelConfig.bSimulation) 
	{
		m_eFuelMode = FUELMODE_SIM;
	}

	return true;
}

tBool cRace::Reset()
{
	m_bRaceOver = false;
	m_bInit		= false;
	m_nInitCounter = 0;
	m_nChaosCounter = 0;
	
	m_oDrivers.clear();

	return true;
}

tBool cRace::AddDriver(const cDriver& i_oDriver)
{
	QMutexLocker locker(&m_oMutex);
	tBool bReturnValue = false;

	if(m_oDrivers.find(i_oDriver.GetID()) != m_oDrivers.end()) {
		bReturnValue = false;
	} else {
		m_oDrivers.insert(std::make_pair(i_oDriver.GetID(),i_oDriver));
		bReturnValue = true;		
	}

	return bReturnValue;
}

tBool cRace::DeleteDriver(const tUInt8& i_nID)
{
    QMutexLocker locker(&m_oMutex);

    tDriverMap::iterator it = m_oDrivers.find(i_nID);
    if(it != m_oDrivers.end()) 
    {
        m_oDrivers.erase(it);
        return true;
    } 
    else 
    {
        return false;
    }
}

const cDriver* cRace::GetDriver(const tUInt8& i_nID) const
{
    if(m_oDrivers.find(i_nID) != m_oDrivers.end()) 
    {
        return &m_oDrivers.at(i_nID);
    } else {
        return NULL;
    }
}

cDriver* cRace::GetDriver(const tUInt8& i_nID)
{
    if(m_oDrivers.find(i_nID) != m_oDrivers.end()) 
    {
        return &m_oDrivers.at(i_nID);
    } else {
        return NULL;
    }
}

cDriver* cRace::GetDriverByPosition(const tUInt8& i_nPostion)
{
	for(tDriverMap::const_iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++ ) { 
		if(itDriver->second.GetPosition() == i_nPostion) 
		{
			return &m_oDrivers.at(itDriver->first);
		}
	}

	return NULL;
}

const cDriver* cRace::GetDriverByPosition(const tUInt8& i_nPostion) const
{
	for(tDriverMap::const_iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++ ) { 
		if(itDriver->second.GetPosition() == i_nPostion) 
        {
			return &m_oDrivers.at(itDriver->first);
		}
	}

	return NULL;
}

const tDriverMap& cRace::GetDriverMap() const
{
	return m_oDrivers;
}

const tDriverMapPointer cRace::GetDriverMapByDisplayID(const tUInt8 i_nDisplayID)
{
	tDriverMapPointer oDriverMap;
	for(tDriverMap::const_iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++ ) 
	{ 
		if(itDriver->second.GetDisplayNumber() == i_nDisplayID) 
		{
			oDriverMap[itDriver->second.GetID()] = &m_oDrivers.at(itDriver->second.GetID());
		}
	}
	return oDriverMap;
}

tBool cRace::UpdateRace(const sData& i_oCUData)
{
    switch (i_oCUData.eType) 
    {
	case DT_EVENT:
		ProcessEvent(i_oCUData);
		break;
    case DT_CU_WORD:
        ProcessCUWord(i_oCUData);
        if (!m_bInit) {
            m_nInitCounter++;
            if (m_nInitCounter > 5) 
            {
                m_bInit = true;
            }
        }
        break;
    case DT_CU_DRIVER:
        if(m_bInit) 
        {
            ProcessCUDriver(i_oCUData);
        }
        break;
    case DT_CONTROLLER:
		if(m_eRaceState != RACE_STATE_CHAOS)
		{
	        ProcessController(i_oCUData);
		}
        break;
	case DT_CU_PROGRAM_WORD:
		ProcessProgramWord(i_oCUData);
		break;
    }
    return true;
}

tBool cRace::ProcessEvent(const sData& i_oCUWord)
{
	switch(i_oCUWord.oEvent.m_eEvent)
	{
	case NONE:
		break;
	case RAINING:
		for (tDriverMap::iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++)
		{
			itDriver->second.ProcessEvent(i_oCUWord.oEvent);
		}
		break;
	}

	return true;
}

tBool cRace::ProcessCUWord(const sData& i_oCUWord)
{
	//Box
	ProcessBox(i_oCUWord);

	//Tanken
	ProcessFuel(i_oCUWord);

	//Auswertung Strafen
	ProcessPenalty(i_oCUWord);

	return true;
}

tBool cRace::ProcessPenalty(const sData& i_oCUWord)
{
	return true;
}

tBool cRace::ProcessBox(const sData& i_oCUWord)
{
	for (tUInt8 i = 0; i < 6; i++) {
		UpdateDriverBox(i, i_oCUWord.oCUWord.m_oIsInBox[i], i_oCUWord.nTimeStamp);
	}

	return true;
}

tBool cRace::ProcessCUDriver(const sData& i_oCUDriver)
{
	UpdateDriverTime(i_oCUDriver.oCUDriver, i_oCUDriver.nTimeStamp);
	return true;
}

tBool cRace::ProcessController(const sData& i_oController)
{
	for (tUInt8 i = 0; i < 6; i++) 
	{
        UpdateDriverController(i_oController.oController[i], i_oController.nTimeStamp);
	}
	return true;
}

tBool cRace::ProcessFuel(const sData& i_oData)
{
	if (FuelMode() != FUELMODE_SIM) 
    {
		for (tUInt8 i = 0; i < 6; i++) 
        {
		    cDriver* opDriver = GetDriver(i);
			if(opDriver != NULL) 
            {
				opDriver->UpdateFuel(i_oData.oCUWord.m_oFuel[i], i_oData.nTimeStamp);
			}
		}
	}

	return true;
}

tBool cRace::ProcessProgramWord(const sData& i_oData)
{
	cDriver* opDriver = GetDriver(i_oData.oProgramWord.nID);
	switch(i_oData.oProgramWord.nCommand)
	{
	case 0:
		if(opDriver != NULL)
		{
			opDriver->SetProgSpeed(i_oData.oProgramWord.nValue);
		}
		break;
	}

	return true;
}

tBool cRace::UpdateDriverTime(const sCUDriver& i_oCUDriver, const tTimeStamp& i_oTimeStamp )
{
	QMutexLocker locker(&m_oMutex);
	
	tBool bReturnValue = false;
	if(m_oDrivers.find(i_oCUDriver.m_iID) != m_oDrivers.end() ) {

		if(m_eRaceMode == MODE_QUALITFYING && m_oDrivers[i_oCUDriver.m_iID].GetNumberOfLaps() < m_nRounds) 
        {
			m_oDrivers[i_oCUDriver.m_iID].UpdateTime(i_oCUDriver.m_n64Timervalue, i_oTimeStamp);
		}
		
        if(m_eRaceMode != MODE_QUALITFYING && !m_oDrivers[i_oCUDriver.m_iID].GetIsDisqualified()) 
        {
		    if(!m_oDrivers[i_oCUDriver.m_iID].GetIsFinish()) 
            {
				if(m_oDrivers[i_oCUDriver.m_iID].GetFuelLevel() > 0)
				{
					m_oDrivers[i_oCUDriver.m_iID].UpdateTime(i_oCUDriver.m_n64Timervalue, i_oTimeStamp);
				}
				else if(m_opConfig->m_oFuelConfig.bCountRoundsByEmptyFuel)
				{
					m_oDrivers[i_oCUDriver.m_iID].UpdateTime(i_oCUDriver.m_n64Timervalue, i_oTimeStamp);
				}
			}
			
            if(m_eRaceMode != MODE_TRAINING && CheckForRaceEnd(i_oCUDriver.m_iID)) 
            {
                // call Race Over
			}
		}
		bReturnValue = true;
	} 
    else 
    {
		return false;
	}

	CalculateDriverPositions(i_oCUDriver.m_iID);

	return bReturnValue;
}

tBool cRace::UpdateDriverController(const sController& i_oController, const tTimeStamp& i_nTimeStamp )
{
	QMutexLocker locker(&m_oMutex);
	
	tBool bReturnValue = true;
	if(m_eFuelMode == FUELMODE_SIM) 
    {
		if(m_oDrivers.find(i_oController.m_ID) != m_oDrivers.end() ) 
        {
			m_oDrivers[i_oController.m_ID].UpdateController(i_oController, i_nTimeStamp);
		} 
        else 
        {
			bReturnValue = false;
		}
	}
	return bReturnValue;
}

tBool cRace::CheckForProgramUpdate(vector<sProgrammWord>& o_oProgrammWords)
{
	QMutexLocker locker(&m_oMutex);

	for (tDriverMap::iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++)
	{
		if(m_opConfig->m_oFuelConfig.bProgrammCarsByFuel)
		{
			tUInt8 nCarSpeed     = itDriver->second.GetCarSpeed();
			tUInt8 nCarSpeedProg = itDriver->second.GetCarSpeedProg();

			if(nCarSpeed != nCarSpeedProg)
			{
				o_oProgrammWords.push_back(sProgrammWord(itDriver->second.GetID(), PROGRAM_SPEED, nCarSpeed));
			}
		}

		if(m_opConfig->m_oFuelConfig.bFlashCarLight)
		{
			if(itDriver->second.IsFlashing())
			{
				o_oProgrammWords.push_back(sProgrammWord(itDriver->second.GetID(), PROGRAM_FLASHES, 8));
			}
		}
	}

	if(o_oProgrammWords.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

tBool cRace::UpdateDriverBox(const tUInt8& i_nDriverID, const bool& i_bIsInBox, const tTimeStamp& i_oTimeStamp)
{
	QMutexLocker locker(&m_oMutex);
	
	tBool bReturnValue = false;
	if( m_oDrivers.find(i_nDriverID) != m_oDrivers.end() ) 
    {
		m_oDrivers[i_nDriverID].UpdateBox(i_bIsInBox,i_oTimeStamp);
		bReturnValue = true;
	} 
    else 
    {
		bReturnValue = false;
	}
	return bReturnValue;
}

tBool cRace::CheckForRaceEnd(tUInt8 i_nDriverID)
{
    tBool bReturnvalue = false;
    if (m_eRaceFinish == FINISH_ROUNDS) 
    {
        if (!m_bDriveFinish) 
        {
            if (m_oDrivers[i_nDriverID].GetNumberOfLaps() >= m_nRounds) 
            {
                m_bRaceOver = true;
                bReturnvalue = true;
            }
        } 
        else 
        {
            if (m_oDrivers[i_nDriverID].GetNumberOfLaps() >= m_nRounds) 
            {
                if (!m_oDrivers[i_nDriverID].GetIsFinish()) 
                {
                    m_oDrivers[i_nDriverID].SetIsFinish(true);
                }

                if (GetNumberOfFinishDrivers() >= m_oDrivers.size() - 1) 
                {
                    m_bRaceOver = true;
                    bReturnvalue = true;
                }
            } 
        }
    }

   if(bReturnvalue || m_eRaceFinish == FINISH_TIME) 
   {
	    // set points for the driver
        CalculateDriverPositions(i_nDriverID);
	    //SetDriverPoints();
   }

   return bReturnvalue;
}

const tUInt cRace::GetNumberOfFinishDrivers() const
{
    tUInt nNumberOfFinishDrivers = 0;
    for (tDriverMap::const_iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++)
    {
        if (itDriver->second.GetIsFinish() || itDriver->second.GetIsDisqualified())
        {
            nNumberOfFinishDrivers++;
        }
    }
    return nNumberOfFinishDrivers;
}

void cRace::SetDriverPoints()
{
	for(tDriverMap::iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++ ) 
    {
        itDriver->second.SetPoints( itDriver->second.GetPoints() +
                                    m_opConfig->m_oRaceConfig.oPoints[itDriver->second.GetPosition()]);
	}
}

void cRace::CalculateDriverPositions(uint i_nDriverID)
{
	switch (m_eRaceMode)
	{
	case MODE_TRAINING:
	case MODE_QUALITFYING:
		SortSequenceOfTheDriverBestTime();
		break;
	case MODE_RACE:
		SortSequenceOfTheDriverRace(i_nDriverID);
		break;
	case MODE_CHAMPIONSHIP:
		//SortSequenceOfTheDriverRace(i_nDriverID);
		break;
	}
}

void cRace::SortSequenceOfTheDriverBestTime()
{
	QMap<tFloat32,cDriver*> oTimeMap;
	
    std::map<tFloat64,cDriver*> oRoundTimes;
    for (tDriverMap::iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++)
    {
        oRoundTimes[itDriver->second.GetBestTime()] = &(itDriver->second);
    }

    tUInt nPositionCounter = 1;
	tFloat64 f64BestTime = oRoundTimes.begin()->first;
    for (std::map<tFloat64,cDriver*>::iterator itRoundTimes = oRoundTimes.begin(); itRoundTimes != oRoundTimes.end(); itRoundTimes++)
    {
        itRoundTimes->second->SetPosition(nPositionCounter);
		itRoundTimes->second->SetTime2Leader( itRoundTimes->first - f64BestTime );
        nPositionCounter++;
    }
}

tBool cRace::IsRaceOver() const
{
	if(m_eRaceMode == MODE_TRAINING)
	{
		return false;
	}
	else
	{
	    return m_bRaceOver;
	}
}

tBool cRace::CreateDriverMessage(const tUInt8& i_nID, const tTimeStamp& i_nTimeStamp, sDriverMessage& o_oDriverMessage) const
{
	const cDriver* opDriver = GetDriver(i_nID);
	if(opDriver != NULL)
	{
		o_oDriverMessage = opDriver->CreateDisplayMessage(i_nTimeStamp);
		return true;
	}
	return false;
}

void cRace::SortSequenceOfTheDriverRace(const tUInt i_nDriverID)
{
	// first
	tUInt nDriverOldPosition = 0;  // old position of the driver
	tUInt nMaxPositionen     = 0;

    std::map<tUInt8, cDriver> OldPositionMap;
    for(tDriverMap::iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++) 
    {
		itDriver->second.SetTime2Leader(0);

		OldPositionMap.insert( make_pair(itDriver->second.GetPosition(), itDriver->second) );
		nMaxPositionen = max(nMaxPositionen,itDriver->second.GetPosition());
		if ( itDriver->second.GetID() == i_nDriverID) 
		{
			nDriverOldPosition = itDriver->second.GetPosition();
		}
    }

	if(nDriverOldPosition == 0) 
    {
		GetDriver(i_nDriverID)->SetPosition(nMaxPositionen+1);
	}
	else if (nDriverOldPosition > 1) 
	{
		tBool bSetDriver = false;
		tUInt8 nPositionCounter = 1;
		cDriver* opDriver = GetDriver(i_nDriverID);
		for(tDriverMap::iterator itDriver = OldPositionMap.begin(); itDriver != OldPositionMap.end(); itDriver++) 
		{
			if(itDriver->second.GetPosition() > 0 && itDriver->second.GetID() != opDriver->GetID())
			{
				if(itDriver->second.GetNumberOfLaps() > opDriver->GetNumberOfLaps())
				{
					GetDriver(itDriver->second.GetID())->SetPosition(nPositionCounter);
					nPositionCounter++;
					opDriver->SetPosition(nPositionCounter);
				}
				else if(itDriver->second.GetNumberOfLaps() == opDriver->GetNumberOfLaps())
				{
					GetDriver(itDriver->second.GetID())->SetPosition(nPositionCounter);
					nPositionCounter++;
					opDriver->SetPosition(nPositionCounter);
				}
				else
				{
					opDriver->SetPosition(nPositionCounter);
					for( ; itDriver != OldPositionMap.end(); itDriver++) 
					{
						if(opDriver->GetID() != itDriver->second.GetID())
						{
							nPositionCounter++;
							GetDriver(itDriver->second.GetID())->SetPosition(nPositionCounter);
						}
					}
					break;
				}
			}
		}

	//	for(QMap<tUInt8, cDriver*>::iterator itDriver = OldPositionMap.begin(); itDriver != OldPositionMap.end(); itDriver++)
	//	{
	//		if ((*itDriver)->Position() > 1) {
	//			if ((*itDriver)->Laps() == OldPositionMap[(*itDriver)->Position() - 1]->Laps()) {
	//				tFloat32 f32DeltaTime = static_cast<tFloat32>((*itDriver)->LastTimerValue() - OldPositionMap[(*itDriver)->Position() - 1]->LastTimerValue());
	//				(*itDriver)->Time2Leader( f32DeltaTime / 1000.f );
	//			} else {
	//				(*itDriver)->Time2Leader( (OldPositionMap[(*itDriver)->Position() - 1]->Laps() - (*itDriver)->Laps() ) *1000);
	//			}
	//		} else {
	//			(*itDriver)->Time2Leader(0);
	//		}
	//	}
	}
}

tFloat32 cRace::GetBestTime() const
{
	tFloat32 nBestTime = 99;
	for(tDriverMap::const_iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++) 
	{
		nBestTime = min( nBestTime, itDriver->second.GetBestTime() );
	}

	return nBestTime;

}

tUInt cRace::GetMaxRounds() const
{
	tUInt nRounds = 0;
	for(tDriverMap::const_iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++) 
	{
		nRounds = max( nRounds, itDriver->second.GetNumberOfLaps() );
	}

	return nRounds;

}

tBool cRace::IsChaos() const
{ 
	if(m_eRaceState == RACE_STATE_CHAOS) 
	{ 
		return true; 
	} 
	else
	{
		return false;
	}
}

void cRace::ActivateChaos(tInt8 n) 
{ 
	if(m_eRaceState == RACE_STATE_NORMAL)
	{
		m_eRaceState = RACE_STATE_CHAOS;
		m_nChaosCounter++;
		if(GetDriver(n) != NULL)
		{
			GetDriver(n)->SetChaosDriver(true);
		}
		m_iChaosDriverID = n;
	}
}

void cRace::DeactivateChaos() 
{ 
	if(GetDriver(m_iChaosDriverID) != NULL)
	{
		GetDriver(m_iChaosDriverID)->SetChaosDriver(false);
	}
	m_iChaosDriverID = -1; 
}

