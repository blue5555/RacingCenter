#include <QApplication>
#include "cMainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
	//Q_INIT_RESOURCE(widgets);
	//Q_INIT_RESOURCE(driverDisplay);
	//Q_INIT_RESOURCE(qled);

    //QTextCodec::setCodecForTr(QTextCodec::codecForName("ISO 8859-1"));
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("ISO 8859-1"));

    MainWindow w;
    w.show();
	w.showMaximized();
	
	//cRacingCenterServer oRacingCenterServer;
	//oRacingCenterServer.StartServer();

    return a.exec();
}