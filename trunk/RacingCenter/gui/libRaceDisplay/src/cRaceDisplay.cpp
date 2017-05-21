#include "libRaceDisplay/cRaceDisplay.h"

#ifndef QT_NO_OPENGL
#include <QGLWidget>
#endif

#define _FILENAME_ "cRaceDisplay: "

cRaceDisplay::cRaceDisplay(QWidget *parent) :
 QGraphicsView(parent)
,m_opConfig(NULL)
,m_opScene(new QGraphicsScene())
,m_eRenderer(OpenGL)
//,m_opMainWindow(new Ui::RaceDisplay)
{	
	//QBrush oBrush;
	//oBrush.setColor(Qt::white);
	//oBrush.setStyle(Qt::SolidPattern);
	//m_opScene->setBackgroundBrush(oBrush);
	m_opConfig = cConfig::instance();
	m_opScene->setSceneRect(0,0,m_opConfig->m_oRaceDisplayConfig.nWidth,m_opConfig->m_oRaceDisplayConfig.nHeight);

	setRenderer(m_eRenderer);
	setHighQualityAntialiasing(false);
	this->setScene(m_opScene);
}

cRaceDisplay::~cRaceDisplay()
{
	if(m_opScene != NULL) {
		delete m_opScene;
	}
}

void cRaceDisplay::configureDisplay(QMap<tUInt8,cDriver*> i_oDrivers)
{
	m_opConfig = cConfig::instance();
	
	m_bDebug = m_opConfig->m_oDebugMessages.bRaceDisplay;
	m_bDebugTiming = m_opConfig->m_oDebugMessagesTiming.bRaceDisplay;

	m_oDrivers = i_oDrivers;

	//m_opScene->setBackgroundBrush(QBrush(QColor(0,0,0),Qt::SolidPattern));

	tUInt nNumberOfColumns = i_oDrivers.size() + 1;
	sRaceDisplayConfig* opRaceDisplayConfig = &m_opConfig->m_oRaceDisplayConfig;
	tUInt nNumberOfRows = opRaceDisplayConfig->oPositions.size() + 1;
	QRectF sceneRect = m_opScene->sceneRect();

	// write header
	for(QMap<tUInt,tUInt>::iterator it = opRaceDisplayConfig->oPositions.begin(); it != opRaceDisplayConfig->oPositions.end(); it++ )
	{	
		QString name = opRaceDisplayConfig->oNames[ it.value() ];
		cBoundBox* opLabelName = new cBoundBox(name, 
											   sceneRect.width()/nNumberOfColumns - DISTANCE_BOUNDBOX, 
											   sceneRect.height()/nNumberOfRows - DISTANCE_BOUNDBOX,
											   Qt::white,
											   -1,it.value());
		m_opScene->addItem(opLabelName);
		opLabelName->setPos(0, ((tFloat32)it.key()) * sceneRect.height()/nNumberOfRows);
	}

	tUInt nDriverCounter = 1;
	for(QMap<tUInt8,cDriver*>::iterator itDriver = m_oDrivers.begin(); itDriver != m_oDrivers.end(); itDriver++ ) {

		cBoundBox* opLabelName = new cBoundBox((*itDriver)->Name(), 
											   sceneRect.width()/nNumberOfColumns - DISTANCE_BOUNDBOX, 
											   sceneRect.height()/nNumberOfRows - DISTANCE_BOUNDBOX,
											   m_opConfig->m_oRaceDisplayConfig.oColors[itDriver.key()],
											   -1,
											   0);
		m_opScene->addItem(opLabelName);
		opLabelName->setPos( ((tFloat32)nDriverCounter) * sceneRect.width()/nNumberOfColumns, 
							 0 * sceneRect.height()/nNumberOfRows);

		for(QMap<tUInt,tUInt>::iterator it = opRaceDisplayConfig->oPositions.begin(); it != opRaceDisplayConfig->oPositions.end(); it++ )
		{	
			QString name = opRaceDisplayConfig->oNames[ it.value() ] + QString("%1").arg((*itDriver)->ID());

			tFloat32 f32Width  = sceneRect.width()/nNumberOfColumns - DISTANCE_BOUNDBOX;
			tFloat32 f32Height = sceneRect.height()/nNumberOfRows - DISTANCE_BOUNDBOX;

			if(it.value() == SHOW_FUEL_LEVEL) {
				f32Width  = (sceneRect.width()/nNumberOfColumns)/2 - DISTANCE_BOUNDBOX;
				f32Height = (sceneRect.height()/nNumberOfRows) - DISTANCE_BOUNDBOX;
			}

			cBoundBox* opLabelName = new cBoundBox(name, 
												   f32Width, 
												   f32Height,
												   m_opConfig->m_oRaceDisplayConfig.oColors[itDriver.key()],
												   itDriver.key(),
												   it.value());
			m_opScene->addItem(opLabelName);
			opLabelName->setPos( ((tFloat32)nDriverCounter) * sceneRect.width()/nNumberOfColumns, 
								 ((tFloat32)it.key()) * sceneRect.height()/nNumberOfRows);

			m_oLabels[itDriver.key()].push_back(opLabelName);

			
			if(it.value() == SHOW_FUEL_LEVEL) {
				cBoundBox* opLabelName = new cBoundBox(name,
													   f32Width, 
													   f32Height,
													   Qt::green,//m_opConfig->m_oRaceDisplayConfig.oColors[itDriver.key()],
													   itDriver.key(),
													   SHOW_PROGRESS_BAR);
				m_opScene->addItem(opLabelName);
				opLabelName->setPos( ((tFloat32)nDriverCounter) * sceneRect.width()/nNumberOfColumns + f32Width, 
								     ((tFloat32)it.key()) * sceneRect.height()/nNumberOfRows);

				m_oLabels[itDriver.key()].push_back(opLabelName);
			}
		}
		nDriverCounter++;
	}
}

