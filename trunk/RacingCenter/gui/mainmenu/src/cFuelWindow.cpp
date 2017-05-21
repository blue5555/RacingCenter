#include "cFuelWindow.h"

using namespace RacingCenter;

cFuelWindow::cFuelWindow(const Ui::MainWindow* i_opMainWindow) :
m_opMainWindow(i_opMainWindow)
    ,m_opDatabase(cDatabase::instance())
    ,m_opConfig(cConfig::instance())
{
}

cFuelWindow::~cFuelWindow()
{

}

tBool cFuelWindow::Init()
{
	SetFuelConfig(m_opConfig->m_oFuelConfig);

    connect(m_opMainWindow->radioButton_FuelMode_Simulation, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->radioButton_FuelMode_CU, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));

    connect(m_opMainWindow->checkBox_Programm_CarSpeed_Fuel, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->checkBox_DisqualifyByEmptyTank, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
	connect(m_opMainWindow->checkBox_CountRoundsByEmptyFuel, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));

	connect(m_opMainWindow->checkBox_Programm_FlashCarLight, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));

    return true;
}

void cFuelWindow::UpdateRaceConfig()
{
    ReadFuelConfig();
    m_opConfig->SaveConfig();
}

tBool cFuelWindow::ReadFuelConfig()
{
    if(m_opMainWindow->radioButton_FuelMode_Simulation->isChecked())
    {
        m_opConfig->m_oFuelConfig.bSimulation = true;
    }
    else
    {
        m_opConfig->m_oFuelConfig.bSimulation = false;
    }

    m_opConfig->m_oFuelConfig.bProgrammCarsByFuel = m_opMainWindow->checkBox_Programm_CarSpeed_Fuel->isChecked();
    m_opConfig->m_oFuelConfig.bCountRoundsByEmptyFuel = m_opMainWindow->checkBox_CountRoundsByEmptyFuel->isChecked();

	m_opConfig->m_oFuelConfig.bFlashCarLight = m_opMainWindow->checkBox_Programm_FlashCarLight->isChecked();

    return true;
}

tBool cFuelWindow::SetFuelConfig(const sFuelConfig& i_oFuelConfig)
{
    m_opMainWindow->radioButton_FuelMode_Simulation->setChecked(i_oFuelConfig.bSimulation);
    m_opMainWindow->checkBox_Programm_CarSpeed_Fuel->setChecked(m_opConfig->m_oFuelConfig.bProgrammCarsByFuel);
    m_opMainWindow->checkBox_CountRoundsByEmptyFuel->setChecked(m_opConfig->m_oFuelConfig.bCountRoundsByEmptyFuel);
	m_opMainWindow->checkBox_Programm_FlashCarLight->setChecked(m_opConfig->m_oFuelConfig.bFlashCarLight);

    return true;
}