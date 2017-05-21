#include <cCUAdapter.h>

#define _FILENAME_ "cCUAdapter: "

using namespace RacingCenter;

cCUAdapter::cCUAdapter(cQueue<sData>& i_oCUDataQueue) : 
 m_oCUDataQueue(i_oCUDataQueue)
,m_bSendProgrammWord(false)
,m_oSerialConnector(m_oRawDataQueue)
{
	m_bDebug = false;
	m_bDebugTiming = false;
	m_bInit = false;
}

cCUAdapter::~cCUAdapter()
{
	DeInit();
}

tBool cCUAdapter::Init(const tInt16& i_i16TimerIntervall, const cSerialportInfo& i_oSerialPortInfo, const tBool& i_bTestData)
{
	cConfig* opConfig = cConfig::instance();

	m_bDebug = opConfig->m_oDebugMessages.bCUAdapter;
	m_bDebugTiming = opConfig->m_oDebugMessagesTiming.bCUAdapter;

	m_i16TimerIntervall = i_i16TimerIntervall;
	m_oSerialPortInfo	= i_oSerialPortInfo;

	m_nErrorCounter = 0;

	if(m_bDebug)
	{
		m_oFileWriter.Init("C:/RacingCenter/CUAdatapterWords.txt");
	}

	m_oTempRawData.Clear();

	DEBUGMSG("Init CUAdaper");
	DEBUGMSG("Init SerialTimer:" << i_i16TimerIntervall);
	tInt16 iTimerConverter = i_i16TimerIntervall;
	DEBUGMSG("Init ConverterTimer:" << iTimerConverter);

	m_bTestData = i_bTestData;

	m_oRawDataQueue.clean();
	
	return m_oSerialConnector.Init(i_oSerialPortInfo);

}

tBool cCUAdapter::Clear()
{
	m_oRawDataQueue.clean();
	return true;
}

tBool cCUAdapter::DeInit()
{
	m_oSerialConnector.DeInit();

	m_oFileWriter.Close();
	m_oRawDataQueue.clean();

	return true;
}

cSerialConnector* cCUAdapter::GetSerialConnector()
{
	return &m_oSerialConnector;
}

QByteArray cCUAdapter::SendData(const eDataSource& i_eDataSOurce)
{
	QByteArray oData2Send;
	oData2Send.clear();

	oData2Send.append(34); // "

	switch(i_eDataSOurce)
	{
	case CU:
		oData2Send.append(63); // ?
		break;
	case ROUNDCOUNTER:
		//oData2Send.append(63); // ?
		break;
	case MIKROCONTROLLER:
		oData2Send.append(65); // A
		break;
	case STARTLIGHT:
		oData2Send.append(83); // A
		break;
	case CONTROLLER:
		oData2Send.append(82); // R
		break;
	case CU_VERSION:
		oData2Send.append(48);
		break;
	default:
		//return ERROR_SERIALPORT_NOT_SUPPORTED;
		break;
	}

	return oData2Send;
}

void cCUAdapter::CallControlUnit(const eDataSource i_eDataSource)
{
	if(m_bDebugTiming) 
    {
		tTimeStamp oTimeStamp = cTimeStamp::GetTimeStamp();
		qDebug() << _FILENAME_ << "TimeOut Serial: " << oTimeStamp; 
	}

	if(m_bTestData) 
    {
		sData oData = m_oTestGenerator.CreateDriverData(0);
		m_oCUDataQueue.push(oData);

        oData = m_oTestGenerator.CreateControllerData(0);
		m_oCUDataQueue.push(oData);
	} 
    else 
    {
	    m_oSerialConnector.SendData(SendData(i_eDataSource));
	}
}

const sData cCUAdapter::ProcessCUDriver(const cRawData& i_oRawData)
{
    sData oData(i_oRawData.GetTimeStamp(),DT_CU_DRIVER);
	
    sCUDriver oCUDriver(i_oRawData.GetByteArray().at(1) - 48 - 1,
						ConvertTimerValue(i_oRawData.GetByteArray()),
					    i_oRawData.GetByteArray().at(10) - 48);
	oData.oCUDriver = oCUDriver;

    return oData;
}

const tUInt32 cCUAdapter::ConvertTimerValue(const QByteArray& i_oData) const
{
	tUInt32 TimerValue = 0;
	for (tUInt8 i = 2; i < 10; i++)
	{
		TimerValue = TimerValue << 4;
		TimerValue |= (i_oData.at(i + 1) & 0x0F);
		TimerValue = TimerValue << 4;
		TimerValue |= (i_oData.at(i) & 0x0F);
		i++;
	}

	DEBUGMSG( "TimerValue: " << TimerValue );

	return TimerValue;
}

