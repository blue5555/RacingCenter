#include "cStartLightSimple.h"
#include <ui_StartLightSimple.h>
#include <libConfig/cConfig.h>

cStartLight::cStartLight(QWidget *parent) :
 QMainWindow(parent)
,m_opStartLight(new Ui::StartLightSimple())
,m_nCurrentState(0)
,m_opLabel(NULL)
{
	Q_INIT_RESOURCE(startLight);

	m_opStartLight->setupUi(this);

	m_opLabel = new AspectRatioPixmapLabel();
	m_opLabel->setAlignment(Qt::AlignCenter);
	m_opStartLight->gridLayout->addWidget(m_opLabel);

	m_oPictures[0] = QPixmap (":images/State_Off.png");
	m_oPictures[1] = QPixmap (":images/State_5.png");
	m_oPictures[2] = QPixmap (":images/State_1.png");
	m_oPictures[3] = QPixmap (":images/State_2.png");
	m_oPictures[4] = QPixmap (":images/State_3.png");
	m_oPictures[5] = QPixmap (":images/State_4.png");
	m_oPictures[6] = QPixmap (":images/State_5.png");
	m_oPictures[7] = QPixmap (":images/State_Go.png");
	m_oPictures[8] = QPixmap (":images/State_Yellow.png");

	m_opLabel->setPixmap(m_oPictures[0]);
	this->setVisible(false);

}

cStartLight::~cStartLight()
{
	if(m_opLabel)
	{
		delete m_opLabel;
		m_opLabel = NULL;
	}
}

void cStartLight::ClearLEDs()
{
	for(tUInt n = 0; n < 4; n++)
	{
		for(tUInt k = 0; k < 5; k++)
		{
			//m_opLeds[n][k]->setValue(false);
		}
	}
}

void cStartLight::UpdateState(unsigned int i_nState)
{
	if(i_nState != m_nCurrentState)
	{
		qDebug() << "Startlight: " << i_nState;
		if(i_nState == 0)
		{
			this->setVisible(false);
		} 
		else if(i_nState == 1) 
		{
			this->setVisible(true);
			this->showMaximized();
		}

		if(i_nState < 9)
		{
			m_opLabel->setPixmap(m_oPictures[i_nState]);
		}
		m_nCurrentState = i_nState;
		update();
	}
	
}