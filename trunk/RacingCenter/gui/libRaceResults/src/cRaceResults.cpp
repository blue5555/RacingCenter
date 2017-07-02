#include "libRaceResults/cRaceResults.h"
#include <libDatabase/cDatabaseRace.h>

using namespace RacingCenter;

cRaceResults::cRaceResults(QWidget *parent, cRace* i_opRace, cDataLogger* i_opDataLogger) :
 QWidget(parent)
,m_opConfig(NULL)
,m_opRace(i_opRace)
,m_opDataLogger(i_opDataLogger)
{
	setWindowTitle("RaceDisplay");
	m_opConfig = cConfig::instance();
	m_opGridLayout = new QGridLayout(this);

	setLayout(m_opGridLayout);

	configureDisplay();

}

cRaceResults::~cRaceResults()
{
}

void cRaceResults::configureDisplay()
{
	m_bDebug        = m_opConfig->m_oDebugMessages.bRaceDisplay;
	m_bDebugTiming  = m_opConfig->m_oDebugMessagesTiming.bRaceDisplay;

	QMap<tUInt,QString> oNames;
	oNames[0] = "Position";
	oNames[1] = "Name";
	oNames[2] = "Laps";
	oNames[3] = "Best Lap";
	oNames[4] = "Points";
	oNames[5] = "Sum of Points";

	m_nNumberOfColumns = oNames.size();
	m_nNumberOfRows = m_opRace->GetDriverMap().size() + 1;

	// write header
	for(tInt64 n = 0; n < oNames.size(); n++)
	{	
		const QString& name = oNames[n];
		QLabel* opLabel = CreateLabel(name, Qt::white);

		m_oLabels.push_back(opLabel);
		m_opGridLayout->addWidget(opLabel, 0, n);
	}

	// write drivers
	tUInt nCol = 0;
	for (tUInt n = 1; n < m_nNumberOfRows; n++)
	{
		cDriver* opDriver = m_opRace->GetDriverByPosition(n);
		nCol = 0;

		tUInt nPoints = m_opConfig->m_oRaceConfig.oPoints[n];

		if(opDriver != NULL)
		{
			opDriver->SetPoints(opDriver->GetPoints() + nPoints);

			QLabel* opLabel = CreateLabel(QString("%1").arg(n), Qt::white);
			m_oLabels.push_back(opLabel);
			m_opGridLayout->addWidget(opLabel, n, nCol);

			nCol++;

			opLabel = CreateLabel(opDriver->GetName().c_str(), Qt::white);
			m_oLabels.push_back(opLabel);
			m_opGridLayout->addWidget(opLabel, n, nCol);

			nCol++;

			opLabel = CreateLabel(QString("%1").arg(opDriver->GetNumberOfLaps()), Qt::white);
			m_oLabels.push_back(opLabel);
			m_opGridLayout->addWidget(opLabel, n, nCol);

			nCol++;

			opLabel = CreateLabel(QString("%1").arg(opDriver->GetBestTime()), Qt::white);
			m_oLabels.push_back(opLabel);
			m_opGridLayout->addWidget(opLabel, n, nCol);

			nCol++;

			opLabel = CreateLabel(QString("%1").arg(nPoints), Qt::white);
			m_oLabels.push_back(opLabel);
			m_opGridLayout->addWidget(opLabel, n, nCol);

			nCol++;

			opLabel = CreateLabel(QString("%1").arg(opDriver->GetPoints()), Qt::white);
			m_oLabels.push_back(opLabel);
			m_opGridLayout->addWidget(opLabel, n, nCol);
		}
	}
}

QLabel* cRaceResults::CreateLabel(const QString& i_strText, const Qt::GlobalColor i_nColor)
{
	QLabel* opLabel = new QLabel(i_strText);

	QPalette pal;
	pal.setColor(QPalette::WindowText, i_nColor);
	pal.setColor(QPalette::Background, Qt::black);

	opLabel->setPalette(pal);
	opLabel->setAutoFillBackground(true);
	opLabel->setScaledContents(true);
	opLabel->setAlignment(Qt::AlignCenter);

	return opLabel;

}

void cRaceResults::resizeEvent(QResizeEvent *event)
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
			fontSize++;
		else
			break;
	}

	fontSize--;
	for(tUInt n = 0; n < m_oLabels.size(); n++) 
	{
		QFont font = m_oLabels[n]->font();
		font.setPixelSize(fontSize);
		m_oLabels[n]->setFont(font);
	}
}

void cRaceResults::closeEvent (QCloseEvent *event)
{
	//if(m_opRace->RaceMode() == MODE_RACE)
	{
		// save results ?
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, "Result", "Save Results?", QMessageBox::Yes|QMessageBox::No);

		if (reply == QMessageBox::Yes) 
		{
			cDatabase* opDatabase = cDatabase::instance();
		} 
		else 
		{
			m_opDataLogger->Clear();
		}
	}

	emit ClosedRaceResults();
}