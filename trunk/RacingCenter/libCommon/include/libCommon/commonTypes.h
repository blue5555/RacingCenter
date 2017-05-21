#ifndef commonTypes_H
#define commonTypes_H

using namespace std;

enum eDataSource
{
	CU = 0,
	ROUNDCOUNTER,
	MIKROCONTROLLER,
	CONTROLLER,
	STARTLIGHT,
	CU_VERSION
};

enum eCarState
{
	CARSTATE_NORMAL,
	CARSTATE_TIRE_DAMAGE,
	CARSTATE_ENGINE_DAMAGE
};

enum eFuelMode
{
	FUELMODE_OFF = 0,
	FUELMODE_ON,
	FUELMODE_REAL,
	FUELMODE_SIM,
	FUELMODE_CU
};

enum eRaceFinish
{
	FINISH_ROUNDS = 0,
	FINISH_TIME
};

enum eRaceMode
{
	MODE_TRAINING = 0,
	MODE_QUALITFYING,
	MODE_RACE,
	MODE_CHAMPIONSHIP
};

enum eRaceState
{
	RACE_STATE_NORMAL,
	RACE_STATE_CHAOS,
	RACE_STATE_READY4NORMAL,
	RACE_STATE_READY4SETNORMAL
};

enum eProgramCommand
{
	PROGRAM_SPEED = 0,
	PROGRAM_BRAKE = 1,
	PROGRAM_FUEL  = 2,
	PROGRAM_FLASHES = 4
};

struct sProgrammWord
{
	tUInt8 nID;
	tUInt8 nValue;
	tUInt8 nCommand;

	sProgrammWord()
	{
		nID = 0;
		nValue = 0;
		nCommand = 0;
	}

	sProgrammWord(tUInt8 i_nID, tUInt8 i_nCommand, tUInt8 i_nValue)
	{
		nID = i_nID;
		nValue = i_nValue;
		nCommand = i_nCommand;
	}
};

struct sController
{
	tInt8 m_ID;
	tInt8 m_Speed;
	tBool m_Button;
	tBool m_Chaos;
	sController()
	{
		m_ID = -1;
		m_Speed = 0;
		m_Button = false;
		m_Chaos = false;
	}
};

struct sRGB
{
	tUInt r;
	tUInt g;
	tUInt b;

	sRGB()
	{
		r = 0;
		g = 0;
		b = 0;
	}

	sRGB(tUInt i_nR, tUInt i_nG, tUInt i_nB)
	{
		r = i_nR;
		g = i_nG;
		b = i_nB;
	}

};

#endif // commonTypes_H