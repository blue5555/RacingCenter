#ifndef cCar_H
#define cCar_H

#include <libCommon/stdafx.h>
#include "cBasicData.h"
#include <libConfig/cConfig.h>
#include "libDatabase/cDatabaseCar.h"

namespace RacingCenter
{

class cCar : public cThing, public cDatabaseCar
{
	//Q_OBJECT

	cConfig*	m_opConfig;

	tBool		m_bFlashOn;
	tBool		m_bBlinkInit;

	tTimeStamp	m_nLastFuelTimeStamp;
	tTimeStamp	m_nLastSendFlashLight;

	eCarState	m_eCarState;
	tFloat64	m_f64FuelFactor;

	tFloat64	m_f64TankLevel;

	tUInt8		m_nProgSpeed;

	tBool		m_bIsInBox;

	public:
		cCar(const std::string& i_strName);
		~cCar();

		void Init(/*const cDatabaseCar& i_oDatabaseCar*/);

		tBool SetCarState(eCarState i_eCarState);
		eCarState GetCarState() const;

		tBool SetFuelFactor(const tFloat64& i_f64FuelFactor);

		tBool IsFlashing();

		tUInt  GetSpeed() const;
        tUInt8 GetProgSpeed() const { return m_nProgSpeed; }

		tFloat64 GetFuelLevel() const { return m_f64TankLevel; }
		void SetFuelLevel(tFloat64 val) { m_f64TankLevel = val; }

		tBool UpdateFuel(const sController& m_oController, const tTimeStamp& i_nTimeStamp);
        tBool UpdateFuel(const tUInt& i_nFuelLevel, const tTimeStamp& i_nTimeStamp);

		tBool UpdateBox(const bool i_bIsInBox, const tTimeStamp& i_oTimeStamp);

		tBool GetIsInBox() const { return m_bIsInBox; }

		tBool UpdateProgSpeed(const tUInt8 i_nProgSpeed);
};

}

#endif //cCar_H