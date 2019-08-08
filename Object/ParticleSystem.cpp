/******************************************************************************/
/*!
\file_name		ParticleSystem.cpp
\project_name	Double Tap
\primary_author	Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains the definitions of the Particle System class. This class
	is a component for game objects. By adding this component onto game object
	gives it a behaviour of a particle systems. The particles systems handles
	creation of particles and manages its behaviours.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "ParticleSystem.h"

/*
	This namespace contains all declarations of the event functions that this
	file will use
*/
namespace
{
	void OnLogicUpdate(object::C_GameObject* p_object);
} // Anonymous namespace

namespace object
{
/******************************************************************************/
/*!
	Non-default constructor for the Particle System. This constructs the
	particle system component by taking in a pointer to the object as a
	archetype for particle creation.
*/
/******************************************************************************/
C_ParticleSystem::C_ParticleSystem(C_GameObject *p_obj)
	: C_Component{ p_obj, PARTICLESYSTEM }, mp_Particle{ nullptr },
	m_MinParticles{ 5 }, m_MaxParticles{ 20 }, m_Loop{ false },
	m_Collidable{ false }, m_Pattern{ PT_NONE }, mp_transform{ nullptr }
{
}

/******************************************************************************/
/*!
	Destructor for the Particle System. This destruct the Particle System
	component and delete all particle object instances in the particle vector
*/
/******************************************************************************/
C_ParticleSystem::~C_ParticleSystem()
{
	for(auto it = m_ParticleList.begin(); it != m_ParticleList.end(); ++it)
		delete(*it);

	mp_Particle = nullptr;
	ParticleInstVector temp;
	m_ParticleList.swap(temp);
}

/******************************************************************************/
/*!
	This function creates all spawnable particles instances and stores it in
	the particle vector.
*/
/******************************************************************************/
void C_ParticleSystem::CreateParticleInst()
{
	for(int i = 0; i < m_MaxParticles; ++i)
	{
		// Clone the particle object
		C_GameObject *temp_inst = mp_Particle->Clone();

		// Clone all components of the particle object
		for(auto it = temp_inst->getCompVec().begin();
			it != temp_inst->getCompVec().end(); ++it)
		{
			(*it)->Set_Obj(temp_inst);
		}

		// Inserts into the particle vector
		m_ParticleList.push_back(temp_inst);
	}

}

/******************************************************************************/
/*!
	This function grabs inactive particle in the particle vector and spawn it
	by parsing it through a pattern function and spawn it with the pattern
	behaviour. This function will also return the pointer to the particle
	object instance. This function will return nullptr if no inactive particle
	exist.
*/
/******************************************************************************/
C_GameObject *C_ParticleSystem::SpawnParticle()
{
	/*
		Traverse the particle vector to find inactive particle object instance,
		parse it through a pattern function and finally spawn the particle with
		the specified pattern behaviour.
	*/
	for(auto it = m_ParticleList.begin(); it != m_ParticleList.end(); ++it)
	{
		if(!(*it)->Get_Active())
		{
			switch(m_Pattern)
			{
			case PT_NONE:
				DefaultEffect(*it);
				break;
			case PT_RAIN:
				RainEffect(*it);
				break;
			case PT_DOOR:
				DoorEffect(*it);
				break;
			case PT_PICKUP:
				PickUpEffect(*it);
				break;
			case PT_BOSSROCK:
				BossRockEffect(*it);
				break;
			case PT_BLOATERSMOKE:
				BloaterSmokeEffect(*it);
				break;
			case PT_SCREAMERSPIT:
				ScreamerSpitEffect(*it);
				break;
			case PT_FIREHAZARD:
				FireHazardEffect(*it);
				break;
			case PT_PIPEHAZARD:
				PipeHazardEffect(*it);
				break;
			case PT_PIPELEAK:
				PipeLeakEffect(*it);
				break;
			}

			(*it)->Set_Active(true);
			static_cast<C_Particle*>((*it)->Find_Component(PARTICLE))->Init();

			return *it;
		}
	}
	return nullptr;
}

/******************************************************************************/
/*!
	This function connects all event functions required to the event dispatcher.
	It also initializes pointers to the owner and the other components as
	required.
*/
/******************************************************************************/
void C_ParticleSystem::Connect()
{
	// Connects the logic update
	if(m_Loop)
		events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);

