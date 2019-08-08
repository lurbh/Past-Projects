/******************************************************************************/
/*!
\file_name      Particle.cpp
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains the definitions of the Particle component class. This class
	controls the behaviour of a particle object(e.g. speed, lifetime, etc...)

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "Particle.h"

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
	Non-default constructor for the Particle component class. This constructs the
	particle component.
*/
/******************************************************************************/
C_Particle::C_Particle(C_GameObject *p_obj)
	: C_Component{ p_obj, PARTICLE }, m_ElapsedTime{ 0.0 }, m_LifeTime{ 0.0 },
	m_StartPos{ 0.0f, 0.0f }, m_Scale{ 1.0f }, m_Opacity{ 1.0f },
	m_MinSpeed{ 0.0f }, m_MaxSpeed{ 0.0f }, m_StartAngle{ 0.0f },
	m_DeltaAngle{ 0.0f }, m_DeathTimer{ true }, m_ChangeAngle{ false },
	mp_transform{ nullptr }, mp_sprite{ nullptr }, mp_rigid{ nullptr }
{
}

/******************************************************************************/
/*!
	The init function of Particle component class. This function initializes the
	object's variables such as positions, velocity, etc...
*/
/******************************************************************************/
void C_Particle::Init()
{
	m_ElapsedTime = 0.0;

	// Initialise transform component
	mp_transform->Set_Position(m_StartPos.x, m_StartPos.y);
	mp_transform->Scale(m_Scale);
	mp_transform->Rotate(m_StartAngle / PI * 180);

	// Initialise sprite component
	mp_sprite->Set_Opacity(m_Opacity);

	// Initialise rigidbody component
	float speed = AERandFloat() * (m_MaxSpeed - m_MinSpeed) + m_MinSpeed;

	mp_rigid->Set_Velocity(cosf(m_StartAngle) * speed,
		sinf(m_StartAngle) * speed);

	mp_rigid->Set_Friction(0.0f);
}

/******************************************************************************/
/*!
	Connects all event functions and initialise the object's core component that
	will be used for the particle behaviours.
*/
/******************************************************************************/
void C_Particle::Connect()
{
	// Connect event function
	events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);

	// Initialise object's core components
	mp_transform = static_cast<C_Transform*>(p_obj->Find_Component(TRANSFORM));
	mp_sprite = static_cast<C_Sprite*>(p_obj->Find_Component(SPRITE));
	mp_rigid = static_cast<C_Rigidbody*>(p_obj->Find_Component(RIGIDBODY));
}

/******************************************************************************/
/*!
	The update function of the Particle component class. This function is called
	every frame.
*/
/******************************************************************************/
void C_Particle::Update()
{
	//  If particle requires to change direction every frame
	if(m_ChangeAngle)
	{
		mp_rigid->Set_Velocity(cosf(static_cast<float>(m_ElapsedTime) *
			m_DeltaAngle + m_StartAngle),
			sinf(static_cast<float>(m_ElapsedTime) *
				m_DeltaAngle + m_StartAngle));
	}

	// If game is not paused and particle need to die after a certain period
	if(m_DeathTimer && !utilities::C_OptionsManager::Get_Pause())
	{
		m_ElapsedTime += utilities::C_Timer::Get_dt();

		// If time elapsed is greater than its life time
		if(m_ElapsedTime >= m_LifeTime)
		{
			// Destroy the particle
			mp_transform->Rotate(-m_StartAngle / PI * 180);
			p_obj->Destroy();
		}
	}
}

/******************************************************************************/
/*!
	This function returns a pointer to the actual particle component.
*/
/******************************************************************************/
C_Particle *C_Particle::Actual()
{
	return this;
}

/******************************************************************************/
/*!
	This function clones a pointer to this particle component.
*/
/******************************************************************************/
C_Particle *C_Particle::Clone() const
{
	return new C_Particle{ p_obj };
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
void OnLogicUpdate(object::C_GameObject* p_object)
{
	static_cast<object::C_Particle*>(p_object->Find_Component(PARTICLE))->
		Update();
}
} // Anonymous namespace