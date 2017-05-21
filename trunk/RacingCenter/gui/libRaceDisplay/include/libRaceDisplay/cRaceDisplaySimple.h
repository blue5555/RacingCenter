#ifndef cRaceDisplaySimple_H
#define cRaceDisplaySimple_H

#include "libCommon/cTimeStamp.h"
#include <libRaceDisplay/cLabel.h>
#include <libRaceDisplay/cProgressBar.h>
#include <libConfig/cConfig.h>
#include <libDataCore/cRace.h>

#include <QWidget>
#include <QGridLayout>
#include <QProgressBar>

//#include <cBoundBox.h>
//#include <cProgressBar.h>

#define DISTANCE_BOUNDBOX 3

QT_BEGIN_NAMESPACE

namespace Ui {
	class RaceDisplaySimple;
}

QT_END_NAMESPACE

namespace RacingCenter
{

class cRaceDisplaySimple : public QWidget
{
    Q_OBJECT

private:
	QTimer				  m_oFastTimer;
	QThread				  m_oFastTimerThread;
	
	QTimer				  m_oTimer;
	QThread				  m_oTimerThread;

	QMutex				  m_oMutex;
	cConfig*			  m_opConfig;

	QGridLayout*		  m_opGridLayout;	     

	tBool				  m_bInit;

	tBool				  m_bDebug;
	tBool				  m_bDebugTiming;

	tUInt				  m_nNumberOfColumns;
	tUInt				  m_nNumberOfRows;

	const tDriverMapPointer m_oDrivers;

	cRace*				 m_opRace;
	cLabel*				 m_opRaceState;

	map<tUInt8, cLabel* > m_oHeader;
	map<tUInt8, cLabel* > m_oDriverName;
	map<tUInt8, vector<cLabel*> > m_oLabels;
	map<tUInt8, cProgressBar* >   m_oProgressBars;

	map<tUInt8, tBool>			m_oUpdate;
	map<tUInt8, sDriverMessage> m_oMessages;

    void configureDisplay();

public:
    explicit cRaceDisplaySimple(const tDriverMapPointer& i_oDriverMap, cRace* i_opRace, QWidget *parent = 0);
    ~cRaceDisplaySimple();

protected:
	virtual void resizeEvent(QResizeEvent *event);
	virtual void closeEvent (QCloseEvent *event);

signals:
	void Closed();

private slots:
	//void UpdateRaceDisplay(sDriverMessage i_oDriverMessage);
	void UpdateDriverRaceDisplay(sDriverMessage i_oDriverMessage);
	//void UpdateCompleteRaceDisplay(/*sDriverMessage i_oDriverMessage*/);
	void UpdateRaceDisplayFast(/*sDriverMessage i_oDriverMessage*/);
};

}

#endif // cRaceDisplay_H
