#ifndef cRace_H
#define cRace_H

#include <libCommon/stdafx.h>
#include "libCommon/cTimeStamp.h"
#include <libCommon/sCUData.h>
#include "libConfig/cConfig.h"
#include "cDriver.h"
#include "cCar.h"

namespace RacingCenter
{

typedef std::map<tUInt8, cDriver>  tDriverMap;
typedef std::map<tUInt8, cDriver*> tDriverMapPointer;

class cRace : public cThing
{
	cConfig*	m_opConfig;

	QMutex		m_oMutex;
	QTimer		m_oRaceTimer;

	//cStartLight m_oStartLight;
	tTimeStamp	m_nStartTime;

	eRaceFinish m_eRaceFinish;

	eRaceState  m_eRaceState;

	eRaceMode	m_eRaceMode;
	eFuelMode	m_eFuelMode;

	tUInt8		m_nChaosCounter;
	tInt8		m_iChaosDriverID;

	tUInt		m_nRounds;
	tUInt		m_nTime;

	tBool		m_bDriveFinish;
	tBool		m_bRaceOver;
    
    tBool       m_bInit;
    tUInt       m_nInitCounter;

	//cTrack		m_oTrack;
    
	tDriverMap m_oDrivers;

	void CalculateDriverPositions(uint i_nDriverID);
	void SortSequenceOfTheDriverBestTime();
	void SortSequenceOfTheDriverRace(uint i_nDriverID);

	void SetDriverPoints();

    tBool UpdateDriverController(const sController& i_oController, const tTimeStamp& i_oTimeStamp);
    tBool UpdateDriverTime(const sCUDriver& i_oCUDriver, const tTimeStamp& i_oTimeStamp);
    tBool UpdateDriverBox(const tUInt8& i_nDriverID, const bool& i_bIsInBox, const tTimeStamp& i_oTimeStamp);
	tBool UpdateDriverSpeed(cDriver& i_oDriver);

	tBool ProcessEvent(const sData& i_oCUWord);
    tBool ProcessCUWord(const sData& i_oCUWord);
    tBool ProcessPenalty(const sData& i_oCUWord);
    tBool ProcessBox(const sData& i_oCUWord);
    tBool ProcessCUDriver(const sData& i_oCUDriver);
    tBool ProcessController(const sData& i_oController);
    tBool ProcessFuel(const sData& i_oData);
	tBool ProcessProgramWord(const sData& i_oData);

    const tUInt GetNumberOfFinishDrivers() const;
    tBool CheckForRaceEnd(tUInt8 i_nDriverID);

	public:
		cRace();
		cRace(const eRaceFinish& i_eRaceFinish, const tUInt16& i_nValue);
		~cRace();

		tBool Init();
		tTimeStamp GetStartTimeStamp() const { return m_nStartTime; }

		tBool IsChaos() const;
		void ActivateChaos(tInt8 n);
		void DeactivateChaos();

		void SetRaceState(eRaceState i_eRaceState) { m_eRaceState = i_eRaceState; }
		eRaceState GetRaceState() const { return m_eRaceState; }

		tUInt GetChaosCounter() const { return m_nChaosCounter; }
		tInt8 GetChaosDriverID() const { return m_iChaosDriverID; }

		eRaceMode RaceMode() const { return m_eRaceMode; }
		void RaceMode(eRaceMode val) { m_eRaceMode = val; }

		eFuelMode FuelMode() const { return m_eFuelMode; }
		void FuelMode(eFuelMode val) { m_eFuelMode = val; }

		eRaceFinish RaceFinish() const { return m_eRaceFinish; }
		void RaceFinish(eRaceFinish val) { m_eRaceFinish = val; }

		tFloat32 GetBestTime() const;
		tBool GetDriveFinish() const { return m_bDriveFinish; }

		tUInt16 Rounds() const { return m_nRounds; }
		void	Rounds(tUInt16 val) { m_nRounds = val; }

		tUInt16 Time() const { return m_nTime; }
		void	Time(tUInt16 val) { m_nTime = val; }

        // update race
        tBool UpdateRace(const sData& i_oCUData);

		// driver functions
		tBool Reset();
		tBool AddDriver(const cDriver& i_oDriver);
        tBool DeleteDriver(const tUInt8& i_nID);

        cDriver*	GetDriver(const tUInt8& i_nID);
		const cDriver* GetDriver(const tUInt8& i_nID) const;
		const cDriver* GetDriverByPosition(const tUInt8& i_nPostion) const;
		cDriver* GetDriverByPosition(const tUInt8& i_nPostion);

		tBool CreateDriverMessage(const tUInt8& i_nID, const tTimeStamp& i_nTimeStamp, sDriverMessage& o_oDriverMessage) const;

		const tDriverMap&		GetDriverMap() const;
		const tDriverMapPointer GetDriverMapByDisplayID(const tUInt8 i_nDisplayID);

		tUInt GetMaxRounds() const;

		tBool CheckForProgramUpdate(vector<sProgrammWord>& o_oProgrammWords);

        tBool IsRaceOver() const;

signals:
		void SendProgrammWord(int i_iController, int i_iProgrammWord, int i_iValue);
		void RaceOver();

public slots:
		void UpdateDriverBlink(int m_iID, bool i_bState);
};

}

#endif // cRace_H