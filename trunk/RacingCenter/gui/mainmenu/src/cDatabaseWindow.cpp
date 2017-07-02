#include "cDatabaseWindow.h"

using namespace RacingCenter;

cDatabaseWindow::cDatabaseWindow(const Ui::MainWindow* i_opMainWindow, cRacingWindow& i_oRacingWindow) :
 m_opMainWindow(i_opMainWindow)
,m_opDatabase(cDatabase::instance())
,m_opConfig(cConfig::instance())
,m_oRacingWindow(i_oRacingWindow)
{
}

cDatabaseWindow::~cDatabaseWindow()
{

}

tBool cDatabaseWindow::Init()
{
    InitDatabaseTree();

    connect(m_opMainWindow->treeWidget_Database, SIGNAL( itemDoubleClicked(QTreeWidgetItem*, int) ), this, SLOT( DatabaseItemDoubleClicked(QTreeWidgetItem*, int) ) );

    connect(m_opMainWindow->pushButton_Add,		SIGNAL( clicked() ), this, SLOT( AddDatabaseItem() ) );
    connect(m_opMainWindow->pushButton_Save,	SIGNAL( clicked() ), this, SLOT( SaveDatabaseItem() ) );
    connect(m_opMainWindow->pushButton_Delete,	SIGNAL( clicked() ), this, SLOT( DeleteDatabaseItem() ) );

    return true;
}

// database functions
tBool cDatabaseWindow::InitDatabaseTree()
{
    m_opDatabase->SaveDatabase();

    m_opMainWindow->treeWidget_Database->clear();
    QTreeWidgetItem* opTreeWidgetItemDrivers = new QTreeWidgetItem(m_opMainWindow->treeWidget_Database);
    opTreeWidgetItemDrivers->setText(0,"Drivers");

    std::list<std::string> oDriverNames = m_opDatabase->GetAllDriverNames();
    for(std::list<std::string>::iterator it = oDriverNames.begin(); it != oDriverNames.end(); it++) 
    {
    		QTreeWidgetItem* opTreeWidgetItemDriver = new QTreeWidgetItem(opTreeWidgetItemDrivers);
    		opTreeWidgetItemDriver->setText(0,it->c_str());
    }

    QTreeWidgetItem* opTreeWidgetItemCars = new QTreeWidgetItem(m_opMainWindow->treeWidget_Database);
    opTreeWidgetItemCars->setText(0,"Cars");

    std::list<std::string> oCarNames = m_opDatabase->GetAllCarNames();
    for(std::list<std::string>::iterator it = oCarNames.begin(); it != oCarNames.end(); it++) 
    {
    	QTreeWidgetItem* opTreeWidgetItemCar = new QTreeWidgetItem(opTreeWidgetItemCars);
    	opTreeWidgetItemCar->setText(0,it->c_str());
    }
    opTreeWidgetItemCars->sortChildren(0,Qt::AscendingOrder);
    
    m_opMainWindow->treeWidget_Database->expandAll();

    m_oRacingWindow.UpdateComboBoxes();

    return true;
}

void cDatabaseWindow::DatabaseItemDoubleClicked(QTreeWidgetItem* opTreeWidgetItem, int column)
{
    QString QSText = opTreeWidgetItem->text(0);
    QTreeWidgetItem* opTreeWidgetItemParent = opTreeWidgetItem->parent();
    if(opTreeWidgetItemParent != NULL) {
    	QString QSParent = opTreeWidgetItemParent->text(0);
    	if(QSParent == "Cars") 
        {
    		// load car information
    		cDatabaseCar oCar = m_opDatabase->GetCar(QSText.toStdString());
   			m_opMainWindow->tabWidget_Information->setCurrentIndex(1);
   			LoadCarInformation(oCar);
    	} else if(QSParent == "Drivers") {
    		// load driver information
    		cDatabaseDriver oDriver = m_opDatabase->GetDriver(QSText.toStdString());
   			m_opMainWindow->tabWidget_Information->setCurrentIndex(0);
   			LoadDriverInformation(oDriver);
    	} else if(QSParent == "Tracks") {
    		// load track information
    	}
    }
}

