#ifndef cDataLogger_H
#define cDataLogger_H

#include "libCommon/stdafx.h"
#include "libDataCore/cRace.h"

namespace RacingCenter
{

class cDataLogger
{
	const cRace* m_opRace;
	map<tUInt, vector<sDriverMessage> > m_oDriverMessages;

	tBool m_bLogging;

public:
	cDataLogger();
	~cDataLogger();

	void Init(const cRace* i_opRace);
	void Clear();

	void AddMessage(const sDriverMessage& i_oDriverMessage);

	cDatabaseRace CreateDatabaseRace();

	void StartLogging();
	void StopLogging();

};

}

#endif  // cSound_H