const sData cCUAdapter::ProcessCUWord(const cRawData& i_oRawData)
{
    sData oData(i_oRawData.GetTimeStamp(),DT_CU_WORD);

    const QByteArray& oRawData = i_oRawData.GetByteArray();

	sCUWord oCUWord;
	// TankLevel
	for (int i = 0; i < 6; i++) {
		oCUWord.m_oFuel[i] = oRawData.at(i+2) - 48;
	}

	// Startlight
	oCUWord.m_nStartLight = oRawData.at(10) - 48;

	// Fuelmode
	int iFuelMode = oRawData.at(11) - 48;
	if (iFuelMode > 11) {
		iFuelMode -= 12;
	} else if (iFuelMode > 7) {
		iFuelMode -= 8;
	} else if (iFuelMode > 3) {
		iFuelMode -= 4;
	}
	switch(iFuelMode) 
	{
		case 0:  oCUWord.m_eFuelMode = FUELMODE_OFF; break;
		case 1:  oCUWord.m_eFuelMode = FUELMODE_ON; break;
		case 2:  oCUWord.m_eFuelMode = FUELMODE_REAL; break;
		default: oCUWord.m_eFuelMode = FUELMODE_OFF; break;
	}

	// Which cars are in box ?
	// Driver 0-3
	for(int i = 0; i < 4; i++)
	{
		oCUWord.m_oIsInBox[i] = ((oRawData.at(12) >> i) & 1);
	}
	//Driver 4-5
	for(int i = 0; i < 2; i++)
	{
		oCUWord.m_oIsInBox[i+4] = ((oRawData.at(13) >> i) & 1);
	}

	oData.oCUWord = oCUWord;

	return oData;
}

const sData cCUAdapter::ProcessProgramData(const cRawData& i_oRawData)
{

	sData oData(i_oRawData.GetTimeStamp(), DT_CU_PROGRAM_WORD);
	const QByteArray& oRawData = i_oRawData.GetByteArray();

	oData.oProgramWord.nID      = oRawData.at(1) & 0x07;
	oData.oProgramWord.nValue   = oRawData.at(2) & 0x0F;
	oData.oProgramWord.nCommand = oRawData.at(3) & 0x1F;

	return oData;
}

const sData cCUAdapter::ProcessCUVersion(const cRawData& i_oRawData)
{
	sData oData(i_oRawData.GetTimeStamp(), DT_CU_VERSION);
	const QByteArray& oRawData = i_oRawData.GetByteArray();

	oData.nCUVersion = 0;

	return oData;
}

const sData cCUAdapter::ProcessControllerData(const cRawData& i_oRawData)
{
    sData oData(i_oRawData.GetTimeStamp(),DT_CONTROLLER);
    const QByteArray& oRawData = i_oRawData.GetByteArray();

	for(int iID = 0; iID < 6; iID++) 
    {
		sController oController;
		if (oRawData.at(iID) > 63 && oRawData.at(iID) < 127)
		{
			oController.m_ID     = iID;
			oController.m_Speed  = ((oRawData.at(iID) & 60) >> 2);
			oController.m_Button = !((oRawData.at(iID) &  2) >> 1);
			oController.m_Chaos  = (oRawData.at(iID) & 1);

			if(m_bDebug)
			{
				qDebug() << "Controller ID: " << oController.m_ID << "\tSpeed: " << oController.m_Speed << "\tButton: " << oController.m_Button << "\tChaos: " << oController.m_Chaos;
			}
		}
		oData.oController[iID] = oController;
	}

	return oData;
}

