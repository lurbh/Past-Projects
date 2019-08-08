/******************************************************************************/
/*!
\file_name        AudioEngine.cpp
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This File contains the implementation for the Sound System

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "AudioEngine.h"
#include "../Defines/AllUtilities.h"
#include <iostream>
#include <string>

namespace sound
{
/******************************************************************************/
/*!
  Function to Initilise the Sound System
*/
/******************************************************************************/
void C_SoundSystem::Init()
{
  int n_noofdrivers;
  // Creates the sound system
  if (FMOD::System_Create(&p_SoundSystem) != FMOD_OK)
  {
    // Report Error if any
    std::cout << "error" << std::endl;
    return;
  }
  // Checks for the amount of drivers available
  p_SoundSystem->getNumDrivers(&n_noofdrivers);
  if (n_noofdrivers == 0)
  {
    // No sound output if no drivers found
    p_SoundSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
  }
  // Initilises the channels for he system
  p_SoundSystem->init(MAXNOOFCHANNELS, FMOD_INIT_NORMAL, 0);
  // Creates channel main, background and soundeffect channel group
  p_SoundSystem->createChannelGroup("SoundSystem", &p_MainChannel);
  p_SoundSystem->createChannelGroup("BG", &p_BGMChannel);
  p_SoundSystem->createChannelGroup("SFX", &p_SFXChannel);
  // Set background and soundeffect channel group 
  // to be under main channel group
  p_MainChannel->addGroup(p_BGMChannel);
  p_MainChannel->addGroup(p_SFXChannel);
  // Create a Channel group for each channel and place them in a map of 
  // channel groups
  for (unsigned i = 0; i < MAXNOOFCHANNELS; ++i)
  {
    FMOD::ChannelGroup * p_channel;
    std::string name;
    name.push_back(static_cast<char>(i));
    // Create a channel group for each channel
    p_SoundSystem->createChannelGroup(name.c_str(), &p_channel);
    // Insert the channal group with thr channel number as the key
    m_channel.insert(std::pair<unsigned, FMOD::ChannelGroup *>(i, p_channel));
  }
}

/******************************************************************************/
/*!
  Function to release the Sound System
*/
/******************************************************************************/
void C_SoundSystem::Release_System()
{
  // CLears all the sound files that was loaded
  ClearAllSound();
  // Releases all the channels group for the channel
  for (unsigned i = 0; i < MAXNOOFCHANNELS; ++i)
  {
    FMOD::ChannelGroup * p_channel;
    p_channel = m_channel.find(i)->second;
    p_channel->release();
  }
  // Clears the map of channel group
  m_channel.clear();
  // Deletes all the Game sound created
  for (auto & elem : m_game_sound)
    delete elem;
  // Clears the vector of game sound
  m_game_sound.clear();

  // Release main, background and soundeffect channel group
  p_MainChannel->release();
  p_BGMChannel->release();
  p_SFXChannel->release();
  // Release the sound system
  p_SoundSystem->release();
}

/******************************************************************************/
/*!
  Function to stop all sounds playing in the Sound System
*/
/******************************************************************************/
void C_SoundSystem::Stop_All_Sounds()
{
  // Stop all channels
  p_MainChannel->stop();
}

/******************************************************************************/
/*!
  Function to update the Sound System
*/
/******************************************************************************/
void C_SoundSystem::Update(void)
{
  // Update the sound system
  p_SoundSystem->update();
}

/******************************************************************************/
/*!
  Function to Create Game Sound
*/
/******************************************************************************/
void C_SoundSystem::Create_Sound(const char * p_soundfilename, 
SOUNDTYPE soundtype, CHANNELGROUP channelgroup, std::string p_soundname)
{
  p_SoundClass p_sound = nullptr;
  // Creates the Game sound
  if (p_SoundSystem->createSound(p_soundfilename, FMOD_DEFAULT, 0, &p_sound) 
    != FMOD_OK)
  {
    // Reports error if game sound creation fails
    std::cout << "errorsound" << std::endl;
    return;
  }
  // Places the Game sound into the Vector of game sound
  m_game_sound.push_back
  (new C_Sound(p_sound, p_soundname, soundtype, channelgroup));
}

/******************************************************************************/
/*!
  Function to find Game Sound
*/
/******************************************************************************/
C_Sound * C_SoundSystem::Find_Sound(std::string name)
{
  // Transverse the vector of game sound
  for (auto &it : m_game_sound)
  {
    // Finds the Game sound that matches with the given name
    if (it->GetName() == name)
      return it;
  }
  return nullptr;
}

