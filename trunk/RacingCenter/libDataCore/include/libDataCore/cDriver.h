#ifndef cDriver_H
#define cDriver_H

#include <libCommon/stdafx.h>
#include "libCommon/sEvent.h"
#include "cBasicData.h"
#include "libDatabase/cDatabase.h"
#include "cCar.h"
//#include "libConfig/cConfig.h"

namespace RacingCenter
{

class cRace;

class cDriver : public cThing, public cDatabaseDriver
{
	const cRace*		m_opRace;
	cConfig*			m_opConfig;

	tInt8				m_iID;

	tUInt				m_nDisplayNumber;

	tUInt				m_nPosition;

	tUInt16				m_nAccidents;

	tUInt64				m_nLastTimerValue;
	
	tTimeStamp			m_nFirstPassTimeStamp;
	tTimeStamp			m_nLastPassTimeStamp;
	tTimeStamp			m_nLastControllerTimeStamp;

	tBool				m_bDisqualified;

	tBool				m_bFirstRound;
	tBool				m_bFinish;

	tFloat64			m_f64BestTime;		
	tFloat64			m_f64Time2Leader;

	vector<tFloat64>	m_oRoundtimes;

	tBool				m_bIsInBox;

	cCar				m_oCar;
	sController			m_oController;

	tBool				m_bChaos;
    
	tBool				Init();

	public:
        cDriver();
        cDriver(cRace* i_opRace, const std::string& i_strDriverName, const tUInt& i_nID, const std::string& i_strCarName);
		~cDriver();

		tBool IsChaosDriver() const { return m_bChaos; }
		void SetChaosDriver(tBool val) { m_bChaos = val; }

		const tInt8 GetID() const;

		cCar* GetCar();		
        tFloat32 GetFuelLevel() { return GetCar()->GetFuelLevel(); };

		tUInt8 GetDisplayNumber() const { return m_nDisplayNumber; }
		void SetDisplayNumber(tUInt8 val) { m_nDisplayNumber = val; }

		const sDriverMessage CreateDisplayMessage(const tTimeStamp& i_nTimeStamp) const;

		const vector<tFloat64>& GetRoundTimes() { return m_oRoundtimes; };

		tUInt GetNumberOfLaps() const { return m_oRoundtimes.size(); };

		tBool GetIsDisqualified() const { return m_bDisqualified; };

		tBool ProcessEvent(const sEvent& i_oEvent);

		tBool IsFlashing();

		tBool UpdateTime(tUInt64 i_nTimerValue, const tTimeStamp& i_oTimeStamp);
		
        tBool UpdateController(const sController& i_oController, const tTimeStamp& i_oTimeStamp);
        tBool UpdateFuel(const tUInt& i_nFuelLevel, const tTimeStamp& i_oTimeStamp);

		tUInt8 GetCarSpeedProg();
		tBool SetProgSpeed(const tUInt8 i_nSpeed);
		tUInt8 GetCarSpeed();

        tBool UpdateBox(const tBool i_bIsInBox, const tTimeStamp& i_oTimeStamp);
        //tBool UpdateFuelSim(const tFloat32& i_f32FuelLevel, const tTimeStamp& i_oTimeStamp);

		tUInt GetNumberOfAccidents() const { return m_nAccidents; }
		//void Accidents(tUInt16 val) { m_nAccidents = val; }

		tFloat32 GetTime2Leader() const { return m_f64Time2Leader; }
		void SetTime2Leader(tFloat32 val) { m_f64Time2Leader = val; }

		tFloat32 GetBestTime() const { return m_f64BestTime; }
		void SetBestTime(tFloat32 val) { m_f64BestTime = val; }

        tUInt GetPosition() const { return m_nPosition; }
        void SetPosition(tUInt8 val) { m_nPosition = val; }

		tBool GetIsFinish() const { return m_bFinish; }
		void SetIsFinish(tBool val) { m_bFinish = val; }

		tFloat32 LastRoundTime() const 
		{ 
			if(m_oRoundtimes.size() > 0) { 
				return m_oRoundtimes.back(); 
			} else {
				return 99.0;
			}
		}

		tUInt64 GetLastTimerValue() const { return m_nLastTimerValue; }

};

}

#endif //cDriver_H