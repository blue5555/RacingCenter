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