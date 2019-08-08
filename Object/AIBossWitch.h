/******************************************************************************/
/*!
\file_name        AIBossWitch.h
\project_name     Double Tap
\primary_author   Low Jin Liang Aaron, aaron.low, 390001116
\brief
        This file contains the definition of the AIBossWitch class
        
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
#include "../Defines/AllActions.h"
#include "../Utilities/CameraEvents.h"

#ifndef BOSS_ITERATIONS_WITCH
#define BOSS_ITERATIONS_WITCH
#define BOSS_FIRST_HP 100
#define BOSS_SECOND_HP 200
#endif

namespace object
{
/******************************************************************************/
/*!
  The AIBossWitch class definition
 */
/******************************************************************************/
class C_AIBossWitch final : public C_Component
{
  // The phase of the boss
  enum BOSSINSTANCE
  {
    FIRST,
    SECOND
  };
  
  // The state of the boss
  enum BOSSSTATE
  {
    SPAWN = 0,
    DEFEND,
    ATTACK,
    FLEE,
    DEATH
  };
  
  // The substate of the boss for the FSM
  enum SUBSTATE
  {
    ENTER,
    UPDATE,
    EXIT
  };
  
  math::Matrix3 *m_player_transform;
  double updatetime       = 0.0;
  int m_health            = BOSS_FIRST_HP;
  BOSSINSTANCE m_instance = FIRST;
  BOSSSTATE m_state       = SPAWN;
  SUBSTATE m_substate     = ENTER;
  bool m_directionX       = false;
  bool m_directionY       = false;
  bool m_dead             = false;

public:
  // Non default constructor of the AIBossWitch object
  C_AIBossWitch(C_GameObject *p_obj, math::Matrix3 *player_transform);
  
  // Member functions
  void Kill                       ();
  void InitPhase2                 ();
  void RedSprite                  ();
  void Connect                    ();
  void Update                     ();
  void Restart                    ();
  void AS_Attack                  ();
  void AS_PlayFirstSpawnAnimation ();
  void AS_MovementSequence        ();
  void AS_FloatMovementSequence   ();
  void AS_FirstDeath              ();
  void AS_SecondDeath             ();
  void AS_PlaySecondSpawnAnimation();
  void AS_Attack2                 ();
  void AS_MovementSequence2       ();
  void CollisionStarted           (object::C_GameObject * p_obj);
  void Set_Player_Transform       (math::Matrix3 *p_transform);
  
  virtual C_AIBossWitch *Actual () override;
  virtual C_AIBossWitch *Clone  () const override;

};
}