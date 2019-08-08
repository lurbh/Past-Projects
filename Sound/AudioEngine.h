/******************************************************************************/
/*!
\file_name        AudioEngine.h
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This File contains the declaration for the Sound System

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "../Defines/SoundDefines.h"
#include <vector>
#include <map>

namespace sound
{
/******************************************************************************/
/*!
  Class the Stores the data for an instance of game sound
*/
/******************************************************************************/
class C_Sound
{
  p_SoundClass mp_Sound;
  SOUNDTYPE m_type;
  CHANNELGROUP m_group;
  std::string m_name;
public:
  C_Sound(p_SoundClass p_sound, std::string name, 
  SOUNDTYPE soundtype, CHANNELGROUP channelgroup);
  p_SoundClass GetSound() const;
  std::string GetName() const;
  SOUNDTYPE GetType() const;
  CHANNELGROUP GetChannel() const;
};

/******************************************************************************/
/*!
  Class the implements an instance of sound system
*/
/******************************************************************************/
class C_SoundSystem
{
  FMOD::System *p_SoundSystem;
  FMOD::ChannelGroup *p_MainChannel, *p_BGMChannel, *p_SFXChannel;
  std::vector<C_Sound*> m_game_sound;
  std::map<unsigned, FMOD::ChannelGroup *> m_channel;
public:
  void Init();
  void Release_System();
  void Stop_All_Sounds();
  void Update(void);
  void Create_Sound(const char *  p_soundfilename, SOUNDTYPE soundtype, 
  CHANNELGROUP channelgroup, std::string p_soundname);
  C_Sound * Find_Sound(std::string name);
  void Play_Sound(std::string p_soundfilemane, float vol = 0.50f, 
  int channel = 50, bool b_loop = false);
  void Pause_Unpause_Channel(int channel);
  void Stop_Channel(int channel);
  void Stop_Channel_Group(CHANNELGROUP cg_channel);
  void Pause_Unpause_Sound(CHANNELGROUP cg_channel);
  void Adjust_Volume(float vol, bool b_mute, CHANNELGROUP cg_channel);
  void MuteAllChannel();
  void UnmuteAllChannel();
  void Release_Sound(std::string p_soundfilemane);
  void ClearAllSound();
};
}