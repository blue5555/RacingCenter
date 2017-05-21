#include "libRaceDisplay/cRaceDisplaySimple.h"

#define _FILENAME_ "cRaceDisplaySimple: "
#define MAX_FONT_SIZE 36

using namespace RacingCenter;

cRaceDisplaySimple::cRaceDisplaySimple(const tDriverMapPointer& i_oDriverMap, cRace* i_opRace, QWidget *parent) :
 QWidget(parent)
,m_opConfig(cConfig::instance())
,m_opGridLayout(NULL)
,m_bInit(false)
,m_nNumberOfRows(0)
,m_nNumberOfColumns(0)
,m_oDrivers(i_oDriverMap)
,m_opRace(i_opRace)
,m_opRaceState(NULL)
{	
	//setBackgroundRole()
	setWindowTitle("RaceDisplay");
	m_opConfig = cConfig::instance();
	m_opGridLayout = new QGridLayout(this);
	setLayout(m_opGridLayout);

    configureDisplay();

	m_oFastTimer.setInterval(100);
	m_oFastTimer.moveToThread(&m_oFastTimerThread);

	connect(&m_oFastTimer,   SIGNAL(timeout()),  this, SLOT( UpdateRaceDisplayFast() ) );
	connect(&m_oFastTimerThread, SIGNAL(started()),  &m_oFastTimer, SLOT(start()));
	connect(&m_oFastTimerThread, SIGNAL(finished()), &m_oFastTimer, SLOT(stop()));

	//m_oTimer.setInterval(1000);
	//m_oTimer.moveToThread(&m_oTimerThread);

	//connect(&m_oTimer,   SIGNAL(timeout()),  this, SLOT( UpdateCompleteRaceDisplay() ) );
	//connect(&m_oTimerThread, SIGNAL(started()),  &m_oTimer, SLOT(start()));
	//connect(&m_oTimerThread, SIGNAL(finished()), &m_oTimer, SLOT(stop()));

	m_oFastTimerThread.start();
	//m_oTimerThread.start();
}

cRaceDisplaySimple::~cRaceDisplaySimple()
{
	//m_oTimerThread.quit();
	m_oFastTimerThread.quit();
}

void cRaceDisplaySimple::configureDisplay()
{
	m_bDebug        = m_opConfig->m_oDebugMessages.bRaceDisplay;
	m_bDebugTiming  = m_opConfig->m_oDebugMessagesTiming.bRaceDisplay;

	m_nNumberOfColumns = m_oDrivers.size() + 1;
	sRaceDisplayConfig* opRaceDisplayConfig = &m_opConfig->m_oRaceDisplayConfig;
	m_nNumberOfRows = opRaceDisplayConfig->oPositions.size() + 1;

	m_opRaceState = new cLabel(QString(""), Qt::white, -1, 0);
	m_opGridLayout->addWidget(m_opRaceState, 0, 0);

	// write header
	for(map<tUInt,tUInt>::iterator it = opRaceDisplayConfig->oPositions.begin(); it != opRaceDisplayConfig->oPositions.end(); it++ )
	{	
		std::string name = opRaceDisplayConfig->oNames[ it->second ];
		cLabel* opLabel = new cLabel(name, Qt::white,-1, it->second);
		
		m_opGridLayout->addWidget(opLabel, it->first, 0);
		m_oHeader[it->first] = opLabel;
	}

	tUInt nDriverCounter = 1;
	for(tDriverMapPointer::const_iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++ ) 
	{
		cLabel* opLabel = new cLabel(itDriver->second->GetName(),
									 m_opConfig->m_oRaceDisplayConfig.oColors[itDriver->first],
									 -1,
									  0);

		m_opGridLayout->addWidget(opLabel, 0, nDriverCounter);
		m_oDriverName[nDriverCounter-1] = opLabel;
		m_oUpdate[itDriver->second->GetID()] = false;

		for(map<tUInt,tUInt>::iterator it = opRaceDisplayConfig->oPositions.begin(); it != opRaceDisplayConfig->oPositions.end(); it++ )
		{	
			QString name = QString(opRaceDisplayConfig->oNames[ it->first ].c_str()) + QString("%1").arg(itDriver->second->GetID());

			if(it->second == SHOW_FUEL_LEVEL) {
				cProgressBar* opProgressBar = new cProgressBar("",m_opConfig->m_oRaceDisplayConfig.oColors[itDriver->first]); 
				m_oProgressBars[itDriver->first] = opProgressBar;				
				m_opGridLayout->addWidget(opProgressBar, it->first, nDriverCounter);
			} 
			else 
			{
				cLabel* opNextLabel = new cLabel(name,
												 m_opConfig->m_oRaceDisplayConfig.oColors[itDriver->first],
												 itDriver->first,
												 it->second);

				m_opGridLayout->addWidget(opNextLabel, it->first, nDriverCounter );

				m_oLabels[itDriver->first].push_back(opNextLabel);
			}
			
			if(it->second == SHOW_FUEL_LEVEL) {
	//			cBoundBox* opLabelName = new cBoundBox(name,
	//												   f32Width, 
	//												   f32Height,
	//												   Qt::green,//m_opConfig->m_oRaceDisplayConfig.oColors[itDriver.key()],
	//												   itDriver.key(),
	//												   SHOW_PROGRESS_BAR);
	//			m_opScene->addItem(opLabelName);
	//			opLabelName->setPos( ((tFloat32)nDriverCounter) * sceneRect.width()/nNumberOfColumns + f32Width, 
	//							     ((tFloat32)it.key()) * sceneRect.height()/nNumberOfRows);

	//			m_oLabels[itDriver.key()].push_back(opLabelName);
			}
		}
		nDriverCounter++;
	}

	m_bInit = true;
}

