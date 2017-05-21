#ifndef cStartLightGui_H
#define cStartLightGui_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <stdafx.h>
//#include <cPixmapItem.h>
#include <cSVGView.h>

QT_BEGIN_NAMESPACE

namespace Ui {
	class StartLightGui;
}

QT_END_NAMESPACE


class StartLightGui : public QMainWindow
{
    Q_OBJECT

private:
	Ui::StartLightGui* m_opStartLightGui;

	tUInt8			m_nState;

public:
    explicit StartLightGui(QWidget *parent = 0);
    ~StartLightGui();

	void setState(const tUInt8& i_nState);

private slots:
	void UpdateState(unsigned int i_nState);

};

#endif // cStartLightGui_H
