#include "libCore/cSound.h"

cSound* cSound::m_opSound = NULL;

void cSound::addSound(eSoundType i_eSoundType, tUInt i_nID)
{
	m_opPlayer->setPlaylist(m_opPlaylist);
	switch(i_eSoundType)
	{
	case SOUND_LAP:
		m_opPlaylist->addMedia(QUrl::fromLocalFile("C:/RacingCenter/sounds/bestlap.wav"));
		break;
	case SOUND_BEST_LAP:
		m_opPlaylist->addMedia(QUrl::fromLocalFile("C:/RacingCenter/sounds/bestlap.wav"));
		break;
	}
	//m_opPlayer->setVolume(50);
	m_opPlayer->play();
}

void cSound::playSound(const std::string& i_strFileName)
{
	m_opPlayer->setMedia(QUrl::fromLocalFile(i_strFileName.c_str()));
	m_opPlayer->setVolume(50);
	m_opPlayer->play();
	qDebug() << m_opPlayer->errorString();
}