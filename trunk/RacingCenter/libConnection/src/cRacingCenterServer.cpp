#include "cRacingCenterServer.h"
#include <cRace.h>

cRacingCenterServer::cRacingCenterServer(QObject *parent) :
QTcpServer(parent)
{
}

void cRacingCenterServer::StartServer()
{
	if(listen(QHostAddress::Any, 4711))
	{
		qDebug() << "Server: started";
	}
	else
	{
		qDebug() << "Server: not started!";
	}
}

void cRacingCenterServer::incomingConnection(int handle)
{
	// at the incoming connection, make a client
	MyClient *client = new MyClient(this);
	client->SetSocket(handle);
	m_oClients.push_back(client);
}

void cRacingCenterServer::SendDataToAllClients(const cRace& i_oRace, const tTimeStamp& i_oTimeStamp)
{
	cConnectionHelper oHelper;

	for(tUInt8 n = 0; n < 6; n++) {
		cDriver* opDriver = i_oRace.GetDriver(n);
		if(opDriver != NULL) {
			oHelper.addDriverMessage(opDriver->CreateDisplayMessage(i_oTimeStamp));
		}
	}

	QByteArray oBytes = oHelper.createMessage(i_oTimeStamp);

	for(QVector<MyClient*>::iterator it = m_oClients.begin(); it != m_oClients.end(); it++ ) {
		(*it)->SendData(oBytes);
	}
}