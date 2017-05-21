#include "cStartLightGui.h"
#include "ui_startlight.h"

#include <QMessageBox>
#include <cConfig.h>

//! [0]
StartLightGui::StartLightGui(QWidget *parent) :
 QMainWindow(parent)
,m_opStartLightGui(new Ui::StartLightGui)
,m_nState(0)
{
	m_opStartLightGui->setupUi(this);
	
	m_opStartLightGui->graphicsView = new cSvgView();
//	QGraphicsScene* m_graphicsScene = new QGraphicsScene();

	//this->show();
 }

StartLightGui::~StartLightGui()
{
    delete m_opStartLightGui;
}

void StartLightGui::UpdateState(unsigned int i_nState)
{
	setState(i_nState);
}

void StartLightGui::setState(const tUInt8& i_nState)
{
	if(i_nState != m_nState) {

		cSvgView* opPixmapItem = (cSvgView*)m_opStartLightGui->graphicsView;

		if(i_nState == 1) {
			opPixmapItem->show();
			//opPixmapItem->showMaximized();
		} else if(i_nState == 0) {
			opPixmapItem->hide();
		}
		if(i_nState != 0) {
			opPixmapItem->showMaximized();
		}		

		QImage image;
		switch(i_nState) {
			case 1: opPixmapItem->openFile(true, ":/images/State_5.svg",NULL); break;
			case 2: opPixmapItem->openFile(true, ":/images/State_1.svg",NULL); break;
			case 3: opPixmapItem->openFile(true, ":/images/State_2.svg",NULL); break;
			case 4: opPixmapItem->openFile(true, ":/images/State_3.svg",NULL); break;
			case 5: opPixmapItem->openFile(true, ":/images/State_4.svg",NULL); break;
			case 6: opPixmapItem->openFile(true, ":/images/State_5.svg",NULL); break;
			case 7: opPixmapItem->openFile(true, ":/images/State_Go.svg",NULL); break;
			case 8: opPixmapItem->openFile(true, ":/images/State_Yellow.svg",NULL); break;
			//case 0: opPixmapItem->openFile(true, ":/images/State_Off.svg",NULL); break;
		}

	}

	m_nState = i_nState;
}