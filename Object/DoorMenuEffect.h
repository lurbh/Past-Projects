/******************************************************************************/
/*!
\file_name      DoorMenuEffect.h
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains the declarations of the Game Object class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "../Events/EventDispatcher.h"  // EventDispatcher
#include "../Object/GameObject.h"       // Game Object class

namespace object
{
class C_DoorMenuEffect : public C_Component
{
	C_Sprite *mp_sprite;                    // Sprite of the object
	C_Transform *mp_transform;              // Transform of the object
	C_Transform *mp_particlesys_transform;  // Transform of the particle system
	C_Transform *mp_enter_key_transform;    // Transform of the enter sprite

	std::string m_normal;                   // The normal sprite for title
	std::string m_glow;                     // The glow sprite for title
	std::string m_next_level;               // The next level to dispatch

	double m_elapsed = 0.2;                 // Time of last collision started

	bool m_is_glow;                         // Bool to check if title is glowing

	void Normal();                          // Function to call in normal state

public:
	// Non-default constructor
	C_DoorMenuEffect(C_GameObject *p_obj);

	// Connect all events
	void Connect();

	// Update function of the Door Menu Effect components
	void Update() override;

	void Glow();                            // Function to call in glow state

											// Getter functions
	inline std::string Get_Next_Level() { return m_next_level; }

	// Setter functions
	inline void Set_Sprite(C_Sprite *sprite) { mp_sprite = sprite; }
	inline void Set_Normal(std::string name) { m_normal = name; }
	inline void Set_Glow(std::string name) { m_glow = name; }
	inline void Set_Elapsed(double time) { m_elapsed = time; }
	inline void Set_Next_Level(std::string level) { m_next_level = level; }
	inline void Set_Particle_Sys_Transform(C_Transform *trans) { mp_particlesys_transform = trans; }
	inline void Set_Enter_Key_Transform(C_Transform *trans) { mp_enter_key_transform = trans; }

	// Virtual function for cloning
	C_DoorMenuEffect *Actual() override;
	C_DoorMenuEffect *Clone() const override;
};
}  // namespace object