void cRaceDisplay::UpdateRaceDisplay(sDriverMessage i_oDriverMessage)
{
	//QMutexLocker locker(&m_oMutex);
	tUInt nRounds = m_opConfig->m_oRaceConfig.nRounds;

	if(m_bDebugTiming) {
		qDebug() << _FILENAME_ << "Update Display: " << QDateTime::currentMSecsSinceEpoch() / 1000;
	}

	//if( m_oLabels.find(i_oDriverMessage.m_iID) != m_oLabels.end() && 
	//	m_oDrivers.find(i_oDriverMessage.m_iID) != m_oDrivers.end() ) 
	{
		vector<cBoundBox*> oLabels = m_oLabels[i_oDriverMessage.m_iID];
		//cDriver* opDriver = m_oDrivers[i_oDriverMessage.m_iID];
		for(vector<cBoundBox*>::iterator it = oLabels.begin(); it != oLabels.end(); it++) 
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
			case SHOW_FUEL_LEVEL:   
				if(i_oDriverMessage.m_bIsInBox) {
					(*it)->setText( QString("B: %1").arg(i_oDriverMessage.m_f32FuelLevel,0,'f',3, '0')); 
				} else {
					(*it)->setText( QString("%1").arg(i_oDriverMessage.m_f32FuelLevel,0,'f',3, '0')); 
				}
				break;
			case SHOW_LAPS:		    (*it)->setText( QString("%1").arg(i_oDriverMessage.m_nRounds) ); break;
			case SHOW_TIME2LEADER:
				if(i_oDriverMessage.m_f32Time2Leader >= 1000) {
					(*it)->setText( QString("Laps: %1").arg(i_oDriverMessage.m_f32Time2Leader/1000) );
				} else {
					(*it)->setText( QString("%1").arg(i_oDriverMessage.m_f32Time2Leader,0,'f',3, '0'));
				}
				break;
			case SHOW_ACCIDENTS:    (*it)->setText( QString("%1").arg(0) ); break;
			case SHOW_CURRENT_TIME: (*it)->setText( QString("%1").arg(i_oDriverMessage.m_f32CurrentRoundTime) ); break;
			case SHOW_PROGRESS_BAR: 
				(*it)->setValue( i_oDriverMessage.m_f32FuelLevel/i_oDriverMessage.m_f32FuelCapacity );
				if(i_oDriverMessage.m_f32FuelLevel/i_oDriverMessage.m_f32FuelCapacity < 0.25) {
					(*it)->fastBlinking(true);
				} else {
					(*it)->fastBlinking(false);
				}
				(*it)->blinking( i_oDriverMessage.m_bIsInBox );
					break;
			case SHOW_PROG_SPEED: (*it)->setText( QString("%1").arg(i_oDriverMessage.m_nProgSpeed) ); break;
			default: break;
			}
		}
	}

	//update();
}
	
void cRaceDisplay::UpdateCompleteRaceDisplay()
{
	//QMutexLocker locker(&m_oMutex);

	for(map<tUInt8, vector<cBoundBox*> >::iterator itDriver = m_oLabels.begin(); itDriver != m_oLabels.end(); itDriver++ ) {
		cDriver* opDriver = m_oDrivers[itDriver->first];
		for(vector<cBoundBox*>::iterator it = itDriver->second.begin(); it != itDriver->second.end(); it++) {

			switch((*it)->Value())
			{
			case SHOW_BEST_LAP:    (*it)->setText( QString("%1").arg(opDriver->BestTime()) ); break;
			case SHOW_LAST_LAP:    (*it)->setText( QString("%1").arg(opDriver->LastRoundTime()) ); break;
			case SHOW_POSITION:    (*it)->setText( QString("%1").arg(opDriver->Position()) ); break;
			case SHOW_FUEL_LEVEL:  (*it)->setText( QString("%1").arg(opDriver->GetFuelLevel()) ); break;
			case SHOW_LAPS:		   (*it)->setText( QString("%1").arg(opDriver->Laps()) ); break;
			case SHOW_TIME2LEADER: (*it)->setText( QString("%1").arg(opDriver->Time2Leader()) ); break;
			case SHOW_ACCIDENTS:   (*it)->setText( QString("%1").arg(opDriver->Accidents()) ); break;
				//case SHOW_CURRENT_TIME: (*it)->setText( QString("%1").arg(opDriver-> ()) ); break;
			default: break;
			}
		}
	}
}

void cRaceDisplay::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	fitInView(QRectF(0,0,scene()->width(),scene()->height()), Qt::KeepAspectRatio ); // Qt::KeepAspectRatio
}

void cRaceDisplay::closeEvent (QCloseEvent *event)
{
	emit Closed();
}

void cRaceDisplay::setRenderer(eRendererType type)
{
	m_eRenderer = type;

	if (m_eRenderer == OpenGL) {
#ifndef QT_NO_OPENGL
		setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
#endif
	} else {
		setViewport(new QWidget);
	}
}

void cRaceDisplay::setHighQualityAntialiasing(bool highQualityAntialiasing)
{
#ifndef QT_NO_OPENGL
	setRenderHint(QPainter::HighQualityAntialiasing, highQualityAntialiasing);
#else
	Q_UNUSED(highQualityAntialiasing);
#endif
}