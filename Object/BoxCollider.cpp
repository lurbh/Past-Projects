/******************************************************************************/
/*!
\file_name        BoxCollider.cpp
\project_name     Double Tap
\primary_author   Low Jin Liang Aaron, aaron.low, 390001116
\brief
        This file contains the member function definitions of the BoxCollider 
        class
        
All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
 */
/******************************************************************************/
#include "BoxCollider.h"

namespace object
{

/******************************************************************************/
/*!
  Conversion constructor of a boxcollider object
 */
/******************************************************************************/
C_BoxCollider::C_BoxCollider(C_GameObject * p_obj)
: C_Component{ p_obj, BOXCOLLIDER }, m_min{}, m_max{}, m_size{ 1.0f, 1.0f }, 
  m_flag{ 0 }, m_active{ true }, m_ghost{ false }
{
}

/******************************************************************************/
/*!
  Non default constructor of a boxcollider object
 */
/******************************************************************************/
C_BoxCollider::C_BoxCollider(C_GameObject * p_obj, math::Vec2 min, math::Vec2 max,
                             math::Vec2 size, math::Vec2 offset, bool ghost)
: C_Component{ p_obj, BOXCOLLIDER }, m_min{ min }, m_max{ max }, m_size{ size }, 
  m_flag{ 0 }, m_offset{ offset }, m_active{ true }, m_ghost{ ghost }
{
}

/******************************************************************************/
/*!
  This function sets the m_offset member of the boxcollider class
 */
/******************************************************************************/
void C_BoxCollider::Set_Offset(float x, float y)
{
  m_offset.x = x;
  m_offset.y = y;
}

/******************************************************************************/
/*!
  This function sets the minimum point of the boxcollider
 */
/******************************************************************************/
void C_BoxCollider::Set_Min(math::Vec2 min)
{
  m_min = min;
}

/******************************************************************************/
/*!
  This function sets the minimum point of the boxcollider
 */
/******************************************************************************/
void C_BoxCollider::Set_Min(float x, float y)
{
  m_min.x = x;
  m_min.y = y;
}

/******************************************************************************/
/*!
  This function sets the maximum point of the boxcollider
 */
/******************************************************************************/
void C_BoxCollider::Set_Max(math::Vec2 max)
{
  m_max = max;
}

/******************************************************************************/
/*!
  This function sets the maximum point of the boxcollider
 */
/******************************************************************************/
void C_BoxCollider::Set_Max(float x, float y)
{
  m_max.x = x;
  m_max.y = y;
}

/******************************************************************************/
/*!
  This function sets the size of the boxcollider
 */
/******************************************************************************/
void C_BoxCollider::Set_Size(math::Vec2 size)
{
  m_size = size;
}

/******************************************************************************/
/*!
  This function sets size of the boxcollider
 */
/******************************************************************************/
void C_BoxCollider::Set_Size(float x, float y)
{
  m_size.x = x;
  m_size.y = y;
}

/******************************************************************************/
/*!
  This function sets the collision flag of the boxcollider
 */
/******************************************************************************/
void C_BoxCollider::Set_Flag(unsigned side)
{
  switch(side)
  {
  case(0):
    m_flag |= COLLISIONTOP;
    break;
  case(1):
    m_flag |= COLLISIONRIGHT;
    break;
  case(2):
    m_flag |= COLLISIONBOTTOM;
    break;
  case(3):
    m_flag |= COLLISIONLEFT;
    break;
  }
  if(m_flag & COLLISIONBOTTOM)
  {
    m_grounded = true;
  }
  else
  {
    m_grounded = false;
  }
}

/******************************************************************************/
/*!
  This function resets the collision flag of the boxcollider
 */
/******************************************************************************/
void C_BoxCollider::Reset_Flag()
{
  m_flag &= 0;
}

/******************************************************************************/
/*!
  This function sets the grounded boolean
 */
/******************************************************************************/
void C_BoxCollider::Set_Grounded(bool grounded)
{
  m_grounded = grounded;
}

/******************************************************************************/
/*!
  Sets the ghostest boolean on the boxcollider
 */
/******************************************************************************/
void C_BoxCollider::Set_Ghost(bool ghost)
{
  m_ghost = ghost;
}

/******************************************************************************/
/*!
  This function sets the active boolean on the boxcollider
 */
/******************************************************************************/
void C_BoxCollider::Set_Active(bool active)
{
  m_active = active;
}

/******************************************************************************/
/*!
  This function gets the maximum point
 */
/******************************************************************************/
math::Vec2 C_BoxCollider::Get_Max() const
{
  return m_max;
}

/******************************************************************************/
/*!
  This function gets the minimum point
 */
/******************************************************************************/
math::Vec2 C_BoxCollider::Get_Min() const
{
  return m_min;
}

/******************************************************************************/
/*!
  This function gets the size of the collider
 */
/******************************************************************************/
math::Vec2 C_BoxCollider::Get_Size() const
{
  return m_size;
}

/******************************************************************************/
/*!
  This function gets the collision flag
 */
/******************************************************************************/
char C_BoxCollider::Get_Flag() const
{
  return m_flag;
}

/******************************************************************************/
/*!
  This function gets grounded boolean
 */
/******************************************************************************/
bool C_BoxCollider::Get_Grounded() const
{
  return m_grounded;
}

/******************************************************************************/
/*!
  This function gets Active boolean
 */
/******************************************************************************/
bool C_BoxCollider::Is_Active() const
{
  return m_active;
}

/******************************************************************************/
/*!
  This function gets Ghost boolean
 */
/******************************************************************************/
bool C_BoxCollider::Get_Ghost() const
{
  return m_ghost;
}

/******************************************************************************/
/*!
  This function gets Offset of the collider
 */
/******************************************************************************/
math::Vec2 C_BoxCollider::Get_Offset() const
{
  return m_offset;
}

/******************************************************************************/
/*!
  This function returns a pointer to the object
 */
/******************************************************************************/
C_BoxCollider * C_BoxCollider::Actual()
{
  return const_cast<C_BoxCollider*>(this);
}

/******************************************************************************/
/*!
  This function creates a clone of this object
 */
/******************************************************************************/
C_BoxCollider * C_BoxCollider::Clone() const
{
  return new C_BoxCollider{ p_obj, m_min, m_max, m_size, m_offset, m_ghost };
}
}
