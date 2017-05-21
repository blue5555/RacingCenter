#ifndef cConnectionHelper_H
#define cConnectionHelper_H

//#include <QObject>
#include <stdafx.h>

class cConnectionHelper //: public QObject
{
	//Q_OBJECT
	tInt8 m_iFrame;

	sConnectionMessageHeader	m_oConnectionMessageHeader;
	QByteArray					m_oByteMessage;
	QVector<sControlMessage>    m_oControlMessages;
	QVector<sDriverMessage>     m_oDriverMessages;
	//QVector<sControllerMessage> m_oControllerMessages;

	tInt8	setFrame();

public:
	cConnectionHelper();
	~cConnectionHelper();

	void		clear();

	void		addControlMessage(sControlMessage i_oControlMessage);
	void		addDriverMessage(sDriverMessage i_oDriverMessage);
	//void		addController(sControllerMessage i_oControllerMessage);
	
	void		addDriverList(QStringList i_oDriverList);
	void		addCarList(QStringList i_oCarList);

	QByteArray	createMessage(const tTimeStamp& i_nTimeStamp);
	QByteArray  createMessageList(enum eMesageType, QStringList i_oList, const tTimeStamp& i_nTimeStamp);

	//void SetSocket(int Descriptor);

// signals:

	// public slots:
		// void connected();
		// void disconnected();
		// void readyRead();
		// void sendData();
		// void TaskResult(int Number);

// private:
	// QTcpSocket *socket;

};

#endif // MYCLIENT_H