void cRaceDisplaySimple::UpdateRaceDisplayFast(/*sDriverMessage i_oDriverMessage*/)
{
	tUInt nRounds = m_opConfig->m_oRaceConfig.nRounds;

	tTimeStamp nTimeStamp = cTimeStamp::GetTimeStamp();

	if(m_bDebugTiming) {
		qDebug() << _FILENAME_ << "Update Display: " << cTimeStamp::GetTimeStamp();
	}

	tTimeStamp nDelta = nTimeStamp - m_opRace->GetStartTimeStamp();

	tTimeStamp nSec   = nDelta % 1000;
	tTimeStamp nMin   = (nDelta / 1000) % 60;
	tTimeStamp nHours = (nDelta / 1000) / 60;

	QString str;
	m_opRaceState->setColor(Qt::white);
	m_opRaceState->setText( str.sprintf("%02i:%02i:%02i",nHours, nMin, nSec) );

	switch(m_opRace->GetRaceState())
	{
	case RACE_STATE_NORMAL:
		m_opRaceState->setBackgroundColor(Qt::green);
		break;
	case RACE_STATE_CHAOS:
		m_opRaceState->setBackgroundColor(Qt::red);
		break;
	case RACE_STATE_READY4NORMAL:
		m_opRaceState->setBackgroundColor(Qt::darkYellow);
		break;
	case RACE_STATE_READY4SETNORMAL:
		m_opRaceState->setBackgroundColor(Qt::green);
		break;
	}

	for(tDriverMapPointer::const_iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++) 
	{
		vector<cLabel*> oLabels = m_oLabels[itDriver->first];
		const sDriverMessage& i_oDriverMessage = itDriver->second->CreateDisplayMessage(nTimeStamp); /*m_oMessages[itDriver->first]*/;
		
		m_oProgressBars[itDriver->first]->setValue(i_oDriverMessage.m_f32FuelLevel,i_oDriverMessage.m_f32FuelCapacity);
		
		if(i_oDriverMessage.m_bIsInBox)
		//if(i_oDriverMessage.m_f32FuelLevel/i_oDriverMessage.m_f32FuelCapacity < 0.25) 
		{
			m_oProgressBars[itDriver->first]->blinking(true);
		} 
		else 
		{
			m_oProgressBars[itDriver->first]->blinking(false);
		}

		for(vector<cLabel*>::iterator it = oLabels.begin(); it != oLabels.end(); it++) 
		{
			if(i_oDriverMessage.m_bChoas)
			{
				(*it)->setBackgroundColor(Qt::darkYellow);
			}
			else
			{
				(*it)->setBackgroundColor(Qt::black);
			}

			switch((*it)->Value())
			{						
			case SHOW_FUEL_LEVEL:   
				if(i_oDriverMessage.m_bIsInBox) {
					(*it)->setText( QString("B: %1").arg(i_oDriverMessage.m_f32FuelLevel,0,'f',3, '0')); 
				} else {
					(*it)->setText( QString("%1").arg(i_oDriverMessage.m_f32FuelLevel,0,'f',3, '0')); 
				}
				break;
			case SHOW_CURRENT_TIME: 
					(*it)->setText( QString("%1").arg(i_oDriverMessage.m_f32CurrentRoundTime) ); 
				break;
			case SHOW_PROG_SPEED: (*it)->setText( QString("%1").arg(i_oDriverMessage.m_nProgSpeed) ); 
				break;
			default: 
				break;
			}
		}
	}
	update();
}

