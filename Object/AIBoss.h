/******************************************************************************/
/*!
\file_name        AIBoss.h
\project_name     Double Tap
\primary_author   Low Jin Liang Aaron, aaron.low, 390001116
\brief
        This file contains the member function definitions of the AIBoss
    class
        
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

namespace object
{

/******************************************************************************/
/*!
  The AIBoss Class
 */
/******************************************************************************/
  class C_AIBoss final : public C_Component
  {
    // The Boss State enum
    enum BOSSSTATE
    {
      SPAWN = 0,
      THROW,
      ROAR,
      JUMP,
      DEATH
    };
    
    // The substate of the boss for the FSM
    enum SUBSTATE
    {
      ENTER,
      UPDATE,
      EXIT
    };
    
    // Member variables
    C_GameObject * m_player;
    SUBSTATE m_substate = ENTER;
    BOSSSTATE m_state;
    int LeapCount       = 0;
    int m_health;
    bool m_direction    = false;
    bool m_shotgunhit   = false;
    bool m_dead         = false;
  public:
    // The enum for the current sprite
    enum CURRENTSPRITE
    {
      IDLE = 0,
      ROARSPRITE,
      LEAPSPRITE,
      THROWSPRITE,
      DEATHSPRITE
    };
    CURRENTSPRITE m_sprite = IDLE;
    
    // Non default constructor
    C_AIBoss(C_GameObject *p_obj, C_GameObject * p_player, 
             BOSSSTATE spawn = SPAWN, int n_hp = BOSS_MAX_HEALTH);
    
    // Member functions
    virtual void      Update() override;
    virtual C_AIBoss* Actual() override;
    virtual C_AIBoss* Clone () const override;
    
    virtual void      Set_Player (C_GameObject *p_player);
    
    void PreLeapAnimation ();
    void PreThrowAnimation();
    void AS_DeathSequence ();
    void AS_SpawnSequence ();
    void Kill             ();
    void Gravity          ();
    void Leap             ();
    void JumpToPlatform   ();
    void Summon           ();
    void RedSprite        ();
    void Init             ();
    void Death            ();
    void ProjectileAttack ();
    void Connect          ();
    
    void CollisionStarted  (object::C_GameObject* p_otherobject);
  };
}