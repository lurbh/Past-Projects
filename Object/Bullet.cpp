/******************************************************************************/
/*!
\file_name        Bullet.cpp
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the implementation for the class C_Bullet

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "Bullet.h"

// FORWARD DECLARE ALL FUNCTIONS THAT ARE GOING TO BE ADDED

namespace
{
  static void OnCollisionStarted(events::C_CollisionEvent p_event);
}


namespace object
{

/******************************************************************************/
/*!
  The Non-Default constructor for C_Bullet
*/
/******************************************************************************/
C_Bullet::C_Bullet(C_GameObject *p_obj)
  : C_Component{ p_obj, BULLET }
{
}

/******************************************************************************/
/*!
  Function to Connect to events
*/
/******************************************************************************/
void C_Bullet::Connect()
{
  events::C_EventDispatcher::Connect(p_obj, OnCollisionStarted);
}

/******************************************************************************/
/*!
  Function to Clone C_Bullet
*/
/******************************************************************************/
C_Bullet *C_Bullet::Clone() const
{
  return new C_Bullet{ p_obj };
}

/******************************************************************************/
/*!
  Update Function for C_Bullet
*/
/******************************************************************************/
void C_Bullet::Update()
{
}

/******************************************************************************/
/*!
  Function to get C_Bullet
*/
/******************************************************************************/
C_Bullet *C_Bullet::Actual()
{
  return this;
}

/******************************************************************************/
/*!
  Function to reset bullet
*/
/******************************************************************************/
void C_Bullet::Reset()
{
  p_obj->Destroy();
  C_Transform * p_transfrom = static_cast<C_Transform *>
  (p_obj->Find_Component(TRANSFORM));
  float direction = p_transfrom->Get_Dir();
  p_transfrom->Rotate(-direction);
}

/******************************************************************************/
/*!
  Function to call when collision happen
*/
/******************************************************************************/
void C_Bullet::CollisionStarted(object::C_GameObject* p_otherobject)
{
  if(p_otherobject->Get_Trait() == T_ENEMY && p_obj->Get_Trait() == T_BULLET)
  {
    if(p_otherobject->Get_Name() == "Bloater" &&
      static_cast<object::C_AIBloater*>(p_otherobject->
      Find_Component(AIBLOATER))->GetState() == BOOM)
      return;
    Reset();
  }
}
}

namespace
{

/******************************************************************************/
/*!
  Function to call CollisionStarted
*/
/******************************************************************************/
void OnCollisionStarted(events::C_CollisionEvent p_event)
{
  (static_cast<object::C_Bullet*>(p_event.Object()->Find_Component(BULLET)))
  ->CollisionStarted(p_event.Other_Object());
}
}

