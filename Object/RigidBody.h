/******************************************************************************/
/*!
\file_name        RigidBody.h
\project_name     Double Tap
\primary_author   Low Jin Liang Aaron, aaron.low, 390001116
\brief
        This file contains the definition of the RigidBody class
        
All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
 */
/******************************************************************************/
#pragma once
#include "Component.h"
#include "../Defines/AllMath.h"

namespace object
{

/******************************************************************************/
/*!
  The definition of the RigidBody class
 */
/******************************************************************************/
class C_Rigidbody final : public C_Component
{
  // Members
  math::Vec2 m_velocity;
  math::Vec2 m_acceleration;
  float      m_friction;
  bool       m_gravity;

public:
  // Constructors for the rigidbody class
  C_Rigidbody(C_GameObject *p_obj, float x = 0, float y = 0,
              float friction = 0.5, bool gravity = true);
  C_Rigidbody(C_GameObject *p_obj, math::Vec2 velocity,
              float friction = 0.5, bool gravity = true);
  
  // Member functions
  void Set_Velocity    (math::Vec2 velocity);
  void Set_Velocity    (float x, float y);
  void Set_VelocityX   (float x);
  void Set_VelocityY   (float y);
  void Set_Acceleration(math::Vec2 acceleration);
  void Set_Acceleration(float x, float y);
  void Set_Gravity     (bool gravity);
  void Set_Friction    (float friction);
  void Add_Velocity    (math::Vec2 velocity);
  void Add_Velocity    (float x, float y);
  void Add_Acceleration(math::Vec2 acceleration);
  void Add_Acceleration(float x, float y);
  
  math::Vec2 Get_Velocity       () const;
  math::Vec2 Get_Velocity_Global() const;
  math::Vec2 Get_Acceleration   () const;
  float      Get_Friction       () const;
  bool       Get_Gravity        () const;
  
  // Virtual functions
  C_Rigidbody *Actual () override;
  C_Rigidbody *Clone  () const override;
};
}