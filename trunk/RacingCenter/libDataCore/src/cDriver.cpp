#include "cDriver.h"
#include "cRace.h"

//#include "libDatabase/cDatabase.h"

using namespace RacingCenter;

cDriver::cDriver() :
 cDatabaseDriver("")
,m_oCar("")
,m_iID(-1)
,m_opRace(NULL)
,m_opConfig(cConfig::instance())
,m_nPosition(0)
,m_f64BestTime(99)
,m_nLastTimerValue(0)
,m_nFirstPassTimeStamp(0)
,m_nLastPassTimeStamp(0)
,m_nLastControllerTimeStamp(0)
,m_bDisqualified(false)
,m_bFirstRound(false)
,m_nAccidents(0)
,m_f64Time2Leader(0)
,m_bChaos(false)
{
    Init();
}

cDriver::cDriver(cRace* i_opRace, const std::string& i_strDriverName, const tUInt& i_nID, const std::string& i_strCarName) :
 cDatabaseDriver(cDatabase::instance()->GetDriver(i_strDriverName))
,m_oCar(i_strCarName)
,m_opRace(i_opRace)
,m_iID(i_nID)
,m_opConfig(cConfig::instance())
,m_nPosition(0)
,m_f64BestTime(99)
,m_nLastTimerValue(0)
,m_nFirstPassTimeStamp(0)
,m_nLastPassTimeStamp(0)
,m_nLastControllerTimeStamp(0)
,m_bDisqualified(false)
,m_bFirstRound(false)
,m_nAccidents(0)
,m_f64Time2Leader(0)
,m_bChaos(false)
{
	Init();
}

cDriver::~cDriver()
{
}

tBool cDriver::Init()
{
	//m_opConfig = cConfig::instance();
	//m_bDebug = m_opConfig->m_oDebugMessages.bDriver;

	//cDatabase* opDatabase = cDatabase::instance();
	//sDatabaseDriver* opDatabaseDriver = opDatabase->GetDriver(m_strName);

	//m_nPoints               = opDatabaseDriver->m_n16Points;
	//m_nWinChampionships     = opDatabaseDriver->m_n16WinChampionships;
	//m_nWinRaces             = opDatabaseDriver->m_n16WinRaces;
	//m_nDrivingChampionships = opDatabaseDriver->m_n16DrivingChampionships;
	//m_nDrivingRaces         = opDatabaseDriver->m_n16DrivingRaces;

	m_bFinish = false;

	return true;
}

const tInt8 cDriver::GetID() const
{
	return m_iID;
}

cCar* cDriver::GetCar()
{
	return &m_oCar;
}

const sDriverMessage cDriver::CreateDisplayMessage(const tTimeStamp& i_oTimeStamp) const
{
	sDriverMessage oDriverMessage;

    memcpy(oDriverMessage.m_strName, m_strName.c_str(),32);
	//oDriverMessage.m_strName = m_strName.c_str();
	oDriverMessage.m_iID		= m_iID;
	oDriverMessage.m_bIsInBox	= m_oCar.GetIsInBox();
	oDriverMessage.m_nPosition	= m_nPosition;
	oDriverMessage.m_nRounds	= m_oRoundtimes.size();

	oDriverMessage.m_nTimeStamp = i_oTimeStamp;

	if(m_opRace)
	{
		oDriverMessage.m_nRaceRounds = m_opRace->Rounds();
		oDriverMessage.m_nRaceMode	 = m_opRace->RaceMode();
	}

	oDriverMessage.m_oController	 = m_oController;
	oDriverMessage.m_nProgSpeed		 = m_oCar.GetProgSpeed();
	oDriverMessage.m_bIsDisqualified = m_bDisqualified;
	oDriverMessage.m_f32FuelLevel    = m_oCar.GetFuelLevel();
	oDriverMessage.m_f32FuelCapacity = m_oCar.GetTankCapacity();

	oDriverMessage.m_bChoas = IsChaosDriver();

	oDriverMessage.m_f32BestLapTime = m_f64BestTime;
	if(!m_bFirstRound) {
		oDriverMessage.m_f32CurrentRoundTime = 0;
		oDriverMessage.m_f32Time2Leader = 0;
	} else {
		oDriverMessage.m_f32CurrentRoundTime = static_cast<tFloat64>((i_oTimeStamp - m_nLastPassTimeStamp))/1000;
		if(oDriverMessage.m_f32CurrentRoundTime > 999) {
			oDriverMessage.m_f32CurrentRoundTime = 999;
		}
		oDriverMessage.m_f32Time2Leader = m_f64Time2Leader;
	}
	if(m_oRoundtimes.size() > 0) {
		oDriverMessage.m_f32LastLapTime = m_oRoundtimes.back();
	} else {
		oDriverMessage.m_f32LastLapTime = 0;
	}
	return oDriverMessage;
}

