#include <libSerialConnector/cRawData.h>

#define _FILENAME_ "cRawData: "

cRawData::cRawData() : cThing()
,m_oTimeStamp(0)
{
	m_bDebug = false;
}

cRawData::cRawData(const tTimeStamp& i_oTimeStamp, QByteArray i_oByteArray) :
 m_oTimeStamp(i_oTimeStamp)
,m_oByteArray(i_oByteArray)
{

}

cRawData::~cRawData()
{
}

void cRawData::Clear()
{
	m_oByteArray.clear();
    m_oTimeStamp = 0;
}

tBool cRawData::MergeRawData(const cRawData& i_oRawData)
{
	m_oByteArray.append(i_oRawData.GetByteArray());
	m_oTimeStamp = (m_oTimeStamp/2 + i_oRawData.GetTimeStamp()/2);
	return true;
}

const tInt16 cRawData::GetIndexOf(const QString& i_QSDelimiter) const
{
	return m_oByteArray.indexOf(i_QSDelimiter);
}

cRawData cRawData::SplitRawData(const tInt16& i_n16Index)
{
    cRawData oNewRawData(m_oTimeStamp,m_oByteArray.left(i_n16Index));
	m_oByteArray = m_oByteArray.right(m_oByteArray.size() - i_n16Index - 1);

    return oNewRawData;
}

const tUInt32 cRawData::GetRawDataLength() const
{
	return m_oByteArray.size();
}