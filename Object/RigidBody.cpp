/******************************************************************************/
/*!
\file_name        RigidBody.cpp
\project_name     Double Tap
\primary_author   Low Jin Liang Aaron, aaron.low, 390001116
\brief
        This file contains the member function definitions of the RigidBody 
        class
        
All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
 */
/******************************************************************************/
#include "RigidBody.h"

namespace object
{
/******************************************************************************/
/*!
  Non default constructor of a RigidBody object
 */
/******************************************************************************/
C_Rigidbody::C_Rigidbody(C_GameObject *p_obj, float x, float y,
                         float friction, bool gravity)
: C_Component{ p_obj, RIGIDBODY }, m_velocity{ math::Vec2{ x, y } },
  m_friction{ friction }, m_gravity{ gravity }
{
}
/******************************************************************************/
/*!
  Non default constructor of a RigidBody object that takes in a vector
 */
/******************************************************************************/
C_Rigidbody::C_Rigidbody(C_GameObject *p_obj, math::Vec2 velocity,
                         float friction, bool gravity)
: C_Component{ p_obj, RIGIDBODY }, m_velocity{ velocity },
  m_friction{ friction }, m_gravity{ gravity }
{
}

/******************************************************************************/
/*!
  This function sets velocity to the input velocity
 */
/******************************************************************************/
void C_Rigidbody::Set_Velocity(math::Vec2 velocity)
{
  m_velocity = velocity * TILESCALE;
}

/******************************************************************************/
/*!
  This function sets velocity to the input floats
 */
/******************************************************************************/
void C_Rigidbody::Set_Velocity(float x, float y)
{
  m_velocity.x = x * TILESCALE;
  m_velocity.y = y * TILESCALE;
}

/******************************************************************************/
/*!
  This function sets the X velocity to the input velocity
 */
/******************************************************************************/
void C_Rigidbody::Set_VelocityX(float x)
{
  m_velocity.x = x * TILESCALE;
}

/******************************************************************************/
/*!
  This function sets the Y velocity to the input velocity
 */
/******************************************************************************/
void C_Rigidbody::Set_VelocityY(float y)
{
  m_velocity.y = y * TILESCALE;
}

/******************************************************************************/
/*!
  This function sets the gravity boolean on the rigidbody object
 */
/******************************************************************************/
void C_Rigidbody::Set_Gravity(bool gravity)
{
  m_gravity = gravity;
}

/******************************************************************************/
/*!
  This function sets the acceleration of the object
 */
/******************************************************************************/
void C_Rigidbody::Set_Acceleration(math::Vec2 acceleration)
{
  m_acceleration = acceleration * TILESCALE;
}

/******************************************************************************/
/*!
  This function sets the acceleration of the object
 */
/******************************************************************************/
void C_Rigidbody::Set_Acceleration(float x, float y)
{
  m_acceleration.x = x * TILESCALE;
  m_acceleration.y = y * TILESCALE;
}

/******************************************************************************/
/*!
  This function sets the friction of the object
 */
/******************************************************************************/
void C_Rigidbody::Set_Friction(float friction)
{
  m_friction = friction;
}

/******************************************************************************/
/*!
  This function adds a velocity to the object
 */
/******************************************************************************/
void C_Rigidbody::Add_Velocity(math::Vec2 velocity)
{
  m_velocity.x += velocity.x * TILESCALE;
  m_velocity.y += velocity.y * TILESCALE;
}

/******************************************************************************/
/*!
  This function adds a velocity to the object
 */
/******************************************************************************/
void C_Rigidbody::Add_Velocity(float x, float y)
{
  m_acceleration.x += x * TILESCALE;
  m_acceleration.y += y * TILESCALE;
}

/******************************************************************************/
/*!
  This function adds an acceleration to the object
 */
/******************************************************************************/
void C_Rigidbody::Add_Acceleration(math::Vec2 acceleration)
{
  m_acceleration.x += acceleration.x * TILESCALE;
  m_acceleration.y += acceleration.y * TILESCALE;
}

/******************************************************************************/
/*!
  This function adds an acceleration to the object
 */
/******************************************************************************/
void C_Rigidbody::Add_Acceleration(float x, float y)
{
  m_acceleration.x += x * TILESCALE;
  m_acceleration.y += y * TILESCALE;
}

/******************************************************************************/
/*!
  This function gets the velocity in local coordinates
 */
/******************************************************************************/
math::Vec2 C_Rigidbody::Get_Velocity() const
{
  return m_velocity / TILESCALE;
}

/******************************************************************************/
/*!
  This function gets the velocity in global coordinates
 */
/******************************************************************************/
math::Vec2 C_Rigidbody::Get_Velocity_Global() const
{
  return m_velocity;
}

/******************************************************************************/
/*!
  This function gets the acceleration in local coordinates
 */
/******************************************************************************/
math::Vec2 C_Rigidbody::Get_Acceleration() const
{
  return m_acceleration / TILESCALE;
}

/******************************************************************************/
/*!
  This function gets the friction of the object
 */
/******************************************************************************/
float C_Rigidbody::Get_Friction() const
{
  return m_friction;
}

/******************************************************************************/
/*!
  This function gets the gravity boolean of the object
 */
/******************************************************************************/
bool C_Rigidbody::Get_Gravity() const
{
  return m_gravity;
}

/******************************************************************************/
/*!
  This function returns a pointer to the object
 */
/******************************************************************************/
C_Rigidbody * C_Rigidbody::Actual()
{
  return const_cast<C_Rigidbody*>(this);
}

/******************************************************************************/
/*!
  This function creates a clone of the object
 */
/******************************************************************************/
C_Rigidbody * C_Rigidbody::Clone() const
{
  return new C_Rigidbody{p_obj, m_velocity, m_friction, m_gravity};
}
}