void cRaceDisplaySimple::UpdateDriverRaceDisplay(sDriverMessage i_oDriverMessage)
{
	if(m_oLabels.find(i_oDriverMessage.m_iID) != m_oLabels.end())
	{
		vector<cLabel*> oLabels = m_oLabels[i_oDriverMessage.m_iID];
		for(vector<cLabel*>::iterator it = oLabels.begin(); it != oLabels.end(); it++) 
		{
			switch((*it)->Value())
			{						
			case SHOW_BEST_LAP:     (*it)->setText( QString("%1").arg(i_oDriverMessage.m_f32BestLapTime,0,'f',3, '0')); break;
			case SHOW_LAST_LAP:
				if(i_oDriverMessage.m_bIsDisqualified) {
					(*it)->setText( "Disqualified" );
				} else {
					(*it)->setText( QString("%1").arg(i_oDriverMessage.m_f32LastLapTime,0,'f',3, '0'));
				}
				break;
			case SHOW_POSITION:     (*it)->setText( QString("%1").arg(i_oDriverMessage.m_nPosition) ); break;
			case SHOW_LAPS:			
				switch(i_oDriverMessage.m_nRaceMode)
				{
				case MODE_RACE:
				case MODE_QUALITFYING:
					(*it)->setText( QString("%1 / %2").arg(i_oDriverMessage.m_nRounds).arg(i_oDriverMessage.m_nRaceRounds) ); 
					break;
				case MODE_TRAINING:
					(*it)->setText( QString("%1").arg(i_oDriverMessage.m_nRounds)); 
					break;
				}
				break;
			case SHOW_TIME2LEADER:
				if(i_oDriverMessage.m_f32Time2Leader >= 1000) {
					(*it)->setText( QString("Laps: %1").arg(i_oDriverMessage.m_f32Time2Leader/1000) );
				} else {
					(*it)->setText( QString("%1").arg(i_oDriverMessage.m_f32Time2Leader,0,'f',3, '0'));
				}
				break;
			case SHOW_ACCIDENTS:  (*it)->setText( QString("%1").arg(0) ); break;
			default: break;
			}
		}
	}
}

