#include "cDriverDisplay.h"

#include <QMessageBox>
#include <cConfig.h>

//! [0]
cDriverDisplay::cDriverDisplay(QWidget *parent) :
 cSvgView(parent)
,m_opThrottle(NULL)
,m_opNeedleThrottle(NULL)
,m_opFuel(NULL)
,m_opNeedleFuel(NULL)
,m_opLedLaneChange(NULL)
,m_opLedInBox (NULL)
,m_opLedOutOfFuel(NULL)
,m_nFuelValue(0)
,m_nThrottleValue(0)
,m_nDriverID(0)
{
	init();
	
	connect(&m_oTimer, SIGNAL(timeout()), SLOT(timeout()), Qt::DirectConnection);
	
	m_oTimer.setInterval(100);
	
}

cDriverDisplay::~cDriverDisplay()
{
}

void cDriverDisplay::start()
{
	m_oTimer.start();
}

void cDriverDisplay::stop()
{
	m_oTimer.stop();
}

void cDriverDisplay::init()
{
	openFile(false,":/images/Throttle.svg",&m_opThrottle);
	openFile(false,":/images/Needle.svg",&m_opNeedleThrottle);

	m_opThrottle->setPos(m_opThrottle->boundingRect().width(),m_opThrottle->boundingRect().height()/2);

	QTransform oTransformThrottleNeedle;
	oTransformThrottleNeedle.translate(m_opThrottle->boundingRect().width()*1.5  - m_opNeedleThrottle->boundingRect().width()/2,
									   m_opThrottle->boundingRect().height() - m_opNeedleThrottle->boundingRect().height()/2);
	m_opNeedleThrottle->setTransform(oTransformThrottleNeedle);
	m_opNeedleThrottle->setTransformOriginPoint(m_opNeedleThrottle->boundingRect().width()/2,m_opNeedleThrottle->boundingRect().height()/2);

	//updateThrottle(100);

	openFile(false,":/images/Fuel.svg",&m_opFuel);
	openFile(false,":/images/Needle.svg",&m_opNeedleFuel);

	m_opFuel->setPos(0, m_opFuel->boundingRect().height()/2);
	QTransform oTransformFuelNeedle;
	oTransformFuelNeedle.translate(m_opFuel->boundingRect().width()/2 - m_opNeedleFuel->boundingRect().width()/2,
								   m_opFuel->boundingRect().height()  - m_opNeedleFuel->boundingRect().height()/2);
	m_opNeedleFuel->setTransform(oTransformFuelNeedle);
	m_opNeedleFuel->setTransformOriginPoint(m_opNeedleFuel->boundingRect().width()/2, m_opNeedleFuel->boundingRect().height()/2 );

	//updateFuel(100);


	m_opLedLaneChange = new QLedIndicator(1);
	scene()->addItem(m_opLedLaneChange);

	m_opLedLaneChange->setTransformOriginPoint(m_opLedLaneChange->boundingRect().width()/2, m_opLedLaneChange->boundingRect().height()/2 );
	m_opLedLaneChange->setPos(m_opThrottle->boundingRect().width()*1.75, m_opLedLaneChange->boundingRect().height()/2 );


	m_opLedInBox = new QLedIndicator(1);
	scene()->addItem(m_opLedInBox);

	m_opLedInBox->setTransformOriginPoint(m_opLedInBox->boundingRect().width()/2, m_opLedInBox->boundingRect().height()/2 );
	m_opLedInBox->setPos(m_opThrottle->boundingRect().width()*1.75, m_opLedInBox->boundingRect().height()*1.6 );

	m_opLedOutOfFuel = new QLedIndicator(0.5);
	scene()->addItem(m_opLedOutOfFuel);

	m_opLedOutOfFuel->setTransformOriginPoint(m_opLedOutOfFuel->boundingRect().width()/2, m_opLedOutOfFuel->boundingRect().height()/2 );
	m_opLedOutOfFuel->setPos( m_opFuel->boundingRect().width() * 0.37 , m_opFuel->boundingRect().height() * 1.27 );


	scene()->setSceneRect(0,0,m_opThrottle->boundingRect().width()*2, m_opThrottle->boundingRect().height()*1.5);
	updateOutline();
}

void cDriverDisplay::timeout()
{

	//updateThrottle(m_nThrottleValue);
	//updateFuel(m_nThrottleValue);

	updateThrottle(m_oDriverMessage.m_oController.m_Speed / 15 * 100);
	//updateThrottle(m_oDriverDisplayMessage / 15);

	update();

}

void cDriverDisplay::UpdateDriverDisplay(sDriverMessage i_oDriverDisplayMessage)
{
	m_oDriverMessage = i_oDriverDisplayMessage;
}

void cDriverDisplay::updateThrottle(const tFloat32& i_nValue)
{	
	m_opNeedleThrottle->setRotation( i_nValue / 100 * 240);
}

void cDriverDisplay::updateFuel(const tFloat32& i_nValue)
{	
	m_opNeedleFuel->setRotation( i_nValue / 100 * 240);
}

void cDriverDisplay::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	fitInView(QRectF(0,0,scene()->width(),scene()->height()), Qt::KeepAspectRatio );
}

void cDriverDisplay::wheelEvent(QWheelEvent *event)
{
	qreal factor = qPow(1.2, event->delta() / 240.0);
	scale(factor, factor);
	event->accept();
}