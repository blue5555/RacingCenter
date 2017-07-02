#ifndef cDatabaseWindow_H
#define cDatabaseWindow_H

#include "libCommon/stdafx.h"
#include "libDatabase/cDatabase.h"
#include "libConfig/cConfig.h"
#include "ui_mainwindow.h"
#include "cRaceWindow.h"

namespace RacingCenter
{

class cDatabaseWindow : public QObject
{
    Q_OBJECT

    const Ui::MainWindow* m_opMainWindow;
    cDatabase*            m_opDatabase;
    cConfig*              m_opConfig;
    cRacingWindow&        m_oRacingWindow;

    tBool InitDatabaseTree();

    void LoadDriverInformation(const cDatabaseDriver& i_oDriver);
    void SaveDriverInformation(cDatabaseDriver& o_oDriver);

    void LoadCarInformation(const cDatabaseCar& i_oCar);
    void SaveCarInformation(cDatabaseCar& i_oCar);

public:
    cDatabaseWindow(const Ui::MainWindow* i_opMainWindow, cRacingWindow& i_oRacingWindow);
    ~cDatabaseWindow();

    tBool Init();

public slots:
    void DatabaseItemDoubleClicked(QTreeWidgetItem* opTreeWidgetItem, int column);
    void AddDatabaseItem();
    void DeleteDatabaseItem();
    void SaveDatabaseItem();

};

}

#endif  // cDatabaseWindow_H