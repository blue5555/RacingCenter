#include "cConnectionHelper.h"

#define _FILENAME_ "cConnectionHelper: "

cConnectionHelper::cConnectionHelper() :
 m_iFrame(0)
// QObject(parent)
{
}

cConnectionHelper::~cConnectionHelper()
{
}

void cConnectionHelper::clear()
{
	m_oByteMessage.clear();
	m_oConnectionMessageHeader.clear();
	m_oControlMessages.clear();
	m_oDriverMessages.clear();
}

void cConnectionHelper::addControlMessage(sControlMessage i_oControlMessage)
{
	m_oControlMessages.push_back(i_oControlMessage);
}

void cConnectionHelper::addDriverMessage(sDriverMessage i_oDriverMessage)
{
	m_oDriverMessages.push_back(i_oDriverMessage);
}

void cConnectionHelper::addDriverList(QStringList i_oDriverList)
{

}

void cConnectionHelper::addCarList(QStringList i_oCarList)
{
	
}

QByteArray cConnectionHelper::createMessageList(enum eMesageType, QStringList i_oList, const tTimeStamp& i_nTimeStamp)
{
	m_oByteMessage.clear();
	m_oConnectionMessageHeader.clear();

	m_oConnectionMessageHeader.nFrameCounter = setFrame();
	m_oConnectionMessageHeader.n64TimeStamp = i_nTimeStamp;

	m_oConnectionMessageHeader.nNumberOfPackages = 1;
	//m_oConnectionMessageHeader.

	return m_oByteMessage;
}

QByteArray cConnectionHelper::createMessage(const tTimeStamp& i_nTimeStamp)
{
	m_oByteMessage.clear();
	m_oConnectionMessageHeader.clear();

	tInt8 a = sizeof(sDriverMessage);	// 66 Byte
	tInt8 b = sizeof(sControlMessage);	//  2 Byte
	tInt8 c = sizeof(sConnectionMessageHeader);	//  20 Byte

	m_oConnectionMessageHeader.nFrameCounter = setFrame();
	m_oConnectionMessageHeader.n64TimeStamp = i_nTimeStamp;
	m_oConnectionMessageHeader.nNumberOfPackages = m_oControlMessages.size() + m_oDriverMessages.size();
	m_oConnectionMessageHeader.nMessageSize = m_oControlMessages.size() * sizeof(sControlMessage) + 
											  m_oDriverMessages.size()  * sizeof(sDriverMessage);

	if(m_oConnectionMessageHeader.nNumberOfPackages > NUMBER_OF_PACKAGES) {
		qDebug() << _FILENAME_ << "NumberOfPackages > NUMBER_OF_PACKAGES";
		return m_oByteMessage;
	}

	tUInt8 nPackageCounter = 0;
	QByteArray controlMessage;
	for(tInt16 n = 0; n < m_oControlMessages.size(); n++) {
		m_oConnectionMessageHeader.nPackages[nPackageCounter] = MESSAGE_CONTROL;
		QByteArray package = QByteArray::fromRawData((char*)&m_oControlMessages[n],sizeof(m_oControlMessages[n]));
		controlMessage.append(package);
		nPackageCounter++;
	}

	QByteArray driverMessage;
	for(tInt16 n = 0; n < m_oDriverMessages.size(); n++) {
		m_oConnectionMessageHeader.nPackages[nPackageCounter] = MESSAGE_DRIVER;
		QByteArray package = QByteArray::fromRawData((char*)&m_oDriverMessages[n],sizeof(m_oDriverMessages[n]));
		driverMessage.append(package);
		nPackageCounter++;
	}

	QByteArray header = QByteArray::fromRawData((char*)&m_oConnectionMessageHeader,sizeof(m_oConnectionMessageHeader));
	m_oByteMessage.append(header);
	m_oByteMessage.append(controlMessage);
	m_oByteMessage.append(driverMessage);

	return m_oByteMessage;
}

tInt8 cConnectionHelper::setFrame()
{
	if(m_iFrame > 126) {
		m_iFrame = 0;
	} else {
		m_iFrame++;
	}
	return m_iFrame;
}