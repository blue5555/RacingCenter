#ifndef sEvent_H
#define sEvent_H

#include "stdafx.h"

namespace RacingCenter
{

enum eEventType
{
	NONE,
	RAINING,
	TIRE,
	ENGINE,
	BRAKE
};

struct sEvent
{
	eEventType m_eEvent;
	
	tInt8	   m_iID;
	tUInt	   m_nCommand;
	tUInt	   m_nValue;

	eCarState  m_eCarState;
	tFloat64   m_f64FuelFactor;

	sEvent()
	{
		m_eEvent = NONE;
		m_eCarState = CARSTATE_NORMAL;
		m_iID = -1;
		m_nCommand = 0;
		m_nValue = 0;
		m_f64FuelFactor = 0;
	}

	sEvent(eEventType i_eEvent, tInt8 i_iID, tUInt i_nValue)
	{
		m_eEvent = i_eEvent;
		m_iID    = i_iID;
		m_nValue = i_nValue;
		
		switch(i_eEvent)
		{
		case RAINING:
			m_nCommand = PROGRAM_SPEED;
			m_eCarState = CARSTATE_TIRE_DAMAGE;
			break;
		case ENGINE:
			m_nCommand = PROGRAM_SPEED;
			m_eCarState = CARSTATE_ENGINE_DAMAGE;
			break;
		case BRAKE:
			m_nCommand = PROGRAM_BRAKE;
			break;
		}
	}
};

}

#endif