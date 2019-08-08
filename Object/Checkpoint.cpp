/******************************************************************************/
/*!
\file_name        Checkpoint.cpp
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the implementation for the class C_Checkpoint

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#include "Checkpoint.h"

namespace
{
  void OnLogicUpdate(object::C_GameObject* p_object);
}

namespace object
{

/******************************************************************************/
/*!
  The Non-Default constructor for C_Checkpoint
*/
/******************************************************************************/
C_Checkpoint::C_Checkpoint(C_GameObject *p_obj, math::Matrix3 *player)
  : C_Component{ p_obj, CUSTOM }, mp_player{player}
{
    
}

/******************************************************************************/
/*!
  Function to Connect to events
*/
/******************************************************************************/
void C_Checkpoint::Connect()
{
  events::C_EventDispatcher::Connect(p_obj, OnLogicUpdate);
}

/******************************************************************************/
/*!
  Update Function for C_Checkpoint
*/
/******************************************************************************/
void C_Checkpoint::Update()
{
  if (p_obj->Get_Active())
  {
    auto dist = mp_player->m_matrix[0][2] - static_cast<object::C_Transform*>
    (p_obj->Find_Component(TRANSFORM))->Get_Transform()->m_matrix[0][2];

    if(abs(dist) < TILESCALE * 2)
    {
      if(!m_possent)
      {
        m_active = true;
        events::C_EventDispatcher::DispatchEvent("Checkpointpos");
        m_possent = true;
      }
    }
  }
}

/******************************************************************************/
/*!
  Function to set player transformation
*/
/******************************************************************************/
void C_Checkpoint::Set_Player_Transform(math::Matrix3 * p_matrix)
{
  mp_player = p_matrix;
}

/******************************************************************************/
/*!
  Function to set active
*/
/******************************************************************************/
void C_Checkpoint::Set_Active(bool active)
{
  m_active = active;
}

/******************************************************************************/
/*!
  Function to get active
*/
/******************************************************************************/
bool C_Checkpoint::Get_Active() const
{
  return m_active;
}

/******************************************************************************/
/*!
  Function to Clone C_Checkpoint
*/
/******************************************************************************/
C_Checkpoint *C_Checkpoint::Clone() const
{
  return new C_Checkpoint{ p_obj , mp_player };
}

/******************************************************************************/
/*!
  Function to get C_Checkpoint
*/
/******************************************************************************/
C_Checkpoint *C_Checkpoint::Actual()
{
  return this;
}
}

namespace
{

/******************************************************************************/
/*!
  Function to call update
*/
/******************************************************************************/
void OnLogicUpdate(object::C_GameObject* p_object)
{
  (static_cast<object::C_Checkpoint*>(p_object->Find_Component(CUSTOM))
  ->Update());
}
}
