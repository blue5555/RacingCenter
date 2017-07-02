#include "libCore/cDataLogger.h"

using namespace RacingCenter;

cDataLogger::cDataLogger()
{

}

cDataLogger::~cDataLogger()
{

}

void cDataLogger::Init(const cRace* i_opRace)
{
	m_opRace = i_opRace;
	Clear();
}

void cDataLogger::Clear()
{
	m_bLogging = false;
	m_oDriverMessages.clear();
	m_oRoundFinish.clear();
}

void cDataLogger::StartLogging()
{
	m_bLogging = true;
}

void cDataLogger::StopLogging()
{
	m_bLogging = false;
}

void cDataLogger::AddRoundFinish(const sDriverMessage& i_oDriverMessage)
{
	if(m_bLogging)
	{
		m_oRoundFinish.push_back(i_oDriverMessage);
	}
}

void cDataLogger::AddDriverMessage(const sDriverMessage& i_oDriverMessage)
{
	if(m_bLogging)
	{
		m_oDriverMessages.push_back(i_oDriverMessage);
	}
}

cDatabaseRace cDataLogger::CreateDatabaseRace()
{
	return cDatabaseRace();
}