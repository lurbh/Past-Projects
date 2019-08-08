/******************************************************************************/
/*!
\file_name        AIBossStealth.h
\project_name     Double Tap
\primary_author   Low Jin Liang Aaron, aaron.low, 390001116
\brief
        This file contains the definition of the AIBossStealth class
        
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

#ifndef BOSS_ITERATIONS
#define BOSS_ITERATIONS
#define NUM_ITERATIONS_FLICKER 5
#define NUM_ITERATIONS_POUND 2
#define NUM_ITERATIONS_FALL 5
#endif

namespace object
{

/******************************************************************************/
/*!
  The AIBossStealth class definition
 */
/******************************************************************************/
  class C_AIBossStealth final : public C_Component
  {
    // The enum of the state of the boss
    enum BOSSSTATE
    {
      SPAWN = 0,
      FLICKER,
      POUND,
      FALL,
      DEATH
    };
    
    // The enum for the Substate of the boss for the FSM
    enum SUBSTATE
    {
      ENTER,
      UPDATE,
      EXIT
    };
    
    math::Matrix3 *m_player_transform;
    int m_health;
    BOSSSTATE m_state;
    SUBSTATE m_substate = ENTER;
    bool m_directionX   = false;
    bool m_directionY   = false;
    bool m_shotgunhit   = false;
    bool m_dead         = false;

  public:
    
    // The current sprite enum
    enum CURRENTSPRITE
    {
      IDLESPRITE = 0,
      FLICKERFADESPRITE,
      FLICKERATTACKSPRITE,
      POUNDSPRITE,
      FALLSPRITE,
      DEATHSPRITE
    };
    
    // The current sprite that the boss is in
    CURRENTSPRITE m_sprite = IDLESPRITE;

    // The constructor of an AIBossStealth object
    C_AIBossStealth(C_GameObject *p_obj, math::Matrix3 *player_transform,
                    BOSSSTATE spawn = SPAWN, int n_hp = BOSS_MAX_HEALTH);
                    
    
    // Member functions
    void Connect                ();
    void Update                 ();
    void RedSprite              ();
    void Init                   ();
    void Death                  ();
    void Kill                   ();
    void AS_SpawnAnimation      ();
    void AS_StateEnterAnimation ();
    void AS_FlickerState        ();
    void AS_PoundState          ();
    void AS_FallState           ();
    void Set_Player_Transform   (math::Matrix3 *p_transform);
    void CollisionStarted       (object::C_GameObject* p_otherobject);
    
    virtual C_AIBossStealth *Actual() override;
    virtual C_AIBossStealth *Clone () const override;

  };

}