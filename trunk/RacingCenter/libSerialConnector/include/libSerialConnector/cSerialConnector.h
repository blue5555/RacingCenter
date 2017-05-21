#ifndef cSerialConnector_H
#define cSerialConnector_H

#include <libCommon/stdafx.h>
#include "libCommon/cTimeStamp.h"
#include <libCommon/cThing.h>
#include "libCommon/cFileWriter.h"
#include <libConfig/cConfig.h>
#include <libConfig/cSerialportInfo.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "cRawData.h"

class cSerialConnector : public QSerialPort, public cThing
{
	Q_OBJECT

	private:
        cConfig*					m_opConfig;
		cQueue<cRawData>&			m_oQueueRawData;
		tBool						m_bInit;
		qint64						m_iStartTime;
		RacingCenter::cFileWriter	m_oFileWriter;

	protected:
        tBool	SetSerialPortInfo(const cSerialportInfo& i_oSerialportInfo);
		tBool   OpenSerialport();

	public:
		cSerialConnector(cQueue<cRawData>& i_opQueueRawData);
		~cSerialConnector();

		tBool   Init(const cSerialportInfo& i_oSerialPortInfo);
		tBool	DeInit();

		tResult SendData(char* m_oBuffer, tInt8 i_nSize);
		tResult	SendData(const string& i_strSendData);
		tResult	SendData(const eDataSource& i_eDataSOurce);
		tResult SendData(const QByteArray& i_oData);

        static std::list<tUInt> GetAllBaudRate();
		static std::list<std::string> GetAllSerialports();

	signals:
		void receivedData();
		void finish();


	private slots:
		void readData();
};

#endif //cSerialConnector_H