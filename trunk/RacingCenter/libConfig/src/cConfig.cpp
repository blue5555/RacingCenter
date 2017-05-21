#include "cConfig.h"
#include "cXMLConfig.h"

#define _FILENAME_ "cConfig: "
#define CONFIG_NAME "/config.xml"

cConfig* cConfig::m_opConfig = NULL;

void cConfig::Init()
{
    m_nMinorVersion = 0;
    m_nMajorVersion = 1;

    m_strDefaultPath = "";

	m_oRaceDisplayConfig.Init();
	m_oRaceConfig.Init();
	m_oFuelConfig.Init();

	m_oDebugMessages.Init();
	m_oDebugMessagesTiming.Init();
	m_oPenalty.Init();

	m_oRaceConfig.bBlinkCar = false;

	m_bDebug = true;
}

tBool cConfig::LoadConfig(const std::string& i_oConfigPath)
{
    if(i_oConfigPath == "")
	{
    }
    else
    {
        m_strDefaultPath = i_oConfigPath;
    }

	cXMLConfig oXMLConfig;
	return oXMLConfig.ReadConfig(this, m_strDefaultPath + CONFIG_NAME);

}

tBool cConfig::SaveConfig(const std::string& i_oConfigPath)
{
    if(i_oConfigPath == "")
    {

    }
    else
    {
        m_strDefaultPath = i_oConfigPath;
    }

	cXMLConfig oXMLConfig;
    return oXMLConfig.SaveConfig(this, m_strDefaultPath + CONFIG_NAME);

}