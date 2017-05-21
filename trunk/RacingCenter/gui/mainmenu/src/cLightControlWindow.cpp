#include "cLightControlWindow.h"

using namespace RacingCenter;

cLightControlWindow::cLightControlWindow(const Ui::MainWindow* i_opMainWindow) : 
 m_opMainWindow(i_opMainWindow)
,m_opLightControl(NULL)
{

}

cLightControlWindow::~cLightControlWindow()
{

}

tBool cLightControlWindow::Init(cLightControl* i_opLightControl)
{
	m_opLightControl = i_opLightControl;

	connect(m_opMainWindow->button_SendLight, SIGNAL(clicked()), this, SLOT( SendLight() ) );
	connect(m_opMainWindow->button_ClearLights, SIGNAL(clicked()), this, SLOT( ClearLights() ) );

	connect(m_opMainWindow->button_StartLightWave, SIGNAL(clicked()), this, SLOT( StartLightWave() ) );
	connect(m_opMainWindow->button_StopLightWave, SIGNAL(clicked()), this, SLOT( StopLightWave() ) );

	connect(m_opMainWindow->button_StartLightBox, SIGNAL(clicked()), this, SLOT( StartLightBox() ) );
	connect(m_opMainWindow->button_StopLightBox, SIGNAL(clicked()), this, SLOT( StopLightBox() ) );

	connect(m_opMainWindow->button_StartLightTribuene, SIGNAL(clicked()), this, SLOT( StartLightTribuene() ) );
	connect(m_opMainWindow->button_StopLightTribuene, SIGNAL(clicked()), this, SLOT( StopLightTribuene() ) );

	connect(m_opMainWindow->button_DimUp, SIGNAL(clicked()), this, SLOT( StartDimUp() ) );
	connect(m_opMainWindow->button_DimDown, SIGNAL(clicked()), this, SLOT( StartDimDown() ) );

	return true;
}

void cLightControlWindow::ClearLights()
{
	m_opLightControl->ClearLights();
}

void cLightControlWindow::StartLightWave()
{
	tFloat64 f64Duration = m_opMainWindow->doubleSpinBox_LightWaveDuration->value();
	if(f64Duration > 0)
	{
		m_opLightControl->StartLightWave(f64Duration);
	}
}

void cLightControlWindow::StopLightWave()
{
	m_opLightControl->StopLightWave();
}

void cLightControlWindow::StartLightBox()
{
	tFloat64 f64Duration = m_opMainWindow->doubleSpinBox_LightBoxDuration->value();
	if(f64Duration > 0)
	{
		m_opLightControl->StartLightBox(f64Duration);
	}
}

void cLightControlWindow::StopLightBox()
{
	m_opLightControl->StopLightBox();
}

void cLightControlWindow::StartLightTribuene()
{
	tFloat64 f64Duration = m_opMainWindow->doubleSpinBox_LightTribueneDuration->value();
	if(f64Duration > 0)
	{
		m_opLightControl->StartLightTribuene(f64Duration);
	}
}

void cLightControlWindow::StopLightTribuene()
{
	m_opLightControl->StopLightTribuene();
}

void cLightControlWindow::StartDimUp()
{
	tUInt nLightID = m_opMainWindow->spinBox_LightID->value();

	sRGB oRGB;
	oRGB.r = 255; //m_opMainWindow->slider_R->value(); 
	oRGB.g = 255; //m_opMainWindow->slider_G->value(); 
	oRGB.b = 0;   //m_opMainWindow->slider_B->value(); 

	m_opLightControl->StartDim(nLightID, oRGB);
}

void cLightControlWindow::StartDimDown()
{
	tUInt nLightID = m_opMainWindow->spinBox_LightID->value();

	sRGB oRGB;
	oRGB.r = 0; 
	oRGB.g = 0; 
	oRGB.b = 0; 

	m_opLightControl->StartDim(nLightID, oRGB);
}

void cLightControlWindow::SendLight()
{
	tUInt nLightID = m_opMainWindow->spinBox_LightID->value();

	sRGB oRGB;
	oRGB.r = m_opMainWindow->slider_R->value(); 
	oRGB.g = m_opMainWindow->slider_G->value(); 
	oRGB.b = m_opMainWindow->slider_B->value(); 

	m_opLightControl->SetLight(nLightID, oRGB);
	m_opLightControl->UpdateLights();
}