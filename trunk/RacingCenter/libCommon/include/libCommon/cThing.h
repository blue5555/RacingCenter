#ifndef cThing_H
#define cThing_H

#include <libCommon/stdafx.h>

#define DEBUGMSG(msg) if(m_bDebug) {qDebug() << _FILENAME_ <<  msg;}
#define DEBUGWARNING(msg) if(m_bDebug) {qWarning() << _FILENAME_ << msg;}
#define DEBUGERROR(msg) if(m_bDebug) {qDebug() << "Error: " << _FILENAME_ << msg;}

#define DEBUGMSGTIMING(msg) if(m_bDebugTiming) {qDebug() << _FILENAME_ <<  msg;}

class cThing
{
private:

protected:
    tBool	m_bDebug;
    tBool	m_bDebugTiming;

public:
		cThing(tBool i_bDebug = false, tBool i_bDebugTiming = false) 
        {
			m_bDebug = i_bDebug;
			m_bDebugTiming = i_bDebugTiming;
		};
		~cThing() {};


};

#endif // cThing_H