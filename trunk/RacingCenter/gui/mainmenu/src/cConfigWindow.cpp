#include "cConfigWindow.h"
#include "libSerialConnector/cSerialConnector.h"

using namespace RacingCenter;

cConfigWindow::cConfigWindow(const Ui::MainWindow* i_opMainWindow) :
 m_opMainWindow(i_opMainWindow)
,m_opDatabase(cDatabase::instance())
,m_opConfig(cConfig::instance())
{
}

cConfigWindow::~cConfigWindow()
{

}

tBool cConfigWindow::Init()
{
    std::list<std::string> oListPorts = cSerialConnector::GetAllSerialports();
	m_opMainWindow->comboBox_COMPort->clear();
    for (std::list<std::string>::iterator it = oListPorts.begin(); it != oListPorts.end(); it++)
    {    
        m_opMainWindow->comboBox_COMPort->addItem(it->c_str());
    }

    if(m_opMainWindow->comboBox_COMPort->findText( m_opConfig->m_oSerialportInfo.PortName() ) >= 0)
    {
        m_opMainWindow->comboBox_COMPort->setCurrentIndex(m_opMainWindow->comboBox_COMPort->findText(m_opConfig->m_oSerialportInfo.PortName()));
    }

    std::list<tUInt> oListBaudRate = cSerialConnector::GetAllBaudRate();
	m_opMainWindow->comboBox_BaudRate->clear();
    for (std::list<tUInt>::iterator it = oListBaudRate.begin(); it != oListBaudRate.end(); it++)
    {    
        m_opMainWindow->comboBox_BaudRate->addItem(QString("%1").arg(*it));
    }

    QString strBaudRate = QString("%1").arg(m_opConfig->m_oSerialportInfo.BaudRate());
    if(m_opMainWindow->comboBox_BaudRate->findText( strBaudRate ) >= 0)
    {
        m_opMainWindow->comboBox_BaudRate->setCurrentIndex(m_opMainWindow->comboBox_BaudRate->findText(strBaudRate));
    }

    m_opMainWindow->spinBox_Timing->setValue( m_opConfig->m_oRaceConfig.nTimingInterval );

	m_opMainWindow->spinBox_Timing->setValue(m_opConfig->m_oRaceConfig.nTimingInterval);

	// RaceDisplay
	m_opMainWindow->spinBox_RaceDisplay_Heigth->setValue(m_opConfig->m_oRaceDisplayConfig.nHeight);
	m_opMainWindow->spinBox_RaceDisplay_Width->setValue(m_opConfig->m_oRaceDisplayConfig.nWidth);

	m_opMainWindow->checkBox_ShowAccidents->setChecked(m_opConfig->m_oRaceDisplayConfig.nRowBitMask & SHOW_ACCIDENTS);
	m_opMainWindow->checkBox_ShowBestTime->setChecked(m_opConfig->m_oRaceDisplayConfig.nRowBitMask & SHOW_BEST_LAP);
	m_opMainWindow->checkBox_ShowCurrentRoundTime->setChecked(m_opConfig->m_oRaceDisplayConfig.nRowBitMask & SHOW_CURRENT_TIME);
	m_opMainWindow->checkBox_ShowFuel->setChecked(m_opConfig->m_oRaceDisplayConfig.nRowBitMask & SHOW_FUEL_LEVEL);
	m_opMainWindow->checkBox_ShowLaps->setChecked(m_opConfig->m_oRaceDisplayConfig.nRowBitMask & SHOW_LAPS);
	m_opMainWindow->checkBox_ShowLastRoundTime->setChecked(m_opConfig->m_oRaceDisplayConfig.nRowBitMask & SHOW_LAST_LAP);
	m_opMainWindow->checkBox_ShowPosition->setChecked(m_opConfig->m_oRaceDisplayConfig.nRowBitMask & SHOW_POSITION);
	m_opMainWindow->checkBox_ShowTime2Leader->setChecked(m_opConfig->m_oRaceDisplayConfig.nRowBitMask & SHOW_TIME2LEADER);

	QStringList oColors;
	oColors
		<< "black"
		<< "white"
		<< "darkGray"
		<< "gray"
		<< "lightGray"
		<< "red"
		<< "green"
		<< "blue"
		<< "cyan"
		<< "magenta"
		<< "yellow"
		<< "darkRed"
		<< "darkGreen"
		<< "darkBlue"
		<< "darkCyan"
		<< "darkMagenta"
		<< "darkYellow";

	m_opMainWindow->comboBox_Color_Driver_1->addItems(oColors);
	m_opMainWindow->comboBox_Color_Driver_1->setCurrentIndex(m_opConfig->m_oRaceDisplayConfig.oColors[0]-2);
	m_opMainWindow->comboBox_Color_Driver_2->addItems(oColors);
	m_opMainWindow->comboBox_Color_Driver_2->setCurrentIndex(m_opConfig->m_oRaceDisplayConfig.oColors[1]-2);
	m_opMainWindow->comboBox_Color_Driver_3->addItems(oColors);
	m_opMainWindow->comboBox_Color_Driver_3->setCurrentIndex(m_opConfig->m_oRaceDisplayConfig.oColors[2]-2);
	m_opMainWindow->comboBox_Color_Driver_4->addItems(oColors);
	m_opMainWindow->comboBox_Color_Driver_4->setCurrentIndex(m_opConfig->m_oRaceDisplayConfig.oColors[3]-2);
	m_opMainWindow->comboBox_Color_Driver_5->addItems(oColors);
	m_opMainWindow->comboBox_Color_Driver_5->setCurrentIndex(m_opConfig->m_oRaceDisplayConfig.oColors[4]-2);
	m_opMainWindow->comboBox_Color_Driver_6->addItems(oColors);
	m_opMainWindow->comboBox_Color_Driver_6->setCurrentIndex(m_opConfig->m_oRaceDisplayConfig.oColors[5]-2);

	QStringList oDisplay;
	oDisplay << "0" << "1";
	m_opMainWindow->comboBox_Display_Driver1->addItems(oDisplay);
	m_opMainWindow->comboBox_Display_Driver1->setCurrentIndex(m_opConfig->m_oRaceConfig.oDrivers[0].nDisplayID);
	m_opMainWindow->comboBox_Display_Driver2->addItems(oDisplay);
	m_opMainWindow->comboBox_Display_Driver2->setCurrentIndex(m_opConfig->m_oRaceConfig.oDrivers[1].nDisplayID);
	m_opMainWindow->comboBox_Display_Driver3->addItems(oDisplay);
	m_opMainWindow->comboBox_Display_Driver3->setCurrentIndex(m_opConfig->m_oRaceConfig.oDrivers[2].nDisplayID);
	m_opMainWindow->comboBox_Display_Driver4->addItems(oDisplay);
	m_opMainWindow->comboBox_Display_Driver4->setCurrentIndex(m_opConfig->m_oRaceConfig.oDrivers[3].nDisplayID);
	m_opMainWindow->comboBox_Display_Driver5->addItems(oDisplay);
	m_opMainWindow->comboBox_Display_Driver5->setCurrentIndex(m_opConfig->m_oRaceConfig.oDrivers[4].nDisplayID);
	m_opMainWindow->comboBox_Display_Driver6->addItems(oDisplay);
	m_opMainWindow->comboBox_Display_Driver6->setCurrentIndex(m_opConfig->m_oRaceConfig.oDrivers[5].nDisplayID);

	m_opMainWindow->comboBox_Source->setCurrentIndex(m_opConfig->m_eDataSource);

	connect( m_opMainWindow->pushButton_SaveConfig, SIGNAL(clicked()), this, SLOT( SaveConfig() ) );

    return true;
}

