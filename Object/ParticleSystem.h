/******************************************************************************/
/*!
\file_name		ParticleSystem.h
\project_name	Double Tap
\primary_author	Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains the declarations of the Particle System class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "../Events/EventDispatcher.h"	// Event classes
#include "../Object/GameObject.h"		// GameObject class
#include "../Object/Particle.h"			// Particle component class

namespace object
{
enum ParticleType
{
	PT_NONE = 0,
	PT_RAIN,		// Raining particles
	PT_DOOR,		// Door aura particles
	PT_PICKUP,		// Pickups aura particles
	PT_BOSSROCK,	// 2nd boss rock tossing particles
	PT_BLOATERSMOKE,// Bloater smoke particles
	PT_SCREAMERSPIT,// Screamer spit particles
	PT_FIREHAZARD,	// Fire particles
	PT_PIPEHAZARD,	// Pipe hazard particles
	PT_PIPELEAK		// Pipe leaking particles
};

class C_ParticleSystem final : public C_Component
{
	using ParticleInstVector = std::vector<C_GameObject *>;

	C_GameObject *mp_Particle;						// Pointer to the particle object
	ParticleInstVector m_ParticleList;				// Vector that stores all particles

	GETSET(int, MinParticles)						// Min number of particles to spawn
		GETSET(int, MaxParticles)					// Max number of spawnable particles
		GETSET(bool, Loop)							// Boolean for looping / no looping
		GETSET(bool, Collidable)					// Boolean for collidable / no collidable
		GETSET(ParticleType, Pattern)				// Particle pattern to spawn

		C_Transform *mp_transform;					// Particle system's transform component

	void DefaultEffect(C_GameObject *particle);		// Default particle pattern
	void RainEffect(C_GameObject *particle);		// Rain particle pattern
	void DoorEffect(C_GameObject *particle);		// Door aura particle pattern
	void PickUpEffect(C_GameObject *particle);		// Pickup aura particle pattern
	void BossRockEffect(C_GameObject *particle);	// 2nd boss rock tossing pattern
	void BloaterSmokeEffect(C_GameObject *particle);// Bloater smoke pattern
	void ScreamerSpitEffect(C_GameObject *particle);// Screamer spit pattern
	void FireHazardEffect(C_GameObject *particle);	// Fire pattern
	void PipeHazardEffect(C_GameObject *particle);	// Pipe hazard pattern
	void PipeLeakEffect(C_GameObject *particle);	// Pipe leak pattern

	C_GameObject* SpawnParticle();					// Emits particles
	void CreateParticleInst();						// Creates all particles instances
public:
	/*
		Deletes the default constructor. No default constructor should be
		create the Particle System component
	*/
	C_ParticleSystem() = delete;

	// Non-default constructor for Particle System class
	C_ParticleSystem(C_GameObject *p_obj);

	// Destructor for Particle System class
	~C_ParticleSystem();

	// Connects all events
	void Connect();

	// Virtual update function
	void Update() override;

	// Draw function for graphics system to draw the particles
	void Draw();

	// Emits the particles
	void Emit();

	// Getter functions
	inline ParticleInstVector *Get_Particle_List() { return &m_ParticleList; }

	// Setter functions
	inline void Set_Particle(C_GameObject *particle) { mp_Particle = particle; }

	// Virtual functions for cloning
	C_ParticleSystem *Actual() override;
	C_ParticleSystem *Clone() const override;
};
}	// namespace object