void cDatabaseWindow::AddDatabaseItem()
{
    QTreeWidgetItem* opCurrentItem = m_opMainWindow->treeWidget_Database->currentItem();
    if(opCurrentItem != NULL) {
    	QString QSText = opCurrentItem->text(0);
    	QTreeWidgetItem* opTreeWidgetItemParent = opCurrentItem->parent();
    	if(opTreeWidgetItemParent != NULL || 
    	   opCurrentItem->text(0) == "Cars" ||
    	   opCurrentItem->text(0) == "Drivers" ||
    	   opCurrentItem->text(0) == "Tracks") {
    		QString QSParent = "";
    		if(opTreeWidgetItemParent != NULL) {
    			QSParent = opTreeWidgetItemParent->text(0);
    		} else {
    			QSParent = opCurrentItem->text(0);
    		}
    		if(QSParent == "Cars") {
    			// add car
    			QString oNewCarName = QString("NewCar %1").arg(m_opDatabase->GetNumberOfCars());
    			m_opDatabase->AddCar(oNewCarName.toStdString());
    		} else if(QSParent == "Drivers") {
    			// add driver
    			QString oNewDriverName = QString("NewDriver %1").arg(m_opDatabase->GetNumberOfDrivers());
    			m_opDatabase->AddDriver(oNewDriverName.toStdString());
    		} else if(QSParent == "Tracks") {
    			// load track information
    		}
    	}
    }

    InitDatabaseTree();

}

void cDatabaseWindow::DeleteDatabaseItem()
{
    QTreeWidgetItem* opCurrentItem = m_opMainWindow->treeWidget_Database->currentItem();
    if(opCurrentItem != NULL) {
    	QString QSText = opCurrentItem->text(0);
    	QTreeWidgetItem* opTreeWidgetItemParent = opCurrentItem->parent();
    	if(opTreeWidgetItemParent != NULL) {
    		QString QSParent = opTreeWidgetItemParent->text(0);
    		if(QSParent == "Cars") {
    			// save car information
    			m_opDatabase->DeleteCar(QSText.toStdString());
    		} else if(QSParent == "Drivers") {
    			// load driver information
    			m_opDatabase->DeleteDriver(QSText.toStdString());
    		} else if(QSParent == "Tracks") {
    			// load track information
    		}
    	}
    }

    InitDatabaseTree();

}

void cDatabaseWindow::LoadDriverInformation(const cDatabaseDriver& i_oDriver)
{
    m_opMainWindow->lineEdit_DriverName->setText(i_oDriver.GetName().c_str());
    m_opMainWindow->label_DriverDrivingChampionships->setText(QString("%1").arg(i_oDriver.GetDrivingChampionships()));
    m_opMainWindow->label_DriverDrivingRaces->setText(QString("%1").arg(i_oDriver.GetDrivingRaces()));
    m_opMainWindow->label_DriverPoints->setText(QString("%1").arg(i_oDriver.GetPoints()));
    m_opMainWindow->label_DriverWonRaces->setText(QString("%1").arg(i_oDriver.GetWinRaces()));
    m_opMainWindow->label_DriverWonChampionships->setText(QString("%1").arg(i_oDriver.GetWinChampionships()));
}

void cDatabaseWindow::SaveDriverInformation(cDatabaseDriver& o_oDriver)
{
    o_oDriver.SetName(m_opMainWindow->lineEdit_DriverName->text().toStdString());
	o_oDriver.SetDrivingChampionships(m_opMainWindow->label_DriverDrivingChampionships->text().toInt());
	o_oDriver.SetDrivingRaces(m_opMainWindow->label_DriverDrivingRaces->text().toInt());
	o_oDriver.SetPoints(m_opMainWindow->label_DriverPoints->text().toInt());
	o_oDriver.SetWinRaces(m_opMainWindow->label_DriverWonRaces->text().toUInt());
	o_oDriver.SetWinChampionships(m_opMainWindow->label_DriverWonChampionships->text().toUInt());
}

