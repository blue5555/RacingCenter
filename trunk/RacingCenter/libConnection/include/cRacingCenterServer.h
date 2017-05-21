#ifndef cRacingCenterServer_H
#define cRacingCenterServer_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <stdafx.h>
#include "cClient.h"
//#include <cRace.h>

class cRace;

class cRacingCenterServer : public QTcpServer
{
	Q_OBJECT

	QVector<MyClient*> m_oClients;

public:
	explicit cRacingCenterServer(QObject *parent = 0);
	void StartServer();

	void SendDataToAllClients(const cRace& i_oRace, const tTimeStamp& i_oTimeStamp);

protected:
	void incomingConnection(int handle);

signals:

	public slots:

};

#endif // cRacingCenterServer_H