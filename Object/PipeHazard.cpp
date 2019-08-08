/******************************************************************************/
/*!
\file_name      PipeHazard.cpp
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains definitions of the Pipe Hazard component class. This class
	forms the behaviour of the pipe hazard in the game. It gives the pipe hazard
	an interval time to emit hazard.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "PipeHazard.h"

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
	Non-default constructor for the Pipe Hazard component class. This constructs
	the pipe hazard component.
*/
/******************************************************************************/
C_PipeHazard::C_PipeHazard(C_GameObject *p_obj)
	: C_Component{ p_obj }, m_elapsed{ 0.0 }, m_EmitTime{ 0.0 },
	m_wait_time{ 0.0 }, m_Interval{ 0.0 }, m_Direction{ 0.0f }, m_position{},
	m_State{ WAIT }, mp_pipe_hazard_system{ nullptr }, mp_transform{ nullptr }
{
}

/******************************************************************************/
/*!
	Connects all event functions and initialise the object's variables that
	will be used for the pipe hazard behaviours.
*/
/******************************************************************************/
void C_PipeHazard::Connect()
{
	// Connect event function
	events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);

	// Initialize transform component
	mp_transform = static_cast<C_Transform*>(p_obj->Find_Component(TRANSFORM));
	C_Transform *p_trans = static_cast<C_Transform*>(mp_pipe_hazard_system->
		Find_Component(TRANSFORM));
	p_trans->Set_Position(m_position.x, m_position.y);
	p_trans->Set_Dir(m_Direction);

	mp_pipe_hazard_system->Set_Active(true);

	// Initialize the box coliider component
	static_cast<C_BoxCollider*>(mp_pipe_hazard_system->
		Find_Component(BOXCOLLIDER))->Set_Active(false);
}

/******************************************************************************/
/*!
	The update function of Pipe Hazard particle system. This function is called
	every frame.
*/
/******************************************************************************/
void C_PipeHazard::Update()
{
	// Check which state the pipe hazard is currently on
	switch(m_State)
	{
	case WAIT:
		Wait(); // Calls the wait state function
		break;
	case EMITSMOKE:
		Emit_Smoke(); // Calls the emit state function
		break;
	}
}

/******************************************************************************/
/*!
	This function updates the behaviour of smoke emission from pipe hazard.
*/
/******************************************************************************/
void C_PipeHazard::Emit_Smoke()
{
	m_elapsed += utilities::C_Timer::Get_dt();

	// Dispatch event once only
	if(!m_sent)
	{
		events::C_EventDispatcher::DispatchEvent("BrokenPipe");
		m_sent = true;
	}

	// If the elapsed time is greater than emission time
	if(m_elapsed >= m_EmitTime)
	{
		m_sent = false;
		static_cast<C_BoxCollider*>(
			mp_pipe_hazard_system->Find_Component(BOXCOLLIDER))->Set_Active(false);
		static_cast<C_ParticleSystem*>(mp_pipe_hazard_system->
			Find_Component(PARTICLESYSTEM))->Set_Pattern(PT_PIPELEAK);
		m_State = WAIT;
		m_elapsed = 0.0;
	}
}

/******************************************************************************/
/*!
	This function updates the behaviour of wait`in from pipe hazard.
*/
/******************************************************************************/
void C_PipeHazard::Wait()
{
	m_wait_time += utilities::C_Timer::Get_dt();
	if(m_wait_time >= m_Interval)
	{
		static_cast<C_BoxCollider*>(mp_pipe_hazard_system->
			Find_Component(BOXCOLLIDER))->Set_Active(true);
		static_cast<C_ParticleSystem*>(mp_pipe_hazard_system->
			Find_Component(PARTICLESYSTEM))->Set_Pattern(PT_PIPEHAZARD);
		m_State = EMITSMOKE;
		m_wait_time = 0.0;
	}
}

/******************************************************************************/
/*!
	This function returns a pointer to the actual pipe hazard component.
*/
/******************************************************************************/
C_PipeHazard *C_PipeHazard::Actual()
{
	return this;
}

/******************************************************************************/
/*!
	This function clones a pointer to this pipe hazard component.
*/
/******************************************************************************/
C_PipeHazard *C_PipeHazard::Clone() const
{
	return new C_PipeHazard{ p_obj };
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
	static_cast<object::C_PipeHazard*>(p_object->
		Find_Component(CUSTOM))->Update();
}
} // Anonymous namespace
