/******************************************************************************/
/*!
\file_name      Particle.h
\project_name   Double Tap
\primary_author Koh Wen Lin, wenlin.koh, 390004216
\brief
This file contains the declarations of the Particle component class.

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "../Events/EventDispatcher.h"  // Event classes
#include "../Object/GameObject.h"       // GameObject class
#include "../Defines/AllUtilities.h"    // Timer class

namespace object
{
class C_Particle final : public C_Component
{
	GETSET(double, ElapsedTime)    // Time elapsed on this object
	GETSET(double, LifeTime)	   // Time before death on this object

	GETSET(math::Vec2, StartPos)   // Initial position of this object
	GETSET(math::Vec2, Scale)      // Scale of this object

	GETSET(float, Opacity)         // Opacity of this object
	GETSET(float, MinSpeed)        // Minimum speed of this object
	GETSET(float, MaxSpeed)        // Maximum speed of this object
	GETSET(float, StartAngle)      // Initial angle of this object
	GETSET(float, DeltaAngle)      // Change in angle of this object

	GETSET(bool, DeathTimer)       /*
									  Set to true - Object will die after a
									  period of time.
									  Set to false - Object will not die.
								   */

	GETSET(bool, ChangeAngle)	   /*
									  Set to true - Object change in angle every
									                frame
									  Set to false - Object doesn't change in
									                 angle
								   */


	C_Transform *mp_transform;     // Transform component of particle
	C_Sprite *mp_sprite;           // Sprite component of particle
	C_Rigidbody *mp_rigid;         // Rigidbody component of particle

public:
	// Non-default construct for Particle component class
	C_Particle(C_GameObject *p_obj);

	// Initialize variables
	void Init();

	// Connects all events
	void Connect();

	// Virtual update function
	void Update() override;

	// Virtual functions for cloning
	virtual C_Particle *Actual() override;
	virtual C_Particle *Clone() const override;
};
}  // namespace object