	// Retrieve the transform component of its owner
	mp_transform = static_cast<C_Transform*>(p_obj->Find_Component(TRANSFORM));

	// Creates spawnable particles
	CreateParticleInst();
}

/******************************************************************************/
/*!
	This function update the Particle System component every frame
*/
/******************************************************************************/
void C_ParticleSystem::Update()
{
	// Emit the particles every frame
	Emit();
}

/******************************************************************************/
/*!
	This function draws all active particles in the particle vector.
*/
/******************************************************************************/
void C_ParticleSystem::Draw()
{
	for(auto it = m_ParticleList.begin(); it != m_ParticleList.end(); ++it)
	{
		// Continue if particle object is inactive
		if(!(*it)->Get_Active())
			continue;

		C_Sprite *p_sprite =
			static_cast<C_Sprite*>((*it)->Find_Component(SPRITE));

		math::Matrix3 transform =
			static_cast<C_Transform*>((*it)->Find_Component(TRANSFORM))
			->Get_Matrix();

		// Render texture if it exist, else render in color mode
		p_sprite->Get_Texture() ? AEGfxSetRenderMode(AE_GFX_RM_TEXTURE)
			: AEGfxSetRenderMode(AE_GFX_RM_COLOR);

		AEGfxSetTransform(transform.m_matrix);
		p_sprite->Update();
	}
}

/******************************************************************************/
/*!
This function emits the particles.
*/
/******************************************************************************/
void C_ParticleSystem::Emit()
{
	// Spawn the minimum number of particles
	for(int i = 0; i < m_MinParticles; ++i)
		SpawnParticle();
}

/******************************************************************************/
/*!
	This function initializes the default pattern to a particle.
*/
/******************************************************************************/
void C_ParticleSystem::DefaultEffect(C_GameObject *particle)
{
	C_Particle * p_particle =
		static_cast<C_Particle*>(particle->Find_Component(PARTICLE));

	float randScale = 0.0f;
	float randDir = 0.0f;
	double randLifetime = 0.0;

	p_particle->Connect();

	// Randomise a direction angle
	randDir = AERandFloat() * PI;
	p_particle->Set_StartAngle(randDir);

	// Initialise starting pos at emitter's position
	p_particle->Set_StartPos(mp_transform->Get_Position());

	// Set the speed range for each particle
	p_particle->Set_MinSpeed(0.5f);
	p_particle->Set_MaxSpeed(1.0f);

	// Randomise a scale for each particle
	randScale = AERandFloat() * (TILESCALE / 2.0f) / TILESCALE;
	p_particle->Set_Scale(math::Vec2{ randScale, randScale });

	// Randomise a life time for each particle
	randLifetime = 1.0f + AERandFloat() * 0.5f;
	p_particle->Set_LifeTime(randLifetime);
}

/******************************************************************************/
/*!
	This function initializes the raining pattern to a particle.
*/
/******************************************************************************/
void C_ParticleSystem::RainEffect(C_GameObject *particle)
{
	C_Particle * p_particle =
		static_cast<C_Particle*>(particle->Find_Component(PARTICLE));

	float randXPos = 0.0f;
	float randDir = 0.0f;
	double randLifetime = 0.0;

	p_particle->Connect();

	// Randomise a direction angle
	randDir = 8 * PI / 6 + AERandFloat() * PI / 6;
	p_particle->Set_StartAngle(randDir);

	// Randomise a transparency value
	p_particle->Set_Opacity(0.15f);
	p_particle->Set_Scale(math::Vec2{ 1.5f, 0.05f });

	// Set the speed range for each particle
	p_particle->Set_MinSpeed(10.0f);
	p_particle->Set_MaxSpeed(20.0f);

	// Randomise an X position within window's width
	randXPos = mp_transform->Get_Position().x +
		AERandFloat() * (WINDOW_WIDTH + 4 * TILESCALE) / TILESCALE;
	p_particle->Set_StartPos(math::Vec2{ randXPos,
		mp_transform->Get_Position().y });

	// Randomise a life time for each particle
	randLifetime = 0.2f + AERandFloat() * 2.0f;
	p_particle->Set_LifeTime(randLifetime);
}

