#include "cLabel.h"

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

void cLabel::setColor(Qt::GlobalColor i_oColor)
{
	/*
	m_r = r;
	m_b = b;
	m_g = g;
	m_alpha = alpha;
	*/
	//this->setStyleSheet( "QLabel { border: 1px solid white; background-color : rgba(0,0,0,0%) }" );
	
	QPalette pal; // = this->palette();
	//if ((value > max)
	{
		pal.setColor(QPalette::WindowText, i_oColor);
		pal.setColor(QPalette::Background, Qt::black);

		//pal.setColor(ui->pLabel->foregroundRole(), Qt::yellow);
	}
	//else{
	//	pal->setColor(QPalette::WindowText, Qt::white);
	//}

	this->setPalette (pal);
	this->setAutoFillBackground(true);
	this->setScaledContents(true);

	this->setAlignment(Qt::AlignCenter);
}

/*
void cLabel::resizeEvent(QResizeEvent* event)
{
	//QLabel::resizeEvent(event);
	
	QFont font = this->font();
	QRect cRect = this->contentsRect();

	qDebug() << text();
	qDebug() << "Width: " << cRect.width() << " Heigth: " << cRect.height();

	if( this->text().isEmpty() )
		return;

	int fontSize = 1;

	while( true )
	{
		QFont f(font);
		f.setPixelSize( fontSize );
		QRect r = QFontMetrics(f).boundingRect( this->text() );
		if (r.height() <= cRect.height() && r.width() <= cRect.width() )
			fontSize++;
		else
			break;
	}

	qDebug() << "FontSize: " << fontSize;

	//font.setPixelSize(fontSize);
	//this->setFont(font);
	
}
*/

/*
void cLabel::resizeEvent(QResizeEvent* event)
{
	bool fit = false;

	QString currentText = text();
	this->setText("");

	QFont myFont = this->font();	
	myFont.setPointSize(50);

	while (!fit)
	{
		QFontMetrics fm( myFont );		
		QRect bound = fm.boundingRect(0,0, this->width(), this->height(), Qt::TextWordWrap | Qt::AlignLeft, currentText);
			 // text size	// label size
		if ( bound.width() + 10 <= this->width() &&
			bound.height() + 10 <= this->height() )
		{
			fit = true;
		} else {
			myFont.setPointSize(myFont.pointSize() - 1);
			if(myFont.pointSize() <= 5) {
				fit = true;
			}
		}
	}

	this->setFont(myFont);
	this->setText(currentText);
}
*/

