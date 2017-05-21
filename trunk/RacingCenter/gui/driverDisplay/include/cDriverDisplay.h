#ifndef cDriverDisplay_H
#define cDriverDisplay_H

#include <QtCore/QtGlobal>
//#include <QMainWindow>
#include <stdafx.h>
#include <cSVGView.h>
#include <cDriver.h>
#include <led.h>
#include <counter.h>
#include <qledindicator.h>

QT_BEGIN_NAMESPACE

namespace Ui {
	class cDriverDisplay;
}

QT_END_NAMESPACE


class cDriverDisplay : public cSvgView
{
    Q_OBJECT

private:
	sDriverMessage		m_oDriverMessage;
	tUInt8				m_nState;

	QGraphicsSvgItem*	m_opThrottle;
	QGraphicsSvgItem*	m_opNeedleThrottle;
	QGraphicsSvgItem*	m_opFuel;
	QGraphicsSvgItem*	m_opNeedleFuel;

	QLedIndicator*		m_opLedLaneChange;
	QLedIndicator*		m_opLedInBox;
	QLedIndicator*		m_opLedOutOfFuel;

	QTimer				m_oTimer;

	tBool				m_bTest;
	tBool				m_bToggle;

	tUInt8				m_nDriverID;

	tInt16				m_nFuelValue;
	tInt16				m_nThrottleValue;

	tBool				m_bLaneChange;
	tBool				m_bIsInBox;

	void init();

public:
    explicit cDriverDisplay(QWidget *parent = 0);
    ~cDriverDisplay();

	void updateThrottle(const tFloat32& i_nValue);
	void updateFuel(const tFloat32& i_nValue);

	void start();
	void stop();

protected:
	virtual void wheelEvent(QWheelEvent *event);
	virtual void resizeEvent(QResizeEvent *event);

private slots:
	void timeout();
	void UpdateDriverDisplay(sDriverMessage);

};

#endif // cDriverDisplay_H
