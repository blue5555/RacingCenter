#ifndef cLabel_H
#define cLabel_H

#include <libCommon/stdafx.h>
#include <QLabel>

class cLabel : public QLabel
{
    Q_OBJECT

	QTimer m_oTimer;
	
	tUInt8 m_r;
	tUInt8 m_g;
	tUInt8 m_b;
	tUInt8 m_alpha;
	tUInt16 m_n16Value;
	tUInt8 m_n8DriverID;

	Qt::GlobalColor m_oColor;
	Qt::GlobalColor m_oBackgroundColor;

	void UpdateColors();

public:
    cLabel(QWidget *parent = 0);
	cLabel(QString i_QSText, 
		   const tUInt i_nColor,
		   const tInt8  i_nDriverID,
		   const tUInt16 i_nValue,
		   QWidget *parent = 0);
	~cLabel();

	void startTimer();
	void stopTimer();

	void setBackground(Qt::GlobalColor i_oBackgroundColor);
	void setColor(Qt::GlobalColor i_oColor);

	tUInt16 Value() const { return m_n16Value; }
	void	setValue(tUInt16 val) { m_n16Value = val; }

	void setFontSize(tUInt8 i_nSize);

public slots:


protected:
	//void resizeEvent(QResizeEvent* event);

private:

};

#endif // cLabel_H