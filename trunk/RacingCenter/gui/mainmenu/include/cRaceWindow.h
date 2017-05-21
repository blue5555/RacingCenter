#ifndef cRaceWindow_H
#define cRaceWindow_H

#include "libCommon/stdafx.h"
#include "libDatabase/cDatabase.h"
#include "libConfig/cConfig.h"
#include "ui_mainwindow.h"

namespace RacingCenter
{

class cRacingWindow : public QObject
{
    Q_OBJECT

    const Ui::MainWindow* m_opMainWindow;
    cDatabase*            m_opDatabase;
    cConfig*              m_opConfig;

    tBool FillComboBox(QComboBox* i_opComboBox, const std::list<std::string>& i_oNames);

	tBool SetFuelConfig(const sFuelConfig& i_oFuelConfig);
	tBool ReadFuelConfig(sFuelConfig& i_oFuelConfig);

    tBool SetDriverConfig(const sDriverConfig& i_oDriverConfig, QCheckBox* i_opCheckBox, QComboBox* i_opComboBoxDriver, QComboBox* i_opComboBoxCar, QComboBox* i_opDisplayName);
    tBool SetRaceConfig(const sRaceConfig& i_oRaceConfig);

    tBool ReadDriverConfig(sDriverConfig& io_oDriverConfig, QCheckBox* i_opCheckBox, QComboBox* i_opDriverName, QComboBox* i_opCarName, QComboBox* i_opDisplayName);
    tBool ReadRaceConfig();

public:
    cRacingWindow(const Ui::MainWindow* i_opMainWindow);
    ~cRacingWindow();

    tBool Init();
    tBool UpdateComboBoxes();

public slots:
    void UpdateRaceConfig();

};



}

#endif  // cRaceWindow_H