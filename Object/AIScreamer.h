/******************************************************************************/
/*!
\file_name        AIScreamer.h
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the declaration for the class C_AIScreamer

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
class C_AIScreamer : public C_Component
{
  int n_health;
  AISTATE m_aistate;
  double m_time;
  double m_timemax;
  double m_screamtime;
  double m_deathanimation;
  double m_hitanimation;
  double m_checktime;
  bool m_hit;
  bool m_shotgunhit;
  bool m_direction;
  bool m_alwaysstatic;
  bool m_scream;
  bool m_dead;
  C_GameObject * m_player;
  COLLISIONMAP * m_map;
  int m_width;
  AISTATE CheckState(AISTATE m_state);
  bool CheckTile();
  void AddAcceleration(float f_speed);
  C_Transform *mp_transform;
public:
  C_GameObject *mp_spitsys;

  C_AIScreamer(C_GameObject *p_obj, C_GameObject * p_player, 
  COLLISIONMAP * p_map, int width, AISTATE m_wander = STATIC, int n_hp = 5);
  void CollisionStarted(object::C_GameObject* p_otherobject);
  void Connect();
  void SetMaxTime(float m_time);
  void SetDirection(bool m_setdirection);
  void SetState(AISTATE m_state);
  void Set_Player(C_GameObject *p_player);
  void ScreamStop();
  void Death();
  inline void Set_Spit_Sys(C_GameObject *p_spitsys) 
  { mp_spitsys = p_spitsys; }

  C_GameObject * GetPlayer() const;
  AISTATE GetState() const;

  virtual C_AIScreamer *Clone() const override;
  virtual void Update() override;
  virtual C_AIScreamer *Actual() override;
  virtual void Reset();
    
};
}