/******************************************************************************/
/*!
	This function initializes the door aura pattern to a particle.
*/
/******************************************************************************/
void C_ParticleSystem::DoorEffect(C_GameObject *particle)
{
	C_Particle * p_particle =
		static_cast<C_Particle*>(particle->Find_Component(PARTICLE));

	float randXPos = 0.0f;
	float randScale = 0.0f;
	float randDir = 0.0f;
	double randLifetime = 0.0;

	p_particle->Connect();

	// Randomise a scale for each particle
	randScale = AERandFloat() * (0.4f * TILESCALE) / TILESCALE;
	p_particle->Set_Scale(math::Vec2{ randScale, randScale });

	// Randomise an X position within door's width
	randXPos = mp_transform->Get_Position().x - 1.0f + AERandFloat() * 2.0f;
	p_particle->Set_StartPos(math::Vec2{ randXPos,
		mp_transform->Get_Position().y });

	// X pos <=  door's x position
	if(randXPos <= mp_transform->Get_Position().x)
	{
		/*
			Set direction angle to move towards the left with angle increment
			forming an arc
		*/
		randDir = 2 * PI / 3 + AERandFloat() * (11 * PI / 12 - 2 * PI / 3);
		p_particle->Set_StartAngle(randDir);
		p_particle->Set_DeltaAngle(-PI / 12);
	}
	else // X pos > door's x position
	{
		/*
			Set direction angle to move towards the right with angle increment
			forming an arc
		*/
		randDir = PI / 12 + AERandFloat() * (PI / 3 - PI / 12);
		p_particle->Set_StartAngle(randDir);
		p_particle->Set_DeltaAngle(PI / 12);
	}

	// Set the speed range for each particle
	p_particle->Set_MinSpeed(1.0f);
	p_particle->Set_MaxSpeed(5.0f);

	// Set boolean to update angle every frame
	p_particle->Set_ChangeAngle(true);

	// Randomise a life time for each particle
	randLifetime = AERandFloat() * 2.0f;
	p_particle->Set_LifeTime(randLifetime);

	// Randomise a transparency value
	p_particle->Set_Opacity(0.25f + AERandFloat() * 0.50f);
}

/******************************************************************************/
/*!
	This function initializes the pickups aura pattern to a particle.
*/
/******************************************************************************/
void C_ParticleSystem::PickUpEffect(C_GameObject *particle)
{
	C_Particle * p_particle =
		static_cast<C_Particle*>(particle->Find_Component(PARTICLE));

	float randScale = 0.0f;
	float randXPos = 0.0f;
	float randDir = 0.0f;
	double randLifetime = 0.0;

	p_particle->Connect();

	// Randomise a direction angle
	randDir = AERandFloat() * PI;
	p_particle->Set_StartAngle(randDir);

	// Randomise an X position within pickups' width
	randXPos = mp_transform->Get_Position().x - 1.0f + AERandFloat() * 2.0f;
	p_particle->Set_StartPos(math::Vec2{ randXPos,
		mp_transform->Get_Position().y });

	// Set the speed range for each particle
	p_particle->Set_MinSpeed(0.5f);
	p_particle->Set_MaxSpeed(1.0f);

	// Randomise a scale for each particle
	randScale = AERandFloat() * (TILESCALE / 2.0f) / TILESCALE;
	p_particle->Set_Scale(math::Vec2{ randScale, randScale });

	// Randomise a life time for each particle
	randLifetime = 0.7f + AERandFloat() * 0.5f;
	p_particle->Set_LifeTime(randLifetime);
}

/******************************************************************************/
/*!
	This function initializes the 2nd boss rock tossing pattern to a particle.
*/
/******************************************************************************/
void C_ParticleSystem::BossRockEffect(C_GameObject *particle)
{
	C_Particle * p_particle =
		static_cast<C_Particle*>(particle->Find_Component(PARTICLE));

	float randScale = 0.0f;
	float randDir = 0.0f;
	double randLifetime = 0.0;

	p_particle->Connect();

	// Randomise a direction angle
	randDir = AERandFloat() * PI;
	p_particle->Set_StartAngle(randDir);

	// Initialize starting position at emitter's position
	p_particle->Set_StartPos(mp_transform->Get_Position());

	// Set the speed range for each particle
	p_particle->Set_MinSpeed(20.0f);
	p_particle->Set_MaxSpeed(15.0f);

	// Randomise a scale for each particle
	randScale = 2.0f + AERandFloat() * 1.0f;
	p_particle->Set_Scale(math::Vec2{ randScale, randScale });

	// Randomise a life time for each particle
	randLifetime = 3.0f;
	p_particle->Set_LifeTime(randLifetime);
}

