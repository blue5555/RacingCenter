#ifndef cStartLight_H
#define cStartLight_H

#include <libCommon/stdafx.h>
#include <QMainWindow>
#include <QPixmap>
#include "qled.h"
#include "cAspectRatioPixmapLabel.h"

QT_BEGIN_NAMESPACE

	namespace Ui {
		class StartLightSimple;
}

QT_END_NAMESPACE

class cStartLight : public QMainWindow
{
    Q_OBJECT

private:
	Ui::StartLightSimple* m_opStartLight;
	QPixmap	m_oPictures[9];

	tUInt m_nCurrentState;
	AspectRatioPixmapLabel* m_opLabel;

	void ClearLEDs();

public:
    cStartLight(QWidget *parent = 0);
    ~cStartLight();

	void UpdateState(unsigned int i_nState);

private slots:
	//void UpdateState(unsigned int i_nState);

};

#endif // cStartLight_H
