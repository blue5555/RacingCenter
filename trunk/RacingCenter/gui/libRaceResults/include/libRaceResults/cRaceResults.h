#ifndef cRaceResults_H
#define cRaceResults_H

#include "libCommon/cThing.h"
#include <libConfig/cConfig.h>
#include <libDataCore/cRace.h>
#include "libCore/cDataLogger.h"

#include <QWidget>
#include <QGridLayout>
#include <QProgressBar>
#include <QLabel>
#include <QMessageBox>

#define DISTANCE_BOUNDBOX 3

QT_BEGIN_NAMESPACE

namespace Ui {
	class cRaceResults;
}

QT_END_NAMESPACE


class cRaceResults : public QWidget, public cThing
{
    Q_OBJECT

private:
	//Ui::RaceDisplay* m_opMainWindow;
	QMutex				  m_oMutex;

	cConfig*			  m_opConfig;
	QGridLayout*		  m_opGridLayout;

	RacingCenter::cDataLogger* m_opDataLogger;
	RacingCenter::cRace*  m_opRace;

	vector<QLabel*>		  m_oLabels;

	tUInt m_nNumberOfColumns;
	tUInt m_nNumberOfRows;

	QLabel* CreateLabel(const QString& i_strText, const Qt::GlobalColor i_nColor);

public:
    explicit cRaceResults(QWidget *parent = 0, RacingCenter::cRace* i_opRace = NULL, RacingCenter::cDataLogger* i_opDataLogger = NULL);
    ~cRaceResults();

	void configureDisplay();
	
protected:
	//virtual void wheelEvent(QWheelEvent *event);
	virtual void resizeEvent(QResizeEvent *event);
	virtual void closeEvent (QCloseEvent *event);

signals:
	void ClosedRaceResults();

private slots:



};

#endif // cRaceResults_H
