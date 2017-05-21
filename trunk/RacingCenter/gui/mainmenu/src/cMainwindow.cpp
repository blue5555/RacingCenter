#include "cMainwindow.h"
#include "ui_mainwindow.h"
#include "cConsole.h"


#include <QMessageBox>
#include <libConfig/cConfig.h>
#include <libDatabase/cDatabase.h>

#include "libQwt/qwt_plot.h"

#define _FILENAME_ "cMainwindow: "

#define CONFIG_PATH	  "config.xml"
#define DATABASE_PATH "database.xml"

//! [0]
MainWindow::MainWindow(QWidget *parent) :
 QMainWindow(parent)
,m_opMainWindow(new Ui::MainWindow)
,m_opConfig(cConfig::instance())
,m_opDatabase(cDatabase::instance())
,m_oRacingWindow(m_opMainWindow)
,m_oFuelWindow(m_opMainWindow)
,m_oDatabaseWindow(m_opMainWindow,m_oRacingWindow)
,m_oConfigWindow(m_opMainWindow)
,m_oLightControlWindow(m_opMainWindow)
,m_bDebug(true)
,m_bTestData(false)
{
	std::string stdApplicationPath = QApplication::applicationDirPath().toStdString();
	DEBUGMSG("ApplicationPath: " << stdApplicationPath.c_str());

	m_opMainWindow->setupUi(this);
	m_opMainWindow->mainToolBar->setIconSize( QSize(32,32) );

	QwtPlot* opQwtPlot = new QwtPlot(m_opMainWindow->widget_Statistics_Qwt);

    m_opConfig->LoadConfig(stdApplicationPath);
    m_opDatabase->LoadDatabase(stdApplicationPath);
    
    m_oDatabaseWindow.Init();
    m_oConfigWindow.Init();
	m_oRacingWindow.Init();
	m_oFuelWindow.Init();
	m_oLightControlWindow.Init(m_oDataProcessor.GetLightControl());

	connect(m_opMainWindow->pushButton_Start, SIGNAL(clicked()),this, SLOT(Start()));
	connect(m_opMainWindow->button_SendLight, SIGNAL(clicked()), this, SLOT(UpdateLight()));
	
	tBool bOk = true;
	if(!m_oDataProcessor.Started()) 
	{
		bOk = m_oDataProcessor.Start(m_opConfig->m_oRaceConfig.nTimingInterval, // 100
									 cSerialportInfo( m_opConfig->m_oSerialportInfo.PortName(),
													  m_opConfig->m_oSerialportInfo.BaudRate(),
													  8,1),
													  m_bTestData);
		if(bOk)
		{
			DEBUGMSG("Init Serialport");
		}
		else
		{
			DEBUGMSG("Can't init Serialport");
		}
	}
}

MainWindow::~MainWindow()
{
	m_oDataProcessor.Stop();
    delete m_opMainWindow;
}

#pragma endregion

