/******************************************************************************/
/*!
\file_name      PipeHazard.h
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
	This file contains declarations of the Pipe Hazard component class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "../Events/EventDispatcher.h"  // EventDispatcher class
#include "../Object/GameObject.h"       // GameObject class
#include "../Defines/AllUtilities.h"    // Timer, OptionsManager
#include "../Object/ParticleSystem.h"   // ParticleSystem class

namespace object
{
// Pipe states
enum PIPESTATE
{
	WAIT = 0, // Waiting state
	EMITSMOKE // Emitting state
};

class C_PipeHazard final : public C_Component
{
	double m_elapsed;                     // Time elapsed in Emit state
	double m_wait_time;                   // Time to wait in Wait state
	bool m_sent;                          // Boolean to dispatch pipe event once
	PIPESTATE m_State;                    // State of the pipe hazard

	GETSET(double, Interval)              // Interval time to next emission state
		GETSET(double, EmitTime)              // Time to emit smoke
		GETSET(float, Direction)              // Direction of the emission

		math::Vec2 m_position;                // Emission position

	C_Transform *mp_transform;            // Owner's transform component
	C_GameObject *mp_pipe_hazard_system;  // PipeHazard particle system

	void Emit_Smoke();                    // Function for emit state
	void Wait();                          // Function for wait state

public:
	// Non-default constructor
	C_PipeHazard(C_GameObject *p_obj);

	// Connect all events
	void Connect();

	// Update function for every frame
	virtual void Update() override;

	// Setter functions
	inline void Set_Initial_Position(float x, float y)
	{
		m_position.x = x, m_position.y = y;
	}

	inline void Set_Pipe_Hazard_System(C_GameObject *p_sys)
	{
		mp_pipe_hazard_system = p_sys;
	}

	// Virtual functions to clone object
	virtual C_PipeHazard *Actual() override;
	virtual C_PipeHazard *Clone() const override;
};
} // namespace object