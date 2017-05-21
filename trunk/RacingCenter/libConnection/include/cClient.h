// myclient.h

#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include <stdafx.h>
#include "cConnectionHelper.h"
#include "cRacingCenterServerTask.h"

class MyClient : public QObject
{
	Q_OBJECT

	//sConnectionMessageHeader m_oConnectionMessageHeader;
	tBool m_bDebug;
	cConnectionHelper m_oConnectionHelper;

	QTimer* m_opTimer; 
public:
	explicit MyClient(QObject *parent = 0);
	~MyClient();

	void SetSocket(int Descriptor);

	void SendData(const QByteArray& i_oByteArry);

signals:

	public slots:
		void connected();
		void disconnected();
		void readyRead();
		void sendTestData();
		
		//void sendTestData();
		// make the server fully ascynchronous
		// by doing time consuming task
		void TaskResult(int Number);

private:
	QTcpSocket *socket;

};

#endif // MYCLIENT_H