void cCUAdapter::ConvertRawData()
{
	qint64 iStart = 0;
	if(m_bDebugTiming) 
    {
		iStart = cTimeStamp::GetTimeStamp();
		qDebug() << _FILENAME_ << "Start Process: " << iStart;
	}

	//cRawData oTempRawData;
	while (!m_oRawDataQueue.isEmpty())
	{
		if(!m_oRawDataQueue.isEmpty())
		{
			cRawData oRawData = m_oRawDataQueue.pull();
			m_oTempRawData.MergeRawData(oRawData);

			tInt16 iIndex = m_oTempRawData.GetIndexOf("$");
			while(iIndex >=0 ) 
			{
				iIndex = m_oTempRawData.GetIndexOf("$");
				if (iIndex >= 0)
				{
                    cRawData oNewData = m_oTempRawData.SplitRawData(iIndex);
					m_oFileWriter.WriteLine(oNewData.GetByteArray());

					//tChar oCheckSumChar = CalculateCheckSum(oNewData.GetByteArray(),0);
					
					if (oNewData.GetRawDataLength() == 18)                 // CU Word
					{
						DEBUGMSG("Receive CU Word");
                        m_oCUDataQueue.push( ProcessCUWord(oNewData));
					}
					else if (oNewData.GetRawDataLength() == 12)           // CU Driver
					{
						DEBUGMSG("Receive CU Driver");
                        m_oCUDataQueue.push( ProcessCUDriver(oNewData));
					}
					else if (oNewData.GetRawDataLength() == 6)            // Controller Word
					{
						if(oNewData.GetByteArray().at(0) == 48)
						{
							DEBUGMSG("Receive CU Version");
							m_oCUDataQueue.push( ProcessCUVersion(oNewData) );
						}
						else
						{
							DEBUGMSG("Receive CU Controller");
							m_oCUDataQueue.push( ProcessControllerData(oNewData));
						}
					} 
					else if (oNewData.GetRawDataLength() == 1) // Feedback Program Word OK
					{
						qDebug() << _FILENAME_ << " Feedback Program Word";
						qDebug() << _FILENAME_ << "Receiving: " << oNewData.GetByteArray() << " ----";
					}
                    else if (oNewData.GetRawDataLength() == 4) // Program Word OK
					{
						m_oCUDataQueue.push( ProcessProgramData(oNewData));
						qDebug() << _FILENAME_ << " ProgrammWord OK";
						qDebug() << _FILENAME_ << "Receiving: " << oNewData.GetByteArray() << " ----";
					}
					else if (oNewData.GetRawDataLength() == 0)
                    {

					}
					else
					{
						m_nErrorCounter++;

						if (m_bDebug)
						{
							//m_oFileWriter.WriteLine(QString(m_nErrorCounter));
							//m_oFileWriter.WriteLine(oNewData.GetByteArray());
						}

						qDebug() << _FILENAME_ << "---- Error: Unknown Length: " << oNewData.GetRawDataLength() << " ----";
						qDebug() << _FILENAME_ << "Receiving: " << oNewData.GetByteArray() << " ----";
						qDebug() << _FILENAME_ << "ErrorCounter: " << m_nErrorCounter; 

					}
				} 
			}
		} 
	}

	if(m_bDebugTiming) {
		qint64 iEnd = cTimeStamp::GetTimeStamp();
		qDebug() << _FILENAME_ << "End Process: " << iEnd;
		qDebug() << _FILENAME_ << "Delta: " << (iEnd -iStart);
	}
}

void cCUAdapter::SendProgrammWord(const tInt8 i_iController, const tInt8 i_iProgrammWord, const tInt8 i_iValue)
{

	QByteArray SendCommandToCU(8,0);
	//SendCommandToCU.resize(8);

	SendCommandToCU[0] = 34; // "
	SendCommandToCU[1] = 74; // J    

	tChar A = (i_iProgrammWord & 0x0F);
	A += 48;
	SendCommandToCU[2] = A; // A

	tChar B = (i_iController & 0x07) << 1;
	B |= (i_iProgrammWord & 0x10) >> 5;
	B += 48;

	SendCommandToCU[3] = B; // B

	SendCommandToCU[4] = (i_iValue + 48); // value

	tChar repeats = 1;
	SendCommandToCU[5] = (repeats + 48); // repeats

	SendCommandToCU[6] = CalculateCheckSum(SendCommandToCU, 2); // checksum

	SendCommandToCU[7] = 36; // $

	//switch(i_iProgrammWord) 
	//{
	//case 0:
	//case 1:
	//case 2:
	//	m_oSerialSendDataPrio1.push(SendCommandToCU);
	//	break;
	//case 4:
	//	m_oSerialSendDataPrio2.push(SendCommandToCU);
	//	break;
	//}

	m_oSerialConnector.SendData(SendCommandToCU);

}

void cCUAdapter::SendShortProgrammWord(const tInt8 i_iController, const tInt8 i_iProgrammWord, const tInt8 i_iValue)
{
	QByteArray SendCommandToCU; //(5,0);
	//SendCommandToCU.resize(8);

	SendCommandToCU[0] = 34; // "
	SendCommandToCU[1] = 80; // P    

	tChar A  = (i_iProgrammWord & 0x1F);
	      A |= 64;
	SendCommandToCU[2] = A;

	tChar B  = i_iValue;
		  B |= 64;
	SendCommandToCU[3] = B; // B

	tChar C  = (i_iController & 0x07);
		  C |= 64;
	SendCommandToCU[4] = C; // B

	SendCommandToCU[5] = 36; // $

	m_bSendProgrammWord = true;

	m_oSerialConnector.SendData(SendCommandToCU);
}

const tUInt16 cCUAdapter::CalculateCheckSum(const QByteArray& i_oWord, int i_iOffset) const
{
	tUInt16 checksum = 0;
	for (tUInt16 i = i_iOffset; i < i_oWord.size() - 1; i++)
	{
		checksum += (i_oWord[i] & 0x0F);
	}

	checksum = checksum & 0x0F;
	checksum += 48;

	return checksum;
}

void cCUAdapter::ActivateChaos()
{
	string strText = "\"S0$";
	m_oSerialConnector.SendData(strText);
}

void cCUAdapter::DeactivateChaos()
{
	string strText = "\"S1$";
	m_oSerialConnector.SendData(strText);
}
