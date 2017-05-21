#include "libRaceDisplay/cProgressBar.h"

using namespace RacingCenter;

#define PROGRESSBAR_SIZE 0.5
#define DELTA_PROGRESSBAR_SIZE (1-PROGRESSBAR_SIZE)
#define VALUE_COLOR_YELLOW 0.4
#define VALUE_COLOR_RED 0.15

cProgressBar::cProgressBar(QString i_QSText, const tUInt i_nColor) : QWidget()
,myText(i_QSText)
,m_nFontColor(i_nColor)
,m_iFontSize(20)
,m_nColor(Qt::green)
,m_bToggle(false)
,m_bStateBlinking(false)
{
	//myTextOption.setAlignment(Qt::AlignCenter);
	//myTextOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

	//setPlainText(i_QSText);

	//m_nColor = i_nColor;

	m_oTimer.setInterval(1000);
	connect(&m_oTimer, SIGNAL(timeout()), SLOT(updateLabel()), Qt::DirectConnection);

}

cProgressBar::~cProgressBar() 
{
}

void cProgressBar::blinking(tBool i_bState)
{
	if(i_bState && !m_bStateBlinking) 
	{
		m_oTimer.start();
		m_bStateBlinking = true;
	} 
	else if (!i_bState && m_bStateBlinking)
	{
		m_bStateBlinking = false;
		m_oTimer.stop();
		m_bToggle = false;
	}
}

void cProgressBar::setFontSize(int i_iFontSize)
{
	m_iFontSize = i_iFontSize;
}

void cProgressBar::setText(QString i_QSText)
{
	myText = i_QSText;
	//setPlainText(myText);
}

QString cProgressBar::getText()
{
	return myText;
}

void cProgressBar::setValue(tFloat32 val, tFloat32 maxValue)
{
	m_f32Value = val / maxValue;
	myText = QString("%1").arg(val, 0,'f', 2, '0');

	if(m_f32Value >= 0.4) {
		m_nColor = Qt::green;
	} else if(m_f32Value < VALUE_COLOR_YELLOW && m_f32Value > VALUE_COLOR_RED) {
		m_nColor = Qt::yellow;
	} else {
		m_nColor = Qt::red;
	}
}

void cProgressBar::updateLabel()
{
	if(m_bToggle) {
		//setPlainText(myText);
	} else {
		//setPlainText("");
	}
	
	m_bToggle = !m_bToggle;
	this->update();
}

//QRectF cProgressBar::boundingRect() const 
//{
//	return QRectF(0,0,m_f32Width,m_f32Heigth);
//}

//QPainterPath cProgressBar::shape() const {
//	QPainterPath path;
//	path.addRect(boundingRect());
//	return path;
//}

void cProgressBar::paintEvent(QPaintEvent*) 
{
	QPainter painter(this);
	painter.fillRect(QRectF(0,0,this->width(),this->height()) ,Qt::black);
	
	QBrush oBrush((Qt::GlobalColor) Qt::gray );
	painter.setBrush(oBrush);
	painter.drawRect(0,0,PROGRESSBAR_SIZE * this->width(),this->height());

	if(!m_bToggle) 
	{
		QBrush oBrush((Qt::GlobalColor)m_nColor);
		painter.setBrush(oBrush);
		painter.drawRect(0,0,PROGRESSBAR_SIZE * m_f32Value * this->width(),this->height());
	}
	else
	{
		int a = 4;
	}
	
	painter.setPen(/*Qt::white*/ (Qt::GlobalColor)m_nFontColor );
	QFont oFont;
	oFont.setPixelSize(m_iFontSize);
	painter.setFont(oFont);
	
	QTextOption myTextOption;
	myTextOption.setAlignment(Qt::AlignCenter);
	myTextOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

	painter.drawText(QRectF(PROGRESSBAR_SIZE * this->width(),
							0, 
							DELTA_PROGRESSBAR_SIZE * this->width(), 
							this->height()), 
							myText,
							myTextOption);

	//QWidget::paint(painter,option,widget);
}

//QSizeF cProgressBar::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
//{
//	return QSizeF(m_f32Width,m_f32Heigth);
//}