void cDatabaseWindow::LoadCarInformation(const cDatabaseCar& i_oCar)
{
    m_opMainWindow->lineEdit_CarName->setText(i_oCar.GetName().c_str());
    m_opMainWindow->doubleSpinBox_CarTankCapacity->setValue(i_oCar.GetTankCapacity());
    m_opMainWindow->spinBox_Speed_0->setValue(i_oCar.GetSpeed(0));
    m_opMainWindow->spinBox_Speed_1->setValue(i_oCar.GetSpeed(1));
    m_opMainWindow->spinBox_Speed_2->setValue(i_oCar.GetSpeed(2));
    m_opMainWindow->spinBox_Speed_3->setValue(i_oCar.GetSpeed(3));
    m_opMainWindow->spinBox_Speed_4->setValue(i_oCar.GetSpeed(4));
    m_opMainWindow->spinBox_Speed_5->setValue(i_oCar.GetSpeed(5));
    m_opMainWindow->spinBox_Speed_6->setValue(i_oCar.GetSpeed(6));
    m_opMainWindow->spinBox_Speed_7->setValue(i_oCar.GetSpeed(7));
    m_opMainWindow->spinBox_Speed_8->setValue(i_oCar.GetSpeed(8));
    m_opMainWindow->spinBox_Speed_9->setValue(i_oCar.GetSpeed(9));
    m_opMainWindow->spinBox_Speed_10->setValue(i_oCar.GetSpeed(10));
    m_opMainWindow->spinBox_Speed_11->setValue(i_oCar.GetSpeed(11));
    m_opMainWindow->spinBox_Speed_12->setValue(i_oCar.GetSpeed(12));
    m_opMainWindow->spinBox_Speed_13->setValue(i_oCar.GetSpeed(13));
    m_opMainWindow->spinBox_Speed_14->setValue(i_oCar.GetSpeed(14));
    m_opMainWindow->spinBox_Speed_15->setValue(i_oCar.GetSpeed(15));

    m_opMainWindow->doubleSpinBox_Consumption_1->setValue( i_oCar.GetConsumption(1));
    m_opMainWindow->doubleSpinBox_Consumption_2->setValue( i_oCar.GetConsumption(2));
    m_opMainWindow->doubleSpinBox_Consumption_3->setValue( i_oCar.GetConsumption(3));
    m_opMainWindow->doubleSpinBox_Consumption_4->setValue( i_oCar.GetConsumption(4));
    m_opMainWindow->doubleSpinBox_Consumption_5->setValue( i_oCar.GetConsumption(5));
    m_opMainWindow->doubleSpinBox_Consumption_6->setValue( i_oCar.GetConsumption(6));
    m_opMainWindow->doubleSpinBox_Consumption_7->setValue( i_oCar.GetConsumption(7));
    m_opMainWindow->doubleSpinBox_Consumption_8->setValue( i_oCar.GetConsumption(8));
    m_opMainWindow->doubleSpinBox_Consumption_9->setValue( i_oCar.GetConsumption(9));
    m_opMainWindow->doubleSpinBox_Consumption_10->setValue(i_oCar.GetConsumption(10));
    m_opMainWindow->doubleSpinBox_Consumption_11->setValue(i_oCar.GetConsumption(11));
    m_opMainWindow->doubleSpinBox_Consumption_12->setValue(i_oCar.GetConsumption(12));
    m_opMainWindow->doubleSpinBox_Consumption_13->setValue(i_oCar.GetConsumption(13));
    m_opMainWindow->doubleSpinBox_Consumption_14->setValue(i_oCar.GetConsumption(14));
    m_opMainWindow->doubleSpinBox_Consumption_15->setValue(i_oCar.GetConsumption(15));
}

void cDatabaseWindow::SaveDatabaseItem()
{
    QTreeWidgetItem* opCurrentItem = m_opMainWindow->treeWidget_Database->currentItem();
    if(opCurrentItem != NULL) {
    	std::string QSText = opCurrentItem->text(0).toStdString();
    	QTreeWidgetItem* opTreeWidgetItemParent = opCurrentItem->parent();
    	if(opTreeWidgetItemParent != NULL) {
    		QString QSParent = opTreeWidgetItemParent->text(0);
    		if(QSParent == "Cars") {
    			// save car information
				m_opDatabase->DeleteCar(QSText);
				cDatabaseCar oCar("");
    			SaveCarInformation(oCar);
				m_opDatabase->UpdateCar(oCar);
    		} else if(QSParent == "Drivers") {
    			// load driver information
    			m_opDatabase->DeleteDriver(QSText);
				cDatabaseDriver oDriver("");
				SaveDriverInformation(oDriver);
				m_opDatabase->UpdateDriver(oDriver);    			
    		} else if(QSParent == "Tracks") {
    			// load track information
    		}
    	}
    }
    InitDatabaseTree();
}