/******************************************************************************/
/*!
	This function initializes the bloater smoke pattern to a particle.
*/
/******************************************************************************/
void C_ParticleSystem::BloaterSmokeEffect(C_GameObject *particle)
{
	C_Particle * p_particle =
		static_cast<C_Particle*>(particle->Find_Component(PARTICLE));

	float randScale = 0.0f;
	float randYPos = 0.0f;
	float randDir = 0.0f;
	float randOpacity = 0.0f;
	double randLifetime = 0.0;

	p_particle->Connect();

	// Randomise a Y position within bloater's height
	randDir = AERandFloat() <= 0.5f ? randDir = PI : 0;
	p_particle->Set_StartAngle(randDir);

	// Randomise a direction angle
	randYPos = mp_transform->Get_Position().y + AERandFloat() * 1.0f;
	p_particle->Set_StartPos(math::Vec2{ mp_transform->Get_Position().x,
		randYPos });

	// Set the speed range for each particle
	p_particle->Set_MinSpeed(0.1f);
	p_particle->Set_MaxSpeed(0.5f);

	// Randomise a transparency value
	randOpacity = 0.1f + AERandFloat() * 0.50f;
	p_particle->Set_Opacity(randOpacity);

	// Randomise a scale for each particle
	randScale = 0.1f + AERandFloat() * 1.0f;
	p_particle->Set_Scale(math::Vec2{ randScale, randScale });

	// Randomise a life time for each particle
	randLifetime = 3.5f + AERandFloat() * 0.5f;
	p_particle->Set_LifeTime(randLifetime);
}

/******************************************************************************/
/*!
	This function initializes the screamer spit pattern to a particle.
*/
/******************************************************************************/
void C_ParticleSystem::ScreamerSpitEffect(C_GameObject *particle)
{
	C_Particle * p_particle =
		static_cast<C_Particle*>(particle->Find_Component(PARTICLE));

	float randScale = 0.0f;
	float randDir = 0.0f;
	float randOpacity = 0.0f;
	double randLifetime = 0.0;

	p_particle->Connect();

	// If emitter's direction is left
	if(mp_transform->Get_Dir() >= 90.0f)
	{
		// Set direction for each particle to left
		randDir = 2 * PI / 3 + AERandFloat() * (PI / 6);
		p_particle->Set_StartAngle(randDir);
	}
	else // Emitter's direction is right
	{
		// Set direction for each particle to right
		randDir = AERandFloat() * (PI / 6);
		p_particle->Set_StartAngle(randDir);
	}

	// Initialize starting position at emitter's position
	p_particle->Set_StartPos(mp_transform->Get_Position());

	// Set the speed range for each particle
	p_particle->Set_MinSpeed(10.0f);
	p_particle->Set_MaxSpeed(15.0f);

	// Randomise a transparency value
	randOpacity = 0.4f + AERandFloat() * 0.5f;
	p_particle->Set_Opacity(randOpacity);

	// Randomise a scale for each particle
	randScale = 0.4f + AERandFloat() * 0.5f;
	p_particle->Set_Scale(math::Vec2{ randScale, randScale });

	// Randomise a life time for each particle
	randLifetime = 0.1f + AERandFloat() * 0.5f;
	p_particle->Set_LifeTime(randLifetime);
}

