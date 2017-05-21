#ifndef cFuelWindow_H
#define cFuelWindow_H

#include "libCommon/stdafx.h"
#include "libDatabase/cDatabase.h"
#include "libConfig/cConfig.h"
#include "ui_mainwindow.h"

namespace RacingCenter
{

class cFuelWindow : public QObject
{
    Q_OBJECT

    const Ui::MainWindow* m_opMainWindow;
    cDatabase*            m_opDatabase;
    cConfig*              m_opConfig;

public:
    cFuelWindow(const Ui::MainWindow* i_opMainWindow);
    ~cFuelWindow();

    tBool Init();
	tBool ReadFuelConfig();
	tBool SetFuelConfig(const sFuelConfig& i_oFuelConfig);


public slots:
    void UpdateRaceConfig();

};

}

#endif  // cFuelWindow_H