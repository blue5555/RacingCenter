#ifndef cDatabaseBaseElement_H
#define cDatabaseBaseElement_H

#include <libCommon/stdafx.h>

class cDatabaseBaseElement
{

protected:
	std::string     	m_strName;
	QStringList m_oDatabaseColumnsName;
	QStringList m_oDatabaseColumnsType;

	tBool AddColumn(std::string i_strColumnName, std::string i_strType);

public:
	cDatabaseBaseElement(const std::string& i_strName = "");
    ~cDatabaseBaseElement();

    const std::string& GetName() const;
    tBool SetName(const std::string& i_strName);

	const QStringList& GetColumnNames() const;
	const QStringList& GetColumnType() const;


};

#endif