/******************************************************************************/
/*!
	This function initializes the fire pattern to a particle.
*/
/******************************************************************************/
void C_ParticleSystem::FireHazardEffect(C_GameObject *particle)
{
	C_Particle * p_particle =
		static_cast<C_Particle*>(particle->Find_Component(PARTICLE));

	float	randNum = AERandFloat();
	float	randXPos = 0.0f;
	float	randYPos = 0.0f;
	float	randScale = 0.0f;
	float	randMinSpeed = 0.0f;
	float	randMaxSpeed = 0.0f;
	float	randDir = 0.0f;
	double	randLifetime = 0.0;

	p_particle->Connect();

	// Randomise a scale for each particle
	randScale = AERandFloat() * (0.3f * TILESCALE) / TILESCALE;
	p_particle->Set_Scale(math::Vec2{ randScale, randScale });

	// Randomise a starting position withing the emitter position
	randXPos = mp_transform->Get_Position().x - 0.5f + AERandFloat() * 1.0f;
	randYPos = mp_transform->Get_Position().y - 0.5f + AERandFloat() * 0.5f;
	p_particle->Set_StartPos(math::Vec2{ mp_transform->Get_Position().x,
		randYPos });

	// X pos <=  emitter's x position
	if(randXPos <= mp_transform->Get_Position().x)
	{
		/*
			Set direction angle to move towards the left with angle increment
			forming an arc
		*/
		randDir = 7 * PI / 12 + randNum * (PI / 3);
		p_particle->Set_StartAngle(randDir);
		p_particle->Set_DeltaAngle(PI / 2 - randDir - PI / 12);
	} // X pos > emitter's x position
	else
	{
		/*
			Set direction angle to move towards the right with angle increment
			forming an arc
		*/
		randDir = randNum * (5 * PI / 12);
		p_particle->Set_StartAngle(randDir);
		p_particle->Set_DeltaAngle(PI / 2 - randDir + PI / 12);
	}

	// Set the speed range for each particle
	randMinSpeed = 1.0f * AERandFloat() * 5.0f;
	p_particle->Set_MinSpeed(randMinSpeed);
	randMaxSpeed = 6.0f + AERandFloat() * 5.0f;
	p_particle->Set_MaxSpeed(randMaxSpeed);

	// Set boolean to update angle every frame
	p_particle->Set_ChangeAngle(true);

	// Randomise a life time for each particle
	randLifetime = AERandFloat() * 1.4f;
	p_particle->Set_LifeTime(randLifetime);

	// Randomise a transparency value
	p_particle->Set_Opacity(0.25f + AERandFloat() * 0.50f);
}

/******************************************************************************/
/*!
	This function initializes the pipe hazard pattern to a particle.
*/
/******************************************************************************/
void C_ParticleSystem::PipeHazardEffect(C_GameObject *particle)
{
	C_Particle * p_particle =
		static_cast<C_Particle*>(particle->Find_Component(PARTICLE));

	float	randScale = 0.0f;
	float	randDir = 0.0f;
	double	randLifetime = 0.0;

	p_particle->Connect();

	// Randomise a scale for each particle
	randScale = (0.4f * TILESCALE) / TILESCALE + AERandFloat() *
		(0.2f * TILESCALE) / TILESCALE;
	p_particle->Set_Scale(math::Vec2{ randScale, randScale });

	// Initialize starting position at emitter's position
	p_particle->Set_StartPos(mp_transform->Get_Position());

	float dir = mp_transform->Get_Dir();

	// If direction of pipe is down
	if(dir >= 270.0f)
	{
		/*
			Set direction for each particle to emit downward within
			a conical shape
		*/
		randDir = 17 * PI / 12 + AERandFloat() * (PI / 6);
		p_particle->Set_StartAngle(randDir);
	}
	else if(dir >= 180.0f) // If direction of pipe is left
	{
		/*
			Set direction for each particle to emit left within
			a conical shape
		*/
		randDir = 11 * PI / 12 + AERandFloat() * (PI / 6);
		p_particle->Set_StartAngle(randDir);
	}
	else if(dir >= 90.0f) // If direction of pipe is up
	{
		/*
			Set direction for each particle to emit upward within
			a conical shape
		*/
		randDir = 5 * PI / 12 + AERandFloat() * (PI / 6);
		p_particle->Set_StartAngle(randDir);
	}
	else // If direction of pipe is right
	{
		/*
			Set direction for each particle to emit right within
			a conical shape
		*/
		randDir = 23 * PI / 12 + AERandFloat() * (PI / 6);
		p_particle->Set_StartAngle(randDir);
	}

	// Set the speed range for each particle
	p_particle->Set_MinSpeed(5.0f);
	p_particle->Set_MaxSpeed(10.0f);

	// Randomise a life time for each particle
	randLifetime = 0.2f + AERandFloat() * 0.4f;
	p_particle->Set_LifeTime(randLifetime);

	// Randomise a transparency value
	p_particle->Set_Opacity(0.5f + AERandFloat() * 0.5f);
}

