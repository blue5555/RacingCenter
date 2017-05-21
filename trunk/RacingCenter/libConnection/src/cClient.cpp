#include "cClient.h"

MyClient::MyClient(QObject *parent) :
 QObject(parent)
,m_opTimer(NULL)
,m_bDebug(false)
{
	QThreadPool::globalInstance()->setMaxThreadCount(5);

	//m_opTimer = new QTimer(this);
	//connect(m_opTimer,   SIGNAL(timeout()),  this, SLOT( sendTestData() ) );
	//m_opTimer->setInterval(1000);
	//m_opTimer->start();
	
}

MyClient::~MyClient()
{
}

void MyClient::SetSocket(int Descriptor)
{
	// make a new socket
	socket = new QTcpSocket(this);

	if(m_bDebug) {
		qDebug() << "A new socket created!";
	}

	connect(socket, SIGNAL(connected()), this, SLOT(connected()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

	socket->setSocketDescriptor(Descriptor);

	if(m_bDebug) {
		qDebug() << " Client connected at " << Descriptor;
	}
}


// asynchronous - runs separately from the thread we created
void MyClient::connected()
{
	if(m_bDebug) {
		qDebug() << "Client connected event";
	}
}

// asynchronous
void MyClient::disconnected()
{
	if(m_bDebug) {
		qDebug() << "Client disconnected";
	}
	if(m_opTimer != NULL) {
		m_opTimer->stop();
	}
}

// Our main thread of execution
// This happening via main thread
// Our code running in our thread not in Qthread
// That's why we're getting the thread from the pool

void MyClient::readyRead()
{
	if(m_bDebug) {
		qDebug() << "MyClient::readyRead()";
	}
	
	QByteArray oRead = socket->readAll();
	
	if(m_bDebug) {
		qDebug() << oRead.size();
	}

	sConnectionMessageHeader oConnectionMessageHeader;

	// Time consumer
	//MyTask *mytask = new MyTask();
	//mytask->setAutoDelete(true);
	//connect(mytask, SIGNAL(Result(int)), this, SLOT(TaskResult(int)), Qt::QueuedConnection);
	//qDebug() << "Starting a new task using a thread from the QThreadPool";
	//QThreadPool::globalInstance()->start(mytask);

}

void MyClient::SendData(const QByteArray& i_oByteArry)
{
	socket->write(i_oByteArry);
}

// After a task performed a time consuming task.
// We grab the result here, and send it to client
void MyClient::TaskResult(int Number)
{
	QByteArray Buffer;
	Buffer.append("\r\nTask result = ");
	Buffer.append(QString::number(Number));

	socket->write(Buffer);
}


void MyClient::sendTestData()
{
	//sConnectionMessageHeader oConnectionMessageHeader;
	
	/*m_oConnectionMessageHeader.nFrameCounter = m_oConnectionMessageHeader.nFrameCounter++;
	if(m_oConnectionMessageHeader.nFrameCounter > 20000) {
	m_oConnectionMessageHeader.nFrameCounter = 10000;
	}
	m_oConnectionMessageHeader.n64TimeStamp  = 1234567890;
	m_oConnectionMessageHeader.nMajorVersion = 1;
	m_oConnectionMessageHeader.nMinorVersion = 1;

	m_oConnectionMessageHeader.nNumberOfPackages = 5;*/

	//QByteArray buf = QByteArray::fromRawData((char*)&oDriverMessage,sizeof(oDriverMessage));

	//char buf[sizeof(oConnectionMessageHeader)];
	//memcpy(buf, &oConnectionMessageHeader, sizeof(oConnectionMessageHeader));

	sDriverMessage oDriverMessage;
	oDriverMessage.m_iID = 1;
	oDriverMessage.m_bIsDisqualified = true;
	oDriverMessage.m_bIsInBox = false;
	oDriverMessage.m_f32CurrentRoundTime = 1.23f;
	oDriverMessage.m_f32FuelCapacity = 70.1f;
	oDriverMessage.m_f32FuelLevel = 30.3f;
	oDriverMessage.m_oController.m_Speed = 15;

	QByteArray buf = QByteArray::fromRawData((char*)&oDriverMessage,sizeof(oDriverMessage));
	//char buf[200];
	//memset(buf,0,sizeof(buf));
	//memcpy(buf, &oConnectionMessageHeader, sizeof(oConnectionMessageHeader));

	//QByteArray buf = "Hallo Welt";

	//qDebug() << "FrameCounter: " << m_oConnectionMessageHeader.nFrameCounter;

	qDebug() << "--- Start ----";
	//for(int i = 0; i < buf.size(); i++) {
	//	int k = buf[i];
	//	qDebug() << k;
	//}
	

	//qDebug() << "SizeOf: " << sizeof(oConnectionMessageHeader);
	//qDebug() << buf;

	//QByteArray Buffer = QByteArray::fromRawData(buf, sizeof(oConnectionMessageHeader));
	//socket->write(Buffer);

	socket->write(buf);
}
