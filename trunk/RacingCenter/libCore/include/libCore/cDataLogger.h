#ifndef cDataLogger_H
#define cDataLogger_H

#include "libCommon/stdafx.h"
#include "libDataCore/cRace.h"

namespace RacingCenter
{

class cDataLogger
{
	const cRace*			m_opRace;
	vector<sDriverMessage>	m_oDriverMessages;
	vector<sDriverMessage>  m_oRoundFinish;

	tBool m_bLogging;

public:
	cDataLogger();
	~cDataLogger();

	void Init(const cRace* i_opRace);
	void Clear();

	void AddRoundFinish(const sDriverMessage& i_oDriverMessage);
	void AddDriverMessage(const sDriverMessage& i_oDriverMessage);

	cDatabaseRace CreateDatabaseRace();

	void StartLogging();
	void StopLogging();

};

}

#endif  // cSound_H