//void cRaceDisplaySimple::UpdateCompleteRaceDisplay(/*sDriverMessage i_oDriverMessage*/)
//{
//	tUInt nRounds = m_opConfig->m_oRaceConfig.nRounds;
//	if(m_bDebugTiming) {
//		qDebug() << _FILENAME_ << "Update Display: " << cTimeStamp::GetTimeStamp();
//	}
//
//	tTimeStamp nTimeStamp = cTimeStamp::GetTimeStamp();
//
//	for(QMap<tUInt8,cDriver*>::iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++)  
//	{
//		vector<cLabel*> oLabels = m_oLabels[itDriver.key()];
//		const sDriverMessage& i_oDriverMessage = (*itDriver)->CreateDisplayMessage(nTimeStamp);
//		for(vector<cLabel*>::iterator it = oLabels.begin(); it != oLabels.end(); it++) 
//		{
//			switch((*it)->Value())
//			{						
//			case SHOW_BEST_LAP:     (*it)->setText( QString("%1").arg(i_oDriverMessage.m_f32BestLapTime,0,'f',3, '0')); break;
//			case SHOW_LAST_LAP:
//				if(i_oDriverMessage.m_bIsDisqualified) {
//					(*it)->setText( "Disqualified" );
//				} else {
//					(*it)->setText( QString("%1").arg(i_oDriverMessage.m_f32LastLapTime,0,'f',3, '0'));
//				}
//			break;
//			case SHOW_POSITION:     (*it)->setText( QString("%1").arg(i_oDriverMessage.m_nPosition) ); break;
//			case SHOW_LAPS:		    (*it)->setText( QString("%1").arg(i_oDriverMessage.m_nRounds) ); break;
//			case SHOW_TIME2LEADER:
//				if(i_oDriverMessage.m_f32Time2Leader >= 1000) {
//					(*it)->setText( QString("Laps: %1").arg(i_oDriverMessage.m_f32Time2Leader/1000) );
//				} else {
//					(*it)->setText( QString("%1").arg(i_oDriverMessage.m_f32Time2Leader,0,'f',3, '0'));
//				}
//			break;
//			case SHOW_ACCIDENTS:  (*it)->setText( QString("%1").arg(0) ); break;
//			case SHOW_PROG_SPEED: (*it)->setText( QString("%1").arg(i_oDriverMessage.m_nProgSpeed) ); break;
//			default: break;
//			}
//		}
//	}
//}
	
void cRaceDisplaySimple::resizeEvent(QResizeEvent *event)
{
	QRect oRect = rect();
	QRect oLabelsize(0,0, oRect.width() / m_nNumberOfColumns, oRect.height() / m_nNumberOfRows );

	QFont font;
	int fontSize = 1;
	font.setPointSize(fontSize);
	while( true )
	{
		QFont f(font);
		f.setPixelSize( fontSize );
		QRect r = QFontMetrics(f).boundingRect( "DummyTextText" );
		if (r.height() <= oLabelsize.height() && r.width() <= oLabelsize.width() )
		{
			fontSize++;
			if(fontSize > MAX_FONT_SIZE)
			{
				break;
			}
		}
		else
		{
			break;
		}
	}

	fontSize--;

	m_opRaceState->setFontSize(fontSize);

	for(map<tUInt8,cLabel*>::iterator itDriverName = m_oDriverName.begin(); itDriverName != m_oDriverName.end(); itDriverName++) 
	{
		itDriverName->second->setFontSize(fontSize);
	}

	for(map<tUInt8,cLabel*>::iterator itHeader = m_oHeader.begin(); itHeader != m_oHeader.end(); itHeader++) 
	{
		itHeader->second->setFontSize(fontSize);
	}

	for(map<tUInt8,cProgressBar*>::iterator itProgressBar = m_oProgressBars.begin(); itProgressBar != m_oProgressBars.end(); itProgressBar++)
	{
		itProgressBar->second->setFontSize(fontSize);
	}

	tInt8 nCounter = 0;
	map<tUInt8,vector<cLabel*> >::iterator itDriver = m_oLabels.begin();
	for(; itDriver != m_oLabels.end(); itDriver++) 
	{
		vector<cLabel*> oLabels = m_oLabels[itDriver->first];
		for(vector<cLabel*>::iterator it = oLabels.begin(); it != oLabels.end(); it++) 
		{
			//if(nCounter < 3) 
			{
				(*it)->setFontSize(fontSize);
			}
		}
		nCounter++;
	}
}

void cRaceDisplaySimple::closeEvent (QCloseEvent *event)
{
	emit Closed();
}