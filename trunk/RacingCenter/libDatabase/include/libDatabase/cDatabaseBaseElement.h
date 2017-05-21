#ifndef cDatabaseBaseElement_H
#define cDatabaseBaseElement_H

#include <libCommon/stdafx.h>

class cDatabaseBaseElement
{

protected:
	std::string     	m_strName;

public:
	cDatabaseBaseElement(const std::string& i_strName = "");
    ~cDatabaseBaseElement();

    const std::string& GetName() const;
    tBool SetName(const std::string& i_strName);

};

#endif