void cConfigWindow::SaveConfig()
{
	// ComPort
	m_opConfig->m_oSerialportInfo.PortName( m_opMainWindow->comboBox_COMPort->currentText() );
	m_opConfig->m_oSerialportInfo.BaudRate( QString(m_opMainWindow->comboBox_BaudRate->currentText()).toUInt() );

	// RaceDisplay
	m_opConfig->m_oRaceDisplayConfig.nHeight = m_opMainWindow->spinBox_RaceDisplay_Heigth->value();
	m_opConfig->m_oRaceDisplayConfig.nWidth  = m_opMainWindow->spinBox_RaceDisplay_Width->value(); 

	m_opConfig->m_oRaceDisplayConfig.nRowBitMask = 0;
	if(m_opMainWindow->checkBox_ShowAccidents->isChecked())			{ m_opConfig->m_oRaceDisplayConfig.nRowBitMask |= SHOW_ACCIDENTS; }
	if(m_opMainWindow->checkBox_ShowBestTime->isChecked())			{ m_opConfig->m_oRaceDisplayConfig.nRowBitMask |= SHOW_BEST_LAP; }
	if(m_opMainWindow->checkBox_ShowCurrentRoundTime->isChecked())	{ m_opConfig->m_oRaceDisplayConfig.nRowBitMask |= SHOW_CURRENT_TIME; }
	if(m_opMainWindow->checkBox_ShowFuel->isChecked())				{ m_opConfig->m_oRaceDisplayConfig.nRowBitMask |= SHOW_FUEL_LEVEL; }
	if(m_opMainWindow->checkBox_ShowLaps->isChecked())				{ m_opConfig->m_oRaceDisplayConfig.nRowBitMask |= SHOW_LAPS; }
	if(m_opMainWindow->checkBox_ShowLastRoundTime->isChecked())		{ m_opConfig->m_oRaceDisplayConfig.nRowBitMask |= SHOW_LAST_LAP; }
	if(m_opMainWindow->checkBox_ShowPosition->isChecked())			{ m_opConfig->m_oRaceDisplayConfig.nRowBitMask |= SHOW_POSITION; }
	if(m_opMainWindow->checkBox_ShowTime2Leader->isChecked())		{ m_opConfig->m_oRaceDisplayConfig.nRowBitMask |= SHOW_TIME2LEADER; }
	if(m_opMainWindow->checkBox_ShowSpeed->isChecked())				{ m_opConfig->m_oRaceDisplayConfig.nRowBitMask |= SHOW_PROG_SPEED; }

	m_opConfig->m_oRaceDisplayConfig.oColors[0] = m_opMainWindow->comboBox_Color_Driver_1->currentIndex()+2;
	m_opConfig->m_oRaceDisplayConfig.oColors[1] = m_opMainWindow->comboBox_Color_Driver_2->currentIndex()+2;
	m_opConfig->m_oRaceDisplayConfig.oColors[2] = m_opMainWindow->comboBox_Color_Driver_3->currentIndex()+2;
	m_opConfig->m_oRaceDisplayConfig.oColors[3] = m_opMainWindow->comboBox_Color_Driver_4->currentIndex()+2;
	m_opConfig->m_oRaceDisplayConfig.oColors[4] = m_opMainWindow->comboBox_Color_Driver_5->currentIndex()+2;
	m_opConfig->m_oRaceDisplayConfig.oColors[5] = m_opMainWindow->comboBox_Color_Driver_6->currentIndex()+2;

	m_opConfig->m_oRaceConfig.oDrivers[0].nDisplayID = m_opMainWindow->comboBox_Display_Driver1->currentIndex();
	m_opConfig->m_oRaceConfig.oDrivers[1].nDisplayID = m_opMainWindow->comboBox_Display_Driver2->currentIndex();
	m_opConfig->m_oRaceConfig.oDrivers[2].nDisplayID = m_opMainWindow->comboBox_Display_Driver3->currentIndex();
	m_opConfig->m_oRaceConfig.oDrivers[3].nDisplayID = m_opMainWindow->comboBox_Display_Driver4->currentIndex();
	m_opConfig->m_oRaceConfig.oDrivers[4].nDisplayID = m_opMainWindow->comboBox_Display_Driver5->currentIndex();
	m_opConfig->m_oRaceConfig.oDrivers[5].nDisplayID = m_opMainWindow->comboBox_Display_Driver6->currentIndex();

    m_opConfig->m_oSerialportInfo.PortName( m_opMainWindow->comboBox_COMPort->currentText() );
    m_opConfig->m_oSerialportInfo.BaudRate( m_opMainWindow->comboBox_BaudRate->currentText().toUInt() );

    m_opConfig->m_oRaceConfig.nTimingInterval = m_opMainWindow->spinBox_Timing->value();

	m_opConfig->m_eDataSource = static_cast<eDataSource>(m_opMainWindow->comboBox_Source->currentIndex());

    m_opConfig->SaveConfig();
}