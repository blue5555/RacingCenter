#ifndef cProgressBar_H
#define cProgressBar_H

#include <libCommon/stdafx.h>
#include <QGraphicsWidget>
#include <QPainter>
#include <QLabel>

namespace RacingCenter
{

class cProgressBar : public QWidget //public QGraphicsTextItem //, public QGraphicsLayoutItem
{
    Q_OBJECT
	
	QTimer m_oTimer;	
	QLabel m_oLabel;

	tUInt  m_nColor;
	tUInt  m_nFontColor;

	tFloat32 m_f32Value;

	tInt8    m_iFontSize;

	tFloat32 m_f32Heigth;
	tFloat32 m_f32Width;

	tBool  m_bStateBlinking;
	tBool  m_bToggle;
	
	tUInt8 m_r;
	tUInt8 m_g;
	tUInt8 m_b;
	tUInt8 m_alpha;

public:
	cProgressBar(QString i_QSText, const tUInt i_nColor);
	~cProgressBar();

	void    setText(QString i_QSText);
	QString getText();

	void	setFontSize(int i_iFontSize);

	void	blinking(tBool i_bState);

	void	setValue(tFloat32 val, tFloat32 maxValue);

protected:
	void paintEvent(QPaintEvent*);
	//void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	//QRectF boundingRect() const;
	//QPainterPath shape() const;

	//virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

private:
		QString myText;
		QTextOption myTextOption;

public slots:
		void updateLabel();

};

}

#endif // cProgressBar_H