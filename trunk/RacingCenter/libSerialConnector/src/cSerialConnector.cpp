#include "libSerialConnector/cSerialConnector.h"
#include <iostream>

#define _FILENAME_ "cSerialConnector: "

cSerialConnector::cSerialConnector(cQueue<cRawData>& i_oQueueRawData) : 
 m_oQueueRawData(i_oQueueRawData)
,m_opConfig(cConfig::instance())
{
	m_bDebug = true;
	m_bInit  = false;

	if (m_bDebug)
	{
		m_oFileWriter.Init("C:/RacingCenter/SerialRawOutput.txt");
	}
}

cSerialConnector::~cSerialConnector()
{
	DeInit();
}

tBool cSerialConnector::Init(const cSerialportInfo& i_oSerialPortInfo)
{
	cConfig* opConfig = cConfig::instance();
	m_bDebug = opConfig->m_oDebugMessages.bSerialconnector;

	connect(this, SIGNAL(readyRead()), this, SLOT(readData()));

	m_iStartTime = 0;

	return SetSerialPortInfo(i_oSerialPortInfo); 
}

tBool cSerialConnector::DeInit()
{
	if (m_bDebug)
	{
		m_oFileWriter.Close();
	}
	close();

	return true;
}

tBool cSerialConnector::SetSerialPortInfo(const cSerialportInfo& i_oSerialportInfo)
{
	cConfig* opConfig = cConfig::instance();
	m_bDebug		= opConfig->m_oDebugMessages.bSerialconnector;
	m_bDebugTiming	= opConfig->m_oDebugMessagesTiming.bSerialconnector;

	//m_oSerialPort.setPortName("COM1");

	setPortName(i_oSerialportInfo.PortName());
	setBaudRate( i_oSerialportInfo.BaudRate() );
	setDataBits( QSerialPort::Data8 );
	setParity(QSerialPort::NoParity);
	setStopBits( QSerialPort::OneStop );
	setFlowControl( QSerialPort::NoFlowControl );

	if(!isOpen()) 
    {
		if(open(QIODevice::ReadWrite)) 
        {
			return true;
		} 
        else 
        {
			return false;
		}
	}
	return true;
}

tBool cSerialConnector::OpenSerialport()
{
    if(!isOpen()) 
    {
        if(!open(QIODevice::ReadWrite)) 
        {
			qDebug() << this->errorString();
			qDebug() << this->error();
            return false;
        }
    }
    return true;
}

tResult cSerialConnector::SendData(char* m_oBuffer, tInt8 i_nSize)
{
    if(!isOpen())
	{
		if(OpenSerialport())
		{
			write(m_oBuffer,i_nSize);
		}
	}
	else
	{
		write(m_oBuffer,i_nSize);
	}

	return ERROR_NOERROR;
}

tResult cSerialConnector::SendData(const QByteArray& i_oData)
{
	if(!isOpen())
	{
		if(OpenSerialport())
		{
			write(i_oData);
		}
	}
	else
	{
		write(i_oData);
	}
	return ERROR_NOERROR;
}

tResult cSerialConnector::SendData(const string& i_strSendData)
{
	if(!isOpen())
	{
		if(OpenSerialport())
		{
			write(i_strSendData.c_str());
		}
	}
	else
	{
		write(i_strSendData.c_str());
	}
	return ERROR_NOERROR;
}

void cSerialConnector::readData()
{
    if(m_bDebugTiming) 
    {
        m_iStartTime = cTimeStamp::GetTimeStamp();
        DEBUGMSGTIMING( "Start Read Data: " << QDateTime::currentMSecsSinceEpoch());
        DEBUGMSGTIMING( "bytesAvailable: " << bytesAvailable());
    }

    QByteArray oData = readAll();

    if (m_bDebug)
    {	
        qDebug() << _FILENAME_ << "Data: " << oData;
		m_oFileWriter.WriteLine(oData);
    }

    tTimeStamp oTimeStamp = cTimeStamp::GetTimeStamp();

    m_oQueueRawData.push(cRawData(oTimeStamp,oData));

    if (m_bDebugTiming)
    {
        qint64 iEndTime = cTimeStamp::GetTimeStamp();

        if(m_bDebugTiming) {
            DEBUGMSGTIMING( "Read: " << oData);
            DEBUGMSGTIMING( "End Read Data: " << cTimeStamp::GetTimeStamp());
            DEBUGMSGTIMING( "Delta Time: " << (iEndTime - m_iStartTime) / 1000 );
        }
    }

}

std::list<std::string> cSerialConnector::GetAllSerialports()
{
	std::list<string> oList;

	QList<QSerialPortInfo> oPorts = QSerialPortInfo::availablePorts();
	for(int n = 0; n < oPorts.size(); n++)
	{
		oList.push_back(oPorts[n].portName().toStdString());
	}

	oList.sort();

	return oList;
}

std::list<tUInt> cSerialConnector::GetAllBaudRate()
{
    std::list<tUInt> list;

    list.push_back(19200);
    list.push_back(38400);
    list.push_back(115200);

    return list;
}