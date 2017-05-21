#include "cRaceWindow.h"

using namespace RacingCenter;

cRacingWindow::cRacingWindow(const Ui::MainWindow* i_opMainWindow) :
 m_opMainWindow(i_opMainWindow)
,m_opDatabase(cDatabase::instance())
,m_opConfig(cConfig::instance())
{
}

cRacingWindow::~cRacingWindow()
{

}

tBool cRacingWindow::Init()
{
	UpdateComboBoxes();

	SetRaceConfig(m_opConfig->m_oRaceConfig);
	SetFuelConfig(m_opConfig->m_oFuelConfig);

    SetDriverConfig(m_opConfig->m_oRaceConfig.oDrivers[0], m_opMainWindow->checkBox_Driver_1, m_opMainWindow->comboBox_Name_Driver_1, m_opMainWindow->comboBox_Name_Car_1, m_opMainWindow->comboBox_Display_Driver1);
    SetDriverConfig(m_opConfig->m_oRaceConfig.oDrivers[1], m_opMainWindow->checkBox_Driver_2, m_opMainWindow->comboBox_Name_Driver_2, m_opMainWindow->comboBox_Name_Car_2, m_opMainWindow->comboBox_Display_Driver2);
    SetDriverConfig(m_opConfig->m_oRaceConfig.oDrivers[2], m_opMainWindow->checkBox_Driver_3, m_opMainWindow->comboBox_Name_Driver_3, m_opMainWindow->comboBox_Name_Car_3, m_opMainWindow->comboBox_Display_Driver3);
    SetDriverConfig(m_opConfig->m_oRaceConfig.oDrivers[3], m_opMainWindow->checkBox_Driver_4, m_opMainWindow->comboBox_Name_Driver_4, m_opMainWindow->comboBox_Name_Car_4, m_opMainWindow->comboBox_Display_Driver4);
    SetDriverConfig(m_opConfig->m_oRaceConfig.oDrivers[4], m_opMainWindow->checkBox_Driver_5, m_opMainWindow->comboBox_Name_Driver_5, m_opMainWindow->comboBox_Name_Car_5, m_opMainWindow->comboBox_Display_Driver5);
    SetDriverConfig(m_opConfig->m_oRaceConfig.oDrivers[5], m_opMainWindow->checkBox_Driver_6, m_opMainWindow->comboBox_Name_Driver_6, m_opMainWindow->comboBox_Name_Car_6, m_opMainWindow->comboBox_Display_Driver6);

    connect(m_opMainWindow->radioButton_Training, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->radioButton_Qualifying, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->radioButton_Race, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->radioButton_Championship, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));

    connect(m_opMainWindow->radioButton_Rounds, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->spinBox_Rounds, SIGNAL(valueChanged(int)), this, SLOT( UpdateRaceConfig() ));

    connect(m_opMainWindow->radioButton_Time, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->spinBox_Time, SIGNAL(valueChanged(int)), this, SLOT( UpdateRaceConfig() ));

    connect(m_opMainWindow->checkBox_DriveFinish, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));

    connect(m_opMainWindow->checkBox_Driver_1, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->checkBox_Driver_2, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->checkBox_Driver_3, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->checkBox_Driver_4, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->checkBox_Driver_5, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->checkBox_Driver_6, SIGNAL(toggled(bool)), this, SLOT( UpdateRaceConfig() ));

    connect(m_opMainWindow->comboBox_Name_Driver_1, SIGNAL(currentIndexChanged(int)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->comboBox_Name_Driver_2, SIGNAL(currentIndexChanged(int)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->comboBox_Name_Driver_3, SIGNAL(currentIndexChanged(int)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->comboBox_Name_Driver_4, SIGNAL(currentIndexChanged(int)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->comboBox_Name_Driver_5, SIGNAL(currentIndexChanged(int)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->comboBox_Name_Driver_6, SIGNAL(currentIndexChanged(int)), this, SLOT( UpdateRaceConfig() ));

    connect(m_opMainWindow->comboBox_Name_Car_1, SIGNAL(currentIndexChanged(int)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->comboBox_Name_Car_2, SIGNAL(currentIndexChanged(int)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->comboBox_Name_Car_3, SIGNAL(currentIndexChanged(int)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->comboBox_Name_Car_4, SIGNAL(currentIndexChanged(int)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->comboBox_Name_Car_5, SIGNAL(currentIndexChanged(int)), this, SLOT( UpdateRaceConfig() ));
    connect(m_opMainWindow->comboBox_Name_Car_6, SIGNAL(currentIndexChanged(int)), this, SLOT( UpdateRaceConfig() ));

    return true;
}

tBool cRacingWindow::UpdateComboBoxes()
{
    FillComboBox(m_opMainWindow->comboBox_Name_Driver_1, m_opDatabase->GetAllDriverNames());
    FillComboBox(m_opMainWindow->comboBox_Name_Driver_2, m_opDatabase->GetAllDriverNames());
    FillComboBox(m_opMainWindow->comboBox_Name_Driver_3, m_opDatabase->GetAllDriverNames());
    FillComboBox(m_opMainWindow->comboBox_Name_Driver_4, m_opDatabase->GetAllDriverNames());
    FillComboBox(m_opMainWindow->comboBox_Name_Driver_5, m_opDatabase->GetAllDriverNames());
    FillComboBox(m_opMainWindow->comboBox_Name_Driver_6, m_opDatabase->GetAllDriverNames());

    FillComboBox(m_opMainWindow->comboBox_Name_Car_1, m_opDatabase->GetAllCarNames());
    FillComboBox(m_opMainWindow->comboBox_Name_Car_2, m_opDatabase->GetAllCarNames());
    FillComboBox(m_opMainWindow->comboBox_Name_Car_3, m_opDatabase->GetAllCarNames());
    FillComboBox(m_opMainWindow->comboBox_Name_Car_4, m_opDatabase->GetAllCarNames());
    FillComboBox(m_opMainWindow->comboBox_Name_Car_5, m_opDatabase->GetAllCarNames());
    FillComboBox(m_opMainWindow->comboBox_Name_Car_6, m_opDatabase->GetAllCarNames());

    return true;
}

void cRacingWindow::UpdateRaceConfig()
{
    ReadRaceConfig();
    m_opConfig->SaveConfig();
}

tBool cRacingWindow::SetFuelConfig(const sFuelConfig& i_oFuelConfig)
{
	m_opMainWindow->checkBox_Programm_CarSpeed_Fuel->setChecked(i_oFuelConfig.bProgrammCarsByFuel);
	m_opMainWindow->checkBox_CountRoundsByEmptyFuel->setChecked(i_oFuelConfig.bCountRoundsByEmptyFuel);

	if(i_oFuelConfig.bSimulation)
	{
		m_opMainWindow->radioButton_FuelMode_Simulation->setChecked(true);
	}
	else
	{
		m_opMainWindow->radioButton_FuelMode_CU->setChecked(true);
	}

	return true;
}

tBool cRacingWindow::SetRaceConfig(const sRaceConfig& i_oRaceConfig)
{
    switch(i_oRaceConfig.nRaceFinish)
    {
    case FINISH_ROUNDS:
        m_opMainWindow->radioButton_Rounds->setChecked(true);
        break;
    case FINISH_TIME:
        m_opMainWindow->radioButton_Time->setChecked(true);
        break;
    }

    m_opMainWindow->spinBox_Rounds->setValue(i_oRaceConfig.nRounds);
    m_opMainWindow->spinBox_Time->setValue(i_oRaceConfig.nTime);

    switch(i_oRaceConfig.nRaceMode)
    {
    case MODE_TRAINING:
        m_opMainWindow->radioButton_Training->setChecked(true);
        break;
    case MODE_RACE:
        m_opMainWindow->radioButton_Race->setChecked(true);
        break;
    case MODE_QUALITFYING:
        m_opMainWindow->radioButton_Qualifying->setChecked(true);
        break;
    case MODE_CHAMPIONSHIP:
        m_opMainWindow->radioButton_Championship->setChecked(true);
        break;
    }

	m_opMainWindow->spinBox_Timing->setValue(i_oRaceConfig.nTimingInterval);
    m_opMainWindow->checkBox_DriveFinish->setChecked(i_oRaceConfig.bDriveFinish);
    m_opMainWindow->checkBox_Count_GhostCar->setChecked(i_oRaceConfig.bCountGhost);
        
    return true;
}

tBool cRacingWindow::FillComboBox(QComboBox* i_opComboBox, const std::list<std::string>& i_oNames)
{
	QString strCurrentText = i_opComboBox->currentText();

    i_opComboBox->clear();
    for (std::list<std::string>::const_iterator it = i_oNames.begin(); it != i_oNames.end(); it++ )
    {
        i_opComboBox->addItem(it->c_str());
    }

	if(i_opComboBox->findText(strCurrentText) >= 0)
	{
		i_opComboBox->setCurrentText(strCurrentText);
	}

    return true;
}

tBool cRacingWindow::SetDriverConfig(const sDriverConfig& i_oDriverConfig, QCheckBox* i_opCheckBox, QComboBox* i_opComboBoxDriver, QComboBox* i_opComboBoxCar, QComboBox* i_opComboBoxDisplay)
{
    i_opCheckBox->setChecked(i_oDriverConfig.bEnabled);

    if(i_opComboBoxDriver->findText(i_oDriverConfig.strName.c_str()) >= 0)
    {
		int nIndex = i_opComboBoxDriver->findText(i_oDriverConfig.strName.c_str());
        i_opComboBoxDriver->setCurrentText(i_oDriverConfig.strName.c_str());
    }

    if(i_opComboBoxCar->findText(i_oDriverConfig.strCarName.c_str()) >= 0)
    {
        i_opComboBoxCar->setCurrentText(i_oDriverConfig.strCarName.c_str());
    }

    return true;
}

tBool cRacingWindow::ReadRaceConfig()
{
    // MainMenu
    if(m_opMainWindow->radioButton_Training->isChecked()) {
        m_opConfig->m_oRaceConfig.nRaceMode = MODE_TRAINING;
    } else 	if(m_opMainWindow->radioButton_Race->isChecked()) {
        m_opConfig->m_oRaceConfig.nRaceMode = MODE_RACE;
    } else 	if(m_opMainWindow->radioButton_Championship->isChecked()) {
        m_opConfig->m_oRaceConfig.nRaceMode = MODE_CHAMPIONSHIP;
    } else 	if(m_opMainWindow->radioButton_Qualifying->isChecked()) {
        m_opConfig->m_oRaceConfig.nRaceMode = MODE_QUALITFYING;
    }

    if(m_opMainWindow->radioButton_Rounds->isChecked()) {
        m_opConfig->m_oRaceConfig.nRaceFinish = FINISH_ROUNDS;
    } else if(m_opMainWindow->radioButton_Time->isChecked()) {
        m_opConfig->m_oRaceConfig.nRaceFinish = FINISH_TIME;
    }

    m_opConfig->m_oRaceConfig.nRounds = m_opMainWindow->spinBox_Rounds->value();
    m_opConfig->m_oRaceConfig.nTime = m_opMainWindow->spinBox_Time->value();

    m_opConfig->m_oRaceConfig.nTimingInterval = m_opMainWindow->spinBox_Timing->value();

    m_opConfig->m_oRaceConfig.bDriveFinish = m_opMainWindow->checkBox_DriveFinish->isChecked();
    
    ReadDriverConfig(m_opConfig->m_oRaceConfig.oDrivers[0], m_opMainWindow->checkBox_Driver_1, m_opMainWindow->comboBox_Name_Driver_1, m_opMainWindow->comboBox_Name_Car_1, m_opMainWindow->comboBox_Display_Driver1);
    ReadDriverConfig(m_opConfig->m_oRaceConfig.oDrivers[1], m_opMainWindow->checkBox_Driver_2, m_opMainWindow->comboBox_Name_Driver_2, m_opMainWindow->comboBox_Name_Car_2, m_opMainWindow->comboBox_Display_Driver2);
    ReadDriverConfig(m_opConfig->m_oRaceConfig.oDrivers[2], m_opMainWindow->checkBox_Driver_3, m_opMainWindow->comboBox_Name_Driver_3, m_opMainWindow->comboBox_Name_Car_3, m_opMainWindow->comboBox_Display_Driver3);
    ReadDriverConfig(m_opConfig->m_oRaceConfig.oDrivers[3], m_opMainWindow->checkBox_Driver_4, m_opMainWindow->comboBox_Name_Driver_4, m_opMainWindow->comboBox_Name_Car_4, m_opMainWindow->comboBox_Display_Driver4);
    ReadDriverConfig(m_opConfig->m_oRaceConfig.oDrivers[4], m_opMainWindow->checkBox_Driver_5, m_opMainWindow->comboBox_Name_Driver_5, m_opMainWindow->comboBox_Name_Car_5, m_opMainWindow->comboBox_Display_Driver5);
    ReadDriverConfig(m_opConfig->m_oRaceConfig.oDrivers[5], m_opMainWindow->checkBox_Driver_6, m_opMainWindow->comboBox_Name_Driver_6, m_opMainWindow->comboBox_Name_Car_6, m_opMainWindow->comboBox_Display_Driver6);

    m_opConfig->m_oRaceConfig.bCountGhost = m_opMainWindow->checkBox_Count_GhostCar->isChecked();

    return true;
}

tBool cRacingWindow::ReadDriverConfig(sDriverConfig& io_oDriverConfig, QCheckBox* i_opCheckBox, QComboBox* i_opDriverName, QComboBox* i_opCarName, QComboBox* i_opComboBoxDisplay)
{
    io_oDriverConfig.bEnabled   = i_opCheckBox->isChecked();
    io_oDriverConfig.strName    = i_opDriverName->currentText().toStdString();
    io_oDriverConfig.strCarName = i_opCarName->currentText().toStdString();

	return true;
}

tBool cRacingWindow::ReadFuelConfig(sFuelConfig& i_oFuelConfig)
{
	i_oFuelConfig.bProgrammCarsByFuel		= m_opMainWindow->checkBox_Programm_CarSpeed_Fuel->isChecked();
	i_oFuelConfig.bCountRoundsByEmptyFuel	= m_opMainWindow->checkBox_CountRoundsByEmptyFuel->isChecked();

	if(m_opMainWindow->radioButton_FuelMode_Simulation->isChecked())
	{
		i_oFuelConfig.bSimulation = true;
	}
	else
	{
		i_oFuelConfig.bSimulation = false;
	}

	return true;
}