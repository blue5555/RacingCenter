#include <cDatabaseCar.h>

cDatabaseCar::cDatabaseCar(const std::string& i_strName) : cDatabaseBaseElement(i_strName)
{
    m_f64TankCapacity = 70;

    m_f64Consumption[0]  = 0.0f;
    m_f64Consumption[1]  = 0.1f;
    m_f64Consumption[2]  = 0.1f;
    m_f64Consumption[3]  = 0.2f;
    m_f64Consumption[4]  = 0.2f;
    m_f64Consumption[5]  = 0.3f;
    m_f64Consumption[6]  = 0.3f;
    m_f64Consumption[7]  = 0.4f;
    m_f64Consumption[8]  = 0.4f;
    m_f64Consumption[9]  = 0.5f;
    m_f64Consumption[10] = 0.5f;
    m_f64Consumption[11] = 0.6f;
    m_f64Consumption[12] = 0.7f;
    m_f64Consumption[13] = 0.8f;
    m_f64Consumption[14] = 0.9f;
    m_f64Consumption[15] = 1.0f;

    m_f64TankSpeed = 7;

    m_oSpeed[0]  = 9;
    m_oSpeed[1]  = 15;
    m_oSpeed[2]  = 15;
    m_oSpeed[3]  = 15;
    m_oSpeed[4]  = 14;
    m_oSpeed[5]  = 14;
    m_oSpeed[6]  = 13;
    m_oSpeed[7]  = 13;
    m_oSpeed[8]  = 12;
    m_oSpeed[9]  = 12;
    m_oSpeed[10] = 11;
    m_oSpeed[11] = 11;
    m_oSpeed[12] = 10;
    m_oSpeed[13] = 10;
    m_oSpeed[14] = 9;
    m_oSpeed[15] = 9;

    m_n8Speed = 15;
    m_n8Brake = 15;
    m_n8Fuel  = 15;

};

cDatabaseCar::~cDatabaseCar()
{

}

tFloat64 cDatabaseCar::GetConsumption(tUInt8 i_nIndex) const
{
    if(i_nIndex > 0 && i_nIndex < 16)
    {
        return m_f64Consumption[i_nIndex];
    }
    return 0;
}

void cDatabaseCar::SetConsumption(tUInt8 i_nIndex, tFloat64 i_f64Value)
{
    if(i_nIndex > 0 && i_nIndex < 16)
    {
        m_f64Consumption[i_nIndex] = i_f64Value;
    }
}

tUInt8 cDatabaseCar::GetSpeed(tUInt8 i_nIndex) const
{
    if(i_nIndex > 0 && i_nIndex < 16)
    {
        return m_oSpeed[i_nIndex];
    }
    return 0;
}

void cDatabaseCar::SetSpeed(tUInt8 i_nIndex, tUInt8 i_f64Value)
{
    if(i_nIndex > 0 && i_nIndex < 16)
    {
        m_oSpeed[i_nIndex] = i_f64Value;
    }
}