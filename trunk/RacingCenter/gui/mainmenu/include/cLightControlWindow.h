#ifndef cLightControlWindow_H
#define cLightControlWindow_H

#include "libCommon/stdafx.h"
#include "libDatabase/cDatabase.h"
#include "libConfig/cConfig.h"
#include "libLightControl/cLightControl.h"
#include "ui_mainwindow.h"

namespace RacingCenter
{

class cLightControlWindow : public QObject
{
	Q_OBJECT

	const Ui::MainWindow* m_opMainWindow;
	cLightControl*		  m_opLightControl;

public:
	cLightControlWindow(const Ui::MainWindow* i_opMainWindow);
	~cLightControlWindow();

	tBool Init(cLightControl* i_opLightControl);

public slots:
	void SendLight();
	void StartLightWave();
	void StopLightWave();

	void StartLightBox();
	void StopLightBox();

	void StartLightTribuene();
	void StopLightTribuene();

	void ClearLights();

	void StartDimUp();
	void StartDimDown();

};

}

#endif  // cLightControlWindow_H