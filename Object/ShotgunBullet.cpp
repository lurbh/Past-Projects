/******************************************************************************/
/*!
\file_name        ShotgunBullet.cpp
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the implementation for the class C_ShotgunBullet

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "ShotgunBullet.h"

namespace
{
  void OnLogicUpdate(object::C_GameObject *p_bullet);
}
namespace object
{

/******************************************************************************/
/*!
  The Non-Default constructor for C_ShotgunBullet
*/
/******************************************************************************/
C_ShotgunBullet::C_ShotgunBullet(C_GameObject * p_obj)
  :C_Bullet{p_obj}
{
}

/******************************************************************************/
/*!
  Function to Connect to events
*/
/******************************************************************************/
void C_ShotgunBullet::Connect()
{
  events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);
}

/******************************************************************************/
/*!
  Function to Clone C_ShotgunBullet
*/
/******************************************************************************/
C_ShotgunBullet * object::C_ShotgunBullet::Clone() const
{
  return new C_ShotgunBullet{p_obj};
}

/******************************************************************************/
/*!
  Update Function for C_ShotgunBullet
*/
/******************************************************************************/
void C_ShotgunBullet::Update()
{  
  if(p_obj->Get_Active())
  {
    m_bullettime += utilities::C_Timer::Get_dt();
    if(m_bullettime > m_bulletmaxtime)
    {
      Reset();
    }
  }
}

/******************************************************************************/
/*!
  Function to reset bullet
*/
/******************************************************************************/
void C_ShotgunBullet::Reset()
{
  p_obj->Destroy();
  C_Transform * p_transfrom = static_cast<C_Transform *>
  (p_obj->Find_Component(TRANSFORM));
  float direction = p_transfrom->Get_Dir();
  p_transfrom->Rotate(-direction);
  m_bullettime = 0;
}

/******************************************************************************/
/*!
  Function to get C_ShotgunBullet
*/
/******************************************************************************/
C_ShotgunBullet * C_ShotgunBullet::Actual()
{
  return this;
}

}

namespace
{

/******************************************************************************/
/*!
  Function to call Update
*/
/******************************************************************************/
void OnLogicUpdate(object::C_GameObject *p_bullet)
{
  static_cast<object::C_ShotgunBullet*>(p_bullet->Find_Component(BULLET))
  ->Update();
}

}
