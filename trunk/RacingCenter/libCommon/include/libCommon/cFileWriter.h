#ifndef cFileWriter_H
#define cFileWriter_H

#include "stdafx.h"

namespace RacingCenter
{

class cFileWriter
{
	QFile*		 m_opFile;
	QTextStream* m_opTextStream;

public:
	cFileWriter();
	~cFileWriter();

	tBool Init(const std::string& i_strFileName);
	tBool Close();

	tBool WriteLine(const QByteArray& i_oData);
	tBool WriteLine(const QString& i_oData);


};

}

#endif // cFileWriter_H