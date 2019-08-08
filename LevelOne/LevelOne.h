/******************************************************************************/
/*!
\file_name        LevelOne.h
\project_name     Double Tap
\primary_author   Ma Ming Shun, mingshun.ma, 440002516
\brief
This file contains the decleration for Level one.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/

#pragma once

#include "../Level/Level.h"
#include "../Utilities/CameraEvents.h"

const int LevelOneWidth = 200;
const int LevelOneHeight = 50;

// LevelSplash should not be inherited anymore
class C_LevelOne final : public level::C_Level<LevelOneWidth, LevelOneHeight>
{
	void Update_HUD();
	int BossWaveCount = 0;
	int BossShootCount = 0;
public:
	int m_player_life;
	bool cameralock;

	object::C_GameObject *mp_health;
	object::C_GameObject *mp_health_indicator;
	object::C_GameObject *mp_life_hud[PLAYER_MAX_HEALTH];

	object::C_GameObject *mp_gun_hud;
	object::C_GameObject *mp_ammo_min_text;
	object::C_GameObject *mp_ammo_max_text;
	object::C_GameObject *mp_ammo_divider;
	unsigned int m_ammo_min_font;
	unsigned int m_ammo_max_font;

	object::C_GameObject *mp_menu_box;
	object::C_GameObject *mp_menu_header;
	object::C_GameObject *mp_resume_button;
	object::C_GameObject *mp_howtoplay_button;
	object::C_GameObject *mp_options_button;
	object::C_GameObject *mp_restart_button;
	object::C_GameObject *mp_credits_button;
	object::C_GameObject *mp_quit_button;
	bool m_menu_active;

	object::C_GameObject *mp_howtoplay_box;
	object::C_GameObject *mp_howtoplay_header;
	object::C_GameObject *mp_shoot_key;
	object::C_GameObject *mp_move_key;
	object::C_GameObject *mp_jump_key;
	object::C_GameObject *mp_howtoplay_esc;
	bool m_howtoplay_active;

	object::C_GameObject *mp_options_box;
	object::C_GameObject *mp_options_header;
	object::C_GameObject *mp_fullscreen_button;
	object::C_GameObject *mp_fullscreen_selector;
	object::C_GameObject *mp_soundfx_button;
	object::C_GameObject *mp_soundfx_selector;
	object::C_GameObject *mp_options_back;
	bool m_options_active;

	object::C_GameObject *mp_credits_box;
	object::C_GameObject *mp_credits_esc;
	bool m_credits_active;

	object::C_GameObject *mp_confirmation_box;
	object::C_GameObject *mp_confirmation_header;
	object::C_GameObject *mp_yes_button;
	object::C_GameObject *mp_no_button;
	bool m_confirmation_active;

	object::C_GameObject *mp_win_box;
	object::C_GameObject *mp_win_header;
	object::C_GameObject *mp_continue;
	bool m_win_active;

	object::C_GameObject *mp_lose_box;
	object::C_GameObject *mp_lose_header;
	object::C_GameObject *mp_lose_yes_button;
	object::C_GameObject *mp_lose_no_button;
	bool m_lose_active;

	object::C_GameObject *mp_rain_particle_prefab;
	object::C_GameObject *mp_rain_particlesys;

	object::C_GameObject *mp_smoke_particle_prefab;
	object::C_ParticleSystem *mp_smoke_particlesys;
	object::C_GameObject *mp_smoke_particleobj;

	object::C_GameObject *mp_spit_particle_prefab;
	object::C_ParticleSystem *mp_spit_particlesys;
	object::C_GameObject *mp_spit_particleobj;

	object::C_GameObject *mp_pickup_particle_prefab;
	object::C_GameObject *mp_pickup_particleobj;

	object::C_GameObject *mp_checkpoint;

	int &GetBossWaveCount();
	int &GetBossShootCount();

	// Overrides the virtual functions of the C_Level Base Class
	void Load() override;
	void Init() override;
	void Update() override;
	void Draw() override;
	void Free() override;
	void Unload() override;

	// Overrides the Clone function of the base class
	// Returns a pointer to a user defined level object
	// DOUBT IT WILL BE USED EVER
	// Syntax is <CLASS NAME OF YOUR LEVEL> * <Clone()> <override modifier>
	virtual C_LevelOne *Clone() const override;

	virtual C_LevelOne *Actual() const override;
};