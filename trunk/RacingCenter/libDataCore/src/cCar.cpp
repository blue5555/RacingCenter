#include <cCar.h>
#include "libDatabase/cDatabase.h"

#define BLICK_LEVEL 10
#define BLINK_TIME  2000

#define _FILENAME_ "cCar: "

using namespace RacingCenter;

cCar::cCar(const std::string& i_strName) : 
 cDatabaseCar(cDatabase::instance()->GetCar(i_strName))
,m_nLastFuelTimeStamp(0)
,m_nLastSendFlashLight(0)
,m_opConfig(cConfig::instance())
,m_eCarState(CARSTATE_NORMAL)
,m_f64FuelFactor(1.0)
{
    Init();
}

cCar::~cCar()
{
}

void cCar::Init()
{
	m_bDebug		= m_opConfig->m_oDebugMessages.bCar;
	m_nProgSpeed	= m_n8Speed;
	m_f64TankLevel	= m_f64TankCapacity;

	m_nLastFuelTimeStamp = 0;
	m_nLastSendFlashLight = 0;

	m_bIsInBox   = false;
	m_bFlashOn	 = false;
	m_bBlinkInit = false;
}

tBool cCar::SetCarState(eCarState i_eCarState)
{
	m_eCarState = i_eCarState;
	return true;
}

eCarState cCar::GetCarState() const
{
	return m_eCarState;
}

tBool cCar::SetFuelFactor(const tFloat64& i_f64FuelFactor)
{
	m_f64FuelFactor = i_f64FuelFactor;
	return true;
}

tBool cCar::UpdateBox(const bool i_bIsInBox, const tTimeStamp& i_oTimeStamp)
{
	m_bIsInBox = i_bIsInBox;
	return true;
}

tBool cCar::UpdateFuel(const sController& i_oController, const tTimeStamp& i_nTimeStamp)
{
	if(m_nLastFuelTimeStamp == 0) {
		m_nLastFuelTimeStamp = i_nTimeStamp;
	} else {
		if(!m_bIsInBox) 
		{
			m_f64TankLevel -= m_f64FuelFactor * m_f64Consumption[i_oController.m_Speed] * static_cast<tFloat32>(i_nTimeStamp-m_nLastFuelTimeStamp) / (1000);
			if(m_f64TankLevel < 0) 
			{
				m_f64TankLevel = 0;
			}
		} else if(i_oController.m_Button && i_oController.m_Speed == 0 && m_bIsInBox) {
			m_f64TankLevel += m_f64TankSpeed * (i_nTimeStamp-m_nLastFuelTimeStamp) / (1000);
			if(m_f64TankLevel > m_f64TankCapacity) 
			{
				m_f64TankLevel = m_f64TankCapacity;
			}
		}

		tUInt8 nFuel = static_cast<tUInt8>( m_f64TankLevel / m_f64TankCapacity * 100 );
		if(nFuel < 100 /* m_opConfig->m_oFuelConfig.nValueYellow*/)
		{
			if(m_nLastSendFlashLight == 0)
			{
				m_nLastSendFlashLight = i_nTimeStamp;
				m_bFlashOn = true;
			}
			else if ( (i_nTimeStamp - m_nLastSendFlashLight) > BLINK_TIME )
			{
				m_nLastSendFlashLight = i_nTimeStamp;
				m_bFlashOn = true;
			}
		}
		else
		{
			m_bFlashOn = false;
		}

	}

	m_nLastFuelTimeStamp = i_nTimeStamp;

	return true;
}

tBool cCar::UpdateFuel(const tUInt& i_nFuelLevel, const tTimeStamp& i_nTimeStamp)
{
    m_f64TankLevel = static_cast<tFloat64>(i_nFuelLevel);
    m_f64TankCapacity = 15.0f;
    return true;
}

tUInt cCar::GetSpeed() const
{
	tUInt nSpeed = 0;
	switch(m_eCarState)
	{
	case CARSTATE_NORMAL:
		nSpeed = m_oSpeed[ static_cast<tUInt8>(15 * m_f64TankLevel / m_f64TankCapacity)];
		break;
	case CARSTATE_TIRE_DAMAGE:
		nSpeed = 0;
		break;
	}

	return nSpeed;
}

tBool cCar::UpdateProgSpeed(const tUInt8 i_nProgSpeed)
{
	m_nProgSpeed = i_nProgSpeed; 
	return true;
}

tBool cCar::IsFlashing()
{
	if(m_bFlashOn)
	{
		m_bFlashOn = false;
		return true;
	}
	else
	{
		return false;
	}
}