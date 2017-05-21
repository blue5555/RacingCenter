#ifndef cSerialportInfo_H
#define cSerialportInfo_H

#include "libCommon/stdafx.h"

class cSerialportInfo
{
	QString  strPortName;
	tUInt32  n32BaudRate;
	tUInt8   n8StopBits;
	tUInt8   n8DataBits;

public:
	cSerialportInfo();
	cSerialportInfo(const QString &i_strPortName,const tInt32 &i_i32Baudrate, const tInt8 &i_i8StopBits,const tInt8 &i_i8DataBits);
	~cSerialportInfo();

	QString PortName() const { return strPortName; }
	void PortName(QString val) { strPortName = val; }

	tUInt32 BaudRate() const { return n32BaudRate; }
	void BaudRate(tUInt32 val) { n32BaudRate = val; }

	tInt8 StopBits() const { return n8StopBits; }
	void StopBits(tInt8 val) { n8StopBits = val; }

	tInt8 DataBits() const { return n8DataBits; }
	void DataBits(tInt8 val) { n8DataBits = val; }
};

QDataStream& operator<< (QDataStream &s, const cSerialportInfo &myClass);
QDataStream& operator>> (QDataStream &s, cSerialportInfo &myClass);

#endif //cSerialportInfo_H