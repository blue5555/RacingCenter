#ifndef cXMLConfig_H
#define cXMLConfig_H

#include "libCommon/stdafx.h"
#include "libCommon/cThing.h"
#include "cConfig.h"
#include "QDomDocument"

class cXMLConfig : public cThing
{
    QDomDocument m_oDomDocument;

    tBool ReadRaceConfig(const QDomElement& i_oElement, sRaceConfig& io_oRaceConfig );
    tBool SaveRaceConfig(QDomElement& io_oElement, const sRaceConfig& i_oRaceConfig );

	tBool ReadCOMConfig(const QDomElement& io_oElement, cSerialportInfo& i_oCOMConfig );
	tBool SaveCOMConfig(QDomElement& io_oElement, const cSerialportInfo& i_oCOMConfig );

	tBool ReadRaceDisplayConfig(const QDomElement& io_oElement, sRaceDisplayConfig& i_oCOMConfig );
	tBool SaveRaceDisplayConfig(QDomElement& io_oElement, const sRaceDisplayConfig& i_oCOMConfig );

	tBool ReadFuelConfig(const QDomElement& io_oElement, sFuelConfig& i_oFuelConfig );
	tBool SaveFuelConfig(QDomElement& io_oElement, const sFuelConfig& i_oFuelConfig );

public:
    cXMLConfig();
    ~cXMLConfig();

    tBool ReadConfig(cConfig* i_opConfig, const std::string& i_strFileName);
    tBool SaveConfig(cConfig* i_opConfig, const std::string& i_strFileName);
};


#endif // cXMLConfig_H