void MainWindow::Start()
{
	tBool bOK = true;

	cConfig* opConfig = m_opConfig->instance();

	opConfig->m_oRaceDisplayConfig.oPositions[1] = SHOW_POSITION;
	opConfig->m_oRaceDisplayConfig.oPositions[2] = SHOW_LAPS;
	opConfig->m_oRaceDisplayConfig.oPositions[3] = SHOW_LAST_LAP;
	opConfig->m_oRaceDisplayConfig.oPositions[4] = SHOW_BEST_LAP;
	opConfig->m_oRaceDisplayConfig.oPositions[5] = SHOW_TIME2LEADER;
	opConfig->m_oRaceDisplayConfig.oPositions[6] = SHOW_FUEL_LEVEL;
	opConfig->m_oRaceDisplayConfig.oPositions[7] = SHOW_CURRENT_TIME;
	opConfig->m_oRaceDisplayConfig.oPositions[8] = SHOW_PROG_SPEED;

	memset(&opConfig->m_oDebugMessagesTiming,false,sizeof(sDebugMessages));
	opConfig->m_oDebugMessagesTiming.bDataProcessor   = false;
	opConfig->m_oDebugMessagesTiming.bCUAdapter       = false;
	opConfig->m_oDebugMessagesTiming.bSerialconnector = false;

	m_oConfigWindow.SaveConfig();

	cRace* opRace = m_oDataProcessor.GetRace();

	opRace->RaceMode(static_cast<eRaceMode>(opConfig->m_oRaceConfig.nRaceMode));

	if(bOK) {
		// check race mode
		if(opRace->RaceMode() != MODE_TRAINING) {
			if(opConfig->m_oRaceConfig.nRaceFinish == FINISH_ROUNDS && opConfig->m_oRaceConfig.nRounds > 0) {
				opRace->RaceFinish(FINISH_ROUNDS);
				opRace->Rounds(opConfig->m_oRaceConfig.nRounds);
			} else if(opConfig->m_oRaceConfig.nRaceFinish == FINISH_TIME && opConfig->m_oRaceConfig.nTime > 0) {
				opRace->RaceFinish(FINISH_TIME);
				opRace->Time(opConfig->m_oRaceConfig.nTime);
			} else {
				// error
				QMessageBox::information( 
					this, 
					tr("Racing Center"), 
					tr("No Race Mode selected.") );
				bOK = false;
			}
		}
	}

	if(bOK) {
		// check fuel mode
		if(opConfig->m_oFuelConfig.bSimulation) 
		{
			opRace->FuelMode(FUELMODE_SIM);
		} 
		else
		{
			opRace->FuelMode(FUELMODE_CU);
		} 
	}

	opRace->Reset();
	if(bOK) {
		// collecting drivers
		tUInt nNumberOfDrivers = 0;
		for(tUInt n = 0; n < 6; n++) 
		{
			if(opConfig->m_oRaceConfig.oDrivers[n].bEnabled) 
			{
				nNumberOfDrivers++;
				cDriver oDriver = cDriver(opRace,
					opConfig->m_oRaceConfig.oDrivers[n].strName,
					n,
					opConfig->m_oRaceConfig.oDrivers[n].strCarName);
				oDriver.SetDisplayNumber( opConfig->m_oRaceConfig.oDrivers[n].nDisplayID );
				opRace->AddDriver(oDriver);
			}	
		}
		if (nNumberOfDrivers == 0)
		{
			// error
			QMessageBox::information( 
				this, 
				tr("Racing Center"), 
				tr("No Drivers selected.") );
			bOK = false;
		}
	}

	if(bOK) 
    {
		bOK = m_oDataProcessor.Start(m_opConfig->m_oRaceConfig.nTimingInterval, // 100
				cSerialportInfo( m_opConfig->m_oSerialportInfo.PortName(),
				m_opConfig->m_oSerialportInfo.BaudRate(),
				8,1),
				m_bTestData);

		if(bOK && !m_oDataProcessor.Processing())
		{
			m_oDataProcessor.StartProcessing();
		}
		else
		{
			qDebug() << _FILENAME_ "Can't start processing";
		}

	}
}

void MainWindow::ClosedRaceDisplay()
{
	m_oDataProcessor.StopProcessing();
	//m_oDataProcessor.Stop();
}

void MainWindow::closeEvent (QCloseEvent *event)
{
	m_oDataProcessor.StopProcessing();
    m_oDataProcessor.Stop();
}

void MainWindow::UpdateLight()
{
	//if(m_opLightControl == NULL)
	//{
	//	m_opLightControl = new cLightControl( m_oDataProcessor.GetCUApdater().GetSerialConnector() );
	//}
	///*
	//m_opLightControl->UpdateLight(m_opMainWindow->spinBox_LightID->value(),
	//							  static_cast<tFloat32>(m_opMainWindow->slider_R->value()) / 100, 							
	//							  static_cast<tFloat32>(m_opMainWindow->slider_G->value()) / 100,
	//							  static_cast<tFloat32>(m_opMainWindow->slider_B->value()) / 100);
	//*/
	//if(!m_opLightControl->GetStatus())
	//{
	//	m_opLightControl->StartLightShow();
	//} 
	//else
	//{
	//	m_opLightControl->StopLightShow();
	//}

}