
#ifndef cSound_H
#define cSound_H

#include "libCommon/stdafx.h"
#include "QtMultimedia/QMediaPlayer"
#include "QtMultimedia/QSound"
#include "QtMultimedia/QMediaPlaylist"

class cSound
{
public:

	static cSound* instance()      
	{                 
		if(m_opSound == NULL) {
			m_opSound = new cSound();
		}
		return m_opSound;         
	}

	enum eSoundType
	{
		SOUND_BEST_LAP,
		SOUND_FINAL_LAP,
		SOUND_LAP,
		SOUND_LEADER,
		SOUND_LEADER_LAP,
		SOUND_RACE_OVER
	};

	void addSound(eSoundType i_eSoundType, tUInt i_nID = 0);
	void playSound(const std::string& i_strFileName);

protected:

private:
	cSound() 
	{
		m_opPlayer = new QMediaPlayer();
		m_opPlaylist = new QMediaPlaylist();
	};

	~cSound() 
	{ 
		if(m_opPlayer != NULL) {
			delete m_opPlayer;
			delete m_opPlaylist;
		}
	};

	static cSound* m_opSound;

	QMediaPlayer* m_opPlayer; //= new QMediaPlayer;
	QMediaPlaylist* m_opPlaylist; // = new QMediaPlaylist(player);
};

#endif  // cSound_H