#include <cDatabaseBaseElement.h>

cDatabaseBaseElement::cDatabaseBaseElement(const std::string& i_strName) :
 m_strName(i_strName)
{

}

cDatabaseBaseElement::~cDatabaseBaseElement()
{

}

const std::string& cDatabaseBaseElement::GetName() const
{
    return m_strName;
}

tBool cDatabaseBaseElement::SetName(const std::string& i_strName)
{
    m_strName = i_strName;
    return true;
}

tBool cDatabaseBaseElement::AddColumn(std::string i_strColumnName, std::string i_strType)
{
	m_oDatabaseColumnsName.append(i_strColumnName.c_str());
	m_oDatabaseColumnsType.append(i_strType.c_str());

	return true;
}

const QStringList& cDatabaseBaseElement::GetColumnNames() const
{
	return m_oDatabaseColumnsName;
}

const QStringList& cDatabaseBaseElement::GetColumnType() const
{
	return m_oDatabaseColumnsType;
}
