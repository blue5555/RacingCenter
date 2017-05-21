#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QTreeWidget>
#include <QMainWindow>
#include <QComboBox>
#include <QCheckBox>
#include <libCore/cDataProcessor.h>
#include <libDatabase/cDatabase.h>
#include "ui_mainwindow.h"

#include "cRaceWindow.h"
#include "cFuelWindow.h"
#include "cDatabaseWindow.h"
#include "cConfigWindow.h"
#include "cLightControlWindow.h"

//#include <cLightControl.h>
//#include <cStartLightGui.h>
//#include <cDriverDisplay.h>
//#include <cRacingCenterServer.h>

QT_BEGIN_NAMESPACE

namespace Ui {
	class MainWindow;
}

QT_END_NAMESPACE

class cConsole;

using namespace RacingCenter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
	tBool m_bDebug;
	tBool m_bTestData;

	Ui::MainWindow* m_opMainWindow;

    cConsole*		m_opConsole;

    cConfig*        m_opConfig;
    cDatabase*      m_opDatabase;

    cRacingWindow   m_oRacingWindow;
    cFuelWindow     m_oFuelWindow;
    cDatabaseWindow m_oDatabaseWindow;
    cConfigWindow   m_oConfigWindow;
	cLightControlWindow m_oLightControlWindow;

	cDataProcessor    m_oDataProcessor;

public:
    explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	virtual void closeEvent (QCloseEvent *event);

private slots:
	void Start();
	void ClosedRaceDisplay();
	void UpdateLight();

};

#endif // MAINWINDOW_H
