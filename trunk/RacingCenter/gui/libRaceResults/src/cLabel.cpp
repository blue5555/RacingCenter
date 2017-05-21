#include "libRaceResults/cLabel.h"

cLabel::cLabel(QWidget *parent) : QLabel(parent)
{
	m_oTimer.setInterval(1000);
}

cLabel::cLabel(QString i_QSText, 
			   const tUInt i_nColor,
			   const tInt8  i_nDriverID,
			   const tUInt16 i_nValue,
			   QWidget *parent) : QLabel(i_QSText, parent)
{
	m_oTimer.setInterval(1000);
	setColor((Qt::GlobalColor)i_nColor);
	m_n16Value = i_nValue;
	m_n8DriverID = i_nDriverID;
}

cLabel::~cLabel()
{
}

void cLabel::startTimer()
{
	m_oTimer.start();
}

void cLabel::stopTimer()
{
	m_oTimer.stop();
}

void cLabel::setFontSize(tUInt8 i_nSize)
{
	QFont font = this->font();
	font.setPixelSize(i_nSize);
	this->setFont(font);
}

void cLabel::setBackground(Qt::GlobalColor i_oBackgroundColor)
{
	m_oBackgroundColor = i_oBackgroundColor;
	UpdateColors();
}

void cLabel::setColor(Qt::GlobalColor i_oColor)
{
	m_oColor = i_oColor;
	UpdateColors();
}

void cLabel::UpdateColors()
{
	QPalette pal; // = this->palette();

	pal.setColor(QPalette::WindowText, m_oColor);
	pal.setColor(QPalette::Background, m_oBackgroundColor);

	this->setPalette (pal);
	this->setAutoFillBackground(true);
	this->setScaledContents(true);

	this->setAlignment(Qt::AlignCenter);
}