#ifndef cBoundBox_H
#define cBoundBox_H

#include <libCommon/stdafx.h>
#include <QGraphicsWidget>
#include <QPainter>
#include <QLabel>

class cBoundBox : public QGraphicsTextItem //, public QGraphicsLayoutItem
{
    Q_OBJECT
	
	QTimer m_oTimer;
	tBool  m_bState;

	tBool  m_bBlink;
	tBool  m_bFastBlink;

	QLabel m_oLabel;

	tUInt  m_nColor;

	tInt8   m_nDriverID;
	tUInt16 m_nValue;

	tFloat32 m_f32Value;

	tFloat32 m_f32Heigth;
	tFloat32 m_f32Width;

	tBool  m_bToggle;
	
	tUInt8 m_r;
	tUInt8 m_g;
	tUInt8 m_b;
	tUInt8 m_alpha;

public:
	cBoundBox(QString i_QSText, 
			  const tFloat32& i_f32Width, 
			  const tFloat32& i_f32Height, 
			  const tUInt i_nColor,
			  const tInt8   i_nDriverID,
			  const tUInt16 i_nValue);
	~cBoundBox();

	void    setText(QString i_QSText);
	QString getText();

	void	blinking(tBool i_bState);
	void	fastBlinking(tBool i_bState);

	tFloat32 getValue() const;
	void	 setValue(tFloat32 val);

	tInt8   DriverID() const { return m_nDriverID; }
	//void    DriverID(tInt8 val) { m_nDriverID = val; }

	tUInt16 Value() const { return m_nValue; }
	//void    Value(tUInt16 val) { m_nValue = val; }

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	QPainterPath shape() const;

	virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

private:
		QString myText;
		QTextOption myTextOption;

public slots:
		void updateLabel();

};

#endif // cBoundBox_H