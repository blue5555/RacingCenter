#ifndef cDatabaseCar_H
#define cDatabaseCar_H

#include <libCommon/stdafx.h>
#include "cDatabaseBaseElement.h"

class cDatabaseCar : public cDatabaseBaseElement
{

protected:
	tFloat64  	m_f64TankCapacity;

    tFloat64	m_f64Consumption[16];
	tUInt8		m_oSpeed[16];

	tFloat64	m_f64TankSpeed;

	tUInt8		m_n8Speed;
    tUInt8		m_n8Brake;
    tUInt8		m_n8Fuel;

public:
	cDatabaseCar(const std::string& i_strName);
    ~cDatabaseCar();

    tFloat64 GetConsumption(tUInt8 i_nIndex) const;
    void     SetConsumption(tUInt8 i_nIndex, tFloat64 i_f64Value);

    tUInt8 GetSpeed(tUInt8 i_nIndex) const;
    void   SetSpeed(tUInt8 i_nIndex, tUInt8 i_f64Value);

    tFloat64 GetTankCapacity() const { return m_f64TankCapacity; }
    void SetTankCapacity(tFloat64 val) { m_f64TankCapacity = val; }

    tFloat64 GetTankSpeed() const { return m_f64TankSpeed; }
    void SetTankSpeed(tFloat64 val) { m_f64TankSpeed = val; }

    tUInt8 GetSpeed() const { return m_n8Speed; }
    void SetSpeed(tUInt8 val) { m_n8Speed = val; }

    tUInt8 GetBrake() const { return m_n8Brake; }
    void SetBrake(tUInt8 val) { m_n8Brake = val; }

    tUInt8 GetFuel() const { return m_n8Fuel; }
    void SetFuel(tUInt8 val) { m_n8Fuel = val; }
};

#endif