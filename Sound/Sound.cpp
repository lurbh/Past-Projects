/******************************************************************************/
/*!
\file_name        Sound.cpp
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This File contains the implementation for the Game Sound

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "AudioEngine.h"

namespace sound
{
/******************************************************************************/
/*!
  Non-Default Constructor for C_Sound
*/
/******************************************************************************/
C_Sound::C_Sound(p_SoundClass p_sound, std::string name , 
SOUNDTYPE soundtype, CHANNELGROUP channelgroup)
  : mp_Sound{ p_sound }, m_type{ soundtype }
  , m_group{ channelgroup }, m_name{ name }
{

}

/******************************************************************************/
/*!
  Function to get sound from game sound
*/
/******************************************************************************/
p_SoundClass C_Sound::GetSound() const
{
  return mp_Sound;
}

/******************************************************************************/
/*!
  Function to get name from game sound
*/
/******************************************************************************/
std::string C_Sound::GetName() const
{
  return m_name;
}

/******************************************************************************/
/*!
  Function to get type from game sound
*/
/******************************************************************************/
SOUNDTYPE C_Sound::GetType() const
{
  return m_type;
}

/******************************************************************************/
/*!
  Function to get channal group from game sound
*/
/******************************************************************************/
CHANNELGROUP C_Sound::GetChannel() const
{
  return m_group;
}
}

