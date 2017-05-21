#include "cBoundBox.h"

cBoundBox::	cBoundBox(QString i_QSText, 
	const tFloat32& i_f32Width, 
	const tFloat32& i_f32Height, 
	const tUInt i_nColor,
	const tInt8   i_nDriverID,
	const tUInt16 i_nValue) :
 myText(i_QSText)
,m_f32Value(1.0)
,m_bToggle(true)
,m_bBlink(false)
,m_bFastBlink(false)
{
	myTextOption.setAlignment(Qt::AlignCenter);
	myTextOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

	m_nColor = i_nColor;

	m_oTimer.setInterval(1000);
	connect(&m_oTimer, SIGNAL(timeout()), SLOT(updateLabel()), Qt::DirectConnection);

}

cBoundBox::~cBoundBox() {

}

void cBoundBox::fastBlinking(tBool i_bState)
{
	if(i_bState) 
	{
		m_bBlink = false;
		if(i_bState != m_bFastBlink) 
		{
			m_oTimer.setInterval(500);
			m_oTimer.start();
		}
	}
	m_bFastBlink = i_bState;

	if(!m_bBlink && !m_bFastBlink) 
	{
		m_oTimer.stop();
		m_bToggle = true;
	}
}

void cBoundBox::blinking(tBool i_bState)
{
	if(i_bState) 
	{
		m_bFastBlink = false;
		if(i_bState != m_bBlink) {
			m_oTimer.setInterval(1000);
			m_oTimer.start();
		}
	}
	m_bBlink = i_bState;
	
	if(!m_bBlink && !m_bFastBlink) 
	{
		m_oTimer.stop();
		m_bToggle = true;
	}
}

void cBoundBox::setText(QString i_QSText)
{
	myText = i_QSText;
}

QString cBoundBox::getText()
{
	return myText;
}

tFloat32 cBoundBox::getValue() const 
{ 
	return m_f32Value; 
}

void cBoundBox::setValue(tFloat32 val) 
{
	m_f32Value = val;
	if(m_f32Value >= 0.4) {
		m_nColor = Qt::green;
	} else if(m_f32Value < 0.4 && m_f32Value > 0.15) {
		m_nColor = Qt::yellow;
	} else {
		m_nColor = Qt::red;
	}
}

void cBoundBox::updateLabel()
{
	if(m_bToggle) {
		//setPlainText(myText);
	} else {
		//setPlainText("");
	}
	
	m_bToggle =! m_bToggle;
	
	update();
}

QRectF cBoundBox::boundingRect() const {
	return QRectF(0,0,m_f32Width,m_f32Heigth);
}

QPainterPath cBoundBox::shape() const {
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

void cBoundBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->fillRect(boundingRect(),Qt::black);
	painter->setPen(/*Qt::white*/ (Qt::GlobalColor)m_nColor );
	painter->setFont(QFont("Open Sans", 30));
	//painter->drawText(boundingRect(),myText,myTextOption);
	
	if(m_nValue != 0x00000100) {
		//painter->drawText(boundingRect(),toPlainText(),myTextOption);
	} else {
		if(m_bToggle) {
			QBrush oBrush((Qt::GlobalColor)m_nColor);
			painter->setBrush(oBrush);
			painter->drawRect(0,0,m_f32Value * m_f32Width,m_f32Heigth);
		}
	}
		//QGraphicsTextItem::paint(painter,option,widget);
	//update();
}

QSizeF cBoundBox::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
	return QSizeF(m_f32Width,m_f32Heigth);
}