/******************************************************************************/
/*!
\file_name        AIBloater.h
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the declaration for the class C_AIBloater

All content © 2017 DigiPen (SINGAPORE) Corporation, all rights
reserved.
*/
/******************************************************************************/
#pragma once

#include "../Events/EventDispatcher.h"
#include "../Object/GameObject.h"
#include "../Defines/AllUtilities.h"
#include "../Types/Any.h"
#include "../Defines/AIState.h"
#include "../Defines/CollisionMap.h"
#include "../Object/ParticleSystem.h"
#include "../Object/Bullet.h"

namespace object
{
class C_GameObject;

/******************************************************************************/
/*!
  Class for AI Component for Bloater
*/
/******************************************************************************/
class C_AIBloater : public C_Component
{
  int n_health;
  AISTATE m_aistate;
  double m_time;
  double m_timemax;
  double m_boomtime;
  double m_hitanimation;
  double m_checktime;
  bool m_hit;
  bool m_shotgunhit;
  bool m_direction;
  bool m_charge;
  math::Vec2 m_chargepos;
  C_GameObject * m_player;
  COLLISIONMAP * m_map;
  int m_width;
    

  AISTATE CheckState(AISTATE m_state);
  bool CheckTile();
  void AddAcceleration(float f_speed);
    

public:
  C_GameObject *mp_smokesys;
  C_AIBloater(C_GameObject *p_obj, C_GameObject * p_player, 
    COLLISIONMAP * p_map, int width, AISTATE m_wander = STATIC, int n_hp = 5);

  inline void Set_Smoke_Sys(C_GameObject *p_smokesys) { mp_smokesys = p_smokesys;}
  void Death();
  void CollisionStarted(object::C_GameObject* p_otherobject);
  void Connect();
  virtual void SetMaxTime(float m_time);
  virtual void SetDirection(bool m_setdirection);
  virtual void SetState(AISTATE m_state);
  virtual void Set_Player(C_GameObject *p_player);
  C_GameObject * GetPlayer() const;
  AISTATE GetState() const;

  virtual C_AIBloater *Clone() const override;
  virtual void Update() override;
  virtual C_AIBloater *Actual() override;
  virtual void Reset();
    
};
}
