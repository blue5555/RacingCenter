#ifndef sController_H
#define sController_H

#include <libCommon/stdafx.h>

struct sController
{
	tUInt8 m_nSpeed;
	tUInt8 m_nTank;
	tBool  m_bLaneChange;

	sController();
	~sController();

};

#endif //sController_H