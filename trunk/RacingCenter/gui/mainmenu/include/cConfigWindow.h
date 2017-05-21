#ifndef cConfigWindow_H
#define cConfigWindow_H

#include "libCommon/stdafx.h"
#include "libDatabase/cDatabase.h"
#include "libConfig/cConfig.h"
#include "ui_mainwindow.h"

namespace RacingCenter
{

class cConfigWindow : public QObject
{
    Q_OBJECT

    const Ui::MainWindow* m_opMainWindow;
    cDatabase*            m_opDatabase;
    cConfig*              m_opConfig;

public:
    cConfigWindow(const Ui::MainWindow* i_opMainWindow);
    ~cConfigWindow();

    tBool Init();

public slots:
    void SaveConfig();

};

}

#endif  // cConfigWindow_H