/******************************************************************************/
/*!
\file_name        AIComponent.h
\project_name     Double Tap
\primary_author   Lur Bing Huii, binghuii.lur, 390002616
\brief
This file contains the declaration for the class C_AI

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
#include "../Object/Bullet.h"

namespace object
{
class C_GameObject;

/******************************************************************************/
/*!
  Class for AI Component for zombies
*/
/******************************************************************************/
class C_AI : public C_Component
{
  int n_health;
  AISTATE m_aistate;
  double m_time;
  double m_timemax;
  double m_checktime;
  double m_hitanimation;
  double m_deathanimation;
  float m_chasevel;
  bool m_hit;
  bool m_direction; // true means facing left false means facing right
  bool m_alwaysstatic;
  bool m_shotgunhit;
  bool m_dead;
  C_GameObject * m_player;
  COLLISIONMAP * m_map;
  int m_width;
  AISTATE CheckState(AISTATE m_state);
  bool CheckTile();
  bool CheckTile2();
  void AddAcceleration(float f_speed);
    
public:
  C_AI(C_GameObject *p_obj, bool m_static, C_GameObject * p_player, 
    COLLISIONMAP * p_map, int width, float vel = 75.0f, 
    AISTATE m_wander = STATIC, int n_hp = 5);
  void CollisionStarted(object::C_GameObject* p_otherobject);
  void Connect();
  void SetMaxTime(float m_time);
  void SetDirection(bool m_setdirection);
  void SetState(AISTATE m_state);
  void Set_Player(C_GameObject *p_player);
  void Enrage();
  C_GameObject * GetPlayer() const;
  void Death();

  virtual C_AI *Clone() const override;
  virtual void Update() override;
  virtual C_AI *Actual() override;
  virtual void Reset();
    
};
}