/******************************************************************************/
/*!
	This function initializes the pipe leaking pattern to a particle.
*/
/******************************************************************************/
void C_ParticleSystem::PipeLeakEffect(C_GameObject *particle)
{
	C_Particle * p_particle =
		static_cast<C_Particle*>(particle->Find_Component(PARTICLE));

	float	randScale = 0.0f;
	float	randDir = 0.0f;
	double	randLifetime = 0.0;

	p_particle->Connect();

	// Randomise a scale for each particle
	randScale = (0.1f * TILESCALE) / TILESCALE + AERandFloat() *
		(0.2f * TILESCALE) / TILESCALE;
	p_particle->Set_Scale(math::Vec2{ randScale, randScale });

	// Initialize starting position at emitter's position
	p_particle->Set_StartPos(mp_transform->Get_Position());

	float dir = mp_transform->Get_Dir();

	// If direction of pipe is down
	if(dir >= 270.0f)
	{
		/*
			Set direction for each particle to emit downward within
			a conical shape
		*/
		randDir = 17 * PI / 12 + AERandFloat() * (PI / 6);
		p_particle->Set_StartAngle(randDir);
	}
	else if(dir >= 180.0f) // If direction of pipe is left
	{
		/*
			Set direction for each particle to emit left within
			a conical shape
		*/
		randDir = 11 * PI / 12 + AERandFloat() * (PI / 6);
		p_particle->Set_StartAngle(randDir);
	}
	else if(dir >= 90.0f) // If direction of pipe is up
	{
		/*
			Set direction for each particle to emit upward within
			a conical shape
		*/
		randDir = 5 * PI / 12 + AERandFloat() * (PI / 6);
		p_particle->Set_StartAngle(randDir);
	}
	else // If direction of pipe is right
	{
		/*
			Set direction for each particle to emit right within
			a conical shape
		*/
		randDir = 23 * PI / 12 + AERandFloat() * (PI / 6);
		p_particle->Set_StartAngle(randDir);
	}

	// Set the speed range for each particle
	p_particle->Set_MinSpeed(1.0f);
	p_particle->Set_MaxSpeed(2.0f);

	// Randomise a life time for each particle
	randLifetime = AERandFloat() * 0.2f;
	p_particle->Set_LifeTime(randLifetime);

	// Randomise a transparency value
	p_particle->Set_Opacity(0.5f + AERandFloat() * 0.5f);
}


/******************************************************************************/
/*!
	This function returns the actual pointer to this Particle System component.
*/
/******************************************************************************/
C_ParticleSystem *C_ParticleSystem::Actual()
{
	return this;
}

/******************************************************************************/
/*!
	This function returns a clone of this Particle System component.
*/
/******************************************************************************/
C_ParticleSystem *C_ParticleSystem::Clone() const
{
	C_ParticleSystem *p_clone = new C_ParticleSystem{ p_obj };

	p_clone->mp_Particle = mp_Particle;
	p_clone->m_ParticleList = m_ParticleList;
	p_clone->m_MinParticles = m_MinParticles;
	p_clone->m_MaxParticles = m_MaxParticles;
	p_clone->m_Loop = m_Loop;
	p_clone->m_Collidable = m_Collidable;
	p_clone->m_Pattern = m_Pattern;
	p_clone->mp_transform = mp_transform;

	return p_clone;
}
} // namespace object

/*
	This namespace contains all definitions of the event functions that this
	file will use
*/
namespace
{
/******************************************************************************/
/*!
	This is an event update function that calls the update function every frame.
*/
/******************************************************************************/
void OnLogicUpdate(object::C_GameObject *p_obj)
{
	static_cast<object::C_ParticleSystem*>
		(p_obj->Find_Component(PARTICLESYSTEM))->Update();
}
} // Anonymous namespace