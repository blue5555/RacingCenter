#include "cFileWriter.h"

using namespace RacingCenter;

cFileWriter::cFileWriter() :
 m_opFile(NULL)
,m_opTextStream(NULL)
{

}

cFileWriter::~cFileWriter()
{
	Close();
}

tBool cFileWriter::Init(const std::string& i_strFileName)
{
	if(m_opFile == NULL)
	{
		m_opFile = new QFile(i_strFileName.c_str());
	}

	if(m_opFile->open(QIODevice::WriteOnly))
	{
		m_opTextStream = new QTextStream(m_opFile);
		return true;
	}
	else
	{
		return false;
	}
}

tBool cFileWriter::Close()
{
	if (m_opFile)
	{
		m_opFile->close();

		delete m_opFile;
		m_opFile = NULL;
	}
	if (m_opTextStream)
	{
		delete m_opTextStream;
		m_opTextStream = NULL;
	}

	return true;
}

tBool cFileWriter::WriteLine(const QString& i_oData)
{
	if(m_opTextStream)
	{
		*m_opTextStream << i_oData << "\n";
		return true;
	}
	else
	{
		return false;
	}
}

tBool cFileWriter::WriteLine(const QByteArray& i_oData)
{
	if(m_opTextStream)
	{
		*m_opTextStream << QString(i_oData) << "\n";
		return true;
	}
	else
	{
		return false;
	}
}