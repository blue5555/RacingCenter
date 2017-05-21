#ifndef cRawData_H
#define cRawData_H

#include <libCommon/stdafx.h>
#include <libCommon/cThing.h>
#include <QByteArray>

class cRawData : public cThing
{
	QByteArray  m_oByteArray;
	tTimeStamp  m_oTimeStamp;
		
	public:
		cRawData();
		cRawData(const tTimeStamp& i_oTimeStamp, QByteArray i_oByteArray);
		~cRawData();

		void Clear();

		const tTimeStamp& GetTimeStamp() const { return m_oTimeStamp; }
		const QByteArray& GetByteArray() const { return m_oByteArray; }

		tBool		   MergeRawData(const cRawData& i_oRawData);
		const tInt16   GetIndexOf(const QString& i_QSDelimiter) const;
        cRawData       SplitRawData(const tInt16& i_n16Index);
        const tUInt32  GetRawDataLength() const;

};

#endif //cRawData_H