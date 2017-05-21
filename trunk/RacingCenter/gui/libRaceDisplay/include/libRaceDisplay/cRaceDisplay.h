#ifndef cRaceDisplay_H
#define cRaceDisplay_H

#include <libConfig/cConfig.h>
#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QGraphicsGridLayout>
#include <QLabel>
#include <QGraphicsWidget>
#include <QTextEdit>
//#include <QtGui/QApplication>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsView>
#include <cLabel.h>
#include <cDriver.h>
#include <cBoundBox.h>
#include <cProgressBar.h>
//#include "ui_racedisplay.h"

#define DISTANCE_BOUNDBOX 3

QT_BEGIN_NAMESPACE

namespace Ui {
	class RaceDisplay;
}

QT_END_NAMESPACE


class cRaceDisplay : public QGraphicsView
{
    Q_OBJECT

private:
	enum eRendererType { Native, OpenGL, Image };
	//Ui::RaceDisplay* m_opMainWindow;
	//QMutex				  m_oMutex;

	eRendererType m_eRenderer;

	cConfig*			  m_opConfig;
	QGraphicsScene*		  m_opScene;

	tBool				  m_bDebug;
	tBool				  m_bDebugTiming;

	//QGraphicsGridLayout   m_oLayout;

	QMap<tUInt8,cDriver*> m_oDrivers;

	map<tUInt8, vector<cBoundBox*> > m_oLabels;
	//vector<cBoundBox*>  m_oLabels;

	//void				configureHeader();
	//void				configureMap();
	//QGraphicsWidget*	configureRow(QString i_QSName, tUInt16 n16Row, tUInt16 n16Column, tBool i_bAddToMap);

	void setRenderer(eRendererType type = Native);

public:
    explicit cRaceDisplay(QWidget *parent = 0);
    ~cRaceDisplay();

	void start();
	void stop();

	void configureDisplay(QMap<tUInt8,cDriver*> i_oDriver);
	//void configureDrivers();
	//void updateDrivers();

protected:
	//virtual void wheelEvent(QWheelEvent *event);
	virtual void resizeEvent(QResizeEvent *event);
	virtual void closeEvent (QCloseEvent *event);

signals:
	void Closed();

private slots:
	void UpdateRaceDisplay(sDriverMessage i_oDriverMessage);
	void UpdateCompleteRaceDisplay();
    void setHighQualityAntialiasing(bool highQualityAntialiasing);

};

#endif // cRaceDisplay_H