void cDatabaseWindow::SaveCarInformation(cDatabaseCar& o_oCar)
{
    o_oCar.SetName(m_opMainWindow->lineEdit_CarName->text().toStdString());
    o_oCar.SetTankCapacity(m_opMainWindow->doubleSpinBox_CarTankCapacity->value());

    o_oCar.SetSpeed(0,  m_opMainWindow->spinBox_Speed_0->value());
    o_oCar.SetSpeed(1,  m_opMainWindow->spinBox_Speed_1->value());
    o_oCar.SetSpeed(2,  m_opMainWindow->spinBox_Speed_2->value());
    o_oCar.SetSpeed(3,  m_opMainWindow->spinBox_Speed_3->value());
    o_oCar.SetSpeed(4,  m_opMainWindow->spinBox_Speed_4->value());
    o_oCar.SetSpeed(5,  m_opMainWindow->spinBox_Speed_5->value());
    o_oCar.SetSpeed(6,  m_opMainWindow->spinBox_Speed_6->value());
    o_oCar.SetSpeed(7,  m_opMainWindow->spinBox_Speed_7->value());
    o_oCar.SetSpeed(8,  m_opMainWindow->spinBox_Speed_8->value());
    o_oCar.SetSpeed(9,  m_opMainWindow->spinBox_Speed_9->value());
    o_oCar.SetSpeed(10, m_opMainWindow->spinBox_Speed_10->value());
    o_oCar.SetSpeed(11, m_opMainWindow->spinBox_Speed_11->value());
    o_oCar.SetSpeed(12, m_opMainWindow->spinBox_Speed_12->value());
    o_oCar.SetSpeed(13, m_opMainWindow->spinBox_Speed_13->value());
    o_oCar.SetSpeed(14, m_opMainWindow->spinBox_Speed_14->value());
    o_oCar.SetSpeed(15, m_opMainWindow->spinBox_Speed_15->value());

    o_oCar.SetConsumption(1, m_opMainWindow->doubleSpinBox_Consumption_1->value());
    o_oCar.SetConsumption(2, m_opMainWindow->doubleSpinBox_Consumption_2->value());
    o_oCar.SetConsumption(3, m_opMainWindow->doubleSpinBox_Consumption_3->value());
    o_oCar.SetConsumption(4, m_opMainWindow->doubleSpinBox_Consumption_4->value());
    o_oCar.SetConsumption(5, m_opMainWindow->doubleSpinBox_Consumption_5->value());
    o_oCar.SetConsumption(6, m_opMainWindow->doubleSpinBox_Consumption_6->value()); 
    o_oCar.SetConsumption(7, m_opMainWindow->doubleSpinBox_Consumption_7->value());
    o_oCar.SetConsumption(8, m_opMainWindow->doubleSpinBox_Consumption_8->value());
    o_oCar.SetConsumption(9, m_opMainWindow->doubleSpinBox_Consumption_9->value());
    o_oCar.SetConsumption(10, m_opMainWindow->doubleSpinBox_Consumption_10->value());
    o_oCar.SetConsumption(11, m_opMainWindow->doubleSpinBox_Consumption_11->value());
    o_oCar.SetConsumption(12, m_opMainWindow->doubleSpinBox_Consumption_12->value());
    o_oCar.SetConsumption(13, m_opMainWindow->doubleSpinBox_Consumption_13->value());
    o_oCar.SetConsumption(14, m_opMainWindow->doubleSpinBox_Consumption_14->value());
    o_oCar.SetConsumption(15, m_opMainWindow->doubleSpinBox_Consumption_15->value());
}

