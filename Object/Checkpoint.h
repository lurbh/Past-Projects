/******************************************************************************/
/*!
\file_name        Checkpoint.h
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the declaration for the class C_Checkpoint

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "../Events/EventDispatcher.h"
#include "../Object/GameObject.h"
#include "../Defines/AllUtilities.h"
#include "../Types/Any.h"
#include "../Defines/CollisionMap.h"

namespace object
{
class C_GameObject;

/******************************************************************************/
/*!
  Class for Component for Checkpoint
*/
/******************************************************************************/
class C_Checkpoint : public C_Component
{
  math::Matrix3 *mp_player;
  bool m_possent = false;
  bool m_spawn = false;
  bool m_active;
public:
  C_Checkpoint(C_GameObject *p_obj, math::Matrix3 * = nullptr);
  void Connect();

  void Set_Player_Transform(math::Matrix3 *p_matrix);
  void Set_Active(bool active);
  bool Get_Active() const;

  virtual C_Checkpoint *Clone() const override;
  virtual void Update() override;
  virtual C_Checkpoint *Actual() override;
};
}