/******************************************************************************/
/*!
  Function to Play the Game Sound
*/
/******************************************************************************/
void C_SoundSystem::Play_Sound(std::string p_soundname, float vol, 
int channel, bool b_loop)
{
  FMOD::ChannelGroup * p_channelgroup;
  FMOD::Channel * p_channel;
  C_Sound * gamesound = Find_Sound(p_soundname);
  bool playing, mute = false;
  // Check if Sound is to be played
  if (!utilities::C_OptionsManager::Get_SoundFX())
    mute = true;

  // Set sound to loop if sound is to loop
  if (b_loop)
  {
    gamesound->GetSound()->setMode(FMOD_LOOP_NORMAL);
    gamesound->GetSound()->setLoopCount(-1);
  }
  // Gets the channel and channel group
  p_SoundSystem->getChannel(channel, &p_channel);
  p_channelgroup = m_channel.find(channel)->second;
  // Check if the channel is playing
  p_channelgroup->isPlaying(&playing);
  // If channel is playing find the next channel that is not playing
  if (playing)
    for (int i = 50; i < MAXNOOFCHANNELS; ++i)
    {
      p_SoundSystem->getChannel(i, &p_channel);
      p_channelgroup = m_channel.find(channel)->second;
      p_channel->isPlaying(&playing);
      if (!playing)
        break;
    }
  // Set which parent channel for the game sound
  switch (gamesound->GetType())
  {
  /*  For each case
      Set the channel group
      Play the sound
      Set the volume         */
  case BACKGROUND:
    p_channel->setChannelGroup(p_BGMChannel);
    p_BGMChannel->addGroup(p_channelgroup);
    p_SoundSystem->playSound
    (gamesound->GetSound(), p_channelgroup, false, &p_channel);
    p_channel->setVolume(vol);
    break;
  case SOUNDEFFECT:
    p_channel->setChannelGroup(p_SFXChannel);
    p_SFXChannel->addGroup(p_channelgroup);
    p_SoundSystem->playSound
    (gamesound->GetSound(), p_channelgroup, false, &p_channel);
    p_channel->setVolume(vol);
    break;
  case SOUNDEFFECTP:
    p_channel->setChannelGroup(p_SFXChannel);
    p_SFXChannel->addGroup(p_channelgroup);
    p_SoundSystem->playSound
    (gamesound->GetSound(), p_channelgroup, false, &p_channel);
    p_channel->setVolume(vol);
    break;
  case SOUNDEFFECTE:
    p_channel->setChannelGroup(p_SFXChannel);
    p_SFXChannel->addGroup(p_channelgroup);
    p_SoundSystem->playSound
    (gamesound->GetSound(), p_channelgroup, false, &p_channel);
    p_channel->setVolume(vol);
    break;
  }
  // Mute the sound if sound is not to be played
  p_MainChannel->setMute(mute);
}

/******************************************************************************/
/*!
  Function to Pause a selected channel
*/
/******************************************************************************/
void C_SoundSystem::Pause_Unpause_Channel(int channel)
{
  bool b_pause;
  FMOD::ChannelGroup * p_channel;
  // Finds the selected channel
  p_channel = m_channel.find(channel)->second;
  // Check if channel is playing
  p_channel->getPaused(&b_pause);
  // Pause if playing and unpause if not
  p_channel->setPaused(!b_pause);
}

/******************************************************************************/
/*!
  Function to Stop a selected channel
*/
/******************************************************************************/
void C_SoundSystem::Stop_Channel(int channel)
{
  FMOD::ChannelGroup * p_channel;
  // Finds the selected channel
  p_channel = m_channel.find(channel)->second;
  // Stops the selected channel
  p_channel->stop();
}

/******************************************************************************/
/*!
  Function to Stop a selected channel group
*/
/******************************************************************************/
void C_SoundSystem::Stop_Channel_Group(CHANNELGROUP cg_channel)
{
  FMOD::ChannelGroup * p_channelgroup;
  // Set the channel group based on selected channel group
  switch (cg_channel)
  {
  case BGM:
    p_channelgroup = p_BGMChannel;
    break;
  case SFX:
    p_channelgroup = p_SFXChannel;
    break;
  default:
    p_channelgroup = p_MainChannel;
    break;
  }
  // Stop the channel group
  p_channelgroup->stop();
}

/******************************************************************************/
/*!
  Function to Pause a selected channel group
*/
/******************************************************************************/
void C_SoundSystem::Pause_Unpause_Sound(CHANNELGROUP cg_channel)
{
  bool b_pause;
  FMOD::ChannelGroup * p_channelgroup;
  // Set the channel group based on selected channel group
  switch (cg_channel)
  {
  case BGM:
    p_channelgroup = p_BGMChannel;
    break;
  case SFX:
    p_channelgroup = p_SFXChannel;
    break;
  default:
    p_channelgroup = p_MainChannel;
    break;
  }
  // Check if channel is playing
  p_channelgroup->getPaused(&b_pause);
  // Pause if playing and unpause if not
  p_channelgroup->setPaused(!b_pause);
}

/******************************************************************************/
/*!
  Function to Adjust the volume of a selected channel group
*/
/******************************************************************************/
void C_SoundSystem::Adjust_Volume
(float vol, bool b_mute, CHANNELGROUP cg_channel)
{
  FMOD::ChannelGroup * p_channelgroup;
  // Set the channel group based on selected channel group
  switch (cg_channel)
  {
  case BGM:
    p_channelgroup = p_BGMChannel;
    break;
  case SFX:
    p_channelgroup = p_SFXChannel;
    break;
  default:
    p_channelgroup = p_MainChannel;
    break;
  }
  // Mute or unmute channel group
  if (b_mute)
  {
    bool mute;
    p_channelgroup->getMute(&mute);
    p_channelgroup->setMute(!mute);
  }
  else
    // Set channel group volume
    p_channelgroup->setVolume(vol);
}

/******************************************************************************/
/*!
  Function to Mute all channels
*/
/******************************************************************************/
void C_SoundSystem::MuteAllChannel()
{
  //  Mutes the main channel
  p_MainChannel->setMute(true);
}

/******************************************************************************/
/*!
  Function to Unmute all channels
*/
/******************************************************************************/
void C_SoundSystem::UnmuteAllChannel()
{
  //  Unmute the main channel
  p_MainChannel->setMute(false);
}

/******************************************************************************/
/*!
  Function to Release a selected game sound
*/
/******************************************************************************/
void C_SoundSystem::Release_Sound(std::string p_soundfilemane)
{
  // Find the game sound
  C_Sound * Remove = Find_Sound(p_soundfilemane);
  // Release the game sound
  Remove->GetSound()->release();
}

/******************************************************************************/
/*!
  Function to Release a all game sound
*/
/******************************************************************************/
void C_SoundSystem::ClearAllSound()
{
  // Transverse the vector of game sound
  for (auto &it : m_game_sound)
  {
    // Release game sound
    it->GetSound()->release();
  }
}
}