tBool cDriver::UpdateTime(tUInt64 i_nTimerValue, const tTimeStamp& i_oTimeStamp)
{
	if(!m_bFirstRound && m_nLastTimerValue == 0) 
    {
		m_bFirstRound = true;
	} 
    else 
    {
		tFloat64 f64RoundTime = 0;
		f64RoundTime = static_cast<tFloat64>(i_nTimerValue - m_nLastTimerValue)/1000.0f;

		if(i_nTimerValue > m_nLastTimerValue)
		{
			f64RoundTime = static_cast<tFloat64>(i_nTimerValue - m_nLastTimerValue)/1000.0f;
			if(f64RoundTime < 1.0)
			{
				f64RoundTime = static_cast<tFloat64>(i_oTimeStamp - m_nLastPassTimeStamp)/1000.0f;
				return false;
			}
		}
		else if(i_nTimerValue == m_nLastTimerValue)
		{
			qDebug() << "Error: Same TimeStamp for Driver ID: " << m_iID;
			f64RoundTime = static_cast<tFloat64>(i_oTimeStamp - m_nLastPassTimeStamp)/1000.0f;
			return false;
		}

		if(m_bDebug) 
		{
			qDebug() << "Driver ID: " << m_iID 
					 << " CU RoundTime: " << f64RoundTime 
					 << " Windows RoundTime: " << (i_oTimeStamp - m_nLastPassTimeStamp)/1000
					 << " CarSpeed: " << m_oCar.GetProgSpeed();
		}
		
		m_oRoundtimes.push_back(f64RoundTime);
		if(f64RoundTime < m_f64BestTime) 
		{
			m_f64BestTime = f64RoundTime;
		}
	}

	m_nLastPassTimeStamp = i_oTimeStamp;
	m_nLastTimerValue = i_nTimerValue;

	return true;
}

tBool cDriver::UpdateController(const sController& i_oController, const tTimeStamp& i_oTimeStamp)
{
	if(i_oController.m_ID == m_iID) 
    {
		m_oController = i_oController;
		m_nLastControllerTimeStamp = i_oTimeStamp;

        m_oCar.UpdateFuel(m_oController,i_oTimeStamp);
        if(m_opConfig->m_oPenalty.bDisqualifiedByEmptyTank && m_oCar.GetFuelLevel() <= 0) 
        {
            m_bDisqualified = true;
        }
		return true;
	} 
    else 
    {
		return false;
	}
}

tBool cDriver::UpdateFuel(const tUInt& i_nFuelLevel, const tTimeStamp& i_oTimeStamp)
{
    m_oCar.UpdateFuel(i_nFuelLevel, i_oTimeStamp);
    return true;
}

tBool cDriver::UpdateBox(const tBool i_bIsInBox, const tTimeStamp& i_nTimeStamp)
{
	m_oCar.UpdateBox(i_bIsInBox, i_nTimeStamp);

	if(i_bIsInBox && m_oCar.GetCarState() != CARSTATE_NORMAL && m_oController.m_Speed == 0)
	{
		m_oCar.SetCarState(CARSTATE_NORMAL);
	}

	return true;
}

tUInt8 cDriver::GetCarSpeed()
{
	return m_oCar.GetSpeed();
}

tUInt8 cDriver::GetCarSpeedProg()
{
	return m_oCar.GetProgSpeed();
}

tBool cDriver::SetProgSpeed(const tUInt8 i_nSpeed)
{
	m_oCar.UpdateProgSpeed(i_nSpeed);
	return true;
}

tBool cDriver::IsFlashing()
{
	return m_oCar.IsFlashing();
}

tBool cDriver::ProcessEvent(const sEvent& i_oEvent)
{
	m_oCar.SetCarState(i_oEvent.m_eCarState);
	m_oCar.SetFuelFactor(i_oEvent.m_f64FuelFactor);

	return true;
}
