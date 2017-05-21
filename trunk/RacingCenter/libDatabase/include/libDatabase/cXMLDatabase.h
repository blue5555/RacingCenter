#ifndef cXMLDatabase_H
#define cXMLDatabase_H

#include "libCommon/stdafx.h"
#include "libCommon/cThing.h"
#include "libDatabase/cDatabase.h"
#include "QDomDocument"

namespace RacingCenter
{

class cXMLDatabase : public cThing
{
    QDomDocument m_oDomDocument;

    tBool           ReadDatabaseDrivers(const QDomElement& i_oElement, cDatabase* io_opDatabase );
    cDatabaseDriver ReadDriver(const QDomElement& i_oElement);

    tBool           SaveDatabaseDrivers(QDomElement& i_oDrivers, cDatabase* io_opDatabase);

    tBool           ReadDatabaseCars(const QDomElement& i_oElement, cDatabase* io_opDatabase );
    cDatabaseCar    ReadCar(const QDomElement& i_oElement);

    tBool           SaveDatabaseCars(QDomElement& i_oDrivers, cDatabase* io_opDatabase);


public:
    cXMLDatabase();
    ~cXMLDatabase();

    tBool ReadDatabase(cDatabase* i_opDatabase, const std::string& i_oFilePath);
    tBool SaveDatabase(cDatabase* i_opDatabase, const std::string& i_oFilePath);
};

}

#endif // cXMLDatabase_H