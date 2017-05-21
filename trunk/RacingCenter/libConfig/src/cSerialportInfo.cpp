#include "cSerialportInfo.h"

cSerialportInfo::cSerialportInfo()
{
	strPortName = "COM1";
	n32BaudRate = 19200;
	n8StopBits  = 1;
	n8DataBits  = 8;
}

cSerialportInfo::cSerialportInfo(const QString &i_strPortName,const tInt32 &i_i32Baudrate, const tInt8 &i_i8StopBits,const tInt8 &i_i8DataBits)
{
	strPortName = i_strPortName;
	n32BaudRate = i_i32Baudrate;
	n8StopBits  = i_i8StopBits;
	n8DataBits  = i_i8DataBits;
}

cSerialportInfo::~cSerialportInfo()
{

}

QDataStream& operator<< (QDataStream &s, const cSerialportInfo &myClass)
{
	s << myClass.PortName();
	s << myClass.BaudRate();
	s << myClass.StopBits();
	s << myClass.DataBits();
	return s;
}

QDataStream& operator>> (QDataStream &s, cSerialportInfo &myClass)
{
	QString strPortName;
	s >> strPortName;
	myClass.PortName(strPortName);

	tUInt32 i32Baudrate;
	s >> i32Baudrate;
	myClass.BaudRate(i32Baudrate);

	tUInt8 i8StopBits;
	s >> i8StopBits;
	myClass.StopBits(i8StopBits);

	tUInt8 i8DataBits;
	s >> i8DataBits;
	myClass.DataBits(i